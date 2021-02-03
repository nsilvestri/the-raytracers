import math

class Vec3:
    def __init__(self, x = 0, y = 0, z = 0):
        self.x = x
        self.y = y
        self.z = z
    
    def length(self):
        return math.sqrt(self.x**2 + self.y**2 + self.z**2)
    
    def scale(self, scalar):
        return Vec3(self.x * scalar, self.y * scalar, self.z * scalar)
    

    def __mul__(self, scalar):
        """Equivalent to Vec3.scale(scalar)"""
        return self.scale(scalar)
    
    def normalize(self):
        if self.length() == 0:
            return self
        return self.scale(1 / self.length())
    
    def __add__(self, right_side):
        return Vec3(self.x + right_side.x, self.y + right_side.y, self.z + right_side.z)
    
    def __sub__(self, right_side):
        return Vec3(self.x - right_side.x, self.y - right_side.y, self.z - right_side.z)
    
    def __str__(self):
        return 'Vec3(%s, %s, %s)' % (self.x, self.y, self.z)
    
    def dot(self, v):
        return (self.x * v.x) + (self.y * v.y) + (self.z * v.z)
