use geefr_ppm::Ppm;
use scene::Scene;
use vek::Vec3;

fn main() {
    let image_width = 800;
    let image_height = 400;
    let mut image = Ppm::new(image_width, image_height);

    let scene = Scene::new();

    image = render(scene, image);

    image.write(String::from("image.ppm")).expect("Failed to save PPM");
}

fn render(scene: Scene, image: Ppm) -> Ppm {
    image
}

pub struct Ray3 {
    origin: Vec3<f32>,
    direction: Vec3<f32>,
}

mod scene {

    pub struct Scene {
        surfaces: Vec<surface::Surface>
    }

    impl Scene {
        pub fn new() -> Self {
            Self {
                surfaces: Vec::new(),
            }
        }
    }

    pub mod surface {
        use vek::Vec3;
        use crate::Ray3;
        pub trait Surface {
            fn hit(&self, r: Ray3) -> bool;
        }

        pub struct Sphere {
            pub position: Vec3<f32>,
            pub radius: f32,
        }

        impl Surface for Sphere {
            fn hit(&self, r: Ray3) -> bool {
                // let oc: vec3 = vec3::sub
                false
            }
        }
    }
}
