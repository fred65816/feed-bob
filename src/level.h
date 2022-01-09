#ifndef LEVEL_H
#define LEVEL_H

#include "sdl.h"
#include "constants.h"
#include "tile.h"
#include "tile_array.h"
#include <stdbool.h>

struct Level {
    struct Tile *tilemap[LEVEL_NUM_COLS][LEVEL_NUM_ROWS];   // The level tilemap
    SDL_Texture *texture;                                   // The level texture
    SDL_Renderer *renderer;                                 // The renderer
};

/**
 * Creates a level instance.
 *
 * @param renderer           The renderer
 * @return                   The level
 */
struct Level *Level_create(SDL_Renderer *renderer);

/**
 * Renders the level.
 *
 * @param level             The level to render
 */
void Level_render(struct Level *level);

/**
 * Set the alpha value of the level tilemap.
 *
 * @param level                The level
 * @param value                The alpha value
 */
void Level_setAlphaMod(struct Level *level, int value);

/**
 * Delete the level.
 *
 * @param level             The level
 */
void Level_delete(struct Level *level);

/**
 * Gets the tiles of an entity of size r.
 *
 * @param array             The tile array
 * @param level             The level
 * @param renderer          The position and size of the entity
 */
void Level_getEntityTiles(struct TileArray *array, 
                          struct Level *level, 
                          SDL_Rect *r);

/**
 * Gets the floor tiles of an entity of size r.
 *
 * @param array             The tile array
 * @param level             The level
 * @param renderer          The position and size of the entity
 */
void Level_getFloorTiles(struct TileArray *array, 
                         struct Level *level, 
                         SDL_Rect *r) ;

#endif