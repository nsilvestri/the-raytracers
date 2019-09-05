package raytracer;

import java.util.List;

public class Scene {

	private List<Surface> surfaces;
	
	public Scene(List<Surface> surfaces) {
		this.surfaces = surfaces;
	}
	
	public Vec3 color(Ray3 r) {
		/* Find the nearest surface which r intersects */
		Surface nearest = null;
		double nearestT = Double.POSITIVE_INFINITY;
		
		for (int i = 0; i < surfaces.size(); i++) {
			HitRecord hitRecord = surfaces.get(i).intersect(r);
			
			// a miss is -INFINITY, and all t < 0 are behind us. Skip em
	        if (hitRecord.getT() < nearestT && hitRecord.getT() > 0) {
	            nearestT = hitRecord.getT();
	            nearest = surfaces.get(i);
	        }
		}
		
		/* BASE CASE: no intersection; return sky color by default */

	    if (nearestT == Double.POSITIVE_INFINITY) {
	        // normalize direction of ray so all values of y will be consistent
	        Vec3 unitDirection = Vec3.normalize(r.getDirection());

	        // proportion of sky color mixture based on y component (up-ness)
	        double t = 0.5 * (unitDirection.getY() + 1.0);

	        // base color of sky
	        Vec3 baseSkyColor = new Vec3(0.5, 0.7, 1.0);
	        baseSkyColor = Vec3.scale(baseSkyColor, t);

	        // what color the sky fades into, going down
	        Vec3 skyColorGradient = new Vec3(1, 1, 1);
	        skyColorGradient = Vec3.scale(skyColorGradient, 1.0 - t);

	        // add base_sky_color and sky_color_gradient
	        Vec3 skyColor = Vec3.add(baseSkyColor, skyColorGradient);

	        return skyColor;
	    }
	    
	    /* nearest now contains the nearest surface; calculate the color */

	    HitRecord hitRecord = nearest.intersect(r);

	    // point of intersection is where r intersected the surface in xyz space
	    Vec3 pointOfIntersection = r.pointAtParameter(hitRecord.getT());

	    // bounce towards a random point in the unit sphere tangent to the hit point
	    Vec3 bounceNoise = Vec3.randomInUnitSphere();

	    // the direction of this bounce is the normal plus the randomness (noise)
	    Vec3 bounceDirection = Vec3.add(hitRecord.getNormal(), bounceNoise);

	    // the next spot we aim for (target) is the p_o_i modified by our bounce direction
	    Vec3 target = Vec3.add(pointOfIntersection, bounceDirection);

	    // the direction of the new ray is the target position - p_o_i
	    Vec3 newRayDirection = Vec3.sub(target, pointOfIntersection);

	    // create the new ray cenetered on our p_o_i pointing in our new direction
	    Ray3 newRay = new Ray3(pointOfIntersection, newRayDirection);

	    // recursive bouncing color
	    Vec3 newRayColor = color(newRay);
	    
	    // surfaces are 50% reflective
	    return Vec3.scale(newRayColor, 0.5);
	}
	
}
