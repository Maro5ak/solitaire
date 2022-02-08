compile: $(wildcard *.c)
	cc -o cards $? -I. -lSDL2 -lSDL2_image
	./cards