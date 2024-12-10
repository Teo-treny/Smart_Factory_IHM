/**
 * @file sdl_label.c
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2024-12-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "sdl_widgets.h"

/**
 * @brief Permet de créer une structure label
 * 
 * @param font Police de caractères
 * @param text Texte du label
 * @param x Position X
 * @param y Position Y
 * @return Label* NULL si erreur
 */
Label* createLabel(TTF_Font* font, char* text, int x, int y) {
    // Alloue l'espace memoire
    Label* label = (Label*)malloc(sizeof(Label));
    if(!label) return NULL;

    // Initialisation du label
    label->font = font;
    label->text = text;
    label->x = x;
    label->y = y;

    // Récupère la taille du texte
    TTF_SizeText(font, text, &label->w, &label->h);

    return label;
}

/**
 * @brief Permet de dessiner un label
 * 
 * @param renderer SDL_Renderer
 * @param label Le label à dessiner
 */
void drawLabel(SDL_Renderer* renderer, Label* label) {
    // Crée la surface du texte
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(label->font, label->text, textColor);
    if(!surface) return;

    // Crée la texture du texte
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture) return;

    // Dessine le texte
    SDL_Rect textRect;
    textRect.x = label->x;
    textRect.y = label->y;
    textRect.w = label->w;
    textRect.h = label->h;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Libère la mémoire
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * @brief Set the Label Text object
 * 
 * @param label Label object
 * @param text Text to set
 */
void setLabelText(Label* label, char* text) {
    label->text = text;
    TTF_SizeText(label->font, text, &label->w, &label->h);
}

/**
 * @brief Permet de libérer la mémoire d'un label
 * 
 * @param label Le label à détruire
 */
void destroyLabel(Label* label) {
    free(label);
}