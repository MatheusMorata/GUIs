#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char* args[]){
    bool rodando = true;
    SDL_Event evt;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio 1.5.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);
    
    SDL_Rect segundo_quadrado = {40, 40, 10, 10};

    while(rodando == true){

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);

        SDL_WaitEvent(&evt);
        
        if(evt.type == SDL_QUIT){
            rodando = false;
        }

        SDL_RenderPresent(renderizador);
        SDL_Delay(16);
    }
    return 0;
}