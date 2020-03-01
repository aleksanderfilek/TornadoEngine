@echo off
g++ -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib main.cpp TE/lib/TornadoEngine.a -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_mixer -lopengl32 -lglew32 -o main
pause 