@echo off
gcc -ITornadoEngine/include -ISDL/include -LSDL/lib  main.c TornadoEngine/src/TE_main.c TornadoEngine/src/TE_graphics.c TornadoEngine/src/TE_math.c TornadoEngine/src/TE_ui.c -static-libgcc -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm -o main