package test;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

import raytracer.Ray3;
import raytracer.Vec3;

public class TestRay3 {
	@Test
	public void testInitialization() {
		Ray3 r = new Ray3(new Vec3(0, 0, 0), new Vec3(1, 2, 3));
		assertEquals(r.getOrigin(), new Vec3(0, 0, 0));
		assertEquals(r.getDirection(), new Vec3(1, 2, 3));
	}
	
	@Test
	public void testPointAtParameter() {
		Ray3 r = new Ray3(new Vec3(-1, -3, -5), new Vec3(1, 2, 3));
		assertEquals(new Vec3(1, 1, 1), r.pointAtParameter(2));
	}
}
