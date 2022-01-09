#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "sdl.h"

struct Spritesheet {
    int numRows;                // The number of rows of the spritesheet
    int numColumns;             // The number of columns of the spritesheet
    int numSprites;             // The total number of sprites
    int spriteWidth;            // The width of a sprite
    int spriteHeight;           // The height of a sprite
    float scale;                // The scale of a sprite
    SDL_Texture *texture;       // The spritesheet texture
    SDL_Renderer *renderer;     // The renderer
};

struct Spritesheet *Spritesheet_create(const char *filename,
                                       int numRows, 
                                       int numColumns,
                                       int numSprites,
                                       SDL_Renderer* renderer);

void Spritesheet_delete(struct Spritesheet *spritesheet);

void Spritesheet_render(struct Spritesheet *spritesheet,
                        int x, int y, int sprite);

void Spritesheet_renderZone(struct Spritesheet *spritesheet, SDL_Rect *zone, int x, int y, int sprite);

void Spritesheet_setAlphaMod(struct Spritesheet *spritesheet, int value);

#endif
