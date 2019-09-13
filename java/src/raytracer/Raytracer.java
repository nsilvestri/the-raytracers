package raytracer;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Raytracer {

	public static void main(String[] args) {
		
	    // set image properties
	    int imageWidth = 200;
	    int imageHeight = 100;
	    int numSamples = 10;
	    
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
	    
		// set up image dimensions in scene
	    Vec3 lowerLeftCorner = new Vec3(-2, -1, -1);
	    Vec3 horizontal = new Vec3(4, 0, 0);
	    Vec3 vertical = new Vec3(0, 2, 0);
	    Vec3 origin = new Vec3(0, 0, 0);
	    
	    List<Surface> surfaces = new ArrayList<Surface>();
	    surfaces.add(new Sphere(new Vec3(0, 0, -1), 0.5));
	    surfaces.add(new Sphere(new Vec3(0, -100.5, -1), 100));
	    
	    Scene scene = new Scene(surfaces);
	    
	    long start = System.nanoTime();
	    
	    // iterate over each pixel, from top to bottom (because of PPM pixel order)
	    for (int j = imageHeight - 1; j >= 0; j--) {
	    	for (int i = 0; i < imageWidth; i++) {
	    		Vec3 pixelColor = new Vec3(0, 0, 0);
	    		for (int s = 0; s < numSamples; s++) {
	    			double u = ((double) i / imageWidth) + (random.nextDouble() / imageWidth);
	    			double v = ((double) j / imageHeight) + (random.nextDouble() / imageHeight);
	    			
	    			Vec3 horizontalOffset = Vec3.scale(horizontal, u);
	    			Vec3 verticalOffset = Vec3.scale(vertical, v);
	    			
	    			Vec3 totalOffset = Vec3.add(horizontalOffset, verticalOffset);
	    			Vec3 direction = Vec3.add(lowerLeftCorner, totalOffset);
	    			
	    			Ray3 r = new Ray3(origin, direction);
	    			
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
					// TODO Auto-generated catch block
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
}
