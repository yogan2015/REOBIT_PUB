#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif

void libinfo()
{
    char* c_date = __DATE__;
    char* c_time = __TIME__;
    char* copyright = "\tREOBIT Ltd. SPb RUSSIA\n\t\t\tIgor Khristich";
    printf("library built: \t\t%s\n\t\t\t%s\ncopyright:\t%s\n\n", c_date, c_time, copyright);    
    copyright = "\t\t��� ������ ��� ������\n\t\t\t������� �. �.";
    printf("���������� ���������: \t%s\n\t\t\t%s\n��������:%s\n", c_date, c_time, copyright);
}