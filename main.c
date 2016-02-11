#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 * Error handling function. Makes sure 'test' is true, and if it is not,
 * formats and prints string 'message' to stderr and exits the program.
 */
void check (int test, const char * message, ...)
{
    if (test) {
        va_list args;
        va_start (args, message);
        vfprintf (stderr, message, args);
        va_end (args);
        fprintf (stderr, "\n");
        exit (EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    check(argc < 2, "Usage: %s <filename>\n", argv[0]);

    int err;
    err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    check(err != 0, "Error: failed to initalize SDL: \"%s\"\n", SDL_GetError());
    err = IMG_Init(IMG_INIT_PNG);
    check(err == 0, "Error: failed to initalize SDL_image: \"%s\"\n", SDL_GetError());

    SDL_Surface *sur = IMG_Load(argv[1]);
    check(sur == NULL, "Error loading image \"%s\"\n", argv[1]);

    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_CreateWindowAndRenderer(sur->w, sur->h, 0, &win, &ren);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, sur);
    SDL_FreeSurface(sur);

    /* Number of textures to draw, doubles every iteration. */
    int numDraws = 2;

    printf("textures, miliseconds,     tex/ms,\n");

    int loop = 1;
    SDL_Event e;
    while(loop) {
        int start, end, i;
        start = SDL_GetTicks();
        for(i=0; i<numDraws; ++i)
            SDL_RenderCopy(ren, tex, NULL, NULL);
        end = SDL_GetTicks();
        SDL_RenderPresent(ren);

        int time = end-start;
        float rate = time==0 ? INFINITY : (float)numDraws/time;

        printf("%8d, %11d, %10.2f,\n", numDraws, time, rate);

        numDraws *= 2;

        while(SDL_PollEvent(&e))
            if(e.type == SDL_QUIT)
                loop = 0;
    }

    IMG_Quit();
    SDL_Quit();
    return 0;
}
