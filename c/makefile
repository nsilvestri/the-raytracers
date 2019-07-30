SRC = main.c vec3.c ray3.c surface.c
raytracer : surface.o vec3.o ray3.o
	gcc -o raytracer main.c vec3.o ray3.o surface.o -lm

vec3.o : vec3.c vec3.h
	gcc -c vec3.c

ray3.o : ray3.c vec3.h vec3.o
	gcc -c ray3.c

surface.o : surface.c surface.h ray3.o vec3.o
	gcc -c surface.c

debug : $(SRC)
	gcc -c -g vec3.c 
	gcc -c -g ray3.c
	gcc -c -g surface.c
	gcc -g -o debug main.c vec3.o ray3.o surface.o -lm

clean : 
	rm raytracer debug *.o
