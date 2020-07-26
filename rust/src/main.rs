mod scene;

use array2d::Array2D;
use geefr_ppm::Ppm;
use scene::Scene;
use vek::vec3;

fn main() {
    let image_width = 800;
    let image_height = 400;
    let mut image = Ppm::new(image_width, image_height);

    let scene = Scene {
        surfaces = 
    };

    image = render(scene, image);

    image.write(String::from("image.ppm")).expect("Failed to save PPM");
}

fn render(scene: Scene, image: Ppm) -> Ppm {
    image
}
