import math

from hit_record import HitRecord

class Surface():
    def __init__(self, material):
        self.material = material

class Sphere(Surface):
    def __init__(self, material, origin, radius):
        super().__init__(material)
        assert radius >= 0, "Sphere radius must be >= 0"
        self.radius = radius
        self.origin = origin

    def intersect(self, r):
        oc = r.origin - self.origin
        # a, b, c are A, B, C of quadratic equation
        a = r.direction.dot(r.direction)
        b = 2 * oc.dot(r.direction)
        c = oc.dot(oc) - self.radius ** 2
        discriminant = b * b - 4 * a * c

        if discriminant < 0:
            # no intersection
            return HitRecord( \
                intersected=False, \
                intersection_distance=float('-inf'), \
                surface=self, \
                normal=None)
        # there are two roots, take the closer (smaller) one
        t_minus = (-b - math.sqrt(discriminant)) / (2 * a)
        t_plus = (-b + math.sqrt(discriminant)) / (2 * a)
        t = min(t_minus, t_plus)

        point_of_intersection = r.point_at_parameter(t)
        # normal is vec3 from origin to p_o_i
        normal = (point_of_intersection - self.origin).normalize()
        return HitRecord( \
            intersected=True, \
            intersection_distance=t, \
            surface=self, \
            normal=normal)
