CC = gcc
CFLAGS = -Wall -g -std=c11
SDL_CFLAGS = `sdl2-config --cflags`
SDL_LIBS = -lSDL2_image -lSDL2_ttf -lSDL2_mixer `sdl2-config --libs`
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
EXEC = game

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(SDL_LIBS) -o $(EXEC)

%.o: %.c %.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -rf $(EXEC)