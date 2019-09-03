package raytracer;

public class Vec3 {
	private double x, y, z;

	public Vec3(double x, double y, double z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public double length() {
		return Math.sqrt(Math.pow(x, 2) +  Math.pow(y, 2) + Math.pow(z, 2));
	}
	
	public static Vec3 scale(Vec3 v, double scalar) {
		Vec3 result = new Vec3(0, 0, 0);
		result.x = v.x * scalar;
		result.y = v.y * scalar;
		result.z = v.z * scalar;
		return result;
	}
	
	public static Vec3 normalize(Vec3 v) {
		if (v.length() == 0) {
			return v;
		}
		
		return Vec3.scale(v, 1 / v.length());
	}
	
	public static Vec3 add(Vec3 left, Vec3 right) {
		Vec3 result = new Vec3(0, 0, 0);
		
		result.setX(left.getX() + right.getX());
		result.setY(left.getY() + right.getY());
		result.setZ(left.getZ() + right.getZ());
		
		return result;
	}
	
	public static Vec3 sub(Vec3 left, Vec3 right) {
		Vec3 result = new Vec3(0, 0, 0);
		
		result.setX(left.getX() - right.getX());
		result.setY(left.getY() - right.getY());
		result.setZ(left.getZ() - right.getZ());
		
		return result;
	}
	
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
}
