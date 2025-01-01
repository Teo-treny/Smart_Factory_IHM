/**
 * @file sdl_gauge.c
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "sdl_widgets.h"

/**
 * @brief Permet de créer une jauge
 * 
 * @param font Police de caractères
 * @param value Valeur de l'aiguille
 * @param min Valeur minimale
 * @param max Valeur maximale
 * @param x Position X
 * @param y Position Y
 * @param start Angle de départ
 * @param end Angle de fin
 * @param title Titre de la jauge
 * @param r Rouge
 * @param g Vert
 * @param b Bleu
 * @param a Alpha
 * @return Gauge* NULL si erreur
 */
Gauge* createGauge(TTF_Font* font, float value, float min, float max, int x, int y, int start, int end, const char* title, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a) {
    // Allouer l'espace mémoire
    Gauge* gauge = (Gauge*)malloc(sizeof(Gauge));
    if (!gauge) return NULL;

    // Initialiser la jauge
    gauge->font = font;
    gauge->value = value;
    gauge->min = min;
    gauge->max = max;
    gauge->x = x;
    gauge->y = y;
    gauge->start = start;
    gauge->end = end;
    gauge->r = r;
    gauge->g = g;
    gauge->b = b;
    gauge->a = a;
    strcpy(gauge->title, title);

    return gauge;
}

/**
 * @brief Permet de dessiner une jauge
 * 
 * @param renderer SDL_Renderer
 * @param gauge La jauge à dessiner
 */
void drawGauge(SDL_Renderer* renderer, Gauge* gauge) {
    // Dessiner l'arc de fond
    for (int rad = GAUGE_RADIUS - 20; rad <= GAUGE_RADIUS; rad++)
        arcRGBA(renderer, gauge->x, gauge->y, rad, gauge->start, gauge->end, gauge->r, gauge->g, gauge->b, gauge->a);

    // Dessiner l'aiguille
    float angle = gauge->start + (gauge->value / gauge->max) * 180;
    float radian = angle * PI / 180.0f;
    int needleLength = GAUGE_RADIUS - 20;
    int endX = gauge->x + cos(radian) * needleLength;
    int endY = gauge->y + sin(radian) * needleLength;
    thickLineRGBA(renderer, gauge->x, gauge->y, endX, endY, 3, 0, 0, 0, 255);

    // Ecrire le titre
    Label* labelTitle = createLabel(gauge->font, gauge->title, gauge->x - 80, gauge->y - GAUGE_RADIUS - 20);
    drawLabel(renderer, labelTitle);

    // Ecriture de la valeur
    char value[10];
    sprintf(value, "%.2f", gauge->value);
    Label* labelValue = createLabel(gauge->font, value, gauge->x - 5, gauge->y);
    drawLabel(renderer, labelValue);

    // Libération de la mémoire
    destroyLabel(labelTitle);
    destroyLabel(labelValue);

    // Version avec des vertex pour éviter les trous dans l'arc de cercle
    // TODO
}

/**
 * @brief Permet de libérer la mémoire d'une jauge
 * 
 * @param gauge La jauge à détruire
 */
void destroyGauge(Gauge* gauge) {
    free(gauge);
}