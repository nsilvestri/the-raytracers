pub trait Surface {
    fn hit(&self, r: ray3) -> bool;
}

pub struct Sphere {
    position: vec3;
    origin: f32;
}

impl Surface for Sphere {
    fn hit(&self, r: ray3) -> bool {
        // let oc: vec3 = vec3::sub
        false
    }
}