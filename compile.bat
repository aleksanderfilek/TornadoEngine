@echo off
g++ -Iinc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib game/main.cpp game/player.cpp game/level.cpp src/TE.cpp src/TE_graphics.cpp src/TE_math.cpp -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglew32 -o main
pause 