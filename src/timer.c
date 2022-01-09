#include "timer.h"

void setSize(struct Timer *timer);
bool initFont(struct Timer *timer);

void setSize(struct Timer *timer) {
    if(timer->fontEnabled) {
        int border = 6;
        int width = 0; 
        int height = TTF_FontHeight(timer->font);
        TTF_SizeText(timer->font, "00:00", &width, &height);
        timer->bRect.x = LEVEL_WIDTH - width - (border * 2);
        timer->bRect.y = 0;
        timer->bRect.w = width + (border * 2);
        timer->bRect.h = height + (border * 2);
        timer->tRect.x = timer->bRect.x + border;
        timer->tRect.y = timer->bRect.y + border;
        timer->tRect.w = width;
        timer->tRect.h = height;

        SDL_Surface *bSur = SDL_CreateRGBSurface(0, timer->bRect.w, timer->bRect.h, 32, 0x00, 0x00, 0x00, 0xFF);
        timer->bTexture = SDL_CreateTextureFromSurface(timer->renderer, bSur);
        SDL_FreeSurface(bSur);
    }
}

bool initFont(struct Timer *timer) {
    if (TTF_WasInit() || TTF_Init() != -1) {
        timer->font = TTF_OpenFont(FONT, TIMER_FONT_SIZE);
        return true;
    }
    return false;
}

struct Timer *Timer_initialize(SDL_Renderer* renderer, int time) {
    struct Timer *timer;
    timer = malloc(sizeof(struct Timer));
    timer->renderer = renderer;
    timer->fontEnabled = initFont(timer);
    timer->endTime = time;
    timer->startTick = SDL_GetTicks();
    timer->secondTick = timer->startTick + 1000;
    setSize(timer);

    return timer;
}

void Timer_decrease(struct Timer *timer) {
    if(timer->startTick >= timer->secondTick) {
        timer->endTime--;
        timer->startTick = SDL_GetTicks();
        timer->secondTick  = timer->startTick + 1000;
    }
    timer->startTick = SDL_GetTicks();
}

bool Timer_isOver(struct Timer *timer) {
    return timer->endTime <= 0;
}

void Timer_render(struct Timer *timer) {
    if(timer->fontEnabled && timer->endTime >= 0) {
        char strTime[5];
        int seconds = timer->endTime == 0 ? 0: timer->endTime % 60;
        int minutes = timer->endTime / 60;
        sprintf(strTime, "%02d:%02d", minutes, seconds);

        SDL_Color tColor = {255, 255, 255};
        SDL_Surface* tSur = TTF_RenderText_Blended(timer->font, strTime, tColor);
        SDL_Texture* tTexture = SDL_CreateTextureFromSurface(timer->renderer, tSur);
        SDL_RenderCopy(timer->renderer, timer->bTexture, NULL, &timer->bRect);
        SDL_RenderCopy(timer->renderer, tTexture, NULL, &timer->tRect);

        SDL_FreeSurface(tSur);
        SDL_DestroyTexture(tTexture);
    }
}

void Timer_delete(struct Timer *timer) {
    if(timer != NULL) {
        if(timer->fontEnabled) {
            TTF_CloseFont(timer->font);
            SDL_DestroyTexture(timer->bTexture);
        }
        free(timer);
    }
}