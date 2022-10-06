
// Do not initialize inputs!
#define IND 1                      //Определяем используемые значения
#define TIMER 2
#define PROVERKA_ONE 3
#define PROVERKA_TWO 4
#define SERVO_HOR_ONE 5
#define SERVO_HOR_TWO 6
#define SERVO_HOR_THREE 7
#define SERVO_VERT_ONE 8
#define SERVO_VERT_TWO 9
#define SERVO_VERT_THREE 10
#define PUSK 11
#define MOVE 11
#define INCREMENT 12
#define DECREMENT 13
#define COMPLETE 14
#define NOT_COMPLETE 15
#define PROVERKA 16
#define INIT 17
#define MOVE_FREE_TWO 18
#define INITIALISATION 19
#define TIMER_SECOND 20
#define POSTANOVKA 21
#define ZAHVAT 22
#define MOVE_FREE_ONE 23
#define MOVE_FREE 24
#define TIMER_FIRST 25
#define SERVO_HOR 26
#define SERVO_VERT 27
#define SERVO_VERT_DOWN 28
#define SERVO_HOR_UP 29
#define SERVO_HOR_DOWN 30
#define SERVO_VERT_UP 31
#define SERVO_VERT_ONE_DOWN 32
#define SERVO_VERT_ONE_UP 33
#define SERVO_HOR_ONE_UP 34
#define STOP 35
#define ROTATE 37
#define HORIZONTAL 38
#define VERTICAL 39
#define DEFINITE 40
#define CALIBROVKA 41
#define SERVO_POSITION_HOR 42
#define SERVO_POSITION_VERT 43
#define END 0

#define POSITION_MODE 3
#define ROTATE_MODE 1
#define CALIBROVKA_MODE 2
#define MOVE_MODE 3

#define ENABLE 1
#define DISABLE 0

#define ZERO_FLOOR 0
#define ONE_FLOOR 1
#define TWO_FLOOR 2
#define THREE_FLOOR 3
#define FOUR_FLOOR 4
#define FIVE_FLOOR 5
#define SIX_FLOOR 6
#define SEVEN_FLOOR 7

#define CURRENT_COOR_UP 9
#define CURRENT_COOR_DOWN 10

#define BIT 1

#define INDEX(__index__)           ((__index__)+1)
#define INDEX_PLUS(__index__)      ((__index__)+2)
#define INDEX_MINUS(__index__)     ((__index__)-1)

static int Func_Key_Switch(int key, BLOCK_STRUCT *v) //Функция определения значения отдельных битов переменной характеризующей состояние концевиков
{
return ((*v->key_switch&(BIT<<key))>>key);
}

static void Func_Timer(int time, BLOCK_STRUCT *v) //Функция таймера, принимает на вход значение временной задержки
{
  switch (v->timer_count)
  {
  case PUSK:
    v->value_timer = DISABLE;          //Обнуление таймера
    v->timer_count = TIMER;
    break;
  case TIMER:
    v->value_timer++;
    if (v->value_timer >= time*v->timer_descrete)                 //Проверкам значений таймера с значением на входе функции
    {
      v->value_timer = DISABLE;
      v->timer_count = END;                     //При выполнении всех условий происходит переход в следующее состояние
    }
    break;
  }
}

static void Func_Servo(int flat, int current_coordinate, int current_floor, BLOCK_STRUCT *v) //Функция управления приводом поворота
{
  switch (v->servo)
  {
  case   PUSK:
    if (flat==HORIZONTAL) v->servo = SERVO_HOR;
    else if(flat==VERTICAL) v->servo = SERVO_VERT;
    v->function_servo = NOT_COMPLETE;
    break;
  case SERVO_HOR:                               //приводу поворота отправляется режим работы работы и значение,Ю на которое необходимо повернуть каретку
    v->mode_servo_hor = POSITION_MODE;
    v->value_servo_hor = current_coordinate;
    v->enable_servo_hor = ENABLE;
    v->servo = PROVERKA_ONE;               //безусловный переход
    v->timer_count = PUSK;
    v->pr_delay_servo = v->time_rotation;
    break;
  case PROVERKA_ONE:                           //По приходу от привода сигнала о завершении работы проверяется значение с датчика поворота, так чтобы значение было в определенном диапазоне
    Func_Timer(v->pr_delay_servo, v);               // Ожидание завершения работы привода поворота
    if(v->timer_count == END)  v->prevention = ENABLE;

    if(*v->finish_servo_hor == ENABLE)
    {
      v->servo = SERVO_POSITION_HOR;
      v->timer_count = PUSK;
    }
    break;
    case SERVO_POSITION_HOR:
      if (((*v->d_povorot) <= ((current_coordinate) + (v->allowable_error_horizontal[current_floor])))&&((*v->d_povorot) >= ((current_coordinate) - (v->allowable_error_horizontal[current_floor]))))//!
      {
      v->enable_servo_hor = DISABLE;
      v->servo = PUSK;                  //При выполнении всех условий происходит переход в следующее состояние
      v->function_servo = COMPLETE;
      }
      Func_Timer(v->pr_delay_position, v);    // Ожидание вхождения в определенный диапазон положения привода поворота
      if(v->timer_count == END)  v->prevention = ENABLE;
      break;
    case SERVO_VERT:                                //Приводу подъема отправляется разрешение работы и значение на которое необходимо переместить каретку
    v->enable_servo_vert = ENABLE;
    v->value_servo_vert = current_coordinate;
    v->servo = SERVO_VERT_ONE;
    v->timer_count = PUSK;
    break;
  case SERVO_VERT_ONE:                    //Выполняется проверка условия, какое значение текущего вертикального перемещения
    if((abs(*v->d_trosic - current_coordinate))>(v->distance))v->pr_delay_servo = v->high_time;
    else if((abs(*v->d_trosic - current_coordinate))<=(v->distance))v->pr_delay_servo = v->low_time;
    v->servo = PROVERKA_TWO;
    break;
  case PROVERKA_TWO:                              //По приходу от привода сигнала о завершении работы, проверяется значение с тросикового датчика, так чтобы оно находилось о\в определенном диапазоне
    Func_Timer(v->pr_delay_servo, v);            // Ожидание завершения работы привода подъема
    if(v->timer_count == END)  v->prevention = ENABLE;

    if(*v->finish_servo_vert == ENABLE)
    {
        v->servo = SERVO_POSITION_VERT;
        v->timer_count = PUSK;
    }
    break;
    case SERVO_POSITION_VERT:
      if (((*v->d_trosic) <= ((current_coordinate) + (v->allowable_error_vert[current_floor])))&&((*v->d_trosic) >= ((current_coordinate) - (v->allowable_error_vert[current_floor]))))//!
      {
      v->enable_servo_vert = DISABLE;
      v->servo = PUSK;                  //При выполнении всех условий происходит переход в следующее состояние
      v->function_servo = COMPLETE;
      }
      Func_Timer(v->pr_delay_position, v);       // Ожидание вхождения в определенный диапазон положения привода подъема
      if(v->timer_count == END)  v->prevention = ENABLE;
      break;
  }
}

static void Func_Move_Free(int first_floor, int second_floor, BLOCK_STRUCT *v)  //Функция перемещения каретки по свободной зоне, перемещение происходит итерационно по одному этажу
{
  switch (v->move_free)
  {
  case INIT:                               //Проверка направления движения
    v->current_floor = first_floor;
    v->move_free = PROVERKA;
    break;
  case PROVERKA:
    if(v->current_floor > second_floor)  v->move_free = SERVO_VERT_DOWN;       //Направление движения вниз
    if(v->current_floor < second_floor)  v->move_free = SERVO_HOR_UP;          //Направление движения вверх
    if(v->current_floor == second_floor) v->move_free = END;                   //В случае ввода одинаковых значений параметров
    break;
    case SERVO_VERT_DOWN:                          //при движении вниз
    Func_Servo((VERTICAL),((v->vert_coor[INDEX(v->current_floor)]) + (v->vert_coor_offset_down[INDEX(v->current_floor)])),(INDEX(v->current_floor)),v);  // Происходит перемещение в вертикальной плоскости на координату в свободной зоне и смещение для движения вниз
    if(v->function_servo == COMPLETE) v->move_free = SERVO_HOR_DOWN;
    break;
  case SERVO_HOR_DOWN:
    Func_Servo((HORIZONTAL),((v->angle_free[INDEX(v->current_floor)]) + (v->angle_offset_down[INDEX(v->current_floor)])),(INDEX(v->current_floor)),v);  //Происходит перемещение в горизонтальной плоскости на угол в свободной зоне и смещение для движения вниз
    if(v->function_servo == COMPLETE)
    {
    if(INDEX_MINUS(v->current_floor) == ZERO_FLOOR)
    {
    v->timer_count = PUSK;
    v->move_free = TIMER;      //Если следующий этаж - зона облучения, запускается задержка, чтобы уменьшить эффект качания контейнера
    }
    else v->move_free = SERVO_VERT_ONE_DOWN;                             //Если следующий этаж - НЕ зона облучения
    }
    break;
  case TIMER:
    //??????
    Func_Timer(v->time_delay, v);
    if(v->timer_count == END) v->move_free = SERVO_VERT_ONE_DOWN;
    break;
  case SERVO_VERT_ONE_DOWN:                 //Происходит перемещение в вертикальной плоскости на координату в свободной зоне следующего этажа
    Func_Servo((VERTICAL),(v->vert_coor[v->current_floor]),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->move_free = DECREMENT;
    break;
  case DECREMENT:         //Декремент, т.е. приход к данному состоянию говорит о перемещении каретки на следющий этаж
    v->current_floor--;
    v->move_free = PROVERKA;
    if (v->current_floor==second_floor) v->move_free = END;    //При выполнении условия равенства текущего и конечного этажа выход из функции
    break;

  case SERVO_HOR_UP:                    //При движении вверх
    if(v->current_floor == ZERO_FLOOR)  //Происходит проверка, если текущий этаж - зона облучения
    {
    Func_Servo((HORIZONTAL),(v->angle_park[INDEX(v->current_floor)]),(INDEX(v->current_floor)),v);    //Привод поворота перемещается на угол, при котором ролики войдут в зацепление с квадратом
    if(v->function_servo == COMPLETE) v->move_free = SERVO_VERT_UP;
    }
    else v->move_free = SERVO_VERT_UP;
    break;
  case SERVO_VERT_UP:                    //Перемещение в вертикальной плоскости на координату в свободной зоне и смещение при движении вверх
    Func_Servo((VERTICAL),((v->vert_coor[INDEX(v->current_floor)]) + (v->vert_coor_offset_up[INDEX(v->current_floor)])),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->move_free = SERVO_HOR_ONE_UP;
    break;
  case SERVO_HOR_ONE_UP:                  //Перемещение в горизонтальной плоскости на угол в свободной зоне и смещение при движении вверх
    Func_Servo((HORIZONTAL),((v->angle_free[INDEX(v->current_floor)]) + (v->angle_offset_up[INDEX(v->current_floor)])),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->move_free = SERVO_VERT_ONE_UP;
    break;
  case SERVO_VERT_ONE_UP:                   //Перемещение в свободной зоне на координату следующего этажа
    Func_Servo((VERTICAL),(v->vert_coor[INDEX_PLUS(v->current_floor)]),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->move_free = INCREMENT;
    break;
  case INCREMENT:                      //Инкремент, этаж увеличивается на один
    v->current_floor++;
    v->move_free = PROVERKA;
    if (v->current_floor==second_floor) v->move_free = END;    //При выполнении всех условий выход из функции
    break;
  }
}

static void Func_Zapusk(BLOCK_STRUCT *v)      //Функция запуска, происходит инициализация  и проверка введенных данных
{
    if (v->zapusk == PUSK)  //Происходит проверка следующих условий: начальный и конечный этаж не должны быть равны; Концевик начального этажа - 1;
  {                        //Если начальный этаж равен нулю - концевик на конечном этаже равен нулю; если конечный этаж равен нулю, концевик начального равен единице
                          //Разрешение работы функции перемещения равно единице;
    if ((*v->first_floor == *v->second_floor)||(*v->first_floor < ZERO_FLOOR)||(*v->first_floor > SEVEN_FLOOR)||(*v->second_floor < ZERO_FLOOR)||(*v->second_floor > SEVEN_FLOOR)||((*v->first_floor == ZERO_FLOOR)&&(((Func_Key_Switch(INDEX_MINUS(*v->second_floor),v))==ENABLE)))||((*v->second_floor == ZERO_FLOOR)&&(((Func_Key_Switch(INDEX_MINUS(*v->first_floor),v))==DISABLE))));
    else if ((((*v->first_floor!=ZERO_FLOOR)&&(*v->second_floor!=ZERO_FLOOR))&&((Func_Key_Switch(INDEX_MINUS(*v->first_floor),v)==DISABLE)||((Func_Key_Switch(INDEX_MINUS(*v->second_floor),v))==ENABLE)))||((v->new_first_floor == DISABLE)&&(*v->first_floor==ZERO_FLOOR)));
    else if ((*v->enable_move==DISABLE)||((*v->first_floor!=ZERO_FLOOR)&&(v->new_first_floor == ENABLE))||((*v->second_floor==ZERO_FLOOR)&&((*v->speed_rotate<v->min_speed)||(*v->speed_rotate>v->max_speed))));
    else
    {
    v->speed_servo_hor = *v->speed_rotate/v->coefficient;
    v->first_floor_mem = *v->first_floor;   //Защита от введения новых значений параметров этажей, при инициализации значения запоминаются и используются до следующей инициализации
    v->second_floor_mem = *v->second_floor;
    v->zapusk = END;                        //Переход к следующему состоянию
    if(v->new_first_floor == ENABLE)
      {
       v->new_first_floor = DISABLE;
      }
    }
  }
}

static void Func_Zahvat(int current_floor,BLOCK_STRUCT *v)           //Функция захвата контейнера из зоны парковки. передается значение текущего этажа
{
  switch (v->zahvat)
  {
  case PROVERKA:                        //Проверка наличия сигнала с концевика о наличии контейнера в зоне парковки
    if((Func_Key_Switch(INDEX_MINUS(current_floor),v))==ENABLE)
    {
    v->zahvat = SERVO_HOR_ONE;
    }
    Func_Timer(v->pr_delay_conteiner, v);              //Ожидание сигнала концевика
    if(v->timer_count == END)  v->prevention = ENABLE;
    break;
  case SERVO_HOR_ONE:                                           //перемещение каретки в горизонтальной плоскости на угол зоны парковки заданного этажа
    Func_Servo((HORIZONTAL),(v->angle_park[INDEX(v->current_floor)]),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->zahvat = SERVO_VERT_ONE;
    break;
  case SERVO_VERT_ONE:                                           //Перемещение с контейнером на парковочную координату и парковочное смещение этажа
    Func_Servo((VERTICAL),((v->vert_coor[INDEX(v->current_floor)]) + (v->park_offset[INDEX(v->current_floor)])),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE)
    {
    v->zahvat = PROVERKA_ONE;
    v->timer_count = PUSK;
    }
    break;
  case PROVERKA_ONE:                                              //Проверка наличия сигнала с концевика об отсутствии контейнера в зоне парковки
    if((Func_Key_Switch(INDEX_MINUS(current_floor),v))==DISABLE)
    {
    v->zahvat = SERVO_HOR_TWO;
    }
    Func_Timer(v->pr_delay_conteiner, v);              //Ожидание сигнала концевика
    if(v->timer_count == END)  v->prevention = ENABLE;
    break;
  case SERVO_HOR_TWO:                                             //Перемещение каретки с контейнером на угол в свободной зоны
    Func_Servo((HORIZONTAL),(v->angle_free[INDEX(v->current_floor)]),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->zahvat = END;
    break;
  }
}

static void Func_Postanovka(int current_floor,BLOCK_STRUCT *v)           //Функция постановки контейнера в зону парковки, передается значение текущего этажа
{
  switch (v->postanovka)
  {
  case PROVERKA:                         //Проверка наличия сигнала с концевика об отсутствии контейнера в зоне парковки
    if((Func_Key_Switch(INDEX_MINUS(current_floor),v))==DISABLE)
    {
    v->postanovka = SERVO_VERT;
    }
    Func_Timer(v->pr_delay_conteiner, v);              //Ожидание сигнала концевика
    if(v->timer_count == END)  v->prevention = ENABLE;
    break;
  case SERVO_VERT:                     //Перемещение с контейнером на парковочную координату и парковочное смещение этажа
    Func_Servo((VERTICAL),((v->vert_coor[INDEX(v->current_floor)]) +( v->park_offset[INDEX(v->current_floor)])),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->postanovka = SERVO_HOR;
    break;
  case SERVO_HOR:                         //перемещение каретки в горизонтальной плоскости на угол зоны парковки заданного этажа
   Func_Servo((HORIZONTAL),(v->angle_park[INDEX(v->current_floor)]),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE)
    {
    v->timer_count = PUSK;
    v->postanovka = TIMER;
    }
    break;
  case TIMER:                           //временная задержка для уменьшения эффекта качания контейнера
    Func_Timer(v->time_delay,v);
    if(v->timer_count == END) v->postanovka = SERVO_VERT_ONE;
    break;
  case SERVO_VERT_ONE:                      //перемещение каретки с контейнером в вертикальной плоскости на координату зоны парковки
    Func_Servo((VERTICAL),(v->vert_coor[INDEX(v->current_floor)]),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE)
    {
    v->postanovka = PROVERKA_ONE;
    v->timer_count = PUSK;
    }
    break;
  case PROVERKA_ONE:                       //Проверка наличия сигнала с концевика о наличии контейнера в зоне парковки
    if((Func_Key_Switch(INDEX_MINUS(current_floor),v))==ENABLE)
        {
        v->postanovka = SERVO_HOR_ONE;
        }
        Func_Timer(v->pr_delay_conteiner, v);
    if(v->timer_count == END)  v->prevention = ENABLE;      //Ожидание сигнала концевика
    break;
  case SERVO_HOR_ONE:                                //Перемещение каретки на горизонтальную координату свободной зоны
    Func_Servo((HORIZONTAL),(v->angle_free[INDEX(v->current_floor)]),(INDEX(v->current_floor)),v);
    if(v->function_servo == COMPLETE) v->postanovka = END;
    break;
  }
}

static void Func_Move(BLOCK_STRUCT *v)
{
   switch (v->move)
  {
  case PUSK:
    v->zapusk = PUSK;        //Вызов функции запуска
    Func_Zapusk(v);
    if (v->zapusk == END)
      {
      v->move = TIMER_FIRST;
      v->timer_count = PUSK;
      }
    break;
  case TIMER_FIRST:
    v->ind_out = MOVE_MODE;                    //Запускается индикатор, сигнализирующий о работе блока перемещения
    Func_Timer(*v->time_first,v);        //Вызов функции задержки перед перемещением
    if (v->timer_count == END)
      {
      v->move = MOVE_FREE;
      v->move_free = INIT;
      }
    break;
  case MOVE_FREE:
    if(v->first_floor_mem != ZERO_FLOOR)
      {
      Func_Move_Free(v->initial_floor, v->first_floor_mem,v);        //Вызов функции перемещения в свободной зоне
      if (v->move_free == END)
        {
        v->move = ZAHVAT;
        v->timer_count = PUSK;
        v->zahvat = PROVERKA;
        }
      }
    else v->move = MOVE_FREE_ONE;
    break;
  case ZAHVAT:
    Func_Zahvat(v->first_floor_mem,v);                                    //Вызов функции захвата контейнера
    if (v->zahvat == END)
      {
      v->move = MOVE_FREE_ONE;
      v->move_free = INIT;
      }
    break;
  case MOVE_FREE_ONE:
    Func_Move_Free(v->first_floor_mem,v->second_floor_mem,v);             //Вызов функции перемещения в свободной зоне
    if (v->move_free == END)
      {
      v->move = POSTANOVKA;
      v->postanovka = PROVERKA;
      v->timer_count = PUSK;
      }
    break;
  case POSTANOVKA:
    if(v->second_floor_mem != ZERO_FLOOR)
      {
      Func_Postanovka(v->second_floor_mem,v);                              //Вызов функции постановки контейнера
      if (v->postanovka == END)
         {
          v->move = MOVE_FREE_TWO;
          v->move_free = INIT;
         }
       }
       else
      {
      v->move = TIMER_SECOND;
      v->timer_count = PUSK;
      }
    break;
  case MOVE_FREE_TWO:
    Func_Move_Free(v->second_floor_mem,v->initial_floor,v);                 //Вызов функции перемещения в свободной зоне
    if (v->move_free == END)
      {
      v->move = TIMER_SECOND;
      v->timer_count = PUSK;
      }
    break;
  case TIMER_SECOND:
    Func_Timer(*v->time_second,v);                                       //Вызов функции задернжки после вывполнения перемещения
    if (v->timer_count == END) v->move = END;
    break;
  }
}

static void Func_Rotate(BLOCK_STRUCT *v)  //Функция вращения контейнера, при нахождении его в зоне облучения
{
  switch (v->rotate)
  {
  case PUSK:
    v->mode_servo_hor = ROTATE_MODE;         //Режим вращения привода поворота
    v->rotate = PROVERKA;
    v->enable_servo_hor = ENABLE;
    v->timer_count = PUSK;
    v->ind_out = ROTATE_MODE;
    break;
  case PROVERKA:    //Производится проверка условий, при которых прекращается вращение: Выключена оператором, мощность реактора превышает установленную, установленное время вращения прекратилось
    Func_Timer(*v->time_rotate,v);
    if((*v->speed_rotate>=v->min_speed)&&(*v->speed_rotate<=v->max_speed))
    v->speed_servo_hor = *v->speed_rotate/v->coefficient;    //Приводу поворота передается скорость, возможность обновления заданной первоначально
    if ((*v->enable_rotate==ENABLE)||(v->timer_count == END)||(*v->d_ktv>=*v->power_rotate))
      {
      v->speed_servo_hor = DISABLE;
      v->enable_servo_hor = DISABLE;
      v->rotate = END;
      }
    break;
  }
}

static void Func_Calibrovka(BLOCK_STRUCT *v)
{
  switch (v->calibrovka)
  {
  case PUSK:
    if(*v->enable_calibrovka==ENABLE)  // Если разрешение работы функции истинно(кнопка нажата) происходит присвоение начальных значений
      {
      v->processing_floor = SEVEN_FLOOR;  // проверка начнется с седьмого этажа
      v->current_coor_up = v->vert_coor[CURRENT_COOR_UP];     //в качестве верхней границы для седьмого этажа берется значениние выше которого каретка находиться не может
      v->current_coor_down = v->vert_coor[v->processing_floor]; // в качестве нижней границы выбирается уровень парковочной зоны
      v->calibrovka = DEFINITE;
      v->ind_out = CALIBROVKA_MODE;                              // индикатор показывет работу функции калибровки
      }
    break;
  case DEFINITE:                                    // Происходит определение вхождения текущих координат каретки в диапазон границ обрабатываемого этажа
    if(v->processing_floor==ONE_FLOOR)v->current_coor_down = v->vert_coor[CURRENT_COOR_DOWN];
    if((*v->d_trosic>=v->current_coor_up)&&(*v->d_trosic<=v->current_coor_down)) v->calibrovka = PROVERKA;
    else v->calibrovka = DECREMENT;
    break;
  case DECREMENT:   // Происходит присвоение для границ следующего этажа
    v->current_coor_up = v->vert_coor[v->processing_floor];
    v->processing_floor--;                            // Декремент
    v->current_coor_down = v->vert_coor[v->processing_floor];
    v->calibrovka = DEFINITE;
    if(v->processing_floor==ZERO_FLOOR) v->prevention = ENABLE;
    break;
  case PROVERKA:

    if((*v->d_povorot >= v->limit_free[v->processing_floor])&&(*v->d_povorot <= v->limit_park[v->processing_floor])) // каретка находится в границах свободной зоны
    {
      if((v->processing_floor == ONE_FLOOR)||((*v->d_trosic >= v->vert_coor[v->processing_floor+1])&&(*v->d_trosic <= (v->vert_coor[v->processing_floor])+v->vert_coor_offset_up[v->processing_floor]))||((v->processing_floor==SEVEN_FLOOR)&&(*v->d_trosic<=v->vert_coor[INDEX(SEVEN_FLOOR)])))
      //каретка на первом этаже
      {
        v->move_free = SERVO_HOR_ONE_UP;
        v->current_floor =  INDEX_MINUS(v->processing_floor);
    }
      else   if((*v->d_trosic <= v->vert_coor[v->processing_floor])&&(*v->d_trosic >= (v->vert_coor[v->processing_floor])+v->vert_coor_offset_up[v->processing_floor])) //каретка в пределах нижней зоны смещения
      {
        v->move_free = SERVO_HOR_DOWN;
        v->current_floor = v->processing_floor;
      }
     v->calibrovka = MOVE_FREE;
    }
    else v->prevention = ENABLE;
    break;
  case MOVE_FREE:                     // Происходит перемещение по на координату текущего этажа в свободной зоне
    Func_Move_Free(v->processing_floor,v->initial_floor,v);             //Вызов функции перемещения в свободной зоне
    if (v->move_free == END)
    {
    v->calibrovka = IND;
    }
    break;
  case IND:
    v->ind_out=DISABLE;                     //Индикатор становится равным нулю
    v->calibrovka = END;                    //Выход из функции
    break;
  }
}

void Init(void)
{
}

void Exec(void)
{
if ((*v->warning)||(!*v->enable)||(v->prevention == ENABLE))
  {
    v->ind_out = DISABLE;           //При получении сигнала аварии или по команде оператора все основные переменные принимают начальные значения, в блоке ожидается калибровка
    v->move = PUSK;
    v->move_free = INIT;
    v->zapusk = PUSK;
    v->calibrovka = PUSK;
    v->move_rotate = CALIBROVKA;
    v->function_servo = COMPLETE;
    v->servo = PUSK;
    v->enable_servo_hor = DISABLE;
    v->enable_servo_vert = DISABLE;
    if((v->prevention)&&(!*v->enable)) v->prevention = DISABLE;
    return;
  }
  switch (v->move_rotate)
  {
  case CALIBROVKA:
    Func_Calibrovka(v);                                // Вызов функции калибровки
    if (v->calibrovka == END) v->move_rotate = MOVE;
    break;
  case MOVE:
    Func_Move(v);        //Вызов функции перемещения
    if((v->second_floor_mem == ZERO_FLOOR)&&(v->move==END))
    {
    v->rotate = PUSK;
    v->move_rotate = ROTATE;
    }
    else if((v->second_floor_mem != ZERO_FLOOR)&&(v->move==END)) v->move_rotate = END;
    break;
  case ROTATE:
    Func_Rotate(v);                       // Вызов функции вращения
    if(v->rotate==END)
    {
    v->move_rotate = END;
    v->new_first_floor = ENABLE;          //Защита от ввода некорректных новых параметров при последующей инициализации данных
    }
    break;
  case END:                               //Переменные принимают начальные значения, в следующем состоянии ожидается инициализация новых данных
    v->ind_out = DISABLE;           //Индикатор завершения работы функций перемещения и вращения
    v->move = PUSK;
    v->move_rotate = MOVE;
    break;
  }
}

