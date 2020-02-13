@echo off
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_animation.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_audio.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_debug.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_ecs.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_graphics.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_math.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_net.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
g++ -c -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib TE/src/TE_physics.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32
ar rs TE/lib/TornadoEngine.a TE.o TE_animation.o TE_audio.o TE_debug.o TE_ecs.o TE_graphics.o TE_math.o TE_net.o TE_physics.o
del *.o
pause