#!/bin/bash
g++ -Iinc -ISDL/include main.cpp src/TE.cpp src/TE_graphics.cpp src/TE_math.cpp -o engine.out $(pkg-config --cflags --libs sdl2 glew) -lSDL_image