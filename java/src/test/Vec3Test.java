package test;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

import raytracer.Vec3;

public class Vec3Test {

	@Test
	public void testInitialization() {
		Vec3 v = new Vec3(1, 2, 3);
		assertEquals(1, v.getX());
		assertEquals(2, v.getY());
		assertEquals(3, v.getZ());
	}
	
	@Test
	public void testLength() {
		Vec3 v1 = new Vec3(1, 0, 0);
		assertEquals(1, v1.length());
		
		Vec3 v2 = new Vec3(0, 0, 0);
		assertEquals(0, v2.length());
	}
	
	@Test
	public void testScale() {
		Vec3 v1 = new Vec3(1, 2, 3);
		v1.scale(2);
		assertEquals(2, v1.getX());
		assertEquals(4, v1.getY());
		assertEquals(6, v1.getZ());
	}
	
	@Test
	public void testNormalization() {
		Vec3 v1 = new Vec3(1, 2, 3);
		v1.normalize();
		assertEquals(1, v1.length());
	}
	
	
}
