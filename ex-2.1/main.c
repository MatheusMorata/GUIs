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
    int i;

    // Recursos essenciais
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *janela = SDL_CreateWindow(
        "Exercicio - 2.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0); 

    SDL_Texture *animacao[10];
    char caminho[64];
    for (i = 0; i < 10; i++) {
        SDL_Surface *superficie;
        snprintf(caminho, sizeof(caminho), "img/anim%d.png", i);
        superficie = IMG_Load(caminho);
        if (!superficie) { 
            printf("Erro ao carregar %s\n", caminho); 
            return 1; 
        }
        animacao[i] = SDL_CreateTextureFromSurface(renderizador, superficie);
        SDL_FreeSurface(superficie);
    }

    SDL_Surface *superficieMunicao = IMG_Load("Municao.png");
    SDL_Surface *superficieEspada = IMG_Load("Espada.png");
    SDL_Texture *texturaMunicao = SDL_CreateTextureFromSurface(renderizador, superficieMunicao);
    SDL_Texture *texturaEspada  = SDL_CreateTextureFromSurface(renderizador, superficieEspada);
    SDL_FreeSurface(superficieMunicao);
    SDL_FreeSurface(superficieEspada);

    bool rodando = true;
    SDL_Event evento;
    int quadro = 0;
    int modo = 0; 
    int code = 0;
    Uint32 tempoLimite = 0;

    Uint32 ultimoTempoQuadro = 0;
    Uint32 atrasoQuadro = 100; 

    SDL_Rect destino;
    destino.x = 300;
    destino.y = 200;
    destino.w = 200;
    destino.h = 200;

    // LOOP PRINCIPAL
    while (rodando) {
        Uint32 agora = SDL_GetTicks();

        if (tempoLimite > 0) {
            if (!AUX_WaitEventTimeout(&evento, &tempoLimite)) {
                SDL_Event eventoUsuario;
                eventoUsuario.type = SDL_USEREVENT;
                eventoUsuario.user.code = code; 
                SDL_PushEvent(&eventoUsuario);
                code = 0;
                continue;
            }
        } else {
            SDL_PollEvent(&evento);
        }

        if (evento.type == SDL_QUIT) {
            rodando = false;
        }
        else if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT) {
            code++;
            tempoLimite = 300; 
        }
        else if (evento.type == SDL_USEREVENT) {
            if (evento.user.code == 2) {
                modo = 2;
                quadro = 0;
                ultimoTempoQuadro = agora;
            } else if (evento.user.code == 3) {
                modo = 3;
                quadro = 0;
                ultimoTempoQuadro = agora;
            }
        }

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);

        if (modo == 2 || modo == 3) {
            if (quadro < 10) {
                if (agora - ultimoTempoQuadro >= atrasoQuadro) {
                    quadro++;
                    ultimoTempoQuadro = agora;
                }
                SDL_RenderCopy(renderizador, animacao[quadro < 10 ? quadro : 9], NULL, &destino);
            } else {
                if (modo == 2)
                    SDL_RenderCopy(renderizador, texturaMunicao, NULL, &destino);
                else if (modo == 3)
                    SDL_RenderCopy(renderizador, texturaEspada, NULL, &destino);
            }
        } else {
            SDL_RenderCopy(renderizador, animacao[0], NULL, &destino);
        }

        SDL_RenderPresent(renderizador);
    }

    // Liberando recursos 
    for (i = 0; i < 10; i++) {
        SDL_DestroyTexture(animacao[i]);
    }
    SDL_DestroyTexture(texturaMunicao);
    SDL_DestroyTexture(texturaEspada);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();
    return 0;
}