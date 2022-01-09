#include "tile_array.h"
#include "constants.h"

struct TileArray *TileArray_init() {
    struct TileArray *array;
    array = malloc(sizeof(struct TileArray));
    array->elements = malloc(sizeof(struct Tile));
    array->currentSize = 0;
    array->capacity = 1;
    return array;
}

bool TileArray_add(struct TileArray *array, struct Tile element) {
    if (array->currentSize == array->capacity) {
        array->capacity *= 2;
        struct Tile *tmp = realloc(array->elements, array->capacity * sizeof(struct Tile));
        if(!tmp) {
            TileArray_delete(array);
            array = NULL;
            fprintf(stderr, "Failed to resize TileArray\n");
            return false;
        } else {
            array->elements = tmp;
        }
    }

    array->elements[array->currentSize].x = element.x;
    array->elements[array->currentSize].y = element.y;
    array->elements[array->currentSize].solid = element.solid;
    array->elements[array->currentSize].rect.x = element.x * TILE_WIDTH;
    array->elements[array->currentSize].rect.y = element.y * TILE_HEIGHT;
    array->elements[array->currentSize].rect.w = TILE_WIDTH;
    array->elements[array->currentSize].rect.h = TILE_HEIGHT;
    array->currentSize++;
    return true;
}

void TileArray_delete(struct TileArray *array) {
    if(array != NULL) {
        free(array->elements);
        free(array);
    }
}
