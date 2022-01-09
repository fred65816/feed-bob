#include "donut_array.h"

struct DonutArray *DonutArray_init() {
    struct DonutArray *array;
    array = malloc(sizeof(struct DonutArray));
    array->elements = malloc(sizeof(struct Donut));
    array->currentSize = 0;
    array->remaining = 0;
    array->capacity = 1;
    array->zone.x = DONUT_ZONE_X;
    array->zone.y = DONUT_ZONE_Y;
    array->zone.w = DONUT_ZONE_WIDTH;
    array->zone.h = DONUT_ZONE_HEIGHT;
    array->audioChannel = -1;
    array->sound = NULL;
    array->sound = Mix_LoadMUS(DONUT_SFX);
    if(array->sound == NULL) {
        fprintf(stderr, "Unable to load OGG file: %s\n", Mix_GetError());
    }
    return array;
}

bool DonutArray_add(struct DonutArray *array, SDL_Renderer *renderer, int x, int y) {
    if (array->currentSize == array->capacity) {
        array->capacity *= 2;
        struct Donut *tmp = realloc(array->elements, array->capacity * sizeof(struct Donut));
        if(!tmp) {
            array->capacity /= 2;
            fprintf(stderr, "Failed to resize DonutArray\n");
            return false;
        } else {
            array->elements = tmp;
        }
    }
    array->elements[array->currentSize].x = x;
    array->elements[array->currentSize].y = y;
    array->elements[array->currentSize].render = true;
    array->elements[array->currentSize].found = false;
    array->elements[array->currentSize].rect.x = x;
    array->elements[array->currentSize].rect.y = y;
    array->elements[array->currentSize].rect.w = DONUT_SCALE_WIDTH;
    array->elements[array->currentSize].rect.h = DONUT_SCALE_HEIGHT;
    array->elements[array->currentSize].animatedSpritesheet = 
        AnimatedSpritesheet_create(DONUT_FILENAME, DONUT_NUM_MOVES, DONUT_NUM_FRAMES,
            DONUT_TOTAL_FRAMES, DONUT_BETWEEN_FRAME, renderer);
    array->elements[array->currentSize].animatedSpritesheet->spritesheet->scale = DONUT_SCALE;
    array->currentSize++;
    array->remaining++;
    return true;
}

void DonutArray_start(struct DonutArray *array) {
    int i;
    for(i = 0; i < array->currentSize && array->remaining > 0; i++) {
        AnimatedSpritesheet_run(array->elements[i].animatedSpritesheet);
    }
}

void DonutArray_render(struct DonutArray *array) {
    int i;
    for(i = 0; i < array->currentSize && array->remaining > 0; i++) {
        if(array->elements[i].render) {
            AnimatedSpritesheet_renderZone(array->elements[i].animatedSpritesheet,
                &array->zone, array->elements[i].rect.x, array->elements[i].rect.y);
        }
        
    }
}

void DonutArray_collide(struct DonutArray *array, SDL_Rect *rectangle) {
    int i;
    for(i = 0; i < array->currentSize && array->remaining > 0; i++) {
        if(array->elements[i].render) {
            if(Player_checkCollision(&array->elements[i].rect, rectangle) && !array->elements[i].found) {
                array->elements[i].found = true;
                DonutArray_playAudio(array);
            }
        }
        if (array->elements[i].found) {
            Uint8 alpha = 0;
            SDL_GetTextureAlphaMod(array->elements[i].animatedSpritesheet->spritesheet->texture, &alpha);
            alpha = alpha < 12 ? 0: alpha - 12;
            AnimatedSpritesheet_setAlphaMod(array->elements[i].animatedSpritesheet, alpha);
            if(alpha == 0) {
                array->elements[i].render = false;
                array->elements[i].found = false;
                array->remaining--;
            }

        }
    }
}

void DonutArray_delete(struct DonutArray *array) {
    int i;
    for(i = 0; i < array->currentSize; i++) {
        AnimatedSpritesheet_delete(array->elements[i].animatedSpritesheet);
    }
    Mix_FreeMusic(array->sound);
    free(array->elements);
    free(array);
}

void DonutArray_playAudio(struct DonutArray *array) {
    if(array->sound != NULL) {
        array->audioChannel = Mix_PlayMusic(array->sound, 0);
        if(array->audioChannel == -1) {
            fprintf(stderr, "Unable to play OGG file: %s\n", Mix_GetError());
        }
    }
}