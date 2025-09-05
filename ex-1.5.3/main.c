#include <SDL2/SDL.h>

int main(int args, char* argc[]){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio 1.5.3",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);

    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
    SDL_RenderClear(renderizador);
    SDL_RenderPresent(renderizador);
    SDL_Delay(500);
    return 0;   
}