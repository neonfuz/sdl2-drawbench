drawbench: main.c
	gcc -o drawbench main.c `sdl2-config --cflags --libs` -lSDL2_image

clean:
	rm drawbench

.PHONY: clean
