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
    bool chegou[3] = {false, false, false};
    SDL_Event evento;
    int timeout;

    SDL_Init(SDL_INIT_EVERYTHING);

    // Elementos essenciais (janela e renderizador)
    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio 1.6",
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

        timeout = 16;

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
        while(AUX_WaitEventTimeoutCount(&evento, &timeout)){

            if(evento.type == SDL_QUIT){
                rodando = false;
            }
            
            // Movendo pelo teclado 
            if(evento.type == SDL_KEYDOWN){
                if(evento.key.keysym.sym == SDLK_d && chegou[1] == false){
                    segundo_quadrado.x += 10;
                }else if(evento.key.keysym.sym == SDLK_a && chegou[1] == false){
                    segundo_quadrado.x -= 10;
                }
            }

            // Movendo pelo mouse 
            if(evento.type == SDL_MOUSEMOTION && chegou[2] == false){
                terceiro_quadrado.x = evento.motion.x;
            }
        }


        // Movendo pelo tempo
        if(!chegou[0]){
            primeiro_quadrado.x += 2;
            if(primeiro_quadrado.x >= linha_chegada_x){
                chegou[0] = true;
                SDL_Log("Quadrado 1 chegou!");
            }
        }

        // Quadrado teclado
        if(segundo_quadrado.x >= linha_chegada_x && !chegou[1]){
            chegou[1] = true;
            SDL_Log("Quadrado 2 chegou!");
        }

        // Quadrado mouse
        if(terceiro_quadrado.x >= linha_chegada_x && !chegou[2]){
            chegou[2] = true;
            SDL_Log("Quadrado 3 chegou!");
        }

        if(chegou[0] == true && chegou[1] == true && chegou[2] == true){
            rodando = false;
        }

    }
    
    // Liberando recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}
