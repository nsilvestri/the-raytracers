use geefr_ppm::Ppm;
use scene::Scene;
use vek::Vec3;

fn main() {
    let image_width = 800;
    let image_height = 400;
    let mut image = Ppm::new(image_width, image_height);

    let scene = Scene::new();

    image = render(scene, image, 1);

    image.write(String::from("image.ppm")).expect("Failed to save PPM");
}

fn render(scene: Scene, mut image: Ppm, num_samples: i32) -> Ppm {
    let x1 = 0;
    let x2 = image.width;
    let y1 = 0;
    let y2 = image.height;

    // X-axis is left, Y is up, -Z is towards the screen
    let lower_left_corner = Vec3{ x: -2.0, y: -1.0, z: -1.0 };
    let horizontal = Vec3{ x: 4.0, y: 0.0, z: 0.0};
    let vertical = Vec3{ x: 0.0, y: 2.0, z: 0.0};
    let origin = Vec3{ x: 0.0, y: 0.0, z: 0.0};

    // iterate over each pixel. Starts at bottom left as 0,0
    for y in y1..y2 {
        // and left to right
        for x in x1..x2 {
            // create a vec3 to store the total color of this pixel
            let mut pixel_color = Vec3{ x: 0.0, y: 0.0, z: 0.0 };

            // sample this pixel num_sample times
            for _s in 0..num_samples {
                // u and v are percentages of the width and height of the image
                // randomness chooses a random point within the square of the pixel
                use rand::{Rng, thread_rng};
                let u: f32 = (x / (x2 - x1)) as f32 + (thread_rng().gen_range(0.0, 1.0) / (x2 - x1) as f32); 
                let v: f32 = (y / (y2 - y1)) as f32 + (thread_rng().gen_range(0.0, 1.0) / (y2 - y1) as f32);
                
                // vec3 component for how for how far right to push our final ray
                let horizontal_offset = horizontal * u;

                // vec3 component for how far up to push our final ray
                let vertical_offset = vertical * v;

                // combine the two components above
                let total_offset = horizontal_offset + vertical_offset;

                // and add it to our lower-left corner to get the final direction
                let direction = lower_left_corner + total_offset;

                // create the ray with our camera position (origin) and calculated direction
                let r: Ray3 = Ray3 { origin, direction };

                // get our color sample for our single ray from the world
                let color_sample = scene.color(r);

                // gamma correct sample
                let color_sample_gamma: Vec3<f32> = Vec3{x: color_sample.x.sqrt(), y: color_sample.y.sqrt(), z: color_sample.z.sqrt()};

                // add sample color to color total for this pixel
                pixel_color = pixel_color + color_sample_gamma;
            }
            
            // pixel_color contains the total of all samples; get the average of each sample
            let pixel_color: Vec3<f32> = pixel_color * (1.0 / num_samples as f32);

            // store in image_data
            let r: u8 = (pixel_color.x * 255 as f32) as u8;
            let g: u8 = (pixel_color.y * 255 as f32) as u8;
            let b: u8 = (pixel_color.z * 255 as f32) as u8;
            let image_y: usize = image.height - y - 1; // y is flipped because origin is top-left in image coords
            image.set_pixel(x, image_y, r, g, b);
        }
    }
    image
}

pub struct Ray3 {
    origin: Vec3<f32>,
    direction: Vec3<f32>,
}

impl Ray3 {
    pub fn point_at_parameter(&self, t: f32) -> Vec3<f32> {
        let scaled_direction = self.direction * t;
        self.origin + scaled_direction
    }
}

mod scene {

    use vek::Vec3;

    pub struct Scene {
        surfaces: Vec<Sphere>
    }

    impl Scene {
        pub fn new() -> Self {
            Self {
                surfaces: vec!(Sphere::new(Vec3{x: 0.0, y: -100.5, z: -1.0}, 100.0))
            }
        }

        pub fn color(&self, r: crate::Ray3) -> Vec3<f32> {
            /* Find the nearest surface which r intersects */
            let mut nearest: &Sphere = &Sphere::zero();
            let mut nearest_t: f32 = std::f32::INFINITY;

            for i in 0..self.surfaces.len() {
                let current_surface = &self.surfaces[i];
                let hit_record = current_surface.hit(&r);
                // a miss is -INFINITY, but all t < 0 are behind us
                if hit_record.t < nearest_t && hit_record.t > 0.0 {
                    nearest_t = hit_record.t;
                    nearest = current_surface;
                }
            }

            /* BASE CASE: no intersection; return sky color by default */

            if nearest_t == std::f32::INFINITY {
                // normalize direction of ray so all values of y will be consistent
                let unit_direction: Vec3<f32> = r.direction.normalized();

                // proportion of sky color mixture based on y component (up-ness)
                let t = 0.5 * (unit_direction.y + 1.0);

                // base color of sky
                let base_sky_color: Vec3<f32> = Vec3{ x: 0.5, y: 0.7, z: 1.0 } * t;

                // what color the sky fades into, going down
                let sky_color_gradient: Vec3<f32> = Vec3{ x: 1.0, y: 1.0, z: 1.0 } * (1.0 - t);

                // add base_sky_color and sky_color_gradient
                return base_sky_color + sky_color_gradient;
            }

            /* nearest now contains the nearest surface; calculate the color */

            let hit_record: HitRecord = nearest.hit(&r);

            // recursive bouncing color
            // todo
            // attenuate color by albedo
            // todo
            return Vec3{ x: 1.0, y: 1.0, z: 1.0 };
        }
    }

    pub struct Sphere {
        position: Vec3<f32>,
        radius: f32,
    }

    impl Sphere {
        pub fn new(position: Vec3<f32>, radius: f32) -> Self {
            Self {
                position: position,
                radius: radius,
            }
        }

        pub fn zero() -> Self {
            Self {
                position: Vec3{ x: 0.0, y: 0.0, z: 0.0 },
                radius: 0.0,
            }
        }

        pub fn hit(&self, r: &crate::Ray3) -> HitRecord {
            let oc: Vec3<f32> = r.origin - self.position;
            /* a, b, c are A, B, C of quadratic equation */
            // a = (dir . dir)
            let a: f32 = Vec3::dot(r.direction, r.direction);
            // b = (dir . (eye - sphere_origin))
            let b: f32 = 2.0 * Vec3::dot(oc, r.direction);
            // c = (ray_pos - sphere_center) . (ray_pos - sphere_center) - R^2
            let c: f32 = Vec3::dot(oc, oc) - (self.radius * self.radius);
            // discr = B^2-4AC
            let discriminant: f32 = (b * b) - (4.0 * a * c);

            /* filling hit_record */
            let t: f32;
            if discriminant < 0.0 {
                t = std::f32::NEG_INFINITY;
            }
            else {
                // there are two roots; we need the closer (smaller) one
                let t_minus: f32 = (-b - discriminant.sqrt()) / (2.0 * a);
                let t_plus: f32 = (-b + discriminant.sqrt()) / (2.0 * a);
                t = t_plus.min(t_minus);
            }

            // point_of_intersection is self-explanatory
            let point_of_intersection: Vec3<f32> = r.point_at_parameter(t);
            // normal_direction is the vec3 from sphere center to p_o_i
            let normal_direction: Vec3<f32> = point_of_intersection - self.position;
            // normalize the normal because why not? Might not be totally necessary
            let normal: Vec3<f32> = normal_direction.normalized();

            HitRecord {
                t,
                normal,
            }
        }
    }

    pub struct HitRecord {
        t: f32,
        normal: Vec3<f32>,
    }
}
