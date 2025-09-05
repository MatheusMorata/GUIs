#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeoutCount(SDL_Event *event, Uint32 *ms) {
    if (!ms){
      return 0; 
    }
    
    // "espera infinita"
    if (*ms == SDL_MAX_UINT32) {
        return SDL_WaitEvent(event);
    }

    // não espera nada
    if (*ms == 0) {
        return SDL_PollEvent(event);
    }

    Uint32 start = SDL_GetTicks();
    int result = SDL_WaitEventTimeout(event, *ms);
    Uint32 elapsed = SDL_GetTicks() - start;

    // subtrai o tempo gasto 
    if (elapsed >= *ms) {
        *ms = 0;
    } else {
        *ms -= elapsed;
    }

    return result;
}
