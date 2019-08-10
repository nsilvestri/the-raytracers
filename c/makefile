raytracer : main.c surface.o vec3.o ray3.o scene.o
	gcc -o raytracer main.c vec3.o ray3.o surface.o scene.o -lm

vec3.o : vec3.c vec3.h
	gcc -c vec3.c

ray3.o : ray3.c vec3.h vec3.o
	gcc -c ray3.c

surface.o : surface.c surface.h ray3.o vec3.o
	gcc -c surface.c

scene.o : scene.c scene.h vec3.o ray3.o surface.o
	gcc -c scene.c

debug : 
	make clean
	gcc -c -g vec3.c 
	gcc -c -g ray3.c
	gcc -c -g surface.c
	gcc -c -g scene.c
	gcc -g -o debug main.c vec3.o ray3.o surface.o scene.o -lm

clean : 
	rm -f raytracer debug *.o
