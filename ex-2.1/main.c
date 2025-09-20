#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

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

int main(int agrs, char* argc[]){

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

    SDL_Texture *anim[10];
    char caminho[64];
    for (int i = 0; i < 10; i++) {
        snprintf(caminho, sizeof(caminho), "img/anim%d.png", i);
        SDL_Surface *surf = IMG_Load(caminho);
        if (!surf) { printf("Erro ao carregar %s\n", caminho); return 1; }
        anim[i] = SDL_CreateTextureFromSurface(renderizador, surf);
        SDL_FreeSurface(surf);
    }

    SDL_Surface *sMun = IMG_Load("Municao.png");
    SDL_Surface *sEsp = IMG_Load("Espada.png");
    SDL_Texture *texMunicao = SDL_CreateTextureFromSurface(renderizador, sMun);
    SDL_Texture *texEspada  = SDL_CreateTextureFromSurface(renderizador, sEsp);
    SDL_FreeSurface(sMun);
    SDL_FreeSurface(sEsp);


    bool rodando = true;
    SDL_Event evento;
    int frame = 0;
    int modo = 0; 


    int code = 0;
    Uint32 timeout = 0;


    while (rodando) {

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 0);
        SDL_RenderClear(renderizador);

        if (timeout > 0) {
            if (!AUX_WaitEventTimeout(&evento, &timeout)) {
                SDL_Event userEvt;
                userEvt.type = SDL_USEREVENT;
                userEvt.user.code = code; 
                SDL_PushEvent(&userEvt);
                code = 0;
                continue;
            }
        } else {
            SDL_WaitEvent(&evento);
        }

        if (evento.type == SDL_QUIT) {
            rodando = false;
        }
        else if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT) {
            code++;
            timeout = 300; 
        }
        else if (evento.type == SDL_USEREVENT) {
            if (evento.user.code == 2) {
                modo = 2;
                frame = 0;
            } else if (evento.user.code == 3) {
                modo = 3;
                frame = 0;
            }
        }

        SDL_RenderClear(renderizador);

        if (modo == 2 || modo == 3) {
            if (frame < 10) {
                SDL_RenderCopy(renderizador, anim[frame], NULL, NULL);
                frame++;
                SDL_Delay(100);
            } else {
                if (modo == 2)
                    SDL_RenderCopy(renderizador, texMunicao, NULL, NULL);
                else if (modo == 3)
                    SDL_RenderCopy(renderizador, texEspada, NULL, NULL);
            }
        }

        SDL_RenderPresent(renderizador);
    }

    // Liberando recursos
    for (int i = 0; i < 10; i++) SDL_DestroyTexture(anim[i]);
    SDL_DestroyTexture(texMunicao);
    SDL_DestroyTexture(texEspada);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();
    return 0;
}