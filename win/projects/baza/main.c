#ifdef RELPATH
    #include "main.h"
#else
    #include "inc/main.h"
#endif

void libinfo();

void main()
{
    rblocale_ru;
    libinfo();
}