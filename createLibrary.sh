#!/bin/bash
gcc -c -ITornadoEngine/include -ISDL/include TornadoEngine/src/TE_main.c TornadoEngine/src/TE_graphics.c TornadoEngine/src/TE_math.c TornadoEngine/src/TE_ecs.c TornadoEngine/src/TE_ui.c  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
ar rvs TornadoEngine/lib/TornadoEngine.a TE_main.o TE_graphics.o TE_math.o TE_ecs.o TE_ui.o
rm TE_main.o TE_graphics.o TE_math.o TE_ecs.o TE_ui.o