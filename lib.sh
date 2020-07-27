#!/bin/bash
gcc -std=c99 -c -Iinclude source/TE_core.c -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
gcc -std=c99 -c -Iinclude source/TE_input.c -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
gcc -std=c99 -c -Iinclude source/TE_math.c -lSDL2main -lSDL2 -lGLEW -lGLU -lGL -lm
gcc -std=c99 -c -Iinclude source/TE_mesh.c -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
gcc -std=c99 -c -Iinclude source/TE_shader.c -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
gcc -std=c99 -c -Iinclude source/TE_graphics.c -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
gcc -std=c99 -c -Iinclude source/TE_texture.c -lSDL2main -lSDL2  -lSOIL -lGLEW -lGLU -lGL
ar rcs -o lib/libTE.a TE_core.o TE_input.o TE_math.o TE_mesh.o TE_shader.o TE_graphics.o TE_texture.o
rm *.o
