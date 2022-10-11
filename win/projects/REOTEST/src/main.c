#include "../inc/main.h"
FILE *f_inputs;
FILE *f_outputs;


union REOTEST_DATA_U h_outputs;
union REOTEST_DATA_U h_inputs;
void REOTEST_DEFAULT_HEADER(union REOTEST_DATA_U* HEADER, int SIZE)
{
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    char checksum;
    HEADER->h.KEY0 = 'Y';
    HEADER->h.KEY1 = 'H';
    HEADER->h.KEY2 = 'W';
    HEADER->h.KEY3 = 'H';
    HEADER->h.SIZE      = SIZE;
    HEADER->h.D_YEAR    = now.tm_year;
    HEADER->h.D_MONTH   = now.tm_mon;
    HEADER->h.D_DAY     = now.tm_mday;
    HEADER->h.T_HOUR    = now.tm_hour;
    HEADER->h.T_MIN     = now.tm_min;
    checksum = HEADER->c[0];
    for (int i=1; i<=17;i++)
    {
        checksum ^= HEADER->c[i];
    }
    HEADER->h.checksum = checksum;
    HEADER->h.term = '}';
};

void main(int argc, char *argv[])
{
    char err_input      = 0;
    char err_output     = 0;
    char *c;
    for (int i=0; i<argc; i++)                                              // поиск входного файла в аргументах командной строки
        {
            c = argv[i];
            if ((*c=='-')&&(*(c+1)=='i'))                                       // найдена команда "-i", в следующей будет содержаться имя файла
            {
                printf("input file: %s\n",argv[i+1]);
                if((f_inputs = fopen((char *)argv[i+1], "r"))!= NULL)               // пытаемся открыть файл
                {
                    char checksum = (char)0x00;
                    for (int j=0; j<(sizeof(struct REOTEST_DATA_HEADER)-2);j++)
                    {
                        h_inputs.c[j] = (char)getc(f_inputs);
                        //printf("%c", h_inputs.c[j]);
                        checksum ^= h_inputs.c[j];
                    }
                    h_inputs.c[sizeof(struct REOTEST_DATA_HEADER)-1] = (char)getc(f_inputs);
                    if(h_inputs.c[sizeof(struct REOTEST_DATA_HEADER)-1] == checksum)
                    {
                        //printf("%x = %x, header is ok.\n",checksum, checksum);
                        getc(f_inputs);
                    }    else
                    {
                        //printf("%x != %x, header is incorrect.\n",checksum, h_inputs.c[sizeof(struct REOTEST_DATA_HEADER)-1]);
                    }
                    //printf("\nsize of input:%d\n",h_inputs.h.SIZE);
                    i = argc+1;
                } else                                                             
                {
                    //printf("Can't open %s\n", argv[i+1]);
                }
            }
        }

    REOTEST_DEFAULT_HEADER(&h_outputs, 0);
    for (int i=0; i<argc; i++) // поиск входного файла в аргументах командной строки
        {
            c = argv[i];
            //printf("%x : %s : %c\n",c,c,*(c+1));
            if ((*c=='-')&&(*(c+1)=='o'))
            {
                printf("output file: %s.txt\n",argv[i+1]);
                f_outputs = fopen((char *)argv[i+1], "w");
                i = argc+1;
            }
            if (i==(argc-1))
            {
                printf("output file: results.out \n");
                f_outputs = fopen("results.out", "w");
            }
        }

        
    char checksum = (char)0x00;
    for (int j=0; j<sizeof(struct REOTEST_DATA_HEADER); j++)
        {
            putc(h_outputs.c[j],f_outputs);
            checksum ^= h_outputs.c[j];
            //printf("checksum:%x %x\n", h_outputs.c[j], checksum);
        }
    putc(checksum, f_outputs);
    putc('}', f_outputs);

    fclose(f_inputs);   fclose(f_outputs);
}