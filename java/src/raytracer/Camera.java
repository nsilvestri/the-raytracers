package raytracer;

public class Camera {
    private Vec3 position;
    private Vec3 lowerLeftCorner;
    private Vec3 horizontal;
    private Vec3 vertical;

    /**
     * Create a new camera with all instance fields set to the default Vec3
     * constructor.
     */
    public Camera() {
        this.position = new Vec3();
        this.lowerLeftCorner = new Vec3();
        this.horizontal = new Vec3();
        this.vertical = new Vec3();
    }

    /**
     * Create a new camera with the given properties.
     * @param position the position of this Camera
     * @param lowerLeftCorner the coordinates of the lower-left corner of the
     * image in world space
     * @param horizontal the location of the lower-right corner, relative to 
     * `lowerLeftCorner`
     * @param vertical the location of the upper-right corner, relative to 
     * `lowerLeftCorner`
     */
    public Camera(Vec3 position, Vec3 lowerLeftCorner, Vec3 horizontal, Vec3 vertical) {
        this.position = position;
        this.lowerLeftCorner = lowerLeftCorner;
        this.horizontal = horizontal;
        this.vertical = vertical;
    }

    public Vec3 getPosition() {
        return position;
    }

    public Vec3 getLowerLeftCorner() {
        return lowerLeftCorner;
    }

    public Vec3 getHorizontal() {
        return horizontal;
    }
    
    public Vec3 getVertical() {
        return vertical;
    }

    public void setPosition(Vec3 position){
        this.position = position;
    }

    public void setLowerLeftCorner(Vec3 lowerLeftCorner) {
        this.lowerLeftCorner = lowerLeftCorner;
    }

    public void setHorizontal(Vec3 horizontal) {
        this.horizontal = horizontal;
    }

    public void setVertical(Vec3 vertical) {
        this.vertical = vertical;
    }
}
