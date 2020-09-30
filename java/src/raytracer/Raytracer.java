package raytracer;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.stream.Stream;

public class Raytracer {

    private int imageWidth;
    private int imageHeight;
    private int numSamples;

    private Scene scene;

    public Raytracer(String inputFile) {
        Camera camera = new Camera(); // camera defaults will probably be overwritten
        Map<String, Material> materials = new HashMap<String, Material>();
        List<Surface> surfaces = new ArrayList<Surface>();
        try (Stream<String> stream = Files.lines(Paths.get(inputFile))) {
            stream.forEach(line -> {
                String[] lineParts = line.split(" ");
                switch(lineParts[0].trim()) {
                    case "":
                    case "#":
                        // comment line; skip
                        break;
                    case "i": {
                        imageWidth = Integer.parseInt(lineParts[1]);
                        imageHeight = Integer.parseInt(lineParts[2]);
                        break;
                    }
                    case "s": {
                        numSamples = Integer.parseInt(lineParts[1]);
                        break;
                    }
                    case "e": {
                        double x = Double.parseDouble(lineParts[1]);
                        double y = Double.parseDouble(lineParts[2]);
                        double z = Double.parseDouble(lineParts[3]);
                        Vec3 position = new Vec3(x, y, z);
                        camera.setPosition(position);
                        break;
                    }
                    case "l": {
                        double x1 = Double.parseDouble(lineParts[1]);
                        double y1 = Double.parseDouble(lineParts[2]);
                        double z1 = Double.parseDouble(lineParts[3]);
                        double x2 = Double.parseDouble(lineParts[4]);
                        double y2 = Double.parseDouble(lineParts[5]);
                        double z2 = Double.parseDouble(lineParts[6]);
                        double x3 = Double.parseDouble(lineParts[7]);
                        double y3 = Double.parseDouble(lineParts[8]);
                        double z3 = Double.parseDouble(lineParts[9]);
                        Vec3 lowerLeftCorner = new Vec3(x1, y1, z1);
                        Vec3 horizontal = new Vec3(x2, y2, z2);
                        Vec3 vertical = new Vec3(x3, y3, z3);
                        camera.setLowerLeftCorner(lowerLeftCorner);
                        camera.setHorizontal(horizontal);
                        camera.setVertical(vertical);
                        break;
                    }
                    case "M": {
                        String materialName = lineParts[1];
                        double albedo = Double.parseDouble(lineParts[2]);
                        double r = Double.parseDouble(lineParts[3]);
                        double g = Double.parseDouble(lineParts[4]);
                        double b = Double.parseDouble(lineParts[5]);
                        Material newMaterial;
                        if (lineParts.length == 7) {
                            double roughness = Double.parseDouble(lineParts[6]);
                            newMaterial = new Metal(materialName, albedo, new Vec3(r, g, b), roughness);
                        } else {
                            newMaterial = new Lambertian(materialName, albedo, new Vec3(r, g, b));
                        }
                        materials.put(materialName, newMaterial);
                        break;
                    }
                    case "S": {
                        double x = Double.parseDouble(lineParts[1]);
                        double y = Double.parseDouble(lineParts[2]);
                        double z = Double.parseDouble(lineParts[3]);
                        double radius = Double.parseDouble(lineParts[4]);
                        String material = lineParts[5];
                        Sphere newSphere = new Sphere(new Vec3(x, y, z), radius, materials.get(material));
                        surfaces.add(newSphere);
                        break;
                    }
                    default:
                        System.err.println("Unrecognized line operation in " + inputFile + ": " + lineParts[0]);
                        break;

                }
            });
        } catch (IOException ioe) {
            System.err.println("Unable to read file " + inputFile);
            System.exit(1);
        }

        scene = new Scene(camera, surfaces);
    }

    public void execute() {
        
        // Set up output file
        FileOutputStream out = null;
        try {
            out = new FileOutputStream("image.ppm");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.exit(1);
        }
        
        try {
            out.write(("P3\n" + imageWidth + " " + imageHeight + "\n255\n").getBytes());
        } catch (IOException e1) {
            e1.printStackTrace();
            System.exit(1);
        }
        
        // seed random number generator
        Random random = new Random();

        long start = System.nanoTime();
        
        // iterate over each pixel, from top to bottom (because of PPM pixel order)
        for (int j = imageHeight - 1; j >= 0; j--) {
            for (int i = 0; i < imageWidth; i++) {
                Vec3 pixelColor = new Vec3(0, 0, 0);
                for (int s = 0; s < numSamples; s++) {
                    double u = ((double) i / imageWidth) + (random.nextDouble() / imageWidth);
                    double v = ((double) j / imageHeight) + (random.nextDouble() / imageHeight);
                    
                    Vec3 horizontalOffset = Vec3.scale(scene.getCamera().getHorizontal(), u);
                    Vec3 verticalOffset = Vec3.scale(scene.getCamera().getVertical(), v);
                    
                    Vec3 totalOffset = Vec3.add(horizontalOffset, verticalOffset);
                    Vec3 direction = Vec3.add(scene.getCamera().getLowerLeftCorner(), totalOffset);
                    
                    Ray3 r = new Ray3(scene.getCamera().getPosition(), direction);
                    
                    Vec3 colorSample = scene.color(r);
                    
                    // gamma correct sample
                    colorSample = Vec3.gammaCorrect(colorSample, 0.5);
                    pixelColor = Vec3.add(pixelColor, colorSample);
                }
                
                // pixel_color contains the total of all samples; get the average of each sample
                pixelColor = Vec3.scale(pixelColor, 1.0 / numSamples);
                
                // write pixel color to file
                int r = (int) (pixelColor.getX() * 255);
                int g = (int) (pixelColor.getY() * 255);
                int b = (int) (pixelColor.getZ() * 255);
                
                String line = r + " " + g + " " + b + '\n';
                try {
                    out.write(line.getBytes());
                } catch (IOException e) {
                    e.printStackTrace();
                    System.exit(1);
                }
            }
        }
        
        long stop = System.nanoTime();
        double timeElapsedSeconds = (stop - start) / 1000000000.0;
        
        System.out.println("Total time: " + timeElapsedSeconds + " seconds");
        System.out.println("Samples/sec: " + (imageWidth * imageHeight * numSamples) / timeElapsedSeconds + " samples/sec");
        
        try {
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Raytracer raytracer = new Raytracer(args[0]);
        raytracer.execute();
    }
}
