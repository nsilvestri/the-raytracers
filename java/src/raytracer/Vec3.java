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
	
	public Vec3 scale(double scalar) {
		this.x = this.x * scalar;
		this.y = this.y * scalar;
		this.z = this.z * scalar;
		return this;
	}
	
	public Vec3 normalize() {
		if (this.length() == 0) {
			return this;
		}
		
		return this.scale(1 / this.length());
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
