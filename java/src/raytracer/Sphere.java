package raytracer;

/**
 * Sphere is an implicit surface representing a perfect 3D sphere. It has a
 * position, radius, and Material associated with it.
 * 
 * @author nick
 *
 */
public class Sphere extends Surface {

    private Vec3 origin;
    private double radius;

    /**
     * Creates a new Sphere with the given parameters.
     * 
     * @param origin   the position of the sphere in XYZ space.
     * @param radius   the radius of the sphere.
     * @param material the material of the sphere.
     */
    public Sphere(Vec3 origin, double radius, Material material) {
        super(material);
        this.origin = origin;

        checkRadius(radius);
        this.radius = radius;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public HitRecord intersect(Ray3 r) {
        Vec3 oc = Vec3.sub(r.getOrigin(), this.origin);
        /* a, b, c are A, B, C of quadratic equation */
        // a = (dir . dir)
        double a = Vec3.dot(r.getDirection(), r.getDirection());
        // b = (dir . (eye - sphere_origin))
        double b = 2 * Vec3.dot(oc, r.getDirection());
        // c = (ray_pos - sphere_center) . (ray_pos - sphere_center) - R^2
        double c = Vec3.dot(oc, oc) - Math.pow(this.radius, 2);
        // discr = B^2-4AC
        double discriminant = (b * b) - (4 * a * c);

        /* filling hit_record */

        HitRecord hitRecord = null;
        if (discriminant < 0) {
            // no intersection
            hitRecord = new HitRecord(this, false, Double.NEGATIVE_INFINITY, null);
        } else {
            // there are two roots; we need the closer (smaller) one
            double tMinus = (-b - Math.sqrt(discriminant)) / (2.0 * a);
            double tPlus = (-b + Math.sqrt(discriminant)) / (2.0 * a);
            double t = Math.min(tPlus, tMinus);

            // point_of_intersection is self-explanatory
            Vec3 point_of_intersection = r.pointAtParameter(t);
            // normal_direction is the vec3 from sphere center to p_o_i
            Vec3 normal_direction = Vec3.sub(point_of_intersection, origin);
            // normalize the normal because why not? Might not be totally necessary
            Vec3 normal = Vec3.normalize(normal_direction);

            hitRecord = new HitRecord(this, true, t, normal);
        }
        return hitRecord;
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

    /**
     * Set the radius to the given value. If the radius is negative, an
     * IllegalArgumentException will be thrown.
     * 
     * @param radius the new radius for this Sphere.
     * @see Sphere#checkRadius(double)
     */
    public void setRadius(double radius) {
        checkRadius(radius);
        this.radius = radius;
    }

    /**
     * Internal validation method for checking that the radius is 0 or greater. If
     * the given radius is negative, this will throw an IllegalArgumentException.
     * 
     * @param radius the radius to be checked
     * @throws IllegalArgumentException
     */
    private static void checkRadius(double radius) {
        if (radius < 0) {
            throw new IllegalArgumentException("Radius must be positive");
        }
    }
}
