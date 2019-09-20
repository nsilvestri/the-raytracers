package raytracer;

public abstract class Surface {

	protected Material material;

	public Surface(Material material) {
		this.material = material;
	}

	/**
	 * Checks whether a given Ray3 will intersect this Surface, and populates a
	 * HitRecord with the appropriate values.
	 * 
	 * @param r the Ray3 to check for intersection with this Surface.
	 * @return A HitRecord with values populated for the intersection. If there is
	 *         no intersection, HitRecord.didIntersect() will return false.
	 */
	public abstract HitRecord intersect(Ray3 r);

	/**
	 * Returns the material associated with this Surface.
	 * @return the material associated with this Surface.
	 */
	public Material getMaterial() {
		return material;
	}
}
