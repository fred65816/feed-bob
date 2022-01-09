#include "animated_spritesheet.h"

struct AnimatedSpritesheet *AnimatedSpritesheet_create(const char *filename,
                                                       int numRows,
                                                       int numColumns,
                                                       int numSprites,
                                                       int delayBetweenFrame,
                                                       SDL_Renderer* renderer) {
    struct AnimatedSpritesheet *as;
    as = (struct AnimatedSpritesheet*)malloc(sizeof(struct AnimatedSpritesheet));
    as->spritesheet = Spritesheet_create(filename, numRows, numColumns,
        numSprites, renderer);
    as->currentRow = 0;
    as->currentColumn = 0;
    as->delayBetweenFrame = delayBetweenFrame;
    as->lastUpdate = -1;
    as->running = false;
    return as;
}

void AnimatedSpritesheet_delete(struct AnimatedSpritesheet *animatedSpritesheet) {
    if (animatedSpritesheet != NULL) {
        Spritesheet_delete(animatedSpritesheet->spritesheet);
        free(animatedSpritesheet);
    }
}

void AnimatedSpritesheet_setRow(struct AnimatedSpritesheet *animatedSpritesheet,
                                int rowNumber, int moveType) {
    if(moveType) {
        animatedSpritesheet->currentColumn = 0;
    }
    animatedSpritesheet->currentRow = rowNumber;
    animatedSpritesheet->lastUpdate = SDL_GetTicks();
}

void AnimatedSpritesheet_run(struct AnimatedSpritesheet *animatedSpritesheet) {
    animatedSpritesheet->running = true;
}

void AnimatedSpritesheet_stop(struct AnimatedSpritesheet *animatedSpritesheet) {
    animatedSpritesheet->running = false;
}

void AnimatedSpritesheet_renderZone(struct AnimatedSpritesheet *animatedSpritesheet,
                                    SDL_Rect *zone, int x, int y) {
    int elapsed;
    if (animatedSpritesheet->running) {
        elapsed = SDL_GetTicks() - animatedSpritesheet->lastUpdate;
    } else {
        elapsed = 0;
    }
    if (elapsed > animatedSpritesheet->delayBetweenFrame) {
        int f = elapsed / animatedSpritesheet->delayBetweenFrame;
        animatedSpritesheet->currentColumn =
            (animatedSpritesheet->currentColumn + f) %
             animatedSpritesheet->spritesheet->numColumns;
        animatedSpritesheet->lastUpdate += elapsed;
    }
    int currentFrame = animatedSpritesheet->currentRow *
                       animatedSpritesheet->spritesheet->numColumns +
                       animatedSpritesheet->currentColumn;
    Spritesheet_renderZone(animatedSpritesheet->spritesheet, zone,
        x, y, currentFrame);
}

void AnimatedSpritesheet_setAlphaMod(struct AnimatedSpritesheet *animatedSpritesheet, int value) {
   Spritesheet_setAlphaMod(animatedSpritesheet->spritesheet, value);
}

