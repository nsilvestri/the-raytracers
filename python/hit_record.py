from surface import Surface
from vec3 import Vec3

@dataclass
class HitRecord():
    intersected: bool
    intersection_distance: float
    surface: Surface
    normal: Vec3
