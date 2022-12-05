#ifdef RELPATH
    #include "main.h"
#else
    #include "inc/main.h"
#endif

void libinfo();

int APIENTRY WinMain(HINSTANCE hi1, HINSTANCE hi2, LPSTR l, int i)
{
    rblocale_ru;
    libinfo();
    int a = main(0, NULL);
}

int main(int argc, char *argv[])    //SDL main
{
    printf("SDL2 STARTED\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL2 INITIALIZED\n");
        return 1;
    }
}