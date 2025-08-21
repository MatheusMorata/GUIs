#include <SDL2\SDL.h>

int main(int argc, char* args[]){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *janela = SDL_CreateWindow(
        "1.3.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    SDL_Delay(1000);
    return 0;
}
