#ifndef DONUT_ARRAY_H
#define DONUT_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "animated_spritesheet.h"
#include "sdl.h"
#include "constants.h"
#include "player.h"

struct Donut {
    struct AnimatedSpritesheet *animatedSpritesheet;    // The animated spritesheet
    int x;                                              // the X position of the donut
    int y;                                              // The Y position of the donut
    bool render;                                        // True if donut is rendered
    bool found;                                         // True if donut has been collected by the player
    SDL_Rect rect;                                      // The size and position of the donut
};

struct DonutArray {
    SDL_Rect zone;                                      // The zone to render of a donut
    struct Donut *elements;                             // The donuts of the donut array
    int currentSize;                                    // The current size of the array in donut number
    int capacity;                                       // The maximum capacity of the array
    int remaining;                                      // The donuts remaining to be collected
    Mix_Music *sound;                                   // The sound effect when collecting a donut
    int audioChannel;                                   // The audio channel of the donut sound effect
};

/**
 * Creates a donut array instance.
 *
 * @return                   The donut array
 */
struct DonutArray *DonutArray_init();

/**
 * Add a donut to the donut array.
 *
 * @param array              The donut array
 * @param renderer           The renderer
 * @param x                  The X position of the donut
 * @param y                  The Y position of the donut
 * @return                   True if the donut was added
 */
bool DonutArray_add(struct DonutArray *array, SDL_Renderer *renderer, int x, int y);

/**
 * Start the rendering of all donuts.
 *
 * @param array            The donut array
 */
void DonutArray_start(struct DonutArray *array);

/**
 * Renders all donuts.
 *
 * @param array            The donut array
 */
void DonutArray_render(struct DonutArray *array);

/**
 * Check if an entity of size rectangle collide with a donut.
 *
 * @param array            The donut array
 * @param rectangle        The entity size and position
 */
void DonutArray_collide(struct DonutArray *array, SDL_Rect *rectangle);

/**
 * Delete the donut array.
 *
 * @param array            The donut array
 */
void DonutArray_delete(struct DonutArray *array);

/**
 * Play a donut sound effect.
 *
 * @param array            The donut array
 */
void DonutArray_playAudio(struct DonutArray *array);

#endif