# the-raytracers

This repository is a collection of raytracers writted in various languages, intended to easily show the difference in how one might approach a problem in different ways, depending on the language.

Raytracing was chosen as the common problem because it can be used to demonstrate the strengths and weaknesses of various languages, as well as being a good project in and of itself.

* Raytracing is easy to understand, even with limited mathematical understanding. All the required to be known (if one is willing to simply accept the math "as is") is that a ray is generated from the camera, through the image, and into the scene, and whatever it hits determines a pixel's color.
* It can be accomplished both imperatively (with procedural or object-oriented programming), or declaratively (with functional programming).
* Easily parallelizable
* Makes use of simple file I/O
* Dependencies unnecessary
* Generates a cool picture at the end

Languages in this repository should be idiomatic of the language they are written in, to highlight the differences in functionality and capability of languages. Unfortunately, I can't claim to be an expert in any of the languages written, and am hardly capable of writing idiomatic language in any language at all. Please feel free to contribute to the repository if you are even slightly more competent than I.

These raytracers are not meant to be overly complex. The feature set for any raytracer should be minimally, but not much beyond:

* point lights
* Blinn-Phong shading
* render spheres and planes
* shadows
* multicore rendering

Optional features I will consider are:

* dielectrics
* mirror reflections
* area lights
* meshes

