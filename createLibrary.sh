#!/bin/bash
g++ -c -Iinc src/TornadoEngine.cpp src/Button.cpp src/Mouse.cpp src/Text.cpp src/Texture.cpp src/Timer.cpp -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
ar rvs lib/TornadoEngine.a TornadoEngine.o Button.o Mouse.o Text.o Texture.o Timer.o
rm TornadoEngine.o Button.o Mouse.o Text.o Texture.o Timer.o