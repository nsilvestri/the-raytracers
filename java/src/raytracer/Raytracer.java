package raytracer;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Raytracer {

	public static void main(String[] args) {
		
		// seed random number generator
		Random random = new Random();
		
	    // set image properties
	    int imageWidth = 200;
	    int imageHeight = 100;
	    int numSamples = 10;
	    
	    System.out.printf("P3\n%d %d\n255\n", imageWidth, imageHeight);
	    
	    Vec3 lowerLeftCorner = new Vec3(-2, -1, -1);
	    Vec3 horizontal = new Vec3(4, 0, 0);
	    Vec3 vertical = new Vec3(2, 0, 0);
	    Vec3 origin = new Vec3(0, 0, 0);
	    
	    List<Surface> surfaces = new ArrayList<Surface>();
	    surfaces.add(new Sphere(new Vec3(0, 0, -1), 0.5));
	    surfaces.add(new Sphere(new Vec3(0, -100.5, -1), 100));
	    
	    // iterate over each pixel, from top to bottom (because of PPM pixel order)
	    for (int j = imageHeight - 1; j >= 0; j--) {
	    	for (int i = 0; i < imageWidth; i++) {
	    		Vec3 pixelColor = new Vec3(0, 0, 0);
	    		for (int s = 0; s < numSamples; s++) {
	    			double u = ((double) i / imageWidth) + (random.nextDouble() / imageWidth);
	    			double v = ((double) i / imageHeight) + (random.nextDouble() / imageHeight);
	    			
	    			Vec3 horizontalOffset = Vec3.scale(horizontal, u);
	    			Vec3 verticalOffset = Vec3.scale(vertical, v);
	    			
	    			Vec3 totalOffset = Vec3.add(horizontalOffset, verticalOffset);
	    			Vec3 direction = Vec3.add(lowerLeftCorner, totalOffset);
	    			
	    			
	    		}
	    	}
	    }
    }
}
