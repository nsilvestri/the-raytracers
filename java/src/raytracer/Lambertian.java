package raytracer;

public class Lambertian extends Material {

    public Lambertian(double albedo, Vec3 color) {
        super(albedo, color);
    }

    @Override
    public Ray3 scatter(Ray3 r, Vec3 pointOfIntersection, Vec3 normal) {
        // bounce towards a random point in the unit sphere tangent to the hit point
        Vec3 bounceNoise = Vec3.randomInUnitSphere();

        // the direction of this bounce is the normal plus the randomness (noise)
        Vec3 bounceDirection = Vec3.add(normal, bounceNoise);

        // the next spot we aim for (target) is the p_o_i modified by our bounce
        // direction
        Vec3 target = Vec3.add(pointOfIntersection, bounceDirection);

        // the direction of the new ray is the target position - p_o_i
        Vec3 newRayDirection = Vec3.sub(target, pointOfIntersection);
        
        return new Ray3(pointOfIntersection, newRayDirection);
    }
}
