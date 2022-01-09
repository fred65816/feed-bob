#include "game.h"

float getDelta(uint64_t last);

struct Game *Game_initialize(SDL_Renderer *renderer) {
    struct Game *game;
    game = (struct Game*)malloc(sizeof(struct Game));
    game->renderer = renderer;
    game->level = Level_create(renderer);
    game->donuts = DonutArray_init(renderer);
    DonutArray_add(game->donuts, renderer, DONUT1_X, DONUT1_Y);
    DonutArray_add(game->donuts, renderer, DONUT2_X, DONUT2_Y);
    DonutArray_add(game->donuts, renderer, DONUT3_X, DONUT3_Y);
    DonutArray_add(game->donuts, renderer, DONUT4_X, DONUT4_Y);
    DonutArray_add(game->donuts, renderer, DONUT5_X, DONUT5_Y);
    game->player = Player_create(renderer);
    game->timer = Timer_initialize(renderer, 40);
    game->song = NULL;
    game->state = GAME_PLAY;
    game->audioChannel = -1;
    return game;
}

void Game_delete(struct Game *game) {
    if (game != NULL) {
        Level_delete(game->level);
        DonutArray_delete(game->donuts);
        Player_delete(game->player);
        Timer_delete(game->timer);
        if(game->song != NULL) {
            Mix_FreeMusic(game->song);
        }
        free(game);
    }
}

void Game_run(struct Game *game) {
    SDL_Event e;
    DonutArray_start(game->donuts);
    while (game->state == GAME_PLAY) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                game->state = GAME_QUIT;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        Player_jump(game->player);
                        break;
                    case SDLK_LEFT:
                        Player_moveLeft(game->player);
                        break;
                    case SDLK_RIGHT:
                        Player_moveRight(game->player);
                        break;
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        game->state = GAME_QUIT;
                        break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        Player_stop(game->player);
                        break;
                }
            }
        }

        Player_update(game->player, game->level);
        DonutArray_collide(game->donuts, &game->player->rect);
        Timer_decrease(game->timer);

        SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear(game->renderer);
        Level_render(game->level);
        DonutArray_render(game->donuts);
        Player_render(game->player);
        Timer_render(game->timer);
        SDL_RenderPresent(game->renderer);

        if(game->donuts->remaining == 0) {
            game->state = GAME_WON;
            SDL_Delay(500);
        } else if(Timer_isOver(game->timer)) {
            game->state = GAME_LOST;
        }
    }
}

void Game_playEnding(struct Game *game) {
    int i;
    Player_stop(game->player);
    SDL_RenderClear(game->renderer);
    Level_render(game->level);
    Player_render(game->player);
    SDL_RenderPresent(game->renderer);

    if(game->state == GAME_LOST) {
        game->song = Mix_LoadMUS(LOST_SFX);
    } else {
        game->song = Mix_LoadMUS(FINAL_SONG);
    }
    if(game->song != NULL) {
        game->audioChannel = Mix_PlayMusic(game->song, 0);
        if(game->audioChannel == -1) {
            fprintf(stderr, "Unable to play OGG file: %s\n", Mix_GetError());
        }
    } else {
        fprintf(stderr, "Unable to load OGG file: %s\n", Mix_GetError());
    }

    SDL_Rect fullRect = {0, 0, LEVEL_WIDTH, LEVEL_HEIGHT};
    SDL_Surface *black = SDL_CreateRGBSurface(0, LEVEL_WIDTH, LEVEL_HEIGHT, 32, 0x00, 0x00, 0x00, 0xFF);
    SDL_Texture *blackTexture = SDL_CreateTextureFromSurface(game->renderer, black);
    SDL_SetTextureBlendMode(blackTexture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(black);

    SDL_Texture* mTexture = NULL;
    SDL_Rect textRect;
    if (TTF_WasInit() || TTF_Init() != -1) {
        char *message = game->state == GAME_LOST ? "Sadly you lost..": "You won the game!";
        TTF_Font* font = TTF_OpenFont(FONT, 90);
        int width = 0, height = TTF_FontHeight(font);
        TTF_SizeText(font, message, &width, &height);
        textRect.x = (LEVEL_WIDTH / 2) - (width / 2);
        textRect.y = (LEVEL_HEIGHT / 2) - (height / 2);
        textRect.w = width;
        textRect.h = height;
        SDL_Color foreground = {255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Blended(font, message, foreground);
        mTexture = SDL_CreateTextureFromSurface(game->renderer, surface);
        TTF_CloseFont(font);
        SDL_FreeSurface(surface);
    }

    for(i = 0; i < 255; i+= 2) {
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, blackTexture, NULL, &fullRect);
        Level_setAlphaMod(game->level, 255 - i);
        Level_render(game->level);
        Player_setAlphaMod(game->player, 255 - i);
        Player_render(game->player);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(8);
    }
    for(i = 0; i < 255; i++) {
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, blackTexture, NULL, &fullRect);
        SDL_SetTextureAlphaMod(mTexture, i);
        SDL_RenderCopy(game->renderer, mTexture, NULL, &textRect);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(6);
    }
    for(i = 0; i < 255; i+=2) {
        SDL_RenderClear(game->renderer);
        SDL_RenderCopy(game->renderer, blackTexture, NULL, &fullRect);
        SDL_SetTextureAlphaMod(mTexture, 255 - i);
        SDL_RenderCopy(game->renderer, mTexture, NULL, &textRect);
        SDL_RenderPresent(game->renderer);
        SDL_Delay(2);
    }

    SDL_DestroyTexture(blackTexture);
    if(mTexture != NULL) SDL_DestroyTexture(mTexture);
}