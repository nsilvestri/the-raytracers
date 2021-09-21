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
	CurrentScene := Scene{[]Surface{BigSphere}}

	for j := ImageHeight - 1; j >= 0; j-- {
		for i := 0; i < ImageWidth; i++ {
			PixelColor := Vec3{0, 0, 0}
			for s := 0; s < NumSamples; s++ {
				u := float64(i/ImageWidth) + (rand.Float64() / float64(ImageWidth))
				v := float64(j/ImageWidth) + (rand.Float64() / float64(ImageHeight))
				HorizontalOffset := Horizontal.Scale(u)
				VerticalOffset := Vertical.Scale(v)
				TotalOffset := HorizontalOffset.Add(VerticalOffset)
				Direction := LowerLeftCorner.Add(TotalOffset)
				r := Ray3{Origin, Direction}
				ColorSample := CurrentScene.SceneColor(r)
				ColorSampleGamma := ColorSample.GammaCorrect(0.5)
				PixelColor = PixelColor.Add(ColorSampleGamma)
			}
			PixelColor = PixelColor.Scale(1.0 / float64(NumSamples))
			fmt.Printf("%d %d %d\n", int32(PixelColor.X*255), int32(PixelColor.X*255), int32(PixelColor.Z*255))
		}
	}
}
