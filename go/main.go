package main

import (
	"fmt"
	"math/rand"
)

func main() {
	fmt.Println("test")

	ImageWidth := 800
	ImageHeight := 400
	NumSamples := 1000

	LowerLeftCorner := Vec3{-2.0, -1.0, -1.0}
	Horizontal := Vec3{4.0, 0.0, 0.0}
	Vertical := Vec3{0.0, 2.0, 0.0}
	Origin := Vec3{0.0, 0.0, 0.0}

	BigSphere := Surface{Sphere, Vec3{0, -100.5, -1}, 100}

	for j := ImageHeight - 1; j >= 0; j-- {
		for i := 0; i < ImageWidth; i++ {
			PixelColor := Vec3{0, 0, 0}
			for s := 0; s < NumSamples; s++ {
				u := (i / ImageWidth) + (rand.Float64() / ImageWidth)
				v := (j / ImageWidth) + (rand.Float64() / ImageHeight)
			}
		}
	}
}
