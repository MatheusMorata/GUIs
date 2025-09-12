#include <SDL2/SDL.h>
#include <stdbool.h>

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

int main(int args, char* argc[]){

    bool rodando = true;
    int timeout = 16;
    SDL_Event evento;

    // Iniciando elementos essenciais do SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio-1.7",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);

    while(rodando){

        

        // Desenhando
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);
        SDL_RenderPresent(renderizador);
        
        while(AUX_WaitEventTimeout(&evento, &timeout)){
            if(evento.type == SDL_QUIT){
                rodando = false;
            }
        }
    }
    return 0;
}