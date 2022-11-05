#include "../inc/main.h"
#define GLUT_DISABLE_ATEXIT_HACK
FILE *f_inputs;
FILE *f_outputs;

void samplestring(char **ass, char *argv[])
{
    *ass = (char*)argv[1];
    printf("%x(%x) - value(adr) of argv[1]\n", argv[1],*argv[1]);
    printf("%x(%x) - value(adr) of output\n", ass,*ass);
    printf("sample string:\"%s\"\n",argv[1]);
}

typedef int (*rbproc)(LPTSTR);
          
void display()
{

}

void main(int argc, char *argv[])
{
    #ifdef USEDLL
    HMODULE hm = LoadLibrary("glut32.dll");

    rbproc  glutInit,
            glutInitDisplayMode,
            glutInitWindowSize,
            glutInitWindowPosition,
            glutInitCreateWindow;

    if(hm == NULL)
    {
        printf("glut32.dll not found!\n");
    }
    else
    {
        printf("glut32.dll found successfully!\n");
        glutInit =                  (rbproc)GetProcAddress(hm, "glutInit");
        glutInitDisplayMode =       (rbproc)GetProcAddress(hm, "glutInitDisplayMode");
        glutInitWindowSize =        (rbproc)GetProcAddress(hm, "glutInitWindowSize");
        glutInitWindowPosition =    (rbproc)GetProcAddress(hm, "glutInitWindowPosition");
        glutInitCreateWindow =      (rbproc)GetProcAddress(hm, "glutInitCreateWindow");
        if (!(glutInit == NULL))
            {   printf("glutInit ON\n");                } 
        else{   printf("no function loaded\n");         }
        if (!(glutInitDisplayMode == NULL))
            {   printf("glutInitDisplayMode ON\n");     } 
        else{   printf("no function loaded\n");         }        
        if (!(glutInitWindowSize == NULL))
            {   printf("glutInitWindowSize ON\n");      } 
        else{   printf("no function loaded\n");         }
        if (!(glutInitWindowPosition == NULL))
            {   printf("glutInitWindowPosition ON\n");  } 
        else{   printf("no function loaded\n");         }
        if (!(glutInitCreateWindow == NULL))
            {   printf("glutInitCreateWindow ON\n");  } 
        else{   printf("no function loaded\n");         }
        glutInit();
        glutInitWindowSize(800, 600);
        glutInitCreateWindow("ass");
    }
    #endif
    glutInit(0, NULL);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("ass");
    glutDisplayFunc(display);
    glutMainLoop();
    rblocale_ru;
 
    //fclose(f_inputs);   fclose(f_outputs);
    //FreeLibrary(hm);
}

#ifdef jopa
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


char err_input      = 0;
    char err_output     = 0;
    char *c;
    for (int i=0; i<argc; i++)                                              // ����� �������� ����� � ���������� ��������� ������
        {
            c = argv[i];
            if ((*c=='-')&&(*(c+1)=='i'))                                       // ������� ������� "-i", � ��������� ����� ����������� ��� �����
            {
                printf("input file: %s\n",argv[i+1]);
                if((f_inputs = fopen((char *)argv[i+1], "r"))!= NULL)               // �������� ������� ����
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
    for (int i=0; i<argc; i++) // ����� �������� ����� � ���������� ��������� ������
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
#endif