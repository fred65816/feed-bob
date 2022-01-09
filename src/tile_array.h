#ifndef TILE_ARRAY_H
#define TILE_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"

struct TileArray {
    struct Tile *elements;          // The tiles of the tile array
    int currentSize;                // Current size in tile number
    int capacity;                   // Maximum capacity of the array
};

/**
 * Creates a tile array instance.
 *
 * @return                   The tile array
 */
struct TileArray *TileArray_init();

/**
 * Add a tile to the tile array.
 *
 * @param array              The tile array
 * @param element            The tile to add
 * @return                   True if tile was added
 */
bool TileArray_add(struct TileArray *array, struct Tile element);

/**
 * Delete the tile array.
 *
 * @param array              The tile array
 */
void TileArray_delete(struct TileArray *array);

#endif