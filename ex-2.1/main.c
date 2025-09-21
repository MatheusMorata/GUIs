#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int AUX_WaitEventTimeout(SDL_Event *evento, Uint32 *ms) {
    if (ms == NULL) {
        return 0; // segurança
    }

    Uint32 inicio = SDL_GetTicks();
    int resultado = SDL_WaitEventTimeout(evento, *ms);
    Uint32 fim = SDL_GetTicks();
    Uint32 decorrido = fim - inicio;

    if (decorrido >= *ms) {
        *ms = 0;
    } else {
        *ms -= decorrido;
    }

    return resultado; 
}

void executarAnimacao(SDL_Renderer *renderer, SDL_Texture **frames, int totalFrames) {
    for (int i = 0; i < totalFrames; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fundo branco
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frames[i], NULL, NULL);
        SDL_RenderPresent(renderer); 
    }
}

int main(int agrs, char* argc[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio - 2.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *frames[10];
    char caminho[64];
    for (int i = 0; i < 10; i++) {
        snprintf(caminho, sizeof(caminho), "img/anim%d.png", i);
        SDL_Surface *img = IMG_Load(caminho);
        if (!img) {
            SDL_Log("Erro ao carregar %s: %s", caminho, IMG_GetError());
            return -1;
        }
        frames[i] = SDL_CreateTextureFromSurface(renderizador, img);
        SDL_FreeSurface(img);
    }

    SDL_Event evento;
    bool rodando = true;
    Uint32 ultimoClique = 0;
    int intervaloDuploClique = 300; 

    while (rodando) {
        Uint32 timeout = 1000;

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
        SDL_RenderClear(renderizador);
        SDL_RenderCopy(renderizador, frames[0], NULL, NULL);
        SDL_RenderPresent(renderizador);
        
        if (AUX_WaitEventTimeout(&evento, &timeout)) {
            switch (evento.type) {
                case SDL_QUIT:
                    rodando = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (evento.button.button == SDL_BUTTON_LEFT) {
                        Uint32 agora = SDL_GetTicks();
                        if (agora - ultimoClique <= (Uint32)intervaloDuploClique) {
                            SDL_Log("Duplo clique detectado!");
                            executarAnimacao(renderizador, frames, 10);
                        }
                        ultimoClique = agora;
                    }
                    break;
            }
        }
    }

    // Liberar recursos
    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(frames[i]);
    }

    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();
    return 0;
}