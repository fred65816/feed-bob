#include "player.h"
#include "tile_array.h"
#include "sdl.h"

void applyGravity(struct Player *player);
bool checkCollision(struct Player *player, struct Level *level);
bool touchFloor(struct Player *player, struct Level *level);
void updateMove(struct Player *player, enum PlayerState playerState, enum MoveType type);

// ----------------- //
// Fonctions privées //
// ----------------- //

void applyGravity(struct Player *player) {
    player->velocityY += player->gravity;
}

bool checkCollision(struct Player *player, struct Level *level) {
    int i;
    bool collision = false;
    struct TileArray *array = TileArray_init();
    Level_getEntityTiles(array, level, &player->rect);

    if(array != NULL) {
        for(i = 0; i < array->currentSize && !collision; i++) {
            if(array->elements[i].solid) {
                if(Player_checkCollision(&array->elements[i].rect, &player->rect)) {
                    collision = true;
                }
            }
        }
        TileArray_delete(array);
    } else {
        collision = true;
    }
    return collision;

}

bool touchFloor(struct Player *player, struct Level *level) {
    int i;
    bool collision = false;

    player->rect.y += 1;
    struct TileArray *array = TileArray_init();
    Level_getFloorTiles(array, level, &player->rect);

    if(array != NULL) {
        for(i = 0; i < array->currentSize && !collision; i++) {
            if(array->elements[i].solid) {
                if(Player_checkCollision(&array->elements[i].rect, &player->rect)) {
                    collision = true;
                }
            }
        }
        TileArray_delete(array);
    } else {
        collision = true;
    }
    
    player->rect.y -= 1;
    return collision;
}

void updateMove(struct Player *player, enum PlayerState playerState, enum MoveType type) {
    player->move->playerState = playerState;
    if(!(player->move->type == SINGLE_CONTINUE || type == SINGLE_CONTINUE)) {
        player->move->startTime = SDL_GetTicks();
        player->move->endTime = player->move->startTime + player->move->duration;
    }
    player->move->type = type;
    AnimatedSpritesheet_setRow(player->animatedSpritesheet, playerState, type);
    AnimatedSpritesheet_run(player->animatedSpritesheet);
}

// ------------------- //
// Fonctions publiques //
// ------------------- //

struct Player *Player_create(SDL_Renderer *renderer) {
    struct Player *player;
    player = (struct Player*)malloc(sizeof(struct Player));
    player->move = (struct PlayerMove*)malloc(sizeof(struct PlayerMove));
    player->move->playerState = IDLE;
    player->move->type = LOOPING_RESTART;
    player->move->duration = PLAYER_MOVE_DURATION;
    player->zone.x = PLAYER_ZONE_X;
    player->zone.y = PLAYER_ZONE_Y;
    player->zone.w = PLAYER_ZONE_WIDTH;
    player->zone.h = PLAYER_ZONE_HEIGHT;
    player->velocityX = 0;
    player->velocityY = 0;
    player->jumpVelocity = PLAYER_JUMP_VELOCITY;
    player->speed = PLAYER_SPEED;
    player->gravity = GAME_GRAVITY;
    player->onFloor = false;
    player->isCollidedLeft = false;
    player->isCollidedRight = false;
    int scaledWidth = (int)(PLAYER_ZONE_WIDTH *  PLAYER_SCALE);
    scaledWidth += TILE_WIDTH - (scaledWidth % TILE_WIDTH);
    int scaledHeight = (int)(PLAYER_ZONE_HEIGHT *  PLAYER_SCALE);
    scaledHeight += TILE_HEIGHT - (scaledHeight % TILE_HEIGHT);
    player->rect.x = LEVEL_INIT_X;
    player->rect.y = LEVEL_INIT_Y;
    player->rect.w = scaledWidth;
    player->rect.h = scaledHeight;
    player->animatedSpritesheet =
        AnimatedSpritesheet_create(PLAYER_FILENAME, PLAYER_NUM_MOVES, PLAYER_NUM_FRAMES, 
            PLAYER_TOTAL_FRAMES, PLAYER_BETWEEN_FRAME, renderer);
    player->animatedSpritesheet->spritesheet->scale = PLAYER_SCALE;
    return player;
}

void Player_delete(struct Player *player) {
    if (player != NULL) {
        AnimatedSpritesheet_delete(player->animatedSpritesheet);
        free(player->move);
        free(player);
    }
}

void Player_render(struct Player *player) {
    if(player->move->type == SINGLE_CONTINUE) {
        int now = SDL_GetTicks();
        if (now > player->move->endTime) {
            AnimatedSpritesheet_stop(player->animatedSpritesheet);
        }    
    }
    AnimatedSpritesheet_renderZone(player->animatedSpritesheet, &player->zone,
                               player->rect.x,
                               player->rect.y);
}

void Player_setAlphaMod(struct Player *player, int value) {
    AnimatedSpritesheet_setAlphaMod(player->animatedSpritesheet, value);
}

void Player_jump(struct Player *player) {
    if(player->onFloor) {
        player->velocityY = -player->jumpVelocity;
        if(player->velocityX < 0) {
            updateMove(player, JUMPING_LEFT, LOOPING_RESTART);
        } else if (player->velocityX > 0) {
            updateMove(player, JUMPING_RIGHT, LOOPING_RESTART);
        } else {
            updateMove(player, JUMPING_STRAIGHT, LOOPING_RESTART);
        }
    }
}

void Player_stop(struct Player *player) {
    if(player->onFloor) {
        updateMove(player, IDLE, LOOPING_RESTART);
    }
    player->velocityX = 0;

}

void Player_moveLeft(struct Player *player) {
    player->velocityX = -player->speed;
    if(player->onFloor && player->move->playerState != WALKING_LEFT) {
        updateMove(player, WALKING_LEFT, LOOPING_RESTART);
    } else if(!player->onFloor && player->move->playerState != JUMPING_LEFT) {
        updateMove(player, JUMPING_LEFT, SINGLE_CONTINUE);
    }
}

void Player_moveRight(struct Player *player) {
    player->velocityX = player->speed;
    if(player->onFloor && player->move->playerState != WALKING_RIGHT) {
        updateMove(player, WALKING_RIGHT, LOOPING_RESTART);
    } else if(!player->onFloor && player->move->playerState != JUMPING_RIGHT) {
        updateMove(player, JUMPING_RIGHT, SINGLE_CONTINUE);
    }
}

bool Player_checkCollision(SDL_Rect *rectA, SDL_Rect *rectB) {
    return (rectB->x < rectA->x + rectA->w &&
             rectB->x + rectB->w > rectA->x &&
             rectB->y < rectA->y + rectA->h &&
             rectB->y + rectB->h > rectA->y);
}

void Player_update(struct Player *player, struct Level *level) {
    float moveX, moveY;

    player->onFloor = touchFloor(player, level);
    
    if (!player->onFloor || player->velocityY < 0) {
        applyGravity(player);
    } else if (player->velocityX < 0 && player->move->playerState == JUMPING_LEFT) {
        updateMove(player, WALKING_LEFT, LOOPING_RESTART);
    } else if (player->velocityX > 0 && player->move->playerState == JUMPING_RIGHT) {
        updateMove(player, WALKING_RIGHT, LOOPING_RESTART);
    } else if (player->velocityX == 0 && !player->isCollidedRight && !player->isCollidedLeft) {
        updateMove(player, IDLE, LOOPING_RESTART);
    }

    moveX = (int)player->velocityX;
    moveY = (int)player->velocityY;

    while (moveX != 0 || moveY != 0) {
        if (moveX > 0) {
            moveX--;
            player->rect.x += 1;
            if(checkCollision(player, level)){
                player->rect.x -= 1;
                player->velocityX = 0;
                moveX = 0;
                player->isCollidedRight = true;
            } else {
                player->isCollidedRight = false;
            }         
        } else if (moveX < 0) {
            moveX++;
            player->rect.x -= 1;
            if(checkCollision(player, level)){
                player->rect.x += 1;
                player->velocityX = 0;
                moveX = 0;
                player->isCollidedLeft = true;
            } else {
                player->isCollidedRight = false;
            }
        }

        if (moveY > 0){
            moveY--;
            player->rect.y += 1;
            if(checkCollision(player, level)){
                player->rect.y -= 1;
                player->velocityY = 0;
                moveY = 0;
            }
        } else if (moveY < 0) {
            moveY++;
            player->rect.y -= 1;
            if(checkCollision(player, level)){
                player->rect.y += 1;
                player->velocityY = 0;
                moveY = 0;
            }
        }
    }
}