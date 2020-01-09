#!/bin/bash
<<<<<<< Updated upstream
g++ -Iinc main.cpp src/TE_main.cpp src/TE_graphics.cpp -o main $(pkg-config --cflags --libs sdl2 glew) -lSDL2_image
=======
gcc -ITornadoEngine/include -ISDL/include main.c TornadoEngine/src/TE_main.c TornadoEngine/src/TE_graphics.c TornadoEngine/src/TE_math.c TornadoEngine/src/TE_ui.c  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -o main
>>>>>>> Stashed changes
