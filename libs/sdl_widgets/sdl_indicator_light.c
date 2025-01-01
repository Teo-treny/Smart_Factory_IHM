/**
 * @file sdl_indicator_light.c
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2025-01-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sdl_widgets.h"

/**
 * @brief Create a Indicator Light object
 * 
 * @param x X position
 * @param y Y position
 * @param w Width
 * @param h Height
 * @param state True or False (base balue)
 * @param title Title of the Indicator Light
 * @param font Font
 * @return IndicatorLight* 
 */
IndicatorLight * createIndicatorLight(int x, int y, int w, int h, bool state, const char* title, TTF_Font* font) {
    // Allocate memory
    IndicatorLight* indicatorLight = (IndicatorLight*)malloc(sizeof(IndicatorLight));
    if (!indicatorLight) return NULL;

    // Initialize the Indicator Light
    indicatorLight->x = x;
    indicatorLight->y = y;
    indicatorLight->w = w;
    indicatorLight->h = h;
    indicatorLight->state = state;
    strcpy(indicatorLight->title, title);
    indicatorLight->font = font;

    return indicatorLight;
}

/**
 * @brief Draw a Indicator Light object
 * 
 * @param renderer renderer
 * @param indicatorLight Indicator Light object to draw
 */
void drawIndicatorLight(SDL_Renderer* renderer, IndicatorLight* indicatorLight) {
    // Draw outline
    filledCircleRGBA(renderer, indicatorLight->x, indicatorLight->y, (indicatorLight->w/2)+3, 0, 0, 0, 255);

    // Draw the Indicator Light
    if (indicatorLight->state) {
        filledCircleRGBA(renderer, indicatorLight->x, indicatorLight->y, indicatorLight->w/2, 64, 235, 0, 255);
    } else {
        filledCircleRGBA(renderer, indicatorLight->x, indicatorLight->y, indicatorLight->w/2, 235, 64, 52, 255);
    }

    // Draw title
    Label* label = createLabel(indicatorLight->font, indicatorLight->title, indicatorLight->x - (indicatorLight->w/2), indicatorLight->y + (indicatorLight->h/2) + 5);
    drawLabel(renderer, label);

    // Cleaning
    destroyLabel(label);
}

/**
 * @brief Destroy a Indicator Light object
 * 
 * @param indicatorLight Indicator Light object to destroy
 */
void destroyIndicatorLight(IndicatorLight* indicatorLight) {
    free(indicatorLight);
}