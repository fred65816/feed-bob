#ifndef MENU_H
#define MENU_H

#include "sdl.h"
#include "constants.h"
#include <stdbool.h>

enum MenuChoice {
    MENU_NONE,                      // The user has made no choice
    MENU_QUIT,                      // The user wants to quit the game
    MENU_PLAY                       // The user wants to play
};

struct Menu {
    enum MenuChoice choice;         // The user's final choice
    enum MenuChoice temp_choice;    // The user's temporary choice
    struct Spritesheet *title;      // The title spritesheet
    struct Spritesheet *play;       // The play option spritesheet
    struct Spritesheet *quit;       // The quit option spritesheet
    SDL_Renderer *renderer;         // The renderer
};

/**
 * Creates a menu.
 *
 * @param renderer           The renderer
 * @return                   The menu
 */
struct Menu *Menu_initialize(SDL_Renderer *renderer);

/**
 * Starts the menu.
 *
 * @param menu              The menu
 */
void Menu_run(struct Menu *menu);

/**
 * Delete the menu.
 *
 * @param menu              The menu
 */
void Menu_delete(struct Menu *menu);

#endif
