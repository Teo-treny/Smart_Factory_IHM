/**
 * @file sdl_navbar.c
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "sdl_widgets.h"
#include <string.h>

/**
 * @brief Permet de créer une barre de navigation
 * 
 * @param font Police de caractères
 * @return NavBar* + NULL si erreur
 */

/**
 * @brief Permet de créer une barre de navigation
 * 
 * @param font Police de caractères
 * @param buttonLabels Tableau de labels
 * @param buttonCount Nombre de boutons
 * @param x X
 * @param y Y
 * @param w W
 * @param h H
 * @return NavBar* NULL si erreur 
 */
NavBar* createNavBar(TTF_Font* font, char* buttonLabels[], int buttonCount, int x, int y, int w, int h) {
    // Allouer de la mémoire pour la barre de navigation
    NavBar* navbar = (NavBar*)malloc(sizeof(NavBar));
    if (!navbar) return NULL;

    // Initialiser la barre de navigation
    navbar->font = font;
    navbar->buttonCount = buttonCount;
    navbar->currentPage = 0;
    navbar->x = x;
    navbar->y = y;
    navbar->w = w;
    navbar->h = h;

    // Couleurs de la barre de navigation
    navbar->activeColor = (SDL_Color){100, 100, 255, 255};  // Bleu clair
    navbar->inactiveColor = (SDL_Color){70, 70, 200, 255};  // Bleu foncé
    navbar->textColor = (SDL_Color){255, 255, 255, 255};    // Blanc

    // Calculer la hauteur de chaque bouton
    int buttonHeight = h / buttonCount;

    // Initialiser chaque bouton sachant que le premier bouton est actif par défaut
    // NavButton est un tableau dynamique
    navbar->buttons = (NavButton*)malloc(buttonCount * sizeof(NavButton));
    for (int i = 0; i < buttonCount; i++) {
        NavButton* button = &navbar->buttons[i];
        button->text = buttonLabels[i];
        button->page = i;
        button->isActive = (i == 0);
        button->rect = (SDL_Rect){x, y + i * buttonHeight, w, buttonHeight};
    }

    return navbar;
}

/**
 * @brief Permet de détruire une barre de navigation
 * 
 * @param navbar 
 */
void destroyNavBar(NavBar* navbar) {
    free(navbar->buttons);
    free(navbar);
}

/**
 * @brief Permet de dessiner une barre de navigation
 * 
 * @param renderer SDL_Renderer
 * @param navbar Structure NavBar
 */
void drawNavBar(SDL_Renderer* renderer, NavBar* navbar) {
    // Dessiner le fond de la barre de navigation
    SDL_SetRenderDrawColor(renderer, 70, 70, 200, 255);
    SDL_Rect navbarRect = {navbar->x, navbar->y, navbar->w, navbar->h}; // Ajuster la hauteur selon vos besoins
    SDL_RenderFillRect(renderer, &navbarRect);

    // Dessiner chaque bouton
    NavButton* button;
    for (int i = 0; i < navbar->buttonCount; i++) {
        button = &navbar->buttons[i];
        
        // Définir la couleur du bouton selon son état
        if (button->isActive) {
            SDL_SetRenderDrawColor(renderer, 
                navbar->activeColor.r,
                navbar->activeColor.g,
                navbar->activeColor.b,
                navbar->activeColor.a);
        } else {
            SDL_SetRenderDrawColor(renderer, 
                navbar->inactiveColor.r,
                navbar->inactiveColor.g,
                navbar->inactiveColor.b,
                navbar->inactiveColor.a);
        }

        // Dessiner le fond du bouton
        SDL_RenderFillRect(renderer, &button->rect);

        // Dessiner le texte du bouton
        if (navbar->font) {
            SDL_Surface* textSurface = TTF_RenderText_Solid(navbar->font, 
            button->text, navbar->textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                
                // Centrer le texte dans le bouton
                SDL_Rect textRect = {
                    button->rect.x + (button->rect.w - textSurface->w) / 2,
                    button->rect.y + (button->rect.h - textSurface->h) / 2,
                    textSurface->w,
                    textSurface->h
                };
                
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);

           }
        } 
    }
}

/**
 * @brief Permet de gérer les évènements de clic sur la barre de navigation
 * 
 * @param navbar Structure NavBar
 * @param x position x du clic
 * @param y position y du clic
 * @return int Page a activer
 */
int handleNavBarClick(NavBar* navbar, int x, int y) {
    if (x > NAVBAR_WIDTH) return navbar->currentPage;

    for (int i = 0; i < navbar->buttonCount; i++) {
        NavButton* button = &navbar->buttons[i];
        if (y >= button->rect.y && y < button->rect.y + button->rect.h) {
            setActivePage(navbar, button->page);
            return button->page;
        }
    }
    return navbar->currentPage;
}

/**
 * @brief Permet d'activer une page
 * 
 * @param navbar Barre de navigation
 * @param int Numéro de page à activer
 */
void setActivePage(NavBar* navbar, int page) {
    navbar->currentPage = page;
    for (int i = 0; i < navbar->buttonCount; i++) {
        navbar->buttons[i].isActive = (navbar->buttons[i].page == page);
    }
}