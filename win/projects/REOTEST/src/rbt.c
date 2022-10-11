#include "..\inc\rbt.h"
int     rbt_get_input (int argc, char* argv[], char** name)
{
    char *c;
    for (int i=0; i<argc-1; i++)
    {
        c = argv[i];
        if ((*c=='-')&&(*(c+1)=='i')) 
        {
            *name = (char*)argv[i+1];
            return 0;    
        }
    }
    return 1;
}

int     rbt_get_output (int argc, char* argv[], char** name)
{
    char *c;
    for (int i=0; i<argc-1; i++)
    {
        c = argv[i];
        if ((*c=='-')&&(*(c+1)=='o')) 
        {
            *name = (char*)argv[i+1];
            return 0;    
        }
    }
    return 1;
}

int rbt_input_open(FILE* inputs, int argc, char* argv[], char** name)
{
    char* fname;
    if (rbt_get_input(argc, argv, &fname))
    {
        return 1;   // анализ командной строки завершился с ошибкой
    }
    
    if ((inputs = (FILE*)fopen(fname,"r"))==NULL)
    {
        return 2;   // искомый файл не существует
    }
    *name = fname;
    
    if (rbt_header_check(inputs))
    {
        union rbtu_header m;
        char checksum = 0x00;
        for (int i=0; i<sizeof(m)-2;i++)
        {
            m.c[i] = getc(inputs);
            checksum ^= m.c[i];
        }
        checksum ^= getc(inputs);
        if (checksum)
        {
            return 3;   //  неправильный формат загоровка, контрольная сумма не соотв.
        }
        getc(inputs);
    }

    fclose(inputs);
    return 0;
}

int rbt_output_open(FILE* outputs, int argc, char* argv[], char** name)
{
    char* fname;
    char* default_fname = "result.output";
    if (rbt_get_output(argc, argv, &fname))
    {
        sareturn 1;   // анализ командной строки завершился с ошибкой
    }
}

int     rbt_header_check(FILE* inputs)
{
    char a = getc(inputs);
    return 1;
}

void rbt_header_print(FILE* outputs)
{

}



void rbt_frame_read(FILE* inputs, union rbtu_inputs* frame)
{

}

void rbt_frame_write(FILE* outputs, union rbtu_outputs* frame)
{

}