#!/usr/bin/python

from camera import Camera
from vec3 import Vec3

class Raytracer:
    def __init__(self):
        camera = Camera()
        materials = []
        surfaces = []
        