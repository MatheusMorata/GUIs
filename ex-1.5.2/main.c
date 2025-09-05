#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeoutCount(SDL_Event *evt, Uint32 *ms) {
    if (ms == NULL || *ms == 0) {
        // Se não há tempo restante, retorna imediatamente
        return 0;
    }

    Uint32 start = SDL_GetTicks();  // tempo inicial

    // Chama a função original com o tempo restante
    int result = SDL_WaitEventTimeout(evt, *ms);

    Uint32 end = SDL_GetTicks();    // tempo final
    Uint32 elapsed = end - start;   // tempo decorrido

    if (elapsed >= *ms) {
        *ms = 0;
    } else {
        *ms -= elapsed;
    }

    return result;
}
