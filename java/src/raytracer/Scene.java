package raytracer;

import java.util.List;

public class Scene {

	private List<Surface> surfaces;

	public Scene(List<Surface> surfaces) {
		this.surfaces = surfaces;
	}

	/**
	 * Return the color that should be returned given a Ray3 interacting with this
	 * Scene. This function implements full recursive bouncing, taking materials
	 * into account.
	 * 
	 * @param r the Ray3 to generate a color from
	 * @return a Vec3 whose components represent the color generated from a Ray3
	 *         interacting with this Scene.
	 */
	public Vec3 color(Ray3 r) {
		/* Find the nearest surface which r intersects */
		HitRecord nearestHitRecord = intersectNearestSurface(r);

		/* BASE CASE: no intersection; return sky color by default */
		if (!nearestHitRecord.didIntersect()) {
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

		// point of intersection is where r intersected the surface in xyz space
		Vec3 pointOfIntersection = r.pointAtParameter(nearestHitRecord.getT());

		// bounce towards a random point in the unit sphere tangent to the hit point
		Vec3 bounceNoise = Vec3.randomInUnitSphere();

		// the direction of this bounce is the normal plus the randomness (noise)
		Vec3 bounceDirection = Vec3.add(nearestHitRecord.getNormal(), bounceNoise);

		// the next spot we aim for (target) is the p_o_i modified by our bounce
		// direction
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

	/**
	 * Return the color red if the given Ray3 intersects with a Surface, and a blue
	 * vector otherwise.
	 * 
	 * Useful for checking if intersections are being calculated correctly. There is
	 * no recursive bouncing with this function.
	 * 
	 * @param r the Ray3 to generate a color from
	 * @return a Vec3 color with full red on intersection with a surface, and blue
	 *         otherwise.
	 */
	public Vec3 colorFlat(Ray3 r) {
		/* Find the nearest surface which r intersects */
		HitRecord nearestHitRecord = intersectNearestSurface(r);

		/* BASE CASE: no intersection; return sky color by default */
		if (!nearestHitRecord.didIntersect()) {
			return new Vec3(0, 0, 1);
		}

		return new Vec3(1, 0, 0);
	}

	/**
	 * Find the nearest Surface in this Scene that would be hit.
	 * 
	 * @param r the Ray3 to check intersection
	 * @return a HitRecord with data filled with the appropriate information
	 */
	public HitRecord intersectNearestSurface(Ray3 r) {
		// default is a hitRecord with no intersection and +inifinity T
		HitRecord nearestHitRecord = new HitRecord();

		for (int i = 0; i < surfaces.size(); i++) {
			HitRecord hitRecord = surfaces.get(i).intersect(r);

			// no intersect? skip
			if (!hitRecord.didIntersect()) {
				continue;
			}

			// T must be positive (in front of the camera), and closer than the current
			// nearest
			if (hitRecord.getT() > 0 && hitRecord.getT() < nearestHitRecord.getT()) {
				nearestHitRecord = hitRecord;
			}
		}

		return nearestHitRecord;
	}
}
