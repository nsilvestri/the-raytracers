package raytracer;

import java.util.Random;

public abstract class Material {
	protected double albedo;
	protected Vec3 color;
	
	public Material(double albedo, Vec3 color) {
		this.albedo = albedo;
		this.color = color;
	}
	
	public abstract Ray3 scatter(Ray3 r, Vec3 pointOfIntersection, Vec3 normal);
	
	public double getAlbedo() {
		return albedo;
	}
	
	public Vec3 getColor() {
		return color;
	}

	/**
	 * Returns <code>true</code> with a probability of albedo.
	 * 
	 * If albedo is 1 (aka, perfectly reflective), this will return
	 * <code>true</code> 100% of the time. If albedo is 0.3, this will return
	 * <code>true</code> 30% of the time.
	 * 
	 * @return <code>true</code> 100*albedo percent of the time, and false
	 *         otherwise.
	 */
	public boolean shouldScatter() {
		Random random = new Random();
		return random.nextDouble() <= albedo;
	}
}
