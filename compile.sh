#!/bin/bash
g++ -ITE/inc main.cpp TE/src/TE.cpp TE/src/TE_graphics.cpp TE/src/TE_math.cpp -o main $(pkg-config --cflags --libs sdl2 glew) -lSDL2_image -lSDL2_ttf

