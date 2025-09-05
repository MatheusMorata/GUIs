#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeoutCount(SDL_Event *event, Uint32 *ms) {
    if (!ms){
      return 0;
    }  

    // "espera infinita"
    if (*ms == SDL_MAX_UINT32) {
        return SDL_WaitEvent(event);
    }

    // não espera, apenas verifica
    if (*ms == 0) {
        return SDL_PollEvent(event);
    }

    Uint32 start = SDL_GetTicks();

    while (*ms > 0) {
        if (SDL_PollEvent(event)) {
            return 1; // evento encontrado
        }

        SDL_Delay(1); 
        Uint32 now = SDL_GetTicks();

        // calcula o tempo decorrido
        Uint32 elapsed = now - start;
        if (elapsed >= *ms) {
            *ms = 0;
            break;
        } else {
            *ms -= elapsed;
            start = now; // atualiza referência
        }
    }

    return 0; // timeout sem eventos
}


int main(int argc, char* args[]){

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Janela *janela = SDL_CreateWindow(
    "Exercicio 1.5.2",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    800, 600, 
    SDL_WINDOW_SHOWN
  );

  SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);


  return 0;
}
