#!/bin/bash
gcc -c -Iinclude src/TE_main.c src/TE_graphics.c src/TE_math.c src/TE_ecs.c src/TE_ui.c  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
ar rvs lib/TornadoEngine.a TE_main.o TE_graphics.o TE_math.o TE_ecs.o TE_ui.o
rm TE_main.o TE_graphics.o TE_math.o TE_ecs.o TE_ui.o