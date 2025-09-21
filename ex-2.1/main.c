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

int main(int agrs, char* argc[]) {
    // Inicialização
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio - 2.1 (Detecção de Duplo Clique)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0); 

    SDL_Event evento;
    bool rodando = true;
    Uint32 ultimoClique = 0;
    int intervaloDuploClique = 300; 

    while (rodando) {
        Uint32 timeout = 1000; 
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
                        }
                        ultimoClique = agora;
                    }
                    break;
            }
        }
    }

    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
