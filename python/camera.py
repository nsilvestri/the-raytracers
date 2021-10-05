from vec3 import Vec3

class Camera():
    def __init__(self):
        self.position = Vec3()
        self.lower_left_corner = Vec3()
        self.horizontal = Vec3()
        self.vertical = Vec3()