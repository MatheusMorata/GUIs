#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[]){
    
    // Inicializando SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Criando janela
    SDL_Window *janela = SDL_CreateWindow(
        "GFX", // Título
        SDL_WINDOWPOS_CENTERED, // Posição em x
        SDL_WINDOWPOS_CENTERED, // Posição em y
        800, // Largura
        600, // Altura
        SDL_WINDOW_SHOWN
    );

    // TESTANDO
    SDL_Delay(1000);

    return 0;
}