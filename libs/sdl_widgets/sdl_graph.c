/**
 * @file sdl_graph.c
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
 * @brief To find the maximum value in an array
 * 
 * @param data 
 * @param dataSize 
 * @return float 
 */
float findMax(float* data, int dataSize) {
    float max = data[0];
    for (int i = 1; i < dataSize; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

/**
 * @brief To find the minimum value in an array
 * 
 * @param data 
 * @param dataSize 
 * @return float 
 */
float findMin(float* data, int dataSize) {
    float min = data[0];
    for (int i = 1; i < dataSize; i++) {
        if (data[i] < min) {
            min = data[i];
        }
    }
    return min;
}

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
Graph* createGraph(TTF_Font* font, float* data, int dataSize, int x, int y, int w, int h, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a, const char* title) {
    // Allouer l'espace mémoire
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;

    // Initialiser le graphique
    graph->font = font;
    graph->dataSize = dataSize;
    graph->x = x;
    graph->y = y;
    graph->w = w;
    graph->h = h;
    graph->r = r;
    graph->g = g;
    graph->b = b;
    graph->a = a;
    graph->minData = 0;
    graph->maxData = findMax(data, dataSize);
    strcpy(graph->title, title);

    // Copier le tableau data dans graph->data
    graph->data = (float*)malloc(dataSize * sizeof(float));
    if (!graph->data) {
        free(graph);
        return NULL;
    }
    for (int i = 0; i < dataSize; i++) {
        graph->data[i] = data[i];
    }

    return graph;
}

/**
 * @brief Permet de dessiner un graphique
 * 
 * @param renderer SDL_Renderer
 * @param graph Le graphique à dessiner
 */
void drawGraph(SDL_Renderer* renderer, Graph* graph) {
    // Dessiner le titre
    Label* labelTitle = createLabel(graph->font, graph->title, graph->x, graph->y - 20);
    drawLabel(renderer, labelTitle);

    // Dessiner le graphique : une ligne pour l'axe X et une pour l'axe Y
    thickLineRGBA(renderer, graph->x, graph->y + graph->h, graph->x + graph->w, graph->y + graph->h, 2, graph->r, graph->g, graph->b, graph->a);
    thickLineRGBA(renderer, graph->x, graph->y, graph->x, graph->y + graph->h, 2, graph->r, graph->g, graph->b, graph->a);

    // Dessiner les graduations sur l'axe x et y
    for (int i = 0; i < graph->dataSize; i++) {
        // Graduation axe X
        int xGrad = graph->x + i * graph->w / graph->dataSize;
        thickLineRGBA(renderer, xGrad, graph->y + graph->h, xGrad, graph->y + graph->h + 5, 2, graph->r, graph->g, graph->b, graph->a);

        // Graduation axe Y
        int yGrad = graph->y + graph->h - i * graph->h / graph->dataSize;
        thickLineRGBA(renderer, graph->x - 5, yGrad, graph->x, yGrad, 2, graph->r, graph->g, graph->b, graph->a);
    }

    // On dessine les valeurs point par point et on relie les points
    // Attention, il faut prendre en compte la valeur maximale actuelle dans le tableau pour éviter que le tracé sorte de l'écran
    Label* labelValue = createLabel(graph->font, "", 0, 0);
    char textTampon[MAX_LABEL];
    for (int i = 0; i < graph->dataSize - 1; i++) {
        // Premier point
        int x1 = graph->x + i * graph->w / graph->dataSize;
        int y1 = graph->y + graph->h - graph->h * (graph->data[i] / graph->maxData);
        // Desinner le valeur du point
        memset(textTampon, 0, MAX_LABEL);
        sprintf(textTampon, "%.2f", graph->data[i]);
        setLabelText(labelValue, textTampon);
        labelValue->x = x1;
        labelValue->y = y1;
        drawLabel(renderer, labelValue);

        // Deuxième point
        int x2 = graph->x + (i + 1) * graph->w / graph->dataSize;
        int y2 = graph->y + graph->h - graph->h * (graph->data[i + 1] / graph->maxData);

        // Relier les points
        thickLineRGBA(renderer, x1, y1, x2, y2, 2, graph->r, graph->g, graph->b, graph->a);

        // On dessiner un petit disque sur chaque point
        filledCircleRGBA(renderer, x1, y1, 3, graph->r, graph->g, graph->b, graph->a);

        if (i == graph->dataSize - 2) {
            // Desinner le valeur du point
            memset(textTampon, 0, MAX_LABEL);
            sprintf(textTampon, "%.2f", graph->data[i + 1]);
            setLabelText(labelValue, textTampon);
            labelValue->x = x2;
            labelValue->y = y2;
            drawLabel(renderer, labelValue);
            filledCircleRGBA(renderer, x2, y2, 3, graph->r, graph->g, graph->b, graph->a);
        }
    }

    // On écrit le minimum en bas à gauche
    memset(textTampon, 0, MAX_LABEL);
    sprintf(textTampon, "%.2f", graph->minData);
    setLabelText(labelValue, textTampon);
    labelValue->x = graph->x - 45;
    labelValue->y = graph->y + graph->h;
    drawLabel(renderer, labelValue);

    // On écrit le maximum en haut à gauche
    memset(textTampon, 0, MAX_LABEL);
    sprintf(textTampon, "%.2f", graph->maxData);
    setLabelText(labelValue, textTampon);
    labelValue->x = graph->x - 45;
    labelValue->y = graph->y;
    drawLabel(renderer, labelValue);

    // Libérer la mémoire
    destroyLabel(labelTitle);
    destroyLabel(labelValue);
}

/**
 * @brief Debug un graphique
 * 
 * @param graph Graphique à débugger
 */
void debugGraph(Graph* graph) {
    printf("Graphique: %s\n", graph->title);
    printf("Position: (%d, %d)\n", graph->x, graph->y);
    printf("Taille: %dx%d\n", graph->w, graph->h);
    printf("Données: ");
    for (int i = 0; i < graph->dataSize; i++) {
        printf("%.2f ", graph->data[i]);
    }
    printf("\n");
}

/**
 * @brief Permet de détruire un graphique
 * 
 * @param graph Le graphique à détruire
 */
void destroyGraph(Graph* graph) {
    free(graph);
}