#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

int main (int argc, char* args[])
{
    int mouseX, mouseY;
    SDL_Rect r_lista[10];
    int vermelho[10];
    int verde[10];
    int azul[10];
    int num_retangulos = 0;
    srand(time(NULL));

    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 400, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event event;
    bool rodando = true;
    while (rodando) {

        // Posibilita que a janela seja fechada pelo alt + f4 ou pelo [X] 
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                rodando = false;
            }
        }

        // Não permite que o retângulo exceda os limites da tela
        if(r.x > 390){
            r.x = 390;
        }else if(r.x < 0){
            r.x = 0;
        }else if(r.y > 390){
            r.y = 390;
        }else if(r.y < 0){
            r.y = 0;
        }

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);

        // Desenhando os quadrados
        for(int i = 0; i < num_retangulos; i++){
            SDL_SetRenderDrawColor(ren, vermelho[i], verde[i], azul[i], 255);
            SDL_RenderFillRect(ren, &r_lista[i]);
        }
        
        SDL_RenderPresent(ren);
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 5;
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    break;
            }

        // Adiciona novos quadrados ao clickar
        }else if(event.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&mouseX, &mouseY);
            if(num_retangulos < 10){
                // Gera cores aleatórias 
                vermelho[num_retangulos] = rand() % 256;
                verde[num_retangulos] = rand() % 256;
                azul[num_retangulos] = rand() % 256;

                SDL_Rect novo = {mouseX, mouseY, 10, 10};
                r_lista[num_retangulos] = novo;
                num_retangulos++;
            }
        }
        SDL_Delay(16);        
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}