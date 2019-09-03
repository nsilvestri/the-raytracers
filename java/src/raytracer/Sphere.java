package raytracer;

public class Sphere extends Surface {

	private Vec3 origin;
	private double radius;
	
	public Sphere(Vec3 origin, double radius) {
		this.origin = origin;
		this.radius = radius;
	}
	
	public Vec3 getOrigin() {
		return origin;
	}

	public void setOrigin(Vec3 origin) {
		this.origin = origin;
	}

	public double getRadius() {
		return radius;
	}

	public void setRadius(double radius) {
		this.radius = radius;
	}
}
