CFLAGS=-g $(shell sdl2-config --cflags) -I/opt/local/include -mwindows
CXXFLAGS=$(shell sdl2-config --cflags) -I/opt/local/include -mwindows
LIBS=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
OBJ=actor.o dragon.o game.o main.o player.o sound.o font.o notice.o sprite.o bullet.o
CC=x86_64-w64-mingw32-gcc
CXX=x86_64-w64-mingw32-g++
LD=x86_64-w64-mingw32-g++

dragonbattle: $(OBJ)
	$(LD) -o dragonbattle $(OBJ) $(LIBS)

clean:
	-rm $(OBJ)

