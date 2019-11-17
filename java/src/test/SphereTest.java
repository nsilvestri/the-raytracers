package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

import raytracer.HitRecord;
import raytracer.Ray3;
import raytracer.Sphere;
import raytracer.Vec3;

public class SphereTest {
    @Test
    public void testInitialization() {
        Vec3 center = new Vec3(1, 2, 3);
        double radius = 1;
        Sphere s = new Sphere(center, radius, null);
        assertEquals(center, s.getOrigin());
        assertEquals(radius, s.getRadius());
    }

    @Test
    public void testBadInitialization() {
        Vec3 center = new Vec3(1, 2, 3);
        double radius = -1;
        assertThrows(IllegalArgumentException.class, () -> new Sphere(center, radius, null));
    }

    @Test
    public void testSetters() {
        Vec3 center = new Vec3(-1, -2, -3);
        double radius = 1;
        Sphere s = new Sphere(center, radius, null);

        Vec3 newCenter = new Vec3(-5, 1, -3);
        s.setOrigin(newCenter);
        assertEquals(newCenter, s.getOrigin());

        double newRadius = 5.0;
        s.setRadius(newRadius);
        assertEquals(newRadius, s.getRadius());
        
        double badRadius = -10.0;
        assertThrows(IllegalArgumentException.class, () -> s.setRadius(badRadius));
    }

    @Test
    public void testIntersectionWithRay() {
        Sphere s = new Sphere(new Vec3(0, 0, -1), 0.5, null);

        // direct hit through center
        Ray3 r = new Ray3(new Vec3(0, 0, 0), new Vec3(0, 0, -1));
        HitRecord hr = s.intersect(r);
        assertTrue(hr.didIntersect());
        assertEquals(hr.getT(), 0.5);
        assertEquals(hr.getNormal(), new Vec3(0, 0, 1));

        // glancing hit
        r = new Ray3(new Vec3(-0.5, 0, 0), new Vec3(0, 0, -1));
        hr = s.intersect(r);
        assertTrue(hr.didIntersect());
        assertEquals(1.0, hr.getT());

        // miss
        r = new Ray3(new Vec3(0, 0, 0), new Vec3(0, 1, 0));
        hr = s.intersect(r);
        assertFalse(hr.didIntersect());
    }
}
