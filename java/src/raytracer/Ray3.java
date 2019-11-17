package raytracer;

public class Ray3 {
    Vec3 origin;
    Vec3 direction;
    
    public Ray3(Vec3 origin, Vec3 direction) {
        this.origin = origin;
        this.direction = direction;
    }
    
    /**
     * Calculate a point along r such that the point is the end of the vector
     * originating from r->origin pointing towards r->direction and scaled by t. * 
     * @param r ray3* the ray to use for origin and direction.
     * @param t float the scalar for the ray
     * 
     * @return vec3* a vec3* representing some point along r, specified by t.
     */
    public Vec3 pointAtParameter(double t) {
        Vec3 scaledDirection = Vec3.scale(direction, t);
        return Vec3.add(origin, scaledDirection);
    }

    public Vec3 getOrigin() {
        return origin;
    }

    public void setOrigin(Vec3 origin) {
        this.origin = origin;
    }

    public Vec3 getDirection() {
        return direction;
    }

    public void setDirection(Vec3 direction) {
        this.direction = direction;
    }
}
