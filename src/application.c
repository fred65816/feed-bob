#include "application.h"
#include "sdl.h"
#include <stdio.h>

struct Application *Application_initialize() {
    struct Application *application;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return NULL;
    }
    if(Mix_OpenAudio(SAMPLE_RATE, AUDIO_TYPE, CHANNELS, AUDIO_BUFFER) != 0) {  
        fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
    }
    if(TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());

    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        fprintf(stderr, "Warning: Linear texture filtering not enabled!");
    }
    application = (struct Application*)malloc(sizeof(struct Application));
    application->window = SDL_CreateWindow("Feed Bob",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        LEVEL_WIDTH, LEVEL_HEIGHT, SDL_WINDOW_SHOWN);
    if (application->window == NULL) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    application->renderer = SDL_CreateRenderer(application->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (application->renderer == NULL) {
        fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_SetRenderDrawColor(application->renderer, 0x00, 0x00, 0x00, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        fprintf(stderr, "SDL_image failed to initialize: %s\n", IMG_GetError());
        return NULL;
    }
    application->menu = Menu_initialize(application->renderer);
    if (application->menu == NULL) {
        fprintf(stderr, "Failed to initialize menu: %s\n", IMG_GetError());
        return NULL;
    }
    application->state = APPLICATION_STATE_MENU;
    return application;
}

void Application_run(struct Application *application) {
    while (application->state != APPLICATION_STATE_QUIT) {
        switch (application->state) {
            case APPLICATION_STATE_MENU:
                Menu_run(application->menu);
                if (application->menu->choice == MENU_QUIT) {
                    application->state = APPLICATION_STATE_QUIT;
                } else if (application->menu->choice == MENU_PLAY) {
                    application->state = APPLICATION_STATE_PLAY;
                }
                break;
            case APPLICATION_STATE_PLAY:
                application->game = Game_initialize(application->renderer);
                if (application->game == NULL) {
                    fprintf(stderr, "Failed to initialize game: %s\n", IMG_GetError());
                    application->state = APPLICATION_STATE_QUIT;
                } else {
                    Game_run(application->game);
                    if (application->game->state == GAME_QUIT) {
                        application->state = APPLICATION_STATE_QUIT;
                    } else if(application->game->state == GAME_WON ||
                        application->game->state == GAME_LOST) {
                        Game_playEnding(application->game);
                        application->state = APPLICATION_STATE_MENU;
                        application->menu->choice = MENU_NONE;
                    }
                }
                break;
            case APPLICATION_STATE_QUIT:
                break;
        }
    }
}

void Application_shutDown(struct Application *application) {
    SDL_DestroyRenderer(application->renderer);
    SDL_DestroyWindow(application->window);
    Menu_delete(application->menu);
    Game_delete(application->game);
    free(application);
    Mix_CloseAudio();
    TTF_Quit();
    application = NULL;
    IMG_Quit();
    SDL_Quit();
}
