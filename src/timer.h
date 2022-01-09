#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdio.h>
#include "sdl.h"
#include "constants.h"

struct Timer {
    SDL_Renderer* renderer;     // The renderer
    TTF_Font* font;             // The timer font
    int startTick;              // The beginning tick of a second 
    int secondTick;             // The ending tick of a second
    int endTime;                // The timer length in seconds
    int currentTime;            // The current time in seconds
    bool fontEnabled;           // True if SDL TTF is enabled
    SDL_Rect bRect;             // the size and position of timer background
    SDL_Rect tRect;             // the size and position of timer
    SDL_Texture *bTexture;      // the timer background texture
};

/**
 * Creates a timer instance.
 *
 * @param renderer           The renderer
 * @param time               The time in seconds
 * @return                   The timer
 */
struct Timer *Timer_initialize(SDL_Renderer* renderer, int time);

/**
 * Decreases the timer of 1 second.
 *
 * @param timer             The timer
 */
void Timer_decrease(struct Timer *timer);

/**
 * Return true if timer is expired.
 *
 * @param timer             The timer
 */
bool Timer_isOver(struct Timer *timer);

/**
 * Renders the timer.
 *
 * @param timer             The timer to render
 */
void Timer_render(struct Timer *timer);

/**
 * Delete the timer.
 *
 * @param timer             The timer
 */
void Timer_delete(struct Timer *timer);

#endif