package raytracer;

public class HitRecord {
	private Surface surface;
	private boolean intersected;
	private double t;
	private Vec3 normal;
	
	public HitRecord(Surface surface, boolean intersected, double t, Vec3 normal) {
		this.intersected = intersected;
		this.t = t;
		this.normal = normal;
	}
	
	public Surface getSurface() {
		return surface;
	}
	
	public void setSurface(Surface surface) {
		this.surface = surface;
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
