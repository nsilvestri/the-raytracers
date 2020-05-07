CC=gcc -O3 -Wall
CC_DEBUG=gcc -Wall

raytracer : raytracer.c vec3.o surface.o ray3.o scene.o material.o image.o
	$(CC) -o raytracer raytracer.c vec3.o ray3.o surface.o scene.o material.o image.o -lm

vec3.o : vec3.c vec3.h
	$(CC) -c vec3.c

ray3.o : ray3.c vec3.h vec3.o
	$(CC) -c ray3.c

surface.o : surface.c surface.h ray3.o vec3.o
	$(CC) -c surface.c

material.o : material.c material.h vec3.o surface.o
	$(CC) -c material.c

scene.o : scene.c scene.h vec3.o ray3.o surface.o material.o
	$(CC) -c scene.c

image.o : image.c image.h
	$(CC) -c image.c

debug : 
	make clean
	$(CC_DEBUG) -c -g vec3.c 
	$(CC_DEBUG) -c -g ray3.c
	$(CC_DEBUG) -c -g surface.c
	$(CC_DEBUG) -c -g scene.c
	$(CC_DEBUG) -c -g material.c
	$(CC_DEBUG) -c -g image.c
	$(CC_DEBUG) -g -o debug raytracer.c vec3.o ray3.o surface.o scene.o material.o image.o -lm

clean : 
	rm -f raytracer debug *.o
