#!/bin/bash

sh lib.sh

gcc -std=c99 -Iinclude -Llib main.c -lTE -lSDL2main -lSDL2  -lSOIL -lGLEW -lGLU -lGL -lm
