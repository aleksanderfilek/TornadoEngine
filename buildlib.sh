gcc -std=c99 -c -Iinclude source/*.c -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
ar rcs -o lib/libTE.a *.o
rm *.o