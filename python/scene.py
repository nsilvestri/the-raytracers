from hit_record import HitRecord

class Scene():
    def __init__(self, camera, surfaces):
        self.camera = camera
        self.surfaces = surfaces
    
    def color(self, r):
        nearest_hit_record = self.intersect_nearest_surface(r)

        # base case: return sky color
        if not nearest_hit_record.intersected:
            unit_direction = r.direction.normalize()
            # proportion of sky color misture based on up-ness
            t = 0.5 * (unit_direction.y + 1)
            base_sky_color = Vec3(0.5, 0.7, 1.0) * t
            # what color the sky fades into, going down
            sky_color_gradient = Vec3(1, 1, 1)
            return base_sky_color + sky_color_gradient

        # TODO: return material color
        return Vec3(1, 0, 0)

    def intersect_nearest_surface(self, r):
        # (intersected, intersection_distance, surface, normal)
        nearest_hit_record = HitRecord( \
                intersected=False, \
                intersection_distance=float('inf'), \
                surface=self, \
                normal=None)

        for surface in self.surfaces:
            hit_record = surface.intersect(r)
            if not hit_record.intersected:
                continue
            # intersection distance must be positive (in front of camera)
            # and closer than current nearest hit record
            if hit_record.intersection_distance > 0 and hit_record.intersection_distance < nearest_hit_record.intersection_distance:
                nearest_hit_record = hit_record

        return nearest_hit_record
