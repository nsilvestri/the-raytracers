package main

import (
	"math"
)

// A Vec3 represents a vector with coordinates X, Y and Z in 3D space.
type Vec3 struct {
	X, Y, Z float64
}

// Add returns the vector v+w.
func (v Vec3) Add(w Vec3) Vec3 {
	return Vec3{v.X + w.X, v.Y + w.Y, v.Z + w.Z}
}

// Sub returns the vector v-w.
func (v Vec3) Sub(w Vec3) Vec3 {
	return v.Add(w.Scale(-1.0))
}

// Scale returns the vector v*s.
func (v Vec3) Scale(s float64) Vec3 {
	return Vec3{v.X * s, v.Y * s, v.Z * s}
}

// Dot returns the dot product of v and w.
func (v Vec3) Dot(w Vec3) float64 {
	return v.X*w.X + v.Y*w.Y + v.Z*w.Z
}

// Len returns the length Vec3.
func (v Vec3) Len() float64 {
	// There might be an argument for just doing the squares on our own, for the
	// sake of line lengths
	// return float64(math.Sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z))
	return float64(math.Sqrt(math.Pow(v.X, 2) + math.Pow(v.Y, 2) + math.Pow(v.Z, 2)))
}

// Normalize returns the normalized vector of a vector. If the length of v is 0,
// v is returned.
func (v Vec3) Normalize() Vec3 {
	if v.Len() == 0 {
		return v
	}
	return v.Scale(1 / v.Len())
}

// Reflect returns the reflection vector of v given a normal n.
func (v Vec3) Reflect(n Vec3) Vec3 {
	return v.Sub(n.Scale(2 * v.Dot(n)))
}
