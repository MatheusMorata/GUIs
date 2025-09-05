#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

int AUX_WaitEventTimeoutCount(SDL_Event *evt, Uint32 *ms) {
    if (ms == NULL || *ms == 0) {
        // Se não há tempo restante, retorna imediatamente
        return 0;
    }

    Uint32 start = SDL_GetTicks();  // tempo inicial

    // Chama a função original com o tempo restante
    int result = SDL_WaitEventTimeout(evt, *ms);

    Uint32 end = SDL_GetTicks();    // tempo final
    Uint32 elapsed = end - start;   // tempo decorrido

    if (elapsed >= *ms) {
        *ms = 0;
    } else {
        *ms -= elapsed;
    }

    return result;
}

int main(int args, char* argc[]){

    // Variáveis
    SDL_Event evento;
    Uint32 timeout = 1; // pequeno timeout para não travar o loop
    bool rodando = true;
    bool andando = false;
    int fundo = 255;
    int R = 0;
    int G = 0;
    int B = 255;
    int direcao = 1;

    // Inicializando SDL2
    SDL_Init(SDL_INIT_EVERYTHING);

    // Criando elementos essencias (janela, renderizador e objetos)
    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio 1.5.3",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);

    SDL_Rect quadrado = {300, 300, 50, 50};

    // Looping principal
    while(rodando){ 

        // Captura eventos, mas com timeout mínimo para não travar
        while(AUX_WaitEventTimeoutCount(&evento, &timeout)){
            if(evento.type == SDL_QUIT){
                rodando = false; 
            }else if(evento.type == SDL_MOUSEBUTTONDOWN){
                if(evento.button.button == SDL_BUTTON_RIGHT){
                    andando = true;
                }else if(evento.button.button == SDL_BUTTON_LEFT){
                    andando = false;
                }
            }else if(evento.type == SDL_KEYDOWN){
                // Novo comportamento muda de cor, quando pressiona a tecla C
                if(evento.key.keysym.sym == SDLK_c){
                    R = rand() % 255;
                    G = rand() % 255;
                    B = rand() % 255;
                }
            }
        }

        // Atualiza posição do quadrado continuamente se andando for true
        if(andando){
            if(quadrado.x + quadrado.w > 800 || quadrado.x < 0){
                direcao *= -1;
            }
            quadrado.x += 5 * direcao; // movimento contínuo
        }

        // Desenhando 
        SDL_SetRenderDrawColor(renderizador, fundo, fundo, fundo, 0);
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, R, G, B, 0);
        SDL_RenderFillRect(renderizador, &quadrado);
        SDL_RenderPresent(renderizador);

        SDL_Delay(16); // ~60 FPS
        timeout = 1;    // reset timeout para captura de eventos
    }

    // Liberando recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;   
}
