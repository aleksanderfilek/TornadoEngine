#!/bin/bash
g++ -Iinc main.cpp src/TE_main.cpp src/TE_graphics.cpp -o main $(pkg-config --cflags --libs sdl2 glew) -lSDL2_image