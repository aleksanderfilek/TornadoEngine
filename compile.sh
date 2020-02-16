#!/bin/bash
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_animation.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_audio.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_debug.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_ecs.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_graphics.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_math.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_net.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_physics.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_input.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
ar rs TE/lib/TornadoEngine.a TE.o TE_animation.o TE_audio.o TE_debug.o TE_ecs.o TE_graphics.o TE_math.o TE_net.o TE_physics.o TE_input.o
rm -f 8.o
g++ -ITE/inc main.cpp TE/lib/TornadoEngine.a -o main $(pkg-config --cflags --libs sdl2 glew) -lSDL2_image -lSDL2_net -lSDL2_ttf

