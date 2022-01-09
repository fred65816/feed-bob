#ifndef APPLICATION_H
#define APPLICATION_H

#include "sdl.h"
#include "constants.h"
#include "menu.h"
#include "game.h"

enum ApplicationState {
    APPLICATION_STATE_MENU,         // The menu is displayed
    APPLICATION_STATE_PLAY,         // The game is played
    APPLICATION_STATE_QUIT          // The player quit the game
};

struct Application {
    enum ApplicationState state;    // The current game state
    struct Menu *menu;              // The game menu
    struct Game *game;              // The current game
    SDL_Window* window;             // The game window
    SDL_Renderer* renderer;         // The renderer
};

struct Application *Application_initialize();

void Application_run(struct Application *application);

void Application_shutDown(struct Application *application);

void Application_playEnding(struct Application *application, struct Game *game);

#endif