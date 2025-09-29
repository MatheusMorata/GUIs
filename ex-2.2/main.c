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

void cliqueNoQuadrado(SDL_Rect quadrado){
    SDL_Log("Clique no quadrado em (%d, %d)", quadrado.x, quadrado.y);
}

int main(int argc, char* argv[]){

    bool rodando = true;
    bool arrastando = false;
    bool cliquePossivel = false;

    int offsetX = 0, offsetY = 0;
    SDL_Event evento;
    Uint32 timeout = 200;

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
    SDL_Rect posicaoOriginal = quadrado;

    while(rodando){
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 0);
        SDL_RenderFillRect(renderizador, &quadrado);

        SDL_RenderPresent(renderizador);

        while(AUX_WaitEventTimeout(&evento, &timeout)){
            switch(evento.type){
                case SDL_QUIT:
                    rodando = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(evento.button.button == SDL_BUTTON_LEFT){
                        SDL_Point p = {evento.button.x, evento.button.y};
                        if(SDL_PointInRect(&p, &quadrado)){
                            arrastando = true;
                            cliquePossivel = true;
                            offsetX = p.x - quadrado.x;
                            offsetY = p.y - quadrado.y;
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if(arrastando){
                        cliquePossivel = false; // se mexeu, não é clique
                        quadrado.x = evento.motion.x - offsetX;
                        quadrado.y = evento.motion.y - offsetY;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if(evento.button.button == SDL_BUTTON_LEFT){
                        if(cliquePossivel){
                            cliqueNoQuadrado(quadrado);
                        }
                        arrastando = false;
                        cliquePossivel = false;
                    }
                    break;

                case SDL_KEYDOWN:
                    if(evento.key.keysym.sym == SDLK_ESCAPE && arrastando){
                        SDL_Log("Gesto cancelado, voltando à posição original.");
                        quadrado = posicaoOriginal;
                        arrastando = false;
                        cliquePossivel = false;
                    }
                    break;
            }
        }
    }

    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}
