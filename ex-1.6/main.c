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


int main(int argc, char* args[]){

    // Variáveis
    bool rodando = true;
    SDL_Event evento;

    SDL_Init(SDL_INIT_EVERYTHING);

    // Elementos essenciais (janela e renderizador)
    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio 1.5.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,600,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);
    
    // Quadrados requisitados no exercício
    SDL_Rect primeiro_quadrado = {0, 100, 20, 20};
    SDL_Rect segundo_quadrado = {0, 300, 20, 20};
    SDL_Rect terceiro_quadrado = {0, 500, 20, 20};

    // Posição da linha de chegada
    int linha_chegada_x = 780;

    while(rodando){
        
        // Fundo
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);

        // Quadrados
        SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 0);
        SDL_RenderFillRect(renderizador, &primeiro_quadrado);
        SDL_SetRenderDrawColor(renderizador, 0, 255, 0, 0);
        SDL_RenderFillRect(renderizador, &segundo_quadrado);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
        SDL_RenderFillRect(renderizador, &terceiro_quadrado);

        // Linha de chegada
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 0); 
        SDL_RenderDrawLine(renderizador, linha_chegada_x, 0, linha_chegada_x, 600);

        // Apresenta
        SDL_RenderPresent(renderizador);

        // Eventos

        
    }

    // Liberando recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}
