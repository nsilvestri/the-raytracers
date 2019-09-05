package raytracer;

public abstract class Surface {
	public abstract HitRecord intersect(Ray3 r);
}
