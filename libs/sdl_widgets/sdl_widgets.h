/**
 * @file sdl_widgets.h
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SDL_WIDGETS_H
#define SDL_WIDGETS_H

// Libs
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdbool.h>
#include "../sdl_shapes/sdl_shapes.h"

// Consts
#define GAUGE_RADIUS 80
#define PI 3.14159265358979323846
#define NAVBAR_WIDTH 150
#define MAX_BUTTONS 5
#define MAX_LABEL 255

// Gauge
typedef struct {
    TTF_Font* font;
    float value;  // Valeur de l'aiguille (entre min et max, mais peut depasser)
    float min;    // Valeur minimale
    float max;    // Valeur maximale
    int color;  // indique s'il faut colorer ou non la jauge
    char title[MAX_LABEL];
    int x, y, start, end;
    int w, h;
    uint8_t r, g, b, a;
} Gauge;

// Graph
typedef struct {
    TTF_Font* font;
    float* data;
    int dataSize;
    int x, y, w, h;
    int r, g, b, a;
    float minData, maxData;
    char title[MAX_LABEL];
} Graph;

// Label
typedef struct {
    char* text;
    int x, y;
    int w, h;
    SDL_Color color;
    TTF_Font* font;
} Label;

// NavButton
typedef struct {
    SDL_Rect rect;
    const char* text;
    bool isActive;
    int page;
} NavButton;

// NavBar
typedef struct {
    NavButton* buttons;
    int buttonCount;
    int currentPage;
    TTF_Font* font;
    SDL_Color activeColor;
    SDL_Color inactiveColor;
    SDL_Color textColor;
    int x, y, w, h;
} NavBar;

// Indicator Light
typedef struct {
    TTF_Font* font;
    char title[MAX_LABEL];
    int x, y, w, h;
    bool state;
} IndicatorLight;

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
Gauge* createGauge(TTF_Font* font, float value, float min, float max, int x, int y, int start, int end, const char* title, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);

/**
 * @brief Permet de dessiner une jauge
 * 
 * @param renderer SDL_Renderer
 * @param gauge La jauge à dessiner
 */
void drawGauge(SDL_Renderer* renderer, Gauge* gauge);

/**
 * @brief Permet de libérer la mémoire d'une jauge
 * 
 * @param gauge La jauge à détruire
 */
void destroyGauge(Gauge* gauge);

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
NavBar* createNavBar(TTF_Font* font, char* buttonLabels[], int buttonCount, int x, int y, int w, int h);

/**
 * @brief Permet de détruire une barre de navigation
 * 
 * @param navbar 
 */
void destroyNavBar(NavBar* navbar);

/**
 * @brief Permet de dessiner une barre de navigation
 * 
 * @param renderer SDL_Renderer
 * @param navbar Structure NavBar
 */
void drawNavBar(SDL_Renderer* renderer, NavBar* navbar);

/**
 * @brief Permet de gérer les évènements de clic sur la barre de navigation
 * 
 * @param navbar Structure NavBar
 * @param x position x du clic
 * @param y position y du clic
 * @return int Page a activer
 */
int handleNavBarClick(NavBar* navbar, int x, int y);

/**
 * @brief Permet d'activer une page
 * 
 * @param navbar Barre de navigation
 * @param int Numéro de page à activer
 */
void setActivePage(NavBar* navbar, int page);

/**
 * @brief Permet de créer une structure label
 * 
 * @param font Police de caractères
 * @param text Texte du label
 * @param x Position X
 * @param y Position Y
 * @return Label* NULL si erreur
 */
Label* createLabel(TTF_Font* font, char* text, int x, int y);

/**
 * @brief Permet de dessiner un label
 * 
 * @param renderer SDL_Renderer
 * @param label Le label à dessiner
 */
void drawLabel(SDL_Renderer* renderer, Label* label);

/**
 * @brief Set the Label Text object
 * 
 * @param label Label object
 * @param text Text to set
 */
void setLabelText(Label* label, char* text);

/**
 * @brief Permet de libérer la mémoire d'un label
 * 
 * @param label Le label à détruire
 */
void destroyLabel(Label* label);

/**
 * @brief Permet de créer un graphique
 * 
 * @param font Police de caractères
 * @param data Données du graphique
 * @param dataSize Taille des données
 * @param x Position X
 * @param y Position Y
 * @param w Largeur
 * @param h Hauteur
 * @param r Rouge
 * @param g Vert
 * @param b Bleu
 * @param a Alpha
 * @param title Titre du graphique
 * @return Graph* NULL si erreur
 */
Graph* createGraph(TTF_Font* font, float* data, int dataSize, int x, int y, int w, int h, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a, const char* title);

/**
 * @brief Permet de dessiner un graphique
 * 
 * @param renderer SDL_Renderer
 * @param graph Le graphique à dessiner
 */
void drawGraph(SDL_Renderer* renderer, Graph* graph);

/**
 * @brief Debug un graphique
 * 
 * @param graph Graphique à débugger
 */
void debugGraph(Graph* graph);

/**
 * @brief Permet de détruire un graphique
 * 
 * @param graph Le graphique à détruire
 */
void destroyGraph(Graph* graph);

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
IndicatorLight * createIndicatorLight(int x, int y, int w, int h, bool state, const char* title, TTF_Font* font);

/**
 * @brief Draw a Indicator Light object
 * 
 * @param renderer renderer
 * @param indicatorLight Indicator Light object to draw
 */
void drawIndicatorLight(SDL_Renderer* renderer, IndicatorLight* indicatorLight);

/**
 * @brief Destroy a Indicator Light object
 * 
 * @param indicatorLight Indicator Light object to destroy
 */
void destroyIndicatorLight(IndicatorLight* indicatorLight);

#endif