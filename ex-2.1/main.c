#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int AUX_WaitEventTimeout(SDL_Event *evento, Uint32 *ms) {
    if (ms == NULL) return 0;
    Uint32 inicio = SDL_GetTicks();
    int resultado = SDL_WaitEventTimeout(evento, *ms);
    Uint32 fim = SDL_GetTicks();
    Uint32 decorrido = fim - inicio;
    if (decorrido >= *ms) *ms = 0;
    else *ms -= decorrido;
    return resultado; 
}

void executarAnimacao(SDL_Renderer *renderer, SDL_Texture **frames, int totalFrames, SDL_Rect *dest) {
    for (int i = 0; i < totalFrames; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frames[i], NULL, dest);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
}

void disparar(SDL_Renderer *renderer, SDL_Texture *proj, SDL_Texture *frameParado, SDL_Rect *destAnim,
              int larguraJanela, int alturaJanela, int w, int h) {
    SDL_Rect objeto;
    objeto.w = w;
    objeto.h = h;
    objeto.x = 450;
    objeto.y = 330;

    while (objeto.x < larguraJanela) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frameParado, NULL, destAnim);
        SDL_RenderCopy(renderer, proj, NULL, &objeto);
        SDL_RenderPresent(renderer);
        objeto.x += 5; 
        SDL_Delay(10);
    }
}

int main(int agrs, char* argc[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    int larguraJanela = 800;
    int alturaJanela = 600;

    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio - 2.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        larguraJanela, alturaJanela,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *frames[10];
    char caminho[64];
    for (int i = 0; i < 10; i++) {
        snprintf(caminho, sizeof(caminho), "img/anim%d.png", i);
        frames[i] = IMG_LoadTexture(renderizador, caminho);
        if (!frames[i]) {
            SDL_Log("Erro ao carregar %s: %s", caminho, IMG_GetError());
            return -1;
        }
    }
    SDL_Texture *municao = IMG_LoadTexture(renderizador, "img/Municao.png");
    SDL_Texture *espada  = IMG_LoadTexture(renderizador, "img/Espada.png");
    if (!municao || !espada) {
        SDL_Log("Erro ao carregar imagens de projéteis!");
        return -1;
    }

    SDL_Rect dest;
    dest.w = 200;
    dest.h = 200;
    dest.x = (larguraJanela - dest.w) / 2;
    dest.y = (alturaJanela - dest.h) / 2;

    SDL_Event evento;
    bool rodando = true;

    Uint32 ultimoClique = 0;
    int contadorCliques = 0;
    int intervaloClique = 500;
    bool acaoPendente = false;

    while (rodando) {
        Uint32 timeout = 50;
        Uint32 agora = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
        SDL_RenderClear(renderizador);
        SDL_RenderCopy(renderizador, frames[0], NULL, &dest);
        SDL_RenderPresent(renderizador);

        if (AUX_WaitEventTimeout(&evento, &timeout)) {
            switch (evento.type) {
                case SDL_QUIT:
                    rodando = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (evento.button.button == SDL_BUTTON_LEFT) {
                        if (agora - ultimoClique <= (Uint32)intervaloClique) {
                            contadorCliques++;
                        } else {
                            contadorCliques = 1;
                        }
                        ultimoClique = agora;
                        acaoPendente = true;
                    }
                    break;
            }
        }

        if (acaoPendente && (agora - ultimoClique > (Uint32)intervaloClique)) {
            if (contadorCliques == 2) {
                executarAnimacao(renderizador, frames, 10, &dest);
                disparar(renderizador, municao, frames[0], &dest, larguraJanela, alturaJanela, 40, 20);
            } else if (contadorCliques == 3) {
                executarAnimacao(renderizador, frames, 10, &dest);
                disparar(renderizador, espada, frames[0], &dest, larguraJanela, alturaJanela, 60, 40);
            }
            contadorCliques = 0;
            acaoPendente = false;
        }
    }

    for (int i = 0; i < 10; i++) SDL_DestroyTexture(frames[i]);
    SDL_DestroyTexture(municao);
    SDL_DestroyTexture(espada);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
