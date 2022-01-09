#include "menu.h"
#include "spritesheet.h"
#include "sdl.h"

struct Menu *Menu_initialize(SDL_Renderer *renderer) {
    struct Menu *menu;
    menu = (struct Menu*)malloc(sizeof(struct Menu));
    menu->renderer = renderer;
    menu->choice = MENU_NONE;
    menu->play = Spritesheet_create(PLAY_YES_FILENAME, 1, 1, 1, renderer);
    menu->quit = Spritesheet_create(QUIT_NO_FILENAME, 1, 1, 1, renderer);
    menu->title = Spritesheet_create(TITLE_FILENAME, 1, 1, 1, renderer);
    menu->temp_choice = MENU_PLAY;
    return menu;
}

void Menu_run(struct Menu *menu) {
    SDL_Event e; int i; bool start = true;

    while (menu->choice == MENU_NONE) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                menu->choice = MENU_QUIT;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        menu->temp_choice = MENU_PLAY;
                        Spritesheet_delete(menu->play);
                        menu->play = NULL;
                        menu->play = Spritesheet_create(PLAY_YES_FILENAME, 1, 1, 1, menu->renderer);
                        Spritesheet_delete(menu->quit);
                        menu->quit = NULL;
                        menu->quit = Spritesheet_create(QUIT_NO_FILENAME, 1, 1, 1, menu->renderer);
                        break;
                    case SDLK_DOWN:
                        menu->temp_choice = MENU_QUIT;
                        Spritesheet_delete(menu->play);
                        menu->play = NULL;
                        menu->play = Spritesheet_create(PLAY_NO_FILENAME, 1, 1, 1, menu->renderer);
                        Spritesheet_delete(menu->quit);
                        menu->quit = NULL;
                        menu->quit = Spritesheet_create(QUIT_YES_FILENAME, 1, 1, 1, menu->renderer);
                        break;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        menu->choice = menu->temp_choice;
                        break;
                }
            }
        }
        if(start) {
            for(i = 0; i < 255; i+= 4) {
                SDL_RenderClear(menu->renderer);
                Spritesheet_setAlphaMod(menu->title, i);
                Spritesheet_render(menu->title, TITLE_X, TITLE_Y, 0);
                Spritesheet_setAlphaMod(menu->play, i);
                Spritesheet_render(menu->play, PLAY_X, PLAY_Y, 0);
                Spritesheet_setAlphaMod(menu->quit, i);
                Spritesheet_render(menu->quit, QUIT_X, QUIT_Y, 0);
                SDL_RenderPresent(menu->renderer);
                SDL_Delay(3);
            }
            start = false;
        }
        SDL_SetRenderDrawColor(menu->renderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear(menu->renderer);
        Spritesheet_render(menu->title, TITLE_X, TITLE_Y, 0);
        Spritesheet_render(menu->play, PLAY_X, PLAY_Y, 0);
        Spritesheet_render(menu->quit, QUIT_X, QUIT_Y, 0);
        SDL_RenderPresent(menu->renderer);
    }
}

void Menu_delete(struct Menu *menu) {
    if (menu != NULL) {
        Spritesheet_delete(menu->title);
        Spritesheet_delete(menu->play);
        Spritesheet_delete(menu->quit);
        free(menu);
    }
}