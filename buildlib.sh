#!/bin/bash

g++ -c -Iinclude  src/TE_core.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  $(pkg-config --cflags --libs sdl2 glew)  -lSOIL
g++ -c -Iinclude src/TE_graphics.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf $(pkg-config --cflags --libs sdl2 glew) -lSOIL 
g++ -c -Iinclude  src/TE_math.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf $(pkg-config --cflags --libs sdl2 glew) -lSOIL 
g++ -c -Iinclude src/TE_input.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf $(pkg-config --cflags --libs sdl2 glew) -lSOIL 
g++ -c -Iinclude src/TE_ui.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf $(pkg-config --cflags --libs sdl2 glew) -lSOIL 
ar rcs -o lib/libTE.a TE_core.o TE_graphics.o TE_math.o TE_input.o TE_ui.o 
rm *.o