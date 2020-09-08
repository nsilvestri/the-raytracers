use surface::Surface;

pub struct Scene {
    surfaces: Vec<Surface>,
}

impl Scene {
    pub fn new() -> Scene {
        Scene {
            surfaces: Vec<Surface>::new();
        }
    }
}