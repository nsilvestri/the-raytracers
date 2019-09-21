CC=gcc -O3

raytracer : main.c vec3.o surface.o ray3.o scene.o material.o
	$(CC) -o raytracer main.c vec3.o ray3.o surface.o scene.o material.o -lm

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

debug : 
	make clean
	$(CC) -c -g vec3.c 
	$(CC) -c -g ray3.c
	$(CC) -c -g surface.c
	$(CC) -c -g scene.c
	$(CC) -c -g material.c
	$(CC) -g -o debug main.c vec3.o ray3.o surface.o scene.o material.o -lm

clean : 
	rm -f raytracer debug *.o
