package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import raytracer.HitRecord;
import raytracer.Ray3;
import raytracer.Sphere;
import raytracer.Vec3;

public class TestSphere {
	@Test
	public void testInitialization() {
		Vec3 center = new Vec3(0, 0, 0);
		double radius = 1;
		Sphere s = new Sphere(center, 1, null);
		assertEquals(center, s.getOrigin());
		assertEquals(radius, s.getRadius());
		
		
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
	}
	
	@Test
	public void testNoIntersectionWithRay() {
		Sphere s = new Sphere(new Vec3(0, 0, -1), 0.5, null);
		
		// miss
		Ray3 r = new Ray3(new Vec3(0, 0, 0), new Vec3(0, 1, 0));
		HitRecord hr = s.intersect(r);
		assertFalse(hr.didIntersect());
	}
}
