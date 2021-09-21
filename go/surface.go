package main

// SurfaceType represents an enum for determining the type of a Surface.
type SurfaceType int

const (
	// Sphere represents a sphere
	Sphere SurfaceType = 0
	// Plane represents a plane
	Plane SurfaceType = 1
)

// Surface represents any surface, and contains the relevant variables for any kind of surface. The used attributes of the struct are determined by Type.
type Surface struct {
	Type SurfaceType

	SphereOrigin Vec3
	SphereRadius float64
}
