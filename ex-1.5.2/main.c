#include <SDL2\SDL.h>

int main(int argc, char* args[]){

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Janela *janela = SDL_CreateWindow(
    "Exercicio 1.5.2",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    800, 600, 
    SDL_WINDOW_SHOWN
  );

  SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);
  

  return 0;
}
