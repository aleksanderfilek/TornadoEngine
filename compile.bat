@echo off
g++ -ITE/inc -ISDL/include -LSDL/lib -IGLEW\include -LGLEW\lib client.cpp TE/src/TE.cpp TE/src/TE_graphics.cpp TE/src/TE_math.cpp TE/src/TE_audio.cpp TE/src/TE_debug.cpp TE/src/TE_ecs.cpp TE/src/TE_net.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lopengl32 -lglew32 -o client
pause 