#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char* args[]){
    
    // Variáveis
    bool rodando = true;
    SDL_Event evt;
    int aleatorio = 0;

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
    SDL_Rect primeiro_quadrado = {400, 300, 20, 20};
    SDL_Rect segundo_quadrado = {400, 300, 20, 20};
    SDL_Rect terceiro_quadrado = {0, 0, 20, 20};

    while(rodando == true){

        // Colorindo fundo
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);

        // Desenhando os quadrados
        SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 0);
        SDL_RenderFillRect(renderizador, &primeiro_quadrado);
        SDL_SetRenderDrawColor(renderizador, 0, 255, 0, 0);
        SDL_RenderFillRect(renderizador, &segundo_quadrado);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
        SDL_RenderFillRect(renderizador, &terceiro_quadrado);

        // Quadrado move-se pelo tempo
        aleatorio = rand() % 4; 
        if(aleatorio == 0){   
            primeiro_quadrado.y -= 5;
        }else if(aleatorio == 1){
            primeiro_quadrado.y += 5;
        }else if(aleatorio == 2){
            primeiro_quadrado.x -= 5;
        }else{
            primeiro_quadrado.x += 5;
        }

        // Eventos de fechar janela, teclado e mouse
        SDL_WaitEvent(&evt);
        if(evt.type == SDL_QUIT){
            rodando = false;
        }else if(evt.type = SDL_KEYDOWN){
            switch(evt.key.keysym.sym){
                case SDLK_w:
                    segundo_quadrado.y -= 5;
                    break;
                case SDLK_s:
                    segundo_quadrado.y += 5;
                    break;
                case SDLK_a:
                    segundo_quadrado.x -= 5;
                    break;
                case SDLK_d:
                    segundo_quadrado.x += 5;
                    break;
            }   
        }
        SDL_RenderPresent(renderizador);
        SDL_Delay(16);
    }
    return 0;
}