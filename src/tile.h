#ifndef TILE_H
#define TILE_H

#include <stdbool.h>
#include "sdl.h"

struct Tile {
    int x;          // The tile X position (in tile number)
    int y;          // The tile Y position (in tile number)
    bool solid;     // True if tile is a wall tile
    SDL_Rect rect;  // The tile position and size (in pixels)
};

/**
 * Creates a tile instance.
 *
 * @param x                 The X position
 * @param y                 The Y position
 * @param solid             The solidity value
 * @return                  The tile
 */
struct Tile *Tile_create(int x, int y, bool solid);

/**
 * Delete the tile.
 *
 * @param tile              The tile
 */
void Tile_delete(struct Tile *tile);

#endif