package raytracer;

public class Metal extends Material {
	
	public Metal(double albedo) {
		super(albedo, new Vec3(1, 1, 1));
		this.albedo = albedo;
	}
	
	@Override
	public Ray3 scatter(Ray3 r, Vec3 pointOfIntersection, Vec3 normal) {
		Vec3 reflected = Vec3.reflect(Vec3.normalize(r.getDirection()), normal);
		return new Ray3(pointOfIntersection, reflected);
	}
	
}
