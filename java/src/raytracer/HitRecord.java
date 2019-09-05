package raytracer;

public class HitRecord {
	private boolean intersected;
	private double t;
	private Vec3 normal;
	
	public HitRecord(boolean intersected, double t, Vec3 normal) {
		this.intersected = intersected;
		this.t = t;
		this.normal = normal;
	}

	public boolean didIntersect() {
		return intersected;
	}

	public void setIntersected(boolean hit) {
		this.intersected = hit;
	}

	public double getT() {
		return t;
	}

	public void setT(double t) {
		this.t = t;
	}

	public Vec3 getNormal() {
		return normal;
	}

	public void setNormal(Vec3 normal) {
		this.normal = normal;
	}
}
