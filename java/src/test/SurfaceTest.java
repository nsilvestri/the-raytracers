package test;


import static org.junit.jupiter.api.Assertions.assertNull;

import org.junit.jupiter.api.Test;

import raytracer.Sphere;

public class SurfaceTest {

	@Test
	public void testGetMaterial() {
		// Surface is abstract; to test this getter we must instantiate a subclass
		Sphere s = new Sphere(null, 0, null);
		assertNull(s.getMaterial());
	}
}
