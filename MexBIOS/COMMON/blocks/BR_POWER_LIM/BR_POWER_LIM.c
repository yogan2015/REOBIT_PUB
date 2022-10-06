#define INIT 0
#define BRAKE_ON 1 //Включение Brake.
#define STOP_COUNT 2 //Остановливаем счетчик на время установления равенства работ (рассчитанной от предельной характеристики ограничения мощности
//и рассчитанной от фактической мощности. Запускаем счетчик и характеристика ограничения продолжает строиться с теми же угловыми коэффициентами и
//по этой характеристике ограничевается фактическая мощность.
#define BRAKE_OFF 3 //Выключение Brake. Восстановление мощности.
#define SECTOR_SEARCHING_BR_ONOFF 4 //Посик участка на кривой восстановления, в котором находится мощность, зафиксированная в момент выключения Brake.
#define VALUE_SEARCHING_BR_ONOFF 5 //Поиск индекса массива (время, t), соотвествующее мощности, зафиксированной в момент выключения Brake из
//массива ограничения мощности. Индекс находится по уравнению прямой, прходящей через две точки, где данные точки это начальные и конечные значения
//найденного участка.
#define SECTOR_SEARCHING_BR_OFFON 6 //Посик участка на кривой ограничения, в котором находится мощность, зафиксированная в момент включения Brake.
#define VALUE_SEARCHING_BR_OFFON 7 //Поиск индекса массива (время, t), соотвествующее мощности, зафиксированной в момент включения Brake из
//массива восстановления мощности. Индекс находится по уравнению прямой, прходящей через две точки, где данные точки это начальные и конечные значения
//найденного участка.
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
float *t1_Buffer = (float *)*v->t1_Buff;
float *P1_Buffer = (float *)*v->P1_Buff;
float *t2_Buffer = (float *)*v->t2_Buff;
float *P2_Buffer = (float *)*v->P2_Buff;

if (*v->Reset_Counter)
  {
    v->Counter_Limit = 0;
    v->Pt_Ref_Sat = P1_Buffer[0];
    v->Integral_A = 0;
    v->Integral_B = 0;
    v->Alarm = 0;
    v->State = INIT;
    return;
  }

  switch (v->State)
  {
  case INIT:
    v->Pt_Ref_Sat = P1_Buffer[0];;
    v->Alarm = 0;
    v->Prev_Pt_Restore = 0;
    v->Prev_Pt_Lim = 0;
    if (*v->Brake_On)
    {
      v->State = BRAKE_ON;
    }
    break;

  case BRAKE_ON: //Включился Brake
    v->Prev_Pt_Lim = 0;
    if (*v->Brake_On < v->pBrake_On) //Условие выключения Brake, Спадающий фронт
    {
      v->State = SECTOR_SEARCHING_BR_ONOFF; //Поиск участка на кривой восстановления
      v->i = 0;
      v->Prev_Pt_Lim = *v->Pt_max_Limit; //Запоминаем текущее значение мощности
      v->Integral_A = 0;
      v->Integral_B = 0;
    }
    v->Counter_Limit += v->SampleTime;

   //Функция ограничения выхода
    v->Pt_Ref_Sat = *v->Pt_max_Limit;
    /*if (v->Pt_Ref_Sat >= *v->Pt_max_Limit)
    {
      v->Pt_Ref_Sat =*v->Pt_Ref;
    }
    if (v->Pt_Ref_Sat <= 0)
    {
      v->Pt_Ref_Sat = 0;
    }*/
    //Рассчет интегралов от мощности по времени, работа
    if (*v->Pt_Ref > P1_Buffer[v->NumPoints]) //Если заданная мощность больше номинальной, расчет интеграла
    {
    v->Integral_A = v->Integral_A + *v->Pt_max_Limit * v->SampleTime;  //Работа, рассчитанная от трактории ограничения мощности
    v->Integral_B = v->Integral_B + *v->Pt_Ref * v->SampleTime;  //Работа, рассчитанная от текущей мощности
    }

    if (v->Counter_Limit >= t1_Buffer[v->NumPoints])
    {
        v->Counter_Limit = t1_Buffer[v->NumPoints];
    }

    if (*v->Pt_max_Limit <= *v->Pt_Ref) //Определяем пересечение заданной мощности с траекторией ограничения мощности
    {
      v->State = STOP_COUNT;
    }

    if (v->Pt_Ref_Sat <= v->Alarm_Level)
    {
      v->Alarm = 1;
    }
    else
    {
      v->Alarm = 0;
    }
    break;

  case STOP_COUNT:
    v->Integral_B = v->Integral_B + v->Pt_Ref_Sat * v->SampleTime; //Работа, рассчитанная от текущей мощности
    if (v->Integral_B >= v->Integral_A) //Ждем пока работа, рассчитанная от текущей мощности станет равной работе, рассчитанной от трактории ограничения мощности
    {
      v->Counter_Limit += v->SampleTime;

      v->Pt_Ref_Sat = *v->Pt_max_Limit; //Ограничение мощности по заданной траектории ограничения мощности
    }
    if (v->Counter_Limit >= t1_Buffer[v->NumPoints])
    {
        v->Counter_Limit = t1_Buffer[v->NumPoints];
    }

    if (*v->Brake_On < v->pBrake_On) //Условие выключения Brake, Спадающий фронт
    {
      v->State = SECTOR_SEARCHING_BR_ONOFF; //Поиск участка на кривой восстановления
      v->i = 0;
      v->Prev_Pt_Lim = *v->Pt_max_Limit; //Запоминаем текущее значение мощности
      v->Integral_A = 0;
      v->Integral_B = 0;
    }

    if (v->Pt_Ref_Sat <= v->Alarm_Level)
    {
      v->Alarm = 1;
    }
    else
    {
      v->Alarm = 0;
    }
    break;

  case BRAKE_OFF:
    v->Prev_Pt_Restore = 0;
    v->Counter_Limit -= v->SampleTime;
    //Функция ограничения выхода
    v->Pt_Ref_Sat = *v->Pt_Restore;
    /*if (v->Pt_Ref_Sat >= *v->Pt_Ref)
    {
      v->Pt_Ref_Sat = *v->Pt_Ref;
    }*/
    if (v->Counter_Limit <= 0)
    {
      v->State = INIT;
      v->Counter_Limit = 0;
    }
    //Если включили Brake
    if (*v->Brake_On)
    {
      v->State = SECTOR_SEARCHING_BR_OFFON;
      v->i = 0;
      v->Integral_A = 0;
      v->Integral_B = 0;
      v->Prev_Pt_Restore = *v->Pt_Restore;
    }

    if (v->Pt_Ref_Sat <= v->Alarm_Level)
    {
      v->Alarm = 1;
    }
    else
    {
      v->Alarm = 0;
    }
    break;

    case SECTOR_SEARCHING_BR_ONOFF:
      if (v->Prev_Pt_Lim <= P2_Buffer[v->i])
      {
        v->i++;
      }
      else
      {
        v->State = VALUE_SEARCHING_BR_ONOFF;
        v->j = v->i - 1;
      }

     break;

    case VALUE_SEARCHING_BR_ONOFF:
      v->Counter_Limit = (t2_Buffer[v->j] - t2_Buffer[v->i])*(v->Prev_Pt_Lim - P2_Buffer[v->i])/(P2_Buffer[v->j] - P2_Buffer[v->i]) + t2_Buffer[v->i];
      v->State = BRAKE_OFF;
     break;

   case SECTOR_SEARCHING_BR_OFFON:
      if (v->Prev_Pt_Restore <= P1_Buffer[v->i])
      {
        v->i++;
      }
      else
      {
        v->State = VALUE_SEARCHING_BR_OFFON;
        v->j = v->i - 1;
      }
     break;

   case VALUE_SEARCHING_BR_OFFON:
      v->Counter_Limit = (t1_Buffer[v->i] - t1_Buffer[v->j])*(v->Prev_Pt_Restore - P1_Buffer[v->j])/(P1_Buffer[v->i] - P1_Buffer[v->j]) + t1_Buffer[v->j];
      v->State = BRAKE_ON;
   break;

  }
  v->pBrake_On = *v->Brake_On;
  v->A_fixed = v->Integral_A;
  v->A_fdb = v->Integral_B;
}

