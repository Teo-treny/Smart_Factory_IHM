/**
 * @file main.c
 * @author Téo Trény
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../libs/sdl_widgets/sdl_widgets.h"
#include "frontend/pages.h"

// #define FONT "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf"
#define FONT "/usr/share/fonts/FreeSans.ttf"

#define WINDOW_LENGTH 720
#define WINDOW_WIDTH 1280

int main(int argc, char* argv[]) {
    // Variables
    static int frameCount = 0;
    static Uint32 lastTime = 0;
    Uint32 currentTime;

    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    // Configuration de SDL pour les écrans tactiles
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    SDL_SetEventFilter(NULL, NULL);
    SDL_EventState(SDL_FINGERDOWN, SDL_ENABLE);
    SDL_EventState(SDL_FINGERMOTION, SDL_ENABLE);
    SDL_EventState(SDL_FINGERUP, SDL_ENABLE);

    // Créer la fenêtre
    SDL_Window* window = SDL_CreateWindow("Dashboard",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WINDOW_WIDTH, WINDOW_LENGTH,
                                        SDL_WINDOW_SHOWN);
    

    // Créer le renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED);
    
    // Mode full screen
    if (argc > 1 && strcmp(argv[1], "fullscreen") == 0)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    // Initialiser la police
    TTF_Font* font = TTF_OpenFont(FONT, 16);
    if (!font) {
        printf("Erreur lors du chargement de la police: %s\n", TTF_GetError());
        return 1;
    }

    // Créer la barre de navigation
    // boutons de la nav bar
    char* buttonLabels[] = {
        "Variateur",
        "I/O",
        "Machines"
    };
    NavBar* navbar = createNavBar(font, buttonLabels, 3, 0, 0, NAVBAR_WIDTH, WINDOW_LENGTH);
    if (!navbar) {
        printf("Erreur lors de la création de la barre de navigation\n");
        return 1;
    }

    SDL_bool quit = SDL_FALSE;
    
    // Définition des jauges
    Gauge* gauges[] = {
        createGauge(font, 0.5f, 0.0f, 50.0f, 250, 150, 180, 360, "Frequence [Hz]", 167, 173, 217, 255),
        createGauge(font, 0.3f, 0.0f, 10.0f, 250, 400, 180, 360, "Temperature", 167, 173, 217, 255),
        createGauge(font, 0.7f, 0.0f, 10.0f, 250, 650, 180, 360, "Pression", 167, 173, 217, 255)
    };

    // Faux tableau de donnée
    float graphData[] = {0.2f, 0.4f, 0.6f, 0.3f, 0.5f, 0.7f, 0.4f, 10.6f};
    int size = sizeof(graphData) / sizeof(graphData[0]);
    printf("Size: %d\n", size);

    // Définition des graph
    Graph* graph[] = {
        createGraph(font, graphData, size, 400, 0, 600, 200, 167, 173, 217, 255, "Graphique 1")
    };
    debugGraph(graph[0]);

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break;
                
                case SDL_FINGERDOWN:
                    // Convertir l'événement tactile en événement de clic de souris
                    event.type = SDL_MOUSEBUTTONDOWN;
                    event.button.button = SDL_BUTTON_LEFT;
                    event.button.x = event.tfinger.x * WINDOW_WIDTH;
                    event.button.y = event.tfinger.y * WINDOW_LENGTH;
                    SDL_PushEvent(&event);
                    break;

                case SDL_FINGERMOTION:
                    // Convertir l'événement de mouvement tactile en événement de mouvement de souris
                    event.type = SDL_MOUSEMOTION;
                    event.motion.x = event.tfinger.x * WINDOW_WIDTH;
                    event.motion.y = event.tfinger.y * WINDOW_LENGTH;
                    SDL_PushEvent(&event);
                    break;

                case SDL_FINGERUP:
                    // Convertir l'événement de relâchement tactile en événement de relâchement de souris
                    event.type = SDL_MOUSEBUTTONUP;
                    event.button.button = SDL_BUTTON_LEFT;
                    event.button.x = event.tfinger.x * WINDOW_WIDTH;
                    event.button.y = event.tfinger.y * WINDOW_LENGTH;
                    SDL_PushEvent(&event);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        PageType newPage = handleNavBarClick(navbar, 
                            event.button.x, event.button.y);
                        // Gérer le changement de page ici
                    }
                    break;
            }
        }
        
        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        // Dessiner la barre de navigation
        drawNavBar(renderer, navbar);
        
        // Données exemple pour les graphiques
        // float graphData[] = {0.2f, 0.4f, 0.6f, 0.3f, 0.5f, 0.7f, 0.4f, 0.6f};

        // Dessiner le contenu en fonction de la page active
        switch (navbar->currentPage) {
            case PAGE_VARIATEUR:
                // page_variateur(renderer, gauges, graphData);
                drawGauge(renderer, gauges[0]);
                drawGauge(renderer, gauges[1]);
                drawGauge(renderer, gauges[2]);
                drawGraph(renderer, graph[0]);
                break;
            
            case PAGE_IO:
                break;
            
            case PAGE_MACHINES:
                break;
            
            default:

                break;
        }
        
        SDL_RenderPresent(renderer);

        // Update des données (à l'avenir on fait ça dans une tâche séparée)
        gauges[0]->value += 0.01f;

        // Attendre 32ms pour obtenir 60 FPS
        SDL_Delay(32);

        // Calculer FPS pour debug
        frameCount++;
        currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000) {
            printf("FPS: %d\n", frameCount);
            frameCount = 0;
            lastTime = currentTime;
        }
    }
    
    // Nettoyage
    //destroyNavBar(navbar);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}