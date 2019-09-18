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
		Vec3 v1Scaled = Vec3.scale(v1, 2);
		assertEquals(2, v1Scaled.getX());
		assertEquals(4, v1Scaled.getY());
		assertEquals(6, v1Scaled.getZ());
	}
	
	@Test
	public void testNormalization() {
		Vec3 v1 = new Vec3(1, 2, 3);
		Vec3 v1Normalized = Vec3.normalize(v1);
		assertEquals(1, v1Normalized.length());
		
		Vec3 zeroLength = new Vec3(0, 0, 0);
		Vec3 zeroLengthNormalized = Vec3.normalize(zeroLength);
		assertEquals(0, zeroLengthNormalized.length());
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
	
	@Test
	public void testRandomInUnitSphere() {
		// perform a statistical analysis to confirm that vectors are of length (0-1]
		for (int i = 0; i < 100; i++) {
			assertTrue(Vec3.randomInUnitSphere().length() <= 1);
		}
	}
	
	@Test
	public void testReflect() {
		/* Reflection straight back */
		Vec3 v1 = new Vec3(0, 0, -1);
		Vec3 normal1 = new Vec3(0, 0, 1);
		Vec3 expected1 = new Vec3(0, 0, 1);
		// normalization required, because reflect simply returns a direction-like Vec3
		assertEquals(expected1, Vec3.normalize(Vec3.reflect(v1, normal1)));
		
		/* Reflection, down, all at 45 degree angles, into flat ground */
//		Vec3 v2 = new Vec3(0, -1, -1);
//		Vec3 normal2 = new Vec3(0, 1, 0);
//		Vec3 expected2 = Vec3.normalize(new Vec3(0, 1, -1));
//		assertEquals(expected2, Vec3.normalize(Vec3.reflect(v2, normal2)));
	}
	
	@Test
	public void testGammaCorrect() {
		Vec3 v0 = new Vec3(0, 0, 0);
		assertEquals(new Vec3(0, 0, 0), Vec3.gammaCorrect(v0, 3));
		
		Vec3 v1 = new Vec3(1, 2, 3);
		assertEquals(new Vec3(1, 8, 27), Vec3.gammaCorrect(v1, 3));
	}
	
	@Test
	public void testToString() {
		Vec3 v1 = new Vec3(0, 0, 0);
		String expected1 = "Vec3(0.0000, 0.0000, 0.0000)";
		assertEquals(expected1, v1.toString());
	}
}
