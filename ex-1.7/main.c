#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define NUM_FRAMES 9
#define FRAME_DELAY 100 // ms por frame

int AUX_WaitEventTimeout(SDL_Event *evt, Uint32 *ms) {
    if (ms == NULL) {
        return 0; // segurança
    }

    Uint32 start = SDL_GetTicks();
    int result = SDL_WaitEventTimeout(evt, *ms);
    Uint32 end = SDL_GetTicks();
    Uint32 elapsed = end - start;

    if (elapsed >= *ms) {
        *ms = 0;
    } else {
        *ms -= elapsed;
    }

    return result; 
}

int main(int args, char* argc[]) {
    bool rodando = true;
    int timeout = 16;
    SDL_Event evento;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* janela = SDL_CreateWindow(
        "Animacao Sprite",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    // Carregar as 9 imagens
    SDL_Texture* frames[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; i++) {
        char filename[64];
        sprintf(filename, "img/anim_%d.png", i+1);
        frames[i] = IMG_LoadTexture(renderizador, filename);
        if (!frames[i]) {
            printf("Erro ao carregar %s: %s\n", filename, IMG_GetError());
            return -1;
        }
    }

    SDL_Rect quadrado = {50, 50, 300, 300};

    int frameAtual = 0;
    Uint32 ultimoTempo = SDL_GetTicks();

    while (rodando) {
        // Eventos
        while (AUX_WaitEventTimeout(&evento, &timeout)) {
            if (evento.type == SDL_QUIT) {
                rodando = false;
            }
        }

        // Atualizar frame
        Uint32 agora = SDL_GetTicks();
        if (agora - ultimoTempo >= FRAME_DELAY) {
            frameAtual = (frameAtual + 1) % NUM_FRAMES;
            ultimoTempo = agora;
        }

        // Desenhar
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);
        SDL_RenderCopy(renderizador, frames[frameAtual], NULL, &quadrado);
        SDL_RenderPresent(renderizador);
    }

    // Liberar recursos
    for (int i = 0; i < NUM_FRAMES; i++) {
        SDL_DestroyTexture(frames[i]);
    }
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
