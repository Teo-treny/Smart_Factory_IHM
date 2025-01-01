/**
 * @file pages.c
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "pages.h"

/**
 * @brief Configure la page variateur
 * 
 * @param TTF_Font* font
 * @param renderer 
 * @param gauges 
 * @param graphs 
 */
void initPageVariateur(TTF_Font* font, Gauge** gauge, Graph** graph, float graphData[], int size) {
    // Jauge
    *gauge = createGauge(font, 0.1f, 0.0f, 50.0f, 250, 150, 180, 360, "Frequence [Hz]", 67, 204, 190, 255);

    // Graph
    *graph = createGraph(font, graphData, size, 400, 20, 800, 200, 67, 204, 190, 255, "Frequence [Hz]");
}

/**
 * @brief Dessine la page variateur
 * 
 * @param renderer
 * @param gauges 
 * @param graphs 
 */
void drawPageVariateur(SDL_Renderer* renderer, Gauge* gauge, Graph* graph) {
    drawGauge(renderer, gauge);
    drawGraph(renderer, graph);
}

/**
 * @brief Dessine la page des entrées sorties
 * 
 */
void page_io(void) {

}

/**
 * Dessine la page des machines
 */
void page_machines(void) {

}