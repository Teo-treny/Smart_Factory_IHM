#ifndef SDL_SHAPES_H
#define SDL_SHAPES_H

#include <SDL2/SDL.h>
#include <math.h>

#define PI 3.14159265358979323846

/**
 * @brief Permet de dessiner un arc avec une épaisseur
 * 
 * @param renderer SDL_Renderer
 * @param x Position X
 * @param y Position Y
 * @param radius Rayon
 * @param startAngle Angle de début
 * @param endAngle Angle de fin
 * @param thickness Epaisseur
 * @param r 
 * @param g 
 * @param b 
 * @param a 
 */
void drawThickArcTriangles(SDL_Renderer* renderer, int x, int y, int radius, float startAngle, float endAngle, int thickness, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

#endif