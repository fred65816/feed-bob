#include "spritesheet.h"

struct Spritesheet *Spritesheet_create(const char *filename,
                                       int numRows,
                                       int numColumns,
                                       int numSprites,
                                       SDL_Renderer* renderer) {
    struct Spritesheet *spritesheet;
    spritesheet = (struct Spritesheet*)malloc(sizeof(struct Spritesheet));
    spritesheet->numRows = numRows;
    spritesheet->numColumns = numColumns;
    spritesheet->numSprites = numSprites;
    spritesheet->scale = 1.0;
    spritesheet->texture = NULL;
    spritesheet->renderer = renderer;
    SDL_Surface *loadedSurface = IMG_Load(filename);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s: %s\n",
               filename, IMG_GetError());
    } else {
        spritesheet->texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (spritesheet->texture == NULL) {
            printf("Unable to create texture from %s: %s\n",
                   filename, SDL_GetError());
        }
        SDL_SetTextureBlendMode(spritesheet->texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(spritesheet->texture, 255);
        spritesheet->spriteWidth = loadedSurface->w / numColumns;
        spritesheet->spriteHeight = loadedSurface->h / numRows;
        SDL_FreeSurface(loadedSurface);
    }
    return spritesheet;
}

void Spritesheet_delete(struct Spritesheet *spritesheet) {
    SDL_DestroyTexture(spritesheet->texture);
    free(spritesheet);
}

void Spritesheet_render(struct Spritesheet *spritesheet,
                        int x, int y, int sprite) {
    int srcx = spritesheet->spriteWidth * (sprite % spritesheet->numColumns);
    int srcy = spritesheet->spriteHeight * (sprite / spritesheet->numColumns);
    SDL_Rect srcrect = {srcx, srcy, spritesheet->spriteWidth, spritesheet->spriteHeight};
    SDL_Rect dstrect = {x, y, (int)(spritesheet->scale * spritesheet->spriteWidth),
                              (int)(spritesheet->scale * spritesheet->spriteHeight)};
    SDL_RenderCopy(spritesheet->renderer, spritesheet->texture, &srcrect, &dstrect);
}

void Spritesheet_renderZone(struct Spritesheet *spritesheet, SDL_Rect *zone, int x, int y, int sprite) {
    int srcx = spritesheet->spriteWidth * (sprite % spritesheet->numColumns) + zone->x;
    int srcy = spritesheet->spriteHeight * (sprite / spritesheet->numColumns) + zone->y;
    SDL_Rect srcrect = {srcx, srcy, zone->w, zone->h};
    SDL_Rect dstrect = {x, y, (int)(spritesheet->scale * zone->w),
                              (int)(spritesheet->scale * zone->h)};
    SDL_RenderCopy(spritesheet->renderer, spritesheet->texture, &srcrect, &dstrect);
}

void Spritesheet_setAlphaMod(struct Spritesheet *spritesheet, int value) {
    SDL_SetTextureAlphaMod(spritesheet->texture, value);
}