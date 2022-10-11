#include <time.h>

struct REOTEST_INPUT
{
    int AI[60];     // числовые входы
    int DI[4];      // дискретные входы
};

struct REOTEST_OUTPUT
{
    int AO[60];     //  числовые выходы
    int DO[4];      //  дискретные выходы
};

struct REOTEST_STATE
{
    int AS[120];    //  числовые переменные состояния
    int DS[8];       //  дискретные переменные состояния
};

struct REOTEST_DATA_HEADER
{
    char KEY0;
    char KEY1;
    char KEY2;
    char KEY3;
    int SIZE;
    short D_YEAR;
    short D_MONTH;
    int D_DAY;
    char T_HOUR;
    char T_MIN;
    char checksum;
    char term;
};

union REOTEST_DATA_U
{
    char c[16];
    struct REOTEST_DATA_HEADER h;
};

void REOTEST_DEFAULT_HEADER(union REOTEST_DATA_U* HEADER, int SIZE);
