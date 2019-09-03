package test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

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
		
		Vec3 zeroLength = new Vec3(0, 0, 0);
		zeroLength.normalize();
		assertEquals(0, zeroLength.length());
	}
	
	@Test
	public void testAdd() {
		Vec3 left = new Vec3(1, 2, 3);
		Vec3 right = new Vec3(-1, -3, -5);
		
		assertEquals(new Vec3(0, -1, -2), Vec3.add(left, right));
	}
	
	@Test
	public void testSub() {
		Vec3 left = new Vec3(1, 2, 3);
		Vec3 right = new Vec3(-1, -3, -5);
		
		assertEquals(new Vec3(2, 5, 8), Vec3.sub(left, right));
	}
	
	@Test
	public void testDot() {
		Vec3 left = new Vec3(1, 1, 1);
		Vec3 right = new Vec3(1, 1, 1);
		
		assertEquals(3, Vec3.dot(left, right));

		left = new Vec3(-1, -2, -3);
		right = new Vec3(1, 2, 3);
		
		assertEquals(-14, Vec3.dot(left, right));
	}
	
	@Test
	public void testEquals() {
		Vec3 v1 = new Vec3(1, 2, 3);
		assertFalse(v1.equals(null));
		assertFalse(v1.equals(new Object()));
		assertTrue(v1.equals(v1));
		
		Vec3 v2 = new Vec3(1, 2, 3);
		assertTrue(v1.equals(v2));
		assertTrue(v2.equals(v1));
		
		Vec3 v3 = new Vec3(-1, 2, 3);
		assertFalse(v1.equals(v3));
		assertFalse(v3.equals(v1));
		
		Vec3 v4 = new Vec3(1, -2, 3);
		assertFalse(v1.equals(v4));
		assertFalse(v4.equals(v1));
		
		Vec3 v5 = new Vec3(1, 2, -3);
		assertFalse(v1.equals(v5));
		assertFalse(v5.equals(v1));
	}
}
