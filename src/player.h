#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "tile.h"
#include "level.h"
#include "sdl.h"
#include "animated_spritesheet.h"

enum PlayerState {
    WALKING_RIGHT               = 0, // The player is walking to the right 
    WALKING_LEFT                = 1, // The player is walking to the left  
    IDLE                        = 2, // The player is idle                 
    JUMPING_STRAIGHT            = 3, // The player is jumping vertically   
    JUMPING_RIGHT               = 4, // The player is jumping to the right
    JUMPING_LEFT                = 5  // The player is jumping to the left
};

enum MoveType {
    SINGLE_CONTINUE             = 0, // Move animation is done once and continue on
                                     // same frame number if previous move was same type.  
    LOOPING_RESTART             = 1, // Move animation loop and animation frame 
                                     // is set to first when starting the move
};

struct PlayerMove {
    enum PlayerState playerState;   // The direction of the move
    enum MoveType type;             // The type of move
    int startTime;                  // The start time
    int endTime;                    // The end time
    int duration;                   // The duration
};

struct Player {
    struct AnimatedSpritesheet *animatedSpritesheet;    // The animated spritesheet
    struct PlayerMove *move;                            // The player current move
    SDL_Rect zone;                                      // The zone to render
    float velocityX;                                    // The X velocity of the player
    float velocityY;                                    // The Y velocity of the player
    int jumpVelocity;                                   // The jump velocity of the player
    int speed;                                          // The speed of the player
    float gravity;                                      // The gravity applied to the player
    bool onFloor;                                       // True if player touch the floor
    bool isCollidedLeft;                                // True if player is against a left wall
    bool isCollidedRight;                               // True if player is against a right wall
    SDL_Rect rect;                                      // The size and position of the player
};

/**
 * Creates a player instance.
 *
 * @param renderer           The renderer
 * @return                   The player
 */
struct Player *Player_create(SDL_Renderer *renderer);

/**
 * Delete the player.
 *
 * @param player            The player
 */
void Player_delete(struct Player *player);

/**
 * Renders the player.
 *
 * @param player            The player to render
 */
void Player_render(struct Player *player);

/**
 * Set the alpha value of the player.
 *
 * @param player               The player
 * @param value                The alpha value
 */
void Player_setAlphaMod(struct Player *player, int value);

/**
 * Makes the player jump.
 *
 * @param player               The player
 */
void Player_jump(struct Player *player);

/**
 * Makes the player stop.
 *
 * @param player               The player
 */
void Player_stop(struct Player *player);

/**
 * Makes the player move left.
 *
 * @param player               The player
 */
void Player_moveLeft(struct Player *player);

/**
 * Makes the player move right.
 *
 * @param player               The player
 */
void Player_moveRight(struct Player *player);

/**
 * Check if there is a collision between two rectangles.
 *
 * @param rectA                The first rectangle
 * @param rectB                The second rectangle
 * @return                     True if there is a collision
 */
bool Player_checkCollision(SDL_Rect *rectA, SDL_Rect *rectB);

/**
 * Check if there are collisions, update the player position and
 * update player move when he touch the floor without pressing a key.
 *
 * @param player               The player
 * @param level                The level
 */
void Player_update(struct Player *player, struct Level *level);

#endif