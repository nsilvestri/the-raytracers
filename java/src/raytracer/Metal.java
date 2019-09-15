package raytracer;

public class Metal extends Material {
	
	private double roughness;
	
	public Metal(double albedo, Vec3 color, double roughness) {
		super(albedo, color);
		this.roughness = roughness;
	}
	
	@Override
	public Ray3 scatter(Ray3 r, Vec3 pointOfIntersection, Vec3 normal) {
		Vec3 reflected = Vec3.reflect(Vec3.normalize(r.getDirection()), normal);
		Vec3 roughnessBounce = Vec3.scale(Vec3.randomInUnitSphere(), roughness);
		return new Ray3(pointOfIntersection, Vec3.add(reflected, roughnessBounce));
	}
	
}
