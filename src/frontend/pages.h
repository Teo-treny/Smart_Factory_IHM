/**
 * @file pages.h
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../libs/sdl_widgets/sdl_widgets.h"

/**
 * @brief Initialise la page variateur
 * 
 * @param font 
 * @param gauge 
 * @param graph 
 * @param graphData 
 * @param size 
 */
void initPageVariateur(TTF_Font* font, Gauge** gauge, Graph** graph, float graphData[], int size);

/**
 * @brief Dessine la page variateur
 * 
 * @param renderer
 * @param gauges 
 * @param graphs 
 */
void drawPageVariateur(SDL_Renderer* renderer, Gauge* gauge, Graph* graph);

/**
 * @brief Dessine la page des entrées sorties
 * 
 */
void page_io(void);

/**
 * Dessine la page des machines
 */
void page_machines(void);
