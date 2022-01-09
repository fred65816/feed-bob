#ifndef GAME_H
#define GAME_H

#include "sdl.h"
#include "level.h"
#include "constants.h"
#include "donut_array.h"
#include "player.h"
#include "timer.h"

enum GameState {
    GAME_PLAY,                  // The player play
    GAME_MENU,                  // The player return to the menu
    GAME_QUIT,                  // The player quit the game
    GAME_WON,                   // The player won the game
    GAME_LOST                   // The player lost the game
};

struct Game {
    struct Level *level;        // The level
    struct Player *player;      // The player
    struct DonutArray *donuts;  // The level donuts
    struct Timer *timer;        // The level timer
    SDL_Renderer *renderer;     // The renderer
    enum GameState state;       // The state of the game
    Mix_Music *song;            // The ending song
    int audioChannel;           // The audio channel of the ending song
};

/**
 * Creates a game instance.
 *
 * @param renderer           The renderer
 * @return                   The game
 */
struct Game *Game_initialize(SDL_Renderer *renderer);

/**
 * Delete the game.
 *
 * @param game               The game
 */
void Game_delete(struct Game *game);

/**
 * Run the game (main game loop).
 *
 * @param game               The game
 */
void Game_run(struct Game *game);

/**
 * Play the game ending.
 *
 * @param game                The game
 */
void Game_playEnding(struct Game *game);

#endif