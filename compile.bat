@echo off
g++ -Iinc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib main.cpp src/TE.cpp src/TE_graphics.cpp -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglew32 -o main
pause 