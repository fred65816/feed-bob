#include "tile.h"
#include "constants.h"

struct Tile *Tile_create(int x, int y, bool solid) {
    struct Tile *tile;
    tile = (struct Tile*)malloc(sizeof(struct Tile));
    tile->x = x;
    tile->y = y;
    tile->solid = solid;
    tile->rect.x = x * TILE_WIDTH;
    tile->rect.y = y * TILE_HEIGHT;
    tile->rect.w = TILE_WIDTH;
    tile->rect.h = TILE_HEIGHT;
    return tile;
}

void Tile_delete(struct Tile *tile) {
    if (tile != NULL) {
        free(tile);
    }
}