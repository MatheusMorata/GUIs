#include <SDL2/SDL.h>
#include <stdbool.h>

// Constantes 
#define LARGURA 800
#define ALTURA 600

int AUX_WaitEventTimeout(SDL_Event *evt, Uint32 *ms) {
    if (ms == NULL) {
        return 0; // segurança
    }

    Uint32 start = SDL_GetTicks(); // tempo inicial

    int result = SDL_WaitEventTimeout(evt, *ms); // 1 = evento, 0 = timeout

    Uint32 end = SDL_GetTicks(); // tempo final
    Uint32 elapsed = end - start; // tempo decorrido

    if (elapsed >= *ms) {
        *ms = 0;
    } else {
        *ms -= elapsed;
    }

    return result; 
}

int main(int argc, char* argv[]){

    // Variáveis
    bool rodando = true;
    SDL_Event evento;
    Uint32 timeout = 200;

    // Inicialização
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow(
        "Exercício - 2.2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGURA, ALTURA,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);

    SDL_Rect quadrado = {400, 300, 50, 50};

    // Desenhando
    while(rodando){
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
        SDL_RenderFillRect(renderizador, &quadrado);
        SDL_RenderPresent(renderizador);

        while(AUX_WaitEventTimeout(&evento, &timeout)){
            if(evento.type == SDL_QUIT){
                rodando = false;
            }
        }

    }

    // Liberando recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}
