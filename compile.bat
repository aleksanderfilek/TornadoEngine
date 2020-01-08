@echo off
g++ -c -Iinc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib src/TE.cpp src/TE_graphics.cpp -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglew32
ar rcs lib/libte.a TE.o TE_graphics.o
g++ -Iinc -IGLEW\include -ISDL/include -LGLEW\lib -LSDL/lib main.cpp lib/libte.a -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglew32 -o main
pause 