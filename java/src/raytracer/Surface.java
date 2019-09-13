package raytracer;

public abstract class Surface {
	protected Material material;
	
	public Surface(Material material) {
		this.material = material;
	}
	public abstract HitRecord intersect(Ray3 r);
	
	public Material getMaterial() {
		return material;
	}
}
