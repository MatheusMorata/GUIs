#include <SDL2/SDL.h>

// Constantes
#define Titulo "ex-1.2.1"
#define Largura 800
#define Altura 600

int main(int argc, char* args[]){

    SDL_Init(SDL_INIT_EVERYTHING); // Inicializando SDL

    // Criando uma janela
    SDL_Window *janela = SDL_CreateWindow(
        Titulo, 
        SDL_WINDOWPOS_CENTERED, // Posição x
        SDL_WINDOWPOS_CENTERED, // Posição y
        Largura, 
        Altura, 
        SDL_WINDOW_SHOWN // Mantém visível
    );    

    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0); // Criando um renderizador

    SDL_Rect quadradoVermelho = {
        200, // Posição x 
        100, // Posição y
        150, // Largura
        150 // Altura
    };

    SDL_Rect quadradoVerde = {
        360, 
        100, 
        150, 
        150 
    };

    SDL_Rect quadradoAzul = {
        200, 
        260, 
        150, 
        150 
    };

    SDL_Rect quadradoAmarelo = {
        360,
        260,
        150,
        150 
    };

    // Definindo cor da tela
    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255); 
    SDL_RenderClear(renderizador);

    // Desenhando os quadrados
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
    SDL_RenderFillRect(renderizador, &quadradoVermelho);

    SDL_SetRenderDrawColor(renderizador, 0, 255, 0, 255);
    SDL_RenderFillRect(renderizador, &quadradoVerde);

    SDL_SetRenderDrawColor(renderizador, 135, 206, 255, 255);
    SDL_RenderFillRect(renderizador, &quadradoAzul);

    SDL_SetRenderDrawColor(renderizador, 255, 255, 0, 255);
    SDL_RenderFillRect(renderizador, &quadradoAmarelo);

    SDL_RenderPresent(renderizador);
    SDL_Delay(5000);

    return 0;
}