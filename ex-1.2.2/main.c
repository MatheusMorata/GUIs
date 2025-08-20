#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>


int main(int argc, char* args[]){

    // Inicializando SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Criando janela
    SDL_Window *janela = SDL_CreateWindow(
        "GFX", // Título
        SDL_WINDOWPOS_CENTERED, // Posição em x
        SDL_WINDOWPOS_CENTERED, // Posição em y
        800, // Largura
        600, // Altura
        SDL_WINDOW_SHOWN // Manter visível
    );

    // Criando renderizador
    SDL_Renderer *renderizador = SDL_CreateRenderer(janela, -1, 0);

    // Colorindo fundo
    SDL_SetRenderDrawColor(renderizador, 0, 255, 64, 255);
    SDL_RenderClear(renderizador);

    // Definindo pontos do losango
    short pontosX[4] = {400, 700, 400, 100};  
    short pontosY[4] = {150, 300, 450, 300};    

    // Desenhando losango
    filledPolygonRGBA(renderizador, pontosX, pontosY, 4, 255, 255, 0, 255);
    SDL_RenderPresent(renderizador);

    // Desenhando círculo azul
    filledCircleRGBA(
        renderizador,
        400, // Posição x
        400, // Posição y
        100, // Raio
        0, 0, 255, 255 // RGBA
    );

    // EXIBINDO
    SDL_Delay(2000);

    return 0;
}