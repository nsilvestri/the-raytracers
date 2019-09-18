package raytracer;

import java.util.Random;

/**
 * A simple 3D vector class, with the operations necessary for use in the
 * pathtracer.
 * 
 * @author nick
 *
 */
public class Vec3 {
	private double x, y, z;

	/**
	 * Creates a new instance of a Vec3 with the given components.
	 * 
	 * @param x the x component of the new Vec3.
	 * @param y the y component of the new Vec3.
	 * @param z the z component of the new Vec3.
	 */
	public Vec3(double x, double y, double z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}

	/**
	 * Calculates the length of this Vec3.
	 * 
	 * @return the length of this Vec3.
	 */
	public double length() {
		return Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2) + Math.pow(z, 2));
	}

	/**
	 * Multiplies each component of this Vec3 by a given scalar.
	 * 
	 * @param v      the Vec3 to scale.
	 * @param scalar the scalar value to multiply.
	 * @return a new Vec3 with values of the result of the scaling.
	 */
	public static Vec3 scale(Vec3 v, double scalar) {
		Vec3 result = new Vec3(0, 0, 0);
		result.x = v.x * scalar;
		result.y = v.y * scalar;
		result.z = v.z * scalar;
		return result;
	}

	/**
	 * Scales this Vec3 so that its length is 1.0. If <code>v</code> has a length of
	 * 0, the original Vec3 is returned.
	 * 
	 * @param v the Vec3 to normalize.
	 * @return a new Vec3 with values of the normalized original Vec3.
	 */
	public static Vec3 normalize(Vec3 v) {
		if (v.length() == 0) {
			return v;
		}

		return Vec3.scale(v, 1 / v.length());
	}

	/**
	 * Sums two Vec3.
	 * 
	 * @param left  the left operand of the subtraction.
	 * @param right the right operand of the subtraction.
	 * @return the sum of the given Vec3.
	 */
	public static Vec3 add(Vec3 left, Vec3 right) {
		Vec3 result = new Vec3(0, 0, 0);

		result.setX(left.getX() + right.getX());
		result.setY(left.getY() + right.getY());
		result.setZ(left.getZ() + right.getZ());

		return result;
	}

	/**
	 * Subtracts two Vec3.
	 * 
	 * @param left  the left operand of the subtraction.
	 * @param right the right operand of the subtraction.
	 * @return the difference of the given Vec3.
	 */
	public static Vec3 sub(Vec3 left, Vec3 right) {
		Vec3 result = new Vec3(0, 0, 0);

		result.setX(left.getX() - right.getX());
		result.setY(left.getY() - right.getY());
		result.setZ(left.getZ() - right.getZ());

		return result;
	}

	/**
	 * Calculates the dot product of two Vec3.
	 * 
	 * @param left  the left operand of the dot product.
	 * @param right the right operand of the dot product.
	 * @return the dot product of the given Vec3.
	 */
	public static double dot(Vec3 left, Vec3 right) {
		return (left.getX() * right.getX()) + (left.getY() * right.getY()) + (left.getZ() * right.getZ());
	}

	@Override
	public boolean equals(Object o) {
		if (o == null) {
			return false;
		}

		if (!(o instanceof Vec3)) {
			return false;
		}

		Vec3 other = (Vec3) o;

		return (getX() == other.getX()) && (getY() == other.getY()) && (getZ() == other.getZ());
	}

	public double getX() {
		return x;
	}

	public void setX(double x) {
		this.x = x;
	}

	public double getY() {
		return y;
	}

	public void setY(double y) {
		this.y = y;
	}

	public double getZ() {
		return z;
	}

	public void setZ(double z) {
		this.z = z;
	}

	/**
	 * Returns a random vec3 with a length of 1.0 or less. Each component of the
	 * vec3 is in the range [-1, 1], as long as the length of the vec3 is 1.0 or
	 * less.
	 * 
	 * @return a random vec3 with a length of 1.0 or less.
	 */
	public static Vec3 randomInUnitSphere() {
		Random random = new Random();
		while (true) {
			// vec3 with components a random length from 0 to +1
			Vec3 randomVec3 = new Vec3(random.nextDouble(), random.nextDouble(), random.nextDouble());
			// double it; components random from 0 to +2
			randomVec3 = Vec3.scale(randomVec3, 2);
			// this is just a vec3 with all 1 components. Bad name. Whatever.
			Vec3 cubeDiag = new Vec3(1, 1, 1);
			// we will create a vec3 that lands somewhere in the -1 to +1 cube
			Vec3 unitCubeVec3 = Vec3.sub(cubeDiag, randomVec3);

			// check if unit_cube_vec3 is longer than 1; AKA, outside of the unit sphere.
			if (unitCubeVec3.length() < 1.0) {
				return unitCubeVec3;
			}
		}
	}

	/**
	 * Returns a new Vec3 that is the value of a Vec3 reflecting off a surface with
	 * the given normal.
	 * 
	 * @param v      the incoming Vec3
	 * @param normal the normal to reflect <code>v</code> off of
	 * @return a new Vec3 that is the reflection of the incoming Vec3
	 */
	public static Vec3 reflect(Vec3 v, Vec3 normal) {
		// return v - 2 * dot(v, n) * n
		double twoDotVN = 2 * Vec3.dot(v, normal);
		return Vec3.sub(v, Vec3.scale(normal, 2 * twoDotVN));
	}

	/**
	 * Gamma corrects this Vec3, under the interpretation that it is representing a
	 * color.
	 * 
	 * @param color the input color to gamma correct.
	 * @param gamma the value to gamma correct by, which is the power to take all
	 *              components to.
	 * @return a new Vec3 as the result of the gamma correction.
	 */
	public static Vec3 gammaCorrect(Vec3 color, double gamma) {
		Vec3 result = new Vec3(0, 0, 0);
		result.x = Math.pow(color.getX(), gamma);
		result.y = Math.pow(color.getY(), gamma);
		result.z = Math.pow(color.getZ(), gamma);
		return result;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		return String.format("Vec3(%f, %f, %f)", x, y, z);
	}
}
