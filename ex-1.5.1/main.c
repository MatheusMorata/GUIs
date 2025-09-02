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
        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
        SDL_RenderFillRect(renderizador, &segundo_quadrado);
        SDL_RenderPresent(renderizador);

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
                    segundo_quadrado.x -= 10;
                    break;
                case SDLK_d:
                    segundo_quadrado.x += 10;
                    break;
            }   
        }
        SDL_Delay(16);
    }
    return 0;
}