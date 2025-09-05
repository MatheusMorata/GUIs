#include <SDL2/SDL.h>
#include <stdbool.h>

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
    Uint32 timeout = 5000;
    bool rodando = true;

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
    while(rodando && timeout > 0){ 

        if(AUX_WaitEventTimeoutCount(&evento, &timeout)){
            if(evento.type == SDL_QUIT){
                rodando = false;
            }else if(evento.type == SDL_MOUSEBUTTONDOWN){
                if(evento.button.button == SDL_BUTTON_LEFT){
                    quadrado.x -= 10; // Move-se para esquerda com click no botão esquerdo do mouse 
                }else if(evento.button.button == SDL_BUTTON_RIGHT){
                    quadrado.x += 10; // Move-se para direita com click no botão direito do mouse
                }
            }
        }

        // Desenhando 
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
        SDL_RenderFillRect(renderizador, &quadrado);
        SDL_RenderPresent(renderizador);

    }

    // Liberando recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;   
}