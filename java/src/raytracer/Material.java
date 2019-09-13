package raytracer;

import java.util.Random;

public class Material {
	private Vec3 color;
	private double albedo;

	public Material(Vec3 color, double albedo) {
		this.color = color;
		this.albedo = albedo;
	}

	public Ray3 scatter(Ray3 r) {
		return r;
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
	public boolean shouldReflect() {
		Random random = new Random();
		return random.nextDouble() <= albedo;
	}

	public Vec3 getColor() {
		return color;
	}

	public void setColor(Vec3 color) {
		this.color = color;
	}

	public double getAlbedo() {
		return albedo;
	}

	public void setAlbedo(double albedo) {
		this.albedo = albedo;
	}
}
