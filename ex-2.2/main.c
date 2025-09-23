#include <SDL2/SDL.h>

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *janela = SDL_CreateWindow(
        "Exercício - 2.2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);

    SDL_Rect quadrado = {400, 300, 50, 50};

    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
    SDL_RenderClear(renderizador);
    SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
    SDL_RenderFillRect(renderizador, &quadrado);
    SDL_RenderPresent(renderizador);
    SDL_Delay(3000);

    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}
