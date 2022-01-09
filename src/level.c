#include "level.h"
#include "tile_array.h"
#include <assert.h>

void generateTexture(struct Level *level);

// ----------------- //
// Private functions //
// ----------------- //

void generateTexture(struct Level *level) {
    FILE *tilemapFile;
    tilemapFile = fopen(LEVEL_FILENAME, "r");
    if (tilemapFile) {
        int x, y;
        level->texture = SDL_CreateTexture(level->renderer,
                         SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                         LEVEL_WIDTH, LEVEL_HEIGHT);
        SDL_SetTextureBlendMode(level->texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(level->texture, 255);
        SDL_SetRenderTarget(level->renderer, level->texture);
        SDL_RenderClear(level->renderer);
        SDL_Surface *wallSurface = IMG_Load(TILE_WALL);
        SDL_Surface *bgSurface = IMG_Load(TILE_BG);
        SDL_Texture *wallTexture = SDL_CreateTextureFromSurface(level->renderer, wallSurface);
        SDL_Texture *bgTexture = SDL_CreateTextureFromSurface(level->renderer, bgSurface);
        SDL_Rect srcrect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
        SDL_Rect dstrect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

        for (y = 0; y < LEVEL_NUM_ROWS; y++) {
            for (x = 0; x < LEVEL_NUM_COLS; x++) {
                dstrect.x = TILE_WIDTH * x;
                dstrect.y = TILE_HEIGHT * y;
                char c = getc(tilemapFile);
                if(c == '\n') {
                    c = getc(tilemapFile);
                }
                if (c == WALL_CHAR) {
                    level->tilemap[x][y] = Tile_create(x, y, true);
                    SDL_RenderCopy(level->renderer, wallTexture, &srcrect, &dstrect);
                } else if (c == BG_CHAR) {
                    level->tilemap[x][y] = Tile_create(x, y, false);
                    SDL_RenderCopy(level->renderer, bgTexture, &srcrect, &dstrect);
                } else {
                    fprintf(stderr, "Invalid tilemap character: \'%c\'\n", c);
                }
            }
        }
        fclose(tilemapFile);   
        SDL_SetRenderTarget(level->renderer, NULL);
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyTexture(bgTexture);
        SDL_FreeSurface(wallSurface);
        SDL_FreeSurface(bgSurface);
    } else {
        fprintf(stderr, "Unable to load tilemap file \"%s\"\n", LEVEL_FILENAME);
    }
}

// ---------------- //
// Public functions //
// ---------------- //

struct Level *Level_create(SDL_Renderer *renderer) {
    struct Level *level;
    level = (struct Level*)malloc(sizeof(struct Level));
    level->renderer = renderer;
    generateTexture(level);
    return level;
}

void Level_render(struct Level *level) {
    SDL_RenderCopy(level->renderer, level->texture, NULL, NULL);
}

void Level_setAlphaMod(struct Level *level, int value) {
    SDL_SetTextureAlphaMod(level->texture, value);
}

void Level_delete(struct Level *level) {
    int x, y;
    if (level != NULL) {
        SDL_DestroyTexture(level->texture);
        for (y = 0; y < LEVEL_NUM_ROWS; y++) {
            for (x = 0; x < LEVEL_NUM_COLS; x++) {
                Tile_delete(level->tilemap[x][y]);
            }
        }
        free(level);
    }
}

void Level_getEntityTiles(struct TileArray *array, struct Level *level, SDL_Rect *r) {
    int i, j;
    for (i = r->x; i <= r->x + r->w; i += TILE_WIDTH) {
        for (j = r->y; j <= r->y + r->h; j += TILE_HEIGHT) {
            if(array != NULL) {
                TileArray_add(array, *(level->tilemap[i / TILE_WIDTH][j / TILE_HEIGHT]));
            }
        }
    }
}

void Level_getFloorTiles(struct TileArray *array, struct Level *level, SDL_Rect *r) {
    int i;
    for(i = r->x; i <= r->x + r->w; i += TILE_WIDTH) {
        if(array != NULL) {
            TileArray_add(array, *(level->tilemap[i / TILE_WIDTH][(r->y + r->h) / TILE_HEIGHT]));
        }
    }
}