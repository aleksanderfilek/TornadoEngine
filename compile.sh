#!/bin/bash
g++ -Iinc main.cpp src/TE.cpp src/TE_graphics.cpp src/TE_math.cpp -o main $(pkg-config --cflags --libs sdl2 glew) -lSDL2_image

