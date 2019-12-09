#!/bin/bash
gcc -ITornadoEngine/include -ISDL/include main.c TornadoEngine/src/TE_main.c TornadoEngine/src/TE_graphics.c TornadoEngine/src/TE_math.c TornadoEngine/src/TE_ui.c  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lm -o main
