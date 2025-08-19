#include <SDL2/SDL.h>

// Constantes
#define Titulo "ex-1.2.1";
#define Largura 800; 
#define Altura 600;

int main(int argc, char* args[]){


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *janela = SDL_CreateWindow(
        titulo, 
        SDL_WINDOWPOS_CENTERED, // Posição x
        SDL_WINDOWPOS_CENTERED, // Posição y
        Largura, 
        Altura, 
        SDL_WINDOW_SHOWN // Mantém visível
    );    

    SDL_Delay(30000);
    
    return 0;
}