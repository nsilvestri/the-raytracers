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

fn render(scene: Scene, image: Ppm, num_samples: i32) -> Ppm {
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
            let pixel_color = Vec3{ x: 0.0, y: 0.0, z: 0.0 };

            // sample this pixel num_sample times
            for s in 0..num_samples {
                // u and v are percentages of the width and height of the image
                // randomness chooses a random point within the square of the pixel
                let mut rng = rand::thread_rng();
                let u: f32 = (x / (x2 - x1)) as f32 + (rng.gen_range(0.0, 1.0) / (x2 - x1) as f32); 
                let v: f32 = (y / (y2 - y1)) as f32 + (rng.gen_range(0.0, 1.0) / (y2 - y1) as f32);
                
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
                vec3 color_sample_gamma = vec3_gamma_correct(color_sample, 0.5);

                // add sample color to color total for this pixel
                pixel_color = vec3_add(pixel_color, color_sample_gamma);
            }
            
            // pixel_color contains the total of all samples; get the average of each sample
            let pixel_color: Vec3<f32> = pixel_color * (1.0 / num_samples as f32);

            // store in image_data
            unsigned char r = pixel_color.x * 255;
            unsigned char g = pixel_color.y * 255;
            unsigned char b = pixel_color.z * 255;
            int image_y = image.height - y - 1; // y is flipped because origin is top-left in image coords
            image.data[(image_y * image.width * 3) + (x * 3) + 0] = r;
            image.data[(image_y * image.width * 3) + (x * 3) + 1] = g;
            image.data[(image_y * image.width * 3) + (x * 3) + 2] = b;
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
            surface nearest;
            float nearest_t = INFINITY;

            for (int i = 0; i < num_surfaces; i++) {
                surface current_surface = surfaces[i];
                hit_record hit_record = surface_hit(current_surface, r);
                // a miss is -INFINITY, but all t < 0 are behind us
                if (hit_record.t < nearest_t && hit_record.t > 0) {
                    nearest_t = hit_record.t;
                    nearest = current_surface;
                }
            }

            /* BASE CASE: no intersection; return sky color by default */

            if (nearest_t == INFINITY) {
                // normalize direction of ray so all values of y will be consistent
                vec3 unit_direction = vec3_normalize(r.direction);

                // proportion of sky color mixture based on y component (up-ness)
                float t = 0.5 * (unit_direction.y + 1.0);

                // base color of sky
                vec3 base_sky_color = vec3_new(0.5, 0.7, 1.0);
                base_sky_color = vec3_scale(base_sky_color, t);

                // what color the sky fades into, going down
                vec3 sky_color_gradient = vec3_new(1, 1, 1);
                sky_color_gradient = vec3_scale(sky_color_gradient, 1.0 - t);

                // add base_sky_color and sky_color_gradient
                return vec3_add(base_sky_color, sky_color_gradient);
            }

            /* nearest now contains the nearest surface; calculate the color */

            hit_record hit_record = surface_hit(nearest, r);

            // recursive bouncing color
            vec3 new_ray_color;
            if (material_should_scatter(nearest.mat)) {
                // point of intersection is where r intersected the surface in xyz space
                vec3 point_of_intersection = ray3_point_at_parameter(r, hit_record.t);
                ray3 scattered = material_scatter(nearest.mat, r, point_of_intersection, hit_record.normal);
                new_ray_color = scene_color(scattered, surfaces, num_surfaces);
            }
            else {
                new_ray_color = nearest.mat.color;
            }
            // attenuate color by albedo
            return vec3_scale(new_ray_color, nearest.mat.albedo);
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

        pub fn hit(&self, r: crate::Ray3) -> HitRecord {
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
