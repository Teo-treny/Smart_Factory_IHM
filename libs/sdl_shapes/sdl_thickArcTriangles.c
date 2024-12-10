#include "sdl_shapes.h"

/**
 * @brief Permet de dessiner un arc avec une épaisseur
 * 
 * @param renderer SDL_Renderer
 * @param x Position X
 * @param y Position Y
 * @param radius Rayon
 * @param startAngle Angle de début
 * @param endAngle Angle de fin
 * @param thickness 
 * @param r 
 * @param g 
 * @param b 
 * @param a 
 */
void drawThickArcTriangles(SDL_Renderer* renderer, int x, int y, int radius, float startAngle, float endAngle, int thickness, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    // Convertir les angles en radians
    startAngle = startAngle * PI / 180.0f;
    endAngle = endAngle * PI / 180.0f;

    // Calculer le nombre de triangles nécessaires
    int numTriangles = (int)((endAngle - startAngle) / (PI / 180.0f)) * thickness;
    printf("Num triangles: %d\n", numTriangles);

    // Allouer de la mémoire pour les points des triangles
    // TODO : Pas la bonne taille de mémoire allouée
    printf("Size of SDL_Vertex: %lu\n", sizeof(SDL_Vertex));
    printf("Size of SDL_Vertex collection: %lu\n", sizeof(SDL_Vertex) * (numTriangles * 3));
    SDL_Vertex* vertices = (SDL_Vertex*)malloc(sizeof(SDL_Vertex) * (numTriangles * 3));
    int vertexIndex = 0;

    // Dessiner l'arc avec épaisseur
    for (int i = 0; i < thickness; i++) {
        float currentAngle = startAngle;
        while (currentAngle <= endAngle) {
            // Calculer les coordonnées des sommets du triangle
            int x1 = x + (int)(cos(currentAngle) * (radius + i));
            int y1 = y + (int)(sin(currentAngle) * (radius + i));
            int x2 = x + (int)(cos(currentAngle + PI / 180.0f) * (radius + i));
            int y2 = y + (int)(sin(currentAngle + PI / 180.0f) * (radius + i));
            int x3 = x + (int)(cos(currentAngle) * (radius + i + 1));
            int y3 = y + (int)(sin(currentAngle) * (radius + i + 1));

            // Ajouter les sommets du triangle
            vertices[vertexIndex++] = (SDL_Vertex){
                .position = {(float)x1, (float)y1},
                .color = {r, g, b, a}
            };
            vertices[vertexIndex++] = (SDL_Vertex){
                .position = {(float)x2, (float)y2},
                .color = {r, g, b, a}
            };
            vertices[vertexIndex++] = (SDL_Vertex){
                .position = {(float)x3, (float)y3},
                .color = {r, g, b, a}
            };

            currentAngle += PI / 180.0f;
        }
    }

    // Dessiner les triangles
    SDL_RenderGeometry(renderer, NULL, vertices, numTriangles * 3, NULL, 0);

    // Libérer la mémoire allouée
    free(vertices);
}