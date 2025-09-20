#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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



    // Liberando recursos
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();
    return 0;
}