/*������� ���������� �� ������� �����.
1. ������� � LD-������� � ������� ������ RAM ������ (device_data_section_name),
� ������� ����� ���������� �������� ������ �������.
2. � h-����� "project_name.h" ��������� ������
extern uint32_t __attribute__((section (".device_data_section_name"))) Buffer_name[Buffer_size].
3. ������� ������, �������� � �-����� "board_project_name.c": uint32_t Buffer_name[Buffer_size].
4. ���������� �������������� h-����.
5. ���������� � ���� ��� �������. */

#ifndef __BORLANDC__
#include "stm32f4xx.h"
//#include "project_name.h"
#endif

// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
#ifndef __BORLANDC__
long j;

if (*v->R && !v->Clear)
{
  v->State =0;
  v->Time = 0;
  v->i = 0;

  /* ������� ������, ��������� � RAM */
  for (j = 0; j < 1024; j++)
  {
     //Buffer_name[j] = 0;
  }
  v->Clear = 1; //���� � ���, ��� ������ ������
}

if (!*v->R)
{
  v->Clear = 0;
  switch (v->State)
  {
    case 0: //�������������. ������ � ������ ������� �������� � ������� �������, ������ ��� ����� ��������.
      v->Out = 0;
      v->Time++;
      //Buffer_name[v->i] = *v->In;
      v->i++;
      if (v->Time >= *v->T_del)
      {
        v->i = 0;
        v->State = 1;
        v->Time = 0;
      }
    break;

    case 1: //��������� ������ ���� ������
      v->Time++;
      //v->Out = Buffer_name[v->i]; //�������� �� ����� �������� In(t - Tdel)
      //Buffer_name[v->i] = *v->In; //����� � ������ �������� In(t)
      if (v->Time >= *v->T_del) //�������� ������ ������� ����� ���� ��� ������ ����� t, ������ 1-��� ������� �������� �������
      {
        v->i = 0;
        v->Time = 0;
      }
      else
      {
        v->i++;
      }
    break;
  }
}
else
{
  v->Out = 0;
}
#endif
}

