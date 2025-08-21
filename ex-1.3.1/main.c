#include <SDL2\SDL.h>
#include <stdbool.h>

int main(int argc, char* args[]){

    bool acabou = false;
    int direcao = 1;

    // Iniciando SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Iniciando janela
    SDL_Window *janela = SDL_CreateWindow(
        "1.3.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    // Iniciando renderizador
    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);

    // Definindo o quadrado
    SDL_Rect quadrado = {
        0, // Posição X
        300, // Posição Y
        50, // Largura
        50  // Altura
    };

    // Looping principal
    while(acabou == false){
        // Colorindo fundo de branco    
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
        SDL_RenderClear(renderizador);

        // Desenhando o quadrado azul
        SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 255);
        SDL_RenderFillRect(renderizador, &quadrado);

        // EXIBINDO RESULTADO
        SDL_RenderPresent(renderizador);
        SDL_Delay(16);
        
        // Animação
        quadrado.x = (quadrado.x + 10) * direcao;

    }

    return 0;
}