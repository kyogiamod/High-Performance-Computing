all: release

release:
	gcc -o mandelbrot mandelbrot.c -lm
	gcc -o mandelbrotp mandelbrotp.c -fopenmp -lm

clean:
	rm *.o
