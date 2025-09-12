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
