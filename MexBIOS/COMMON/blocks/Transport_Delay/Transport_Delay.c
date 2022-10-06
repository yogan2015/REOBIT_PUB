/*Краткая инструкция по запуску блока.
1. Создаем в LD-скрипте в области памяти RAM секцию (device_data_section_name),
в которую будем складывать значения нашего буффера.
2. В h-файле "project_name.h" добавляем строку
extern uint32_t __attribute__((section (".device_data_section_name"))) Buffer_name[Buffer_size].
3. Создаем буффер, например в С-файле "board_project_name.c": uint32_t Buffer_name[Buffer_size].
4. Подключаем соотвествующий h-файл.
5. Используем в коде имя буффрер. */

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

  /* Очищаем буффер, созданный в RAM */
  for (j = 0; j < 1024; j++)
  {
     //Buffer_name[j] = 0;
  }
  v->Clear = 1; //Флаг о том, что буффер очищен
}

if (!*v->R)
{
  v->Clear = 0;
  switch (v->State)
  {
    case 0: //Инициализация. Кладем в буффер входные значения в течение времени, меньше чем вермя задержки.
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

    case 1: //Обновляем каждый такт буффер
      v->Time++;
      //v->Out = Buffer_name[v->i]; //Передаем на выход значение In(t - Tdel)
      //Buffer_name[v->i] = *v->In; //Ложим в буффер значение In(t)
      if (v->Time >= *v->T_del) //Обнуляем индекс буффера после того как прошло время t, равное 1-ому периоду входного сигнала
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

