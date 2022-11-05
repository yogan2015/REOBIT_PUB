#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// структуры
    struct rbt_inputs
    {
        int AI[60];     // числовые входы
        int DI[4];      // дискретные входы
    };

    union rbtu_inputs
    {
        int                 c[64];
        struct rbt_inputs   h;
    };

    struct rbt_outputs
    {
        int AO[60];     //  числовые выходы
        int DO[4];      //  дискретные выходы
    };

    union rbtu_outputs
    {
        int                 c[64];
        struct rbt_outputs  h;
    };

    struct rbt_status
    {
        int AS[120];    //  числовые переменные состояния
        int DS[8];       //  дискретные переменные состояния
    };

    union rbtu_status
    {
        int                 c[128];
        struct rbt_status   h;
    };

    struct rbt_header
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

    union rbtu_header
    {
        char c[16];
        struct rbt_header h;
    };

// Прототипы функций

    int     rbt_get_input       (int argc, char* argv[], char** name);
    int     rbt_get_output      (int argc, char* argv[], char** name);
    
    int     rbt_input_open      (FILE* inputs,  int argc, char* argv[], char** name);
    int     rbt_output_open     (FILE* outputs, int argc, char* argv[], char** name);

    int     rbt_header_check    (FILE* inputs);     // проверка заголовка
    void    rbt_header_print    (FILE* outputs);    // запись заголовка

    void    rbt_frame_read      (FILE* inputs, union rbtu_inputs* frame);
    void    rbt_frame_write     (FILE* outputs, union rbtu_outputs* frame);

    void    rbt_update          (union rbtu_inputs* frame_in, union rbtu_outputs* frame_out);

    void    rbt_convert_csv     ();