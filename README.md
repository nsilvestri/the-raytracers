# the-raytracers

This repository is a collection of raytracers writted in various languages, intended to easily show the difference in how one might approach a problem in different ways, depending on the language. Raytracing was chosen as the common problem because it provides many surfaces to demonstrate said differences:

* Parallelization
* File I/O
* Dependencies (or lack thereof)
* Recursion
* Paradigmal differences (e.g. imperative vs. functional)

Each raytracer has a makefile associated with it (except where otherwise noted), and executing `make` within the language's directory will generate an executable named `raytracer`. Languages in this repository should be idiomatic of the language they are written in, to highlight the differences in functionality and capability of languages. Unfortunately, I can't claim to be an expert in any of the languages demonstrated, and am hardly capable of writing idiomatic code2 in any language at all. Please feel free to contribute to the repository if you are even slightly more competent than I.

# Languages

| Language | Raycasting | File I/O | Parallelization | CLI args | Notes |
|:-:|:-:|:-:|:-:|:-:|:-:|
|[C](c)|x|output|yes, non-functional and buggy||
|[C++](cpp) |x|x||x|(not a Monte Carlo raycaster. Will be rewritten)|
|[Java](java)|x|output|||
|Rust|||||uses Cargo crates as dependencies instead of implementing vectors and PPM generators|
|Go|||||
|Python|||||

These raytracers are not meant to be overly complex. The feature set for any raytracer is based on those covered in Peter Shirley's [Raytracing in a Weekend (PDF)](http://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf).