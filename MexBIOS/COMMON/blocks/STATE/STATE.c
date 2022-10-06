
//States
#define WAIT_STATE 0
#define INIT_STATE 1
#define OPEN_STATE 2
#define CLOSE_STATE 3
#define STOP_STATE 4
#define RVM_STATE 5
#define BLOCK_STATE 6
#define ALARM_STATE 7
#define FOTO_STATE 8


//Discrete_Input Masks
#define COMMAND_BIT 1
#define FOTO_BIT 2
#define ALARM_BIT 4
#define BLOCK_BIT 8
#define VKZ_ANOTHER_BLOCK_BIT 16
#define VKO_ANOTHER_BLOCK_BIT 32

//DIP Masks
#define FOTO_TYPE_BIT 1
#define ALARM_TYPE_BIT 2
#define DIPS_ON_OFF_BIT 4
#define SPEED_DIVIDER_1_BIT 8
#define SPEED_DIVIDER_2_BIT 16
#define DIRECTION_OF_ROTATION_BIT 32
//#define ??? 64
//#define ??? 128

//Discrete_Output Masks
#define VKO_BIT_OUT 1
#define VKZ_BIT_OUT 2
#define RVM_BIT_OUT 4
#define STOP_BIT_OUT 8
#define FOTO_BIT_OUT 16
#define BLOCK_BIT_OUT 32
#define ALARM_BIT_OUT 64
#define INIT_BIT_OUT 128
#define RESET_POSITION_BIT_OUT 256
//#define ??? 16
//#define ??? 32
//#define ??? 64
//#define ??? 128


//SubStates WAIT_STATE



//SubStates INIT_STATE
#define FIRST_CLOSING 0
#define VKZ_POS_CHECK 1
#define POSITION_RESET_ON 2
#define POSITION_RESET_OFF 3
#define FIRST_CLOSED 4
#define FIRST_OPENING 5
#define VKO_POS_CHECK 6
#define DOOR_LENGTH_CHECK 7
#define STOPPING_TO_VKO_POS 8
#define FIRST_OPENED 9
#define SECOND_CLOSING 10
#define SECOND_CLOSED 11

//SubStates OPEN_STATE
#define OPENING 0
#define RVM_IN_OPENING 1
#define OPENING_AFTER_RVM 2
#define STOP_IN_OPENING 3
#define OPENING_AFTER_STOP 4
#define BLOCK_IN_OPENING 5
#define OPENING_AFTER_BLOCK 6
#define ALARM_WAITING_OF_OPENING 7
#define ALARM_STOP_AND_CLOSING 8
#define FOTO_IN_OPENING 9
#define OPENING_AFTER_FOTO 10

//SubStates CLOSE_STATE
#define CLOSING 0
#define RVM_IN_CLOSING 1
#define CLOSING_AFTER_RVM 2
#define STOP_IN_CLOSING 3
#define CLOSING_AFTER_STOP 4
#define BLOCK_IN_CLOSING 5
#define CLOSING_AFTER_BLOCK 6
#define ALARM_WAITING_OF_CLOSING 7
#define ALARM_STOP_AND_OPENING 8
#define FOTO_IN_CLOSING 9
#define CLOSING_AFTER_FOTO 10


//SubStates STOP_STATE
#define OPENING_STOP 0
#define OPENING_STOP_INDENT 1
#define CLOSING_STOP 2
#define CLOSING_STOP_INDENT 3
#define STOP_END 4


//SubStates RVM_STATE
#define OPENING_RVM 0
#define OPENING_RVM_INDENT 1
#define CLOSING_RVM 2
#define CLOSING_RVM_INDENT 3
#define RVM_END 4


//SubStates BLOCK_STATE
#define OPENING_BLOCK 0
#define OPENING_BLOCK_INDENT 1
#define CLOSING_BLOCK 2
#define CLOSING_BLOCK_INDENT 3
#define BLOCK_END 4


//SubStates ALARM_STATE
#define ALARM_STOP_IN_OPENING 0
#define ALARM_CLOSING 1
#define ALARM_STOP_IN_CLOSING 2
#define ALARM_OPENING 3
#define ALARM_END 4


//SubStates FOTO_STATE
#define OPENING_FOTO 0
#define OPENING_FOTO_INDENT 1
#define CLOSING_FOTO 2
#define CLOSING_FOTO_INDENT 3
#define FOTO_END 4


//DIRECTIONS
#define OPEN_DIRECTION 1
#define CLOSE_DIRECTION -1
#define STOP_DIRECTION 0


//Timers Defines
#define Timer_VKO_VKZ_Another_Block_On 1
#define Timer_VKO_VKZ_Another_Block 2
#define Timer_VKO_On 3
#define Timer_VKO 4
#define Timer_VKZ_On 5
#define Timer_VKZ 6
#define Timer_Current_On 7
#define Timer_Current 8
#define Timer_Position_On 9
#define Timer_Position 10
#define Timer_Command_On 11
#define Timer_Command 12
#define Timer_Block_On 13
#define Timer_Block 14
#define Timer_Alarm_On 15
#define Timer_Alarm 16
#define Timer_Foto_On 17
#define Timer_Foto 18

//Delays Defines
#define VKO_VKZ_Another_Block_Change_Delay 1
#define VKO_On_Delay 2
#define VKZ_On_Delay 3
#define Current_RVM_Delay 4
#define Current_Stop_Delay 5
#define Command_Change_Delay 6
#define Block_Change_Delay 7
#define Alarm_Change_Delay 8
#define Foto_Change_Delay 9
#define Position_Stop_Delay 10
#define Current_VKZ_Block_Delay 11


//POSs Defines
#define STOP_POS 1
#define RVM_POS 2
#define BLOCK_POS 3
#define ALARM_POS 4
#define FOTO_POS 5
#define STOP_INDENT_POS_END 6
#define STOP_POS_END 7
#define AR_POS_END 8
#define AT_POS_START 9

//SPDs Defines
#define STOP_SPD 1
#define RVM_SPD 2
#define BLOCK_SPD 3
#define ALARM_SPD 4
#define FOTO_SPD 5
#define SPD_MAX 6
#define SPD_MIN 7
#define SPD_SYNCH 8
#define SPD_RVM_Level 9


//Indents Defines
#define VKO_AREA_Indent 1
#define VKZ_AREA_Indent 2
#define Open_Indent 3
#define Close_Indent 4
#define STOP_Indent 5
#define RVM_Indent 6
#define BLOCK_Indent 7
#define FOTO_Indent 8
#define VKZ_Block_Indent 9

//Current_Levels Defines
#define Current_Open_RVM_Level 1
#define Current_Close_RVM_Level 2
#define Current_Open_Stop_Level 3
#define Current_Close_Stop_Level 4
#define Current_VKZ_Block_Level 5


//AR_AT_POSs Defines
#define AR_POS 1
#define AT_POS 2
#define STOP_AT_POS 3
#define RVM_AT_POS 4
#define BLOCK_AT_POS 5
#define ALARM_AT_POS 6
#define FOTO_AT_POS 7
#define AR_AT_INDENT_POS 8

//AR_AT_SPDs Defines
#define AR_SPD 1
#define AT_SPD 2
#define STOP_AT_SPD 3
#define RVM_AT_SPD 4
#define BLOCK_AT_SPD 5
#define ALARM_AT_SPD 6
#define FOTO_AT_SPD 7
#define AR_AT_INDENT_SPD 8



#define IMPULSE_TYPE 1



static void ON_FLAG(BLOCK_STRUCT *v, int FLAG)
{
  v->g_Discrete_Output |= FLAG;
}

static void RESET_FLAG(BLOCK_STRUCT *v, int FLAG)
{
  v->g_Discrete_Output &= ~FLAG;
}



static void OPEN_CLOSE_MOVE(BLOCK_STRUCT *v, int Start_POS, int End_Pos, int Direction)
{

  if(v->Points_Changing_Enable)
  {

  if(*v->g_Discrete_Input & COMMAND_BIT)
  {
    v->AR = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * v->g_AR_AT_POSs[AR_POS]) / v->g_AR_AT_SPDs[AR_SPD];//длина участка разгона.
    v->AT = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * v->g_AR_AT_POSs[AT_POS]) / v->g_AR_AT_SPDs[AT_SPD];//длина участка торможения.
  }
  else
  {
    v->AR = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * v->g_AR_AT_POSs[AT_POS]) / v->g_AR_AT_SPDs[AT_SPD];//длина участка разгона.
    v->AT = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * v->g_AR_AT_POSs[AR_POS]) / v->g_AR_AT_SPDs[AR_SPD];//длина участка торможения.
  }



    if(Start_POS < v->g_Indents[Close_Indent])
    {
      Start_POS = v->g_Indents[Close_Indent];
    }

    if(End_Pos > v->g_Door_Length - v->g_Indents[Open_Indent])
    {
      End_Pos = v->g_Door_Length - v->g_Indents[Open_Indent];
    }


    if((Start_POS + v->AR) > (v->g_Door_Length - v->g_Indents[Open_Indent] - v->g_Indents[VKO_AREA_Indent]))
    {
      v->g_POSs[AR_POS_END] = v->g_Door_Length - v->g_Indents[Open_Indent] - v->g_Indents[VKO_AREA_Indent];//позиция окончания разгона.
    }
    else
    {
      v->g_POSs[AR_POS_END] = Start_POS + v->AR;//позиция окончания разгона.
    }

    if((End_Pos - v->AT) < (v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent]))
    {
      v->g_POSs[AT_POS_START] = v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent];//позиция начала торможения.
    }
    else
    {
      v->g_POSs[AT_POS_START] = End_Pos - v->AT;//позиция начала торможения.
    }


    if(v->g_POSs[AR_POS_END] < v->g_POSs[AT_POS_START])//есть ли пересечение крывых разгона и торможения.
    {

      v->g_Points[1] = Start_POS;
      v->g_Points[2] = v->g_SPDs[SPD_MIN];
      v->g_Points[3] = v->g_POSs[AR_POS_END];
      v->g_Points[4] = v->g_SPDs[SPD_MAX];
      v->g_Points[5] = v->g_POSs[AT_POS_START];
      v->g_Points[6] = v->g_SPDs[SPD_MAX];
      v->g_Points[7] = End_Pos;
      v->g_Points[8] = v->g_SPDs[SPD_MIN];

      v->g_Points[9] = v->g_Door_Length;
      v->g_Points[10] = v->g_SPDs[SPD_MAX];
      v->g_Num_Of_Points = 4;
      v->g_Direction = Direction;

    }
    else
    {
      //POS0
      v->g_Points[1] = Start_POS;
      v->g_Points[2] = v->g_SPDs[SPD_MIN];
      //POS2
      v->g_Points[5] = End_Pos;
      v->g_Points[6] = v->g_SPDs[SPD_MIN];
      //POS1

      if(
        (v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT)))
        >
        (v->g_Door_Length - v->g_Indents[Open_Indent] - v->g_Indents[VKO_AREA_Indent])
        )
      {
        v->g_Points[3] = v->g_Door_Length - v->g_Indents[Open_Indent] - v->g_Indents[VKO_AREA_Indent];
      }
      else
      {
        v->g_Points[3] = v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT));
      }

      if(
        (v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT)))
        <
        (v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent])
        )
      {
        v->g_Points[3] = v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent];
      }
      else
      {
        v->g_Points[3] = v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT));
      }

      if(
        (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
        >
        v->g_SPDs[SPD_MAX]
        )
      {
        v->g_Points[4] = v->g_SPDs[SPD_MAX];
      }
      else
      {
        v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
      }

      if(
        (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
        <
        v->g_SPDs[SPD_MIN]
        )
      {
        v->g_Points[4] = v->g_SPDs[SPD_MIN];
      }
      else
      {
        v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
      }

      v->g_Points[7] = 0;
      v->g_Points[8] = 0;

      v->g_Points[9] = v->g_Door_Length;
      v->g_Points[10] = v->g_SPDs[SPD_MAX];
      v->g_Num_Of_Points = 3;
      v->g_Direction = Direction;

    }

    if(*v->g_Discrete_Input & COMMAND_BIT)
    {
      v->g_POSs[STOP_INDENT_POS_END] = End_Pos;
    }
    else
    {
      v->g_POSs[STOP_INDENT_POS_END] = Start_POS;
    }

  }

  v->Points_Changing_Enable = 0;
}

static void STOPPING_MOVE(BLOCK_STRUCT *v, int Start_POS, int Start_SPD, int STOPPING_AT_POS, int STOPPING_AT_SPD, int Direction)
{

  if(v->Points_Changing_Enable)
  {

    v->STOP_AT = ((Start_SPD - v->g_SPDs[SPD_MIN]) * STOPPING_AT_POS) / STOPPING_AT_SPD;

    if(Direction == OPEN_DIRECTION)
    {

      if((Start_POS + v->STOP_AT) > (v->g_Door_Length - v->g_Indents[Open_Indent] ))
      {
        v->g_POSs[STOP_POS_END] = v->g_Door_Length - v->g_Indents[Open_Indent] ;
      }
      else
      {
        v->g_POSs[STOP_POS_END] = Start_POS + v->STOP_AT;
      }

      v->g_Points[1] = Start_POS;
      v->g_Points[2] = Start_SPD;
      v->g_Points[3] = v->g_POSs[STOP_POS_END];
      v->g_Points[4] = v->g_SPDs[SPD_MIN];

      v->g_Points[5] = 0;
      v->g_Points[6] = 0;
      v->g_Points[7] = 0;
      v->g_Points[8] = 0;

      v->g_Points[9] = v->g_Door_Length;
      v->g_Points[10] = v->g_SPDs[SPD_MAX];
      v->g_Num_Of_Points = 2;
      v->g_Direction = Direction;
    }

    if(Direction == CLOSE_DIRECTION)
    {

      if((Start_POS - v->STOP_AT) < (v->g_Indents[Close_Indent] ))
      {
        v->g_POSs[STOP_POS_END] = v->g_Indents[Close_Indent] ;
      }
      else
      {
        v->g_POSs[STOP_POS_END] = Start_POS - v->STOP_AT;
      }

      v->g_Points[1] = v->g_POSs[STOP_POS_END];
      v->g_Points[2] = v->g_SPDs[SPD_MIN];
      v->g_Points[3] = Start_POS;
      v->g_Points[4] = Start_SPD;

      v->g_Points[5] = 0;
      v->g_Points[6] = 0;
      v->g_Points[7] = 0;
      v->g_Points[8] = 0;

      v->g_Points[9] = v->g_Door_Length;
      v->g_Points[10] = v->g_SPDs[SPD_MAX];
      v->g_Num_Of_Points = 2;
      v->g_Direction = Direction;

    }

  }

  if(*v->g_Speed_Feed <= v->g_SPDs[SPD_MIN])
  {
    v->g_POSs[STOP_POS_END] = *v->g_Position_Feed;
  }

  v->Points_Changing_Enable = 0;
}

static void INDENT_MOVE(BLOCK_STRUCT *v, int Indent, int Direction)
{

  if(v->Points_Changing_Enable)
  {

    v->AR = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * v->g_AR_AT_POSs[AR_AT_INDENT_POS]) / v->g_AR_AT_SPDs[AR_AT_INDENT_SPD];//длина участка разгона.
    v->AT = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * v->g_AR_AT_POSs[AR_AT_INDENT_POS]) / v->g_AR_AT_SPDs[AR_AT_INDENT_SPD];//длина участка торможения.



    if(Direction == OPEN_DIRECTION)
    {


      if((v->g_POSs[STOP_POS_END] + Indent) > (v->g_Door_Length - v->g_Indents[Open_Indent] ))
      {
        v->g_POSs[STOP_INDENT_POS_END] = v->g_Door_Length - v->g_Indents[Open_Indent] ;
      }
      else
      {
        v->g_POSs[STOP_INDENT_POS_END] = v->g_POSs[STOP_POS_END] + Indent;
      }


      //POS0
      v->g_Points[1] = v->g_POSs[STOP_POS_END];
      v->g_Points[2] = v->g_SPDs[SPD_MIN];
      //POS2
      v->g_Points[5] = v->g_POSs[STOP_INDENT_POS_END];
      v->g_Points[6] = v->g_SPDs[SPD_MIN];
      //POS1

      if(
        (v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT)))
        >
        (v->g_Door_Length - v->g_Indents[Open_Indent] - v->g_Indents[VKO_AREA_Indent])
        )
      {
        v->g_Points[3] = v->g_Door_Length - v->g_Indents[Open_Indent] - v->g_Indents[VKO_AREA_Indent];
      }
      else
      {
        v->g_Points[3] = v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT));
      }


      if(
        (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
        >
        v->g_SPDs[SPD_MAX]
        )
      {
        v->g_Points[4] = v->g_SPDs[SPD_MAX];
      }
      else
      {
        v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
      }


      if(
        (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
        <
        v->g_SPDs[SPD_MIN]
        )
      {
        v->g_Points[4] = v->g_SPDs[SPD_MIN];
      }
      else
      {
        v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
      }

      v->g_Points[7] = 0;
      v->g_Points[8] = 0;

      v->g_Points[9] = v->g_Door_Length;
      v->g_Points[10] = v->g_SPDs[SPD_MAX];
      v->g_Num_Of_Points = 3;
      v->g_Direction = Direction;

    }

    if(Direction == CLOSE_DIRECTION)
    {


      if((v->g_POSs[STOP_POS_END] - Indent) < (v->g_Indents[Close_Indent]))
      {
        v->g_POSs[STOP_INDENT_POS_END] = v->g_Indents[Close_Indent];
      }
      else
      {
        v->g_POSs[STOP_INDENT_POS_END] = v->g_POSs[STOP_POS_END] - Indent;
      }


      //POS0
      v->g_Points[1] = v->g_POSs[STOP_INDENT_POS_END];
      v->g_Points[2] = v->g_SPDs[SPD_MIN];
      //POS2
      v->g_Points[5] = v->g_POSs[STOP_POS_END];
      v->g_Points[6] = v->g_SPDs[SPD_MIN];
      //POS1

      if(
        (v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT)))
        <
        (v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent])
        )
      {
        v->g_Points[3] = v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent];
      }
      else
      {
        v->g_Points[3] = v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT));
      }

      if(
        (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
        >
        v->g_SPDs[SPD_MAX]
        )
      {
        v->g_Points[4] = v->g_SPDs[SPD_MAX];
      }
      else
      {
        v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
      }


      if(
        (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
        <
        v->g_SPDs[SPD_MIN]
        )
      {
        v->g_Points[4] = v->g_SPDs[SPD_MIN];
      }
      else
      {
        v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
      }


      v->g_Points[7] = 0;
      v->g_Points[8] = 0;

      v->g_Points[9] = v->g_Door_Length;
      v->g_Points[10] = v->g_SPDs[SPD_MAX];
      v->g_Num_Of_Points = 3;
      v->g_Direction = Direction;
    }

  }

  v->Points_Changing_Enable = 0;
}



static void GO_TO(BLOCK_STRUCT *v, int State, int Sub_State)
{
  v->g_State = State;
  v->g_Sub_State = Sub_State;
  v->Points_Changing_Enable = 1;
}

static void ANOTHER_BLOCK_VKO_VKZ_COUNTER(BLOCK_STRUCT *v)
{
  if(
    ((*v->g_Discrete_Input & VKZ_ANOTHER_BLOCK_BIT) != (v->g_Discrete_Input_Prev & VKZ_ANOTHER_BLOCK_BIT))
    ||
    ((*v->g_Discrete_Input & VKO_ANOTHER_BLOCK_BIT) != (v->g_Discrete_Input_Prev & VKO_ANOTHER_BLOCK_BIT))
    )//Условие, что сигналы VKO или VKZ от другого блока изменили состояние.
  {

    v->g_Timers[Timer_VKO_VKZ_Another_Block_On] = 1;//Включение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.

    if(v->g_Timers[Timer_VKO_VKZ_Another_Block] > v->g_Delays[VKO_VKZ_Another_Block_Change_Delay])
    {
      v->g_Timers[Timer_VKO_VKZ_Another_Block_On] = 0;//Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.

      //////VKZ_Counter//////
      if((v->g_Discrete_Input_Prev & VKZ_ANOTHER_BLOCK_BIT) < (*v->g_Discrete_Input & VKZ_ANOTHER_BLOCK_BIT))//Если сигнал VKZ от другого блока изменил состояние из 0 в 1.
      {
        v->g_VKZ_Another_Block_Counter++;//Увеличение счётчика срабатывания сигнала VKZ от другого блока на 1.
      }

      //////VKO_Counter//////
      if((v->g_Discrete_Input_Prev & VKO_ANOTHER_BLOCK_BIT) < (*v->g_Discrete_Input & VKO_ANOTHER_BLOCK_BIT))//Если сигнал VKO изменил состояние из 0 в 1.
      {
        v->g_VKO_Another_Block_Counter++;//Увеличение счётчика срабатывания сигнала VKO от другого блока на 1.
      }

      v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.

    }

  }
  else
  {
    v->g_Timers[Timer_VKO_VKZ_Another_Block_On] = 0;//Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.
  }
}

static void ANOTHER_BLOCK_VKO_VKZ(BLOCK_STRUCT *v)
{
  if(
    ((*v->g_Discrete_Input & VKZ_ANOTHER_BLOCK_BIT) != (v->g_Discrete_Input_Prev & VKZ_ANOTHER_BLOCK_BIT))
    ||
    ((*v->g_Discrete_Input & VKO_ANOTHER_BLOCK_BIT) != (v->g_Discrete_Input_Prev & VKO_ANOTHER_BLOCK_BIT))
    )//Условие, что сигналы VKO или VKZ от другого блока изменили состояние.
  {
    v->g_Timers[Timer_VKO_VKZ_Another_Block_On] = 1;//Включение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.

    if(v->g_Timers[Timer_VKO_VKZ_Another_Block] > v->g_Delays[VKO_VKZ_Another_Block_Change_Delay])
    {
      v->g_Timers[Timer_VKO_VKZ_Another_Block_On] = 0;//Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.
      v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.
    }

  }
  else
  {
    v->g_Timers[Timer_VKO_VKZ_Another_Block_On] = 0;//Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.
  }
}

static void VKO_VKZ_CHECK(BLOCK_STRUCT *v)
{

  if(v->g_Discrete_Input_Prev & COMMAND_BIT)
  {
    if(
    (*v->g_Position_Feed >= (v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent]))
    &&
    (v->g_Discrete_Output & VKZ_BIT_OUT)
    )
    {
    v->g_Timers[Timer_VKZ_On] = 1;//Включение таймера тока.

    if(v->g_Timers[Timer_VKZ] > v->g_Delays[VKZ_On_Delay])
    {
      v->g_Timers[Timer_VKZ_On] = 0;
      RESET_FLAG(v, VKZ_BIT_OUT);
    }

    }
  else
    {
    v->g_Timers[Timer_VKZ_On] = 0;
    }
  if(
    (*v->g_Position_Feed >= (v->g_Door_Length - v->g_Indents[Open_Indent] - v->Position_Limit))
    &&
    (*v->g_Position_Feed <= (v->g_Door_Length - v->g_Indents[Open_Indent] + v->Position_Limit))
    &&
    (!(v->g_Discrete_Output & VKO_BIT_OUT))
  )
    {
    v->g_Timers[Timer_VKO_On] = 1;//Включение таймера тока.

    if(v->g_Timers[Timer_VKO] > v->g_Delays[VKO_On_Delay])
    {
      v->g_Timers[Timer_VKO_On] = 0;
      ON_FLAG(v, VKO_BIT_OUT);
    }
    }
  else if(
    (*v->g_Position_Feed <= ((v->g_Door_Length - v->g_Indents[Open_Indent]) - v->g_Indents[VKO_AREA_Indent]))
    &&
    (v->g_Discrete_Output & VKO_BIT_OUT)
  )
    {
    v->g_Timers[Timer_VKO_On] = 1;//Включение таймера тока.
    if(v->g_Timers[Timer_VKO] > v->g_Delays[VKO_On_Delay])
    {
      v->g_Timers[Timer_VKO_On] = 0;
      RESET_FLAG(v, VKO_BIT_OUT);
    }
    }
  else
  {
    v->g_Timers[Timer_VKO_On] = 0;
  }
  }

  else
  {
    if(
    (*v->g_Position_Feed <= ((v->g_Door_Length - v->g_Indents[Open_Indent]) - v->g_Indents[VKO_AREA_Indent]))
    &&
    (v->g_Discrete_Output & VKO_BIT_OUT)
  )
    {
    v->g_Timers[Timer_VKO_On] = 1;//Включение таймера тока.
    if(v->g_Timers[Timer_VKO] > v->g_Delays[VKO_On_Delay])
    {
      v->g_Timers[Timer_VKO_On] = 0;
      RESET_FLAG(v, VKO_BIT_OUT);
    }
    }
  else
  {
    v->g_Timers[Timer_VKO_On] = 0;
  }

    if(
    (*v->g_Position_Feed >= (v->g_Indents[Close_Indent] - v->Position_Limit))
    &&
    (*v->g_Position_Feed <= (v->g_Indents[Close_Indent] + v->Position_Limit))
    &&
    (!(v->g_Discrete_Output & VKZ_BIT_OUT))
    )
    {
    v->g_Timers[Timer_VKZ_On] = 1;//Включение таймера тока.
    if(v->g_Timers[Timer_VKZ] > v->g_Delays[VKZ_On_Delay])
    {
      v->g_Timers[Timer_VKZ_On] = 0;
      ON_FLAG(v, VKZ_BIT_OUT);
    }
    }
  else if(
    (*v->g_Position_Feed >= (v->g_Indents[Close_Indent] + v->g_Indents[VKZ_AREA_Indent]))
    &&
    (v->g_Discrete_Output & VKZ_BIT_OUT)
    )
    {
    v->g_Timers[Timer_VKZ_On] = 1;//Включение таймера тока.

    if(v->g_Timers[Timer_VKZ] > v->g_Delays[VKZ_On_Delay])
    {
      v->g_Timers[Timer_VKZ_On] = 0;
      RESET_FLAG(v, VKZ_BIT_OUT);
    }
    }
  else
  {
    v->g_Timers[Timer_VKZ_On] = 0;
  }
  }
}

static void RVM_CHECK(BLOCK_STRUCT *v)
{
  if(v->g_State == OPEN_STATE)
  {
    if(
        (*v->g_Current_Feed > v->g_Current_Levels[Current_Open_RVM_Level]) //Условие, что ток возрос выше уставки RVM.
      &&
        (*v->g_Speed_Feed < v->g_SPDs[SPD_RVM_Level])
      )
    {
      v->g_Timers[Timer_Current_On] = 1;//Включение таймера тока.

      if(v->g_Timers[Timer_Current] > v->g_Delays[Current_RVM_Delay])
      {
        v->g_Timers[Timer_Current_On] = 0;
    ON_FLAG(v, RVM_BIT_OUT);
  GO_TO(v, OPEN_STATE, RVM_IN_OPENING);
      }
    }
    else
    {
      v->g_Timers[Timer_Current_On] = 0;//Выключение таймера тока.
    }
  }

  if(v->g_State == CLOSE_STATE)
  {
    if(
        (*v->g_Current_Feed > v->g_Current_Levels[Current_Close_RVM_Level]) //Условие, что ток возрос выше уставки RVM.
      &&
        (*v->g_Speed_Feed < v->g_SPDs[SPD_RVM_Level])
      )
    {
      v->g_Timers[Timer_Current_On] = 1;//Включение таймера тока.

      if(v->g_Timers[Timer_Current] > v->g_Delays[Current_RVM_Delay])
      {
        v->g_Timers[Timer_Current_On] = 0;
    ON_FLAG(v, RVM_BIT_OUT);
  GO_TO(v, CLOSE_STATE, RVM_IN_CLOSING);
      }
    }
    else
    {
      v->g_Timers[Timer_Current_On] = 0;//Выключение таймера тока.
    }
  }
}

static void STOP_CHECK(BLOCK_STRUCT *v)
{
    if(
      ((*v->g_Discrete_Input & COMMAND_BIT) != (v->g_Discrete_Input_Prev & COMMAND_BIT))
    )//Условие, что произошла смена команды.
  {
   v->g_Timers[Timer_Command_On] = 1;//Включение таймера смены команды.

   if(v->g_Timers[Timer_Command] > v->g_Delays[Command_Change_Delay])//Условие, что прошло время для изменения команды.
   {
    v->g_Timers[Timer_Command_On] = 0;
    if(v->g_State == OPEN_STATE)
    {
    ON_FLAG(v, STOP_BIT_OUT);
    GO_TO(v, OPEN_STATE, STOP_IN_OPENING);
    v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.
    }
    if(v->g_State == CLOSE_STATE)
    {
    ON_FLAG(v, STOP_BIT_OUT);
    GO_TO(v, CLOSE_STATE, STOP_IN_CLOSING);
    v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.
    }
   }
  }
  else
  {
  v->g_Timers[Timer_Command_On] = 0;
  }
 }

static void BLOCK_CHECK(BLOCK_STRUCT *v)
{

  if(
    (v->g_Discrete_Output & VKZ_BIT_OUT)
    &&
    (!(v->g_Discrete_Output & BLOCK_BIT_OUT))
    )
  {
    if(
      (*v->g_Current_Feed > v->g_Current_Levels[Current_VKZ_Block_Level])
      &&
      ((*v->g_Position_Feed - v->g_Indents[Close_Indent]) > v->g_Indents[VKZ_Block_Indent])
      &&
      (!(v->g_Discrete_Input_Prev & COMMAND_BIT))
      )
    {
      v->g_Timers[Timer_Current_On] = 1;

      if(v->g_Timers[Timer_Current] > v->g_Delays[Current_VKZ_Block_Delay])
      {
        v->g_Timers[Timer_Current_On] = 0;
        ON_FLAG(v, BLOCK_BIT_OUT);
      }
    }
    else
    {
      v->g_Timers[Timer_Current] = 0;
    }
  }

  if(
    (v->g_Discrete_Output & VKZ_BIT_OUT)
    &&
    (v->g_Discrete_Output & BLOCK_BIT_OUT)
    )
  {
    if(
      (*v->g_Current_Feed < v->g_Current_Levels[Current_VKZ_Block_Level])
      &&
      ((*v->g_Position_Feed - v->g_Indents[Close_Indent]) < v->g_Indents[VKZ_Block_Indent])
      &&
      (v->g_Discrete_Input_Prev & COMMAND_BIT)
      )
    {
      v->g_Timers[Timer_Current_On] = 1;

      if(v->g_Timers[Timer_Current] > v->g_Delays[Current_VKZ_Block_Delay])
      {
        v->g_Timers[Timer_Current_On] = 0;
        RESET_FLAG(v, BLOCK_BIT_OUT);
      }
    }
    else
    {
      v->g_Timers[Timer_Current] = 0;
    }
  }

  if((*v->g_Discrete_Input & BLOCK_BIT) != (v->g_Discrete_Input_Prev & BLOCK_BIT))
  {
    v->g_Timers[Timer_Block_On] = 1;

    if(v->g_Timers[Timer_Block] > v->g_Delays[Block_Change_Delay])
    {
      v->g_Timers[Timer_Block_On] = 0;

    v->g_Discrete_Input_Prev = *v->g_Discrete_Input;

      if(v->g_Discrete_Input_Prev & COMMAND_BIT)
      {
        GO_TO(v, OPEN_STATE, OPENING);
      }
    }
  }
  else
  {
    v->g_Timers[Timer_Block_On] = 0;
  }

}
/*
static void ALARM_CHECK(BLOCK_STRUCT *v)
{

}
*/
static void FOTO_CHECK(BLOCK_STRUCT *v)
{
  if(
      ((*v->g_Discrete_Input & FOTO_BIT) != (v->g_Discrete_Input_Prev & FOTO_BIT))
      )//Условие, что произошла смена команды.
    {
      v->g_Timers[Timer_Foto_On] = 1;//Включение таймера смены команды.

      if(v->g_Timers[Timer_Foto] > v->g_Delays[Foto_Change_Delay])//Условие, что прошло время для изменения команды.
      {
        v->g_Timers[Timer_Foto_On] = 0;

    if(*v->g_Discrete_Input & FOTO_BIT)
    {
      ON_FLAG(v, FOTO_BIT_OUT);
    }

    if(v->g_State == CLOSE_STATE)
    {
      GO_TO(v, CLOSE_STATE, FOTO_IN_CLOSING);
    }


        v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.
      }
    }
    else
    {
      v->g_Timers[Timer_Foto_On] = 0;
    }
}
/*
static void BLOCK_ALARM_FOTO_CHECK(BLOCK_STRUCT *v)
{

}
*/

static void POS_GE_AND_SE_OR_Min_SPD(BLOCK_STRUCT *v, int POS, int State, int Sub_State)
{
  if(((*v->g_Position_Feed >= (POS - v->Position_Limit)) && (*v->g_Position_Feed <= (POS + v->Position_Limit))) || (*v->g_Speed_Feed <= v->g_SPDs[SPD_MIN]))//???????????????????????
  {
    v->g_Timers[Timer_Position_On] = 1;

    if(v->g_Timers[Timer_Position] > v->g_Delays[Position_Stop_Delay])
    {
      v->g_Timers[Timer_Position_On] = 0;
      GO_TO(v, State, Sub_State);
    }
  }
  else
  {
    v->g_Timers[Timer_Position_On] = 0;
  }
}

static void POS_GE_AND_SE(BLOCK_STRUCT *v, int POS, int State, int Sub_State)
{
  if(((*v->g_Position_Feed >= (POS - v->Position_Limit)) && (*v->g_Position_Feed <= (POS + v->Position_Limit))))
  {
    v->g_Timers[Timer_Position_On] = 1;

    if(v->g_Timers[Timer_Position] > v->g_Delays[Position_Stop_Delay])
    {
      v->g_Timers[Timer_Position_On] = 0;
      GO_TO(v, State, Sub_State);
    }
  }
  else
  {
    v->g_Timers[Timer_Position_On] = 0;
  }
}


static void OPENING_CLOSING_ALGORITHM(BLOCK_STRUCT *v, int State, int Sub_State, int Checking_BIT)
{
  if(v->g_Discrete_Output & Checking_BIT)//Движение в зоке VKO.
  {
    GO_TO(v, State, Sub_State);
  }

  RVM_CHECK(v);
  STOP_CHECK(v);
}


static void Timers(BLOCK_STRUCT *v)
{
  if(v->g_Timers[Timer_VKO_VKZ_Another_Block_On])
  {
    v->g_Timers[Timer_VKO_VKZ_Another_Block] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
  }


  if(v->g_Timers[Timer_VKO_On])
  {
    v->g_Timers[Timer_VKO] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_VKO] = 0;
  }


  if(v->g_Timers[Timer_VKZ_On])
  {
    v->g_Timers[Timer_VKZ] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_VKZ] = 0;
  }



  if(v->g_Timers[Timer_Current_On])
  {
    v->g_Timers[Timer_Current] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_Current] = 0;
  }



  if(v->g_Timers[Timer_Position_On])
  {
    v->g_Timers[Timer_Position] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_Position] = 0;
  }



  if(v->g_Timers[Timer_Command_On])
  {
    v->g_Timers[Timer_Command] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_Command] = 0;
  }



  if(v->g_Timers[Timer_Block_On])
  {
    v->g_Timers[Timer_Block] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_Block] = 0;
  }



  if(v->g_Timers[Timer_Alarm_On])
  {
    v->g_Timers[Timer_Alarm] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_Alarm] = 0;
  }



  if(v->g_Timers[Timer_Foto_On])
  {
    v->g_Timers[Timer_Foto] += v->Timer_Discrete;
  }
  else
  {
    v->g_Timers[Timer_Foto] = 0;
  }
}


static void TO_OPEN(BLOCK_STRUCT *v)
{
  if(
    (!(v->g_Discrete_Output & VKO_BIT_OUT))
    &&
    (!(v->g_Discrete_Input_Prev & BLOCK_BIT))
  &&
    (!(v->g_Discrete_Output & BLOCK_BIT_OUT))
    )
  {
    //Открыть.
    if(v->g_Discrete_Output & RVM_BIT_OUT)
    {
      GO_TO(v, OPEN_STATE, OPENING_AFTER_RVM);
    }
    else if(v->g_Discrete_Output & STOP_BIT_OUT)
    {
      GO_TO(v, OPEN_STATE, OPENING_AFTER_STOP);
    }
    else if(v->g_Discrete_Output & FOTO_BIT_OUT)
    {
      GO_TO(v, OPEN_STATE, OPENING_AFTER_FOTO);
    }
    else
    {
      GO_TO(v, OPEN_STATE, OPENING);
    }
  }
}


static void TO_CLOSE(BLOCK_STRUCT *v)
{
  if(
    (!(v->g_Discrete_Input_Prev & FOTO_BIT))
    &&
    (!(v->g_Discrete_Output & VKZ_BIT_OUT))
    &&
    (!(v->g_Discrete_Input_Prev & BLOCK_BIT))
  &&
    (!(v->g_Discrete_Output & BLOCK_BIT_OUT))
    )
  {
    //Закрыть.
    if(v->g_Discrete_Output & RVM_BIT_OUT)
    {
      GO_TO(v, CLOSE_STATE, CLOSING_AFTER_RVM);
    }
    else if(v->g_Discrete_Output & STOP_BIT_OUT)
    {
      GO_TO(v, CLOSE_STATE, CLOSING_AFTER_STOP);
    }
    else if(v->g_Discrete_Output & FOTO_BIT_OUT)
    {
      GO_TO(v, CLOSE_STATE, CLOSING_AFTER_FOTO);
    }
    else
    {
      GO_TO(v, CLOSE_STATE, CLOSING);
    }
  }
}


static void IMPULSE_COMMAND(BLOCK_STRUCT *v)
{
  if((*v->g_Discrete_Input & COMMAND_BIT) != (v->g_Discrete_Input_Prev & COMMAND_BIT))//Условие, что произошла смена команды.
  {
    v->g_Timers[Timer_Command_On] = 1;//Включение таймера смены команды.

    if(v->g_Timers[Timer_Command] > v->g_Delays[Command_Change_Delay])//Условие, что прошло время для изменения команды.
    {
      v->g_Timers[Timer_Command_On] = 0;//Выключение таймера смены команды.

      v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.

      if(v->g_Discrete_Input_Prev & COMMAND_BIT)//Определение команды.
      {
        TO_OPEN(v);
      }
      else
      {
        TO_CLOSE(v);
      }
    }
  }
  else
  {
    if((v->g_Timers[Timer_Command] != 0))//Условие что смена была, но на время короче чем время для изменения команды.
    {
      v->g_Timers[Timer_Command_On] = 0;

      if(v->g_Discrete_Input_Prev & COMMAND_BIT)//Определение команды.
      {
        TO_OPEN(v);
      }
      else
      {
        TO_CLOSE(v);
      }
    }
  }
}

static void POSITIVE_COMMAND(BLOCK_STRUCT *v)
{
  if (*v->g_Discrete_Input & COMMAND_BIT)
  {
    if (v->g_Discrete_Input_Prev & COMMAND_BIT)
    {
      v->g_Timers[Timer_Command_On] = 0;
    }
    else
    {
      v->g_Timers[Timer_Command_On] = 1;
    }

    if (v->g_Timers[Timer_Command] >= v->g_Delays[Command_Change_Delay])
    {
      v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.
    }
  }
  else
  {
    if (!(v->g_Discrete_Input_Prev & COMMAND_BIT))
    {
      v->g_Timers[Timer_Command_On] = 0;
    }
    else
    {
      v->g_Timers[Timer_Command_On] = 1;
    }

    if (v->g_Timers[Timer_Command] >= v->g_Delays[Command_Change_Delay])
    {
      v->g_Discrete_Input_Prev = *v->g_Discrete_Input;//Сохранение состояния.
    }
  }

  if(v->g_Discrete_Input_Prev & COMMAND_BIT)//Определение команды.
  {
    TO_OPEN(v);
  }
  else
  {
    TO_CLOSE(v);
  }
}



static void Mooving_Wait(BLOCK_STRUCT *v)
{

  VKO_VKZ_CHECK(v);
  ANOTHER_BLOCK_VKO_VKZ(v);

  if(v->Command_Type == IMPULSE_TYPE)
  {
    IMPULSE_COMMAND(v);
  }
  else
  {
    POSITIVE_COMMAND(v);
  }

  FOTO_CHECK(v);
  BLOCK_CHECK(v);
}

static void PV_Coordinates_Wait(BLOCK_STRUCT *v)
{

  v->g_Direction = STOP_DIRECTION;

}



static void Mooving_Init(BLOCK_STRUCT *v)
{
  ANOTHER_BLOCK_VKO_VKZ_COUNTER(v);
  switch(v->g_Sub_State)
  {
    case FIRST_CLOSING://Первое закрытие.

    RESET_FLAG(v, INIT_BIT_OUT);
      if(*v->g_Current_Feed > v->g_Current_Levels[Current_Close_Stop_Level]) //Условие, что ток возрос выше уставки нахождения упора.
      {
        v->g_Timers[Timer_Current_On] = 1;//Включение таймера тока.

        if(v->g_Timers[Timer_Current] > v->g_Delays[Position_Stop_Delay])
        {
          v->g_Timers[Timer_Current_On] = 0;
      GO_TO(v, INIT_STATE, VKZ_POS_CHECK);
        }

      }
      else
      {
        v->g_Timers[Timer_Current_On] = 0;//Выключение таймера тока.
      }

    break;

    case VKZ_POS_CHECK://Запоминание позиции в состоянии Закрыто.

    GO_TO(v, INIT_STATE, POSITION_RESET_ON);

    break;

    case POSITION_RESET_ON://Подача сигнала на сброс позиции.

      ON_FLAG(v, RESET_POSITION_BIT_OUT);
    GO_TO(v, INIT_STATE, POSITION_RESET_OFF);

    break;

    case POSITION_RESET_OFF://Сброс сигнала на сброс позиции.

    RESET_FLAG(v, RESET_POSITION_BIT_OUT);
  GO_TO(v, INIT_STATE, FIRST_CLOSED);

    break;

    case FIRST_CLOSED://?????? ???????? ?????????.


    ON_FLAG(v, VKZ_BIT_OUT);

    v->g_Timers[Timer_VKZ_On]  = 1;

    if(v->g_Timers[Timer_VKZ] > v->g_Delays[VKZ_On_Delay])
    {
     v->g_Timers[Timer_VKZ_On]=0;
     GO_TO(v, INIT_STATE, FIRST_OPENING);
    }

    break;

    case FIRST_OPENING://Первое открытие.


      RESET_FLAG(v, VKZ_BIT_OUT);
    if(*v->g_Current_Feed > v->g_Current_Levels[Current_Open_Stop_Level]) //Условие, что ток возрос выше уставки нахождения упора.
      {
        v->g_Timers[Timer_Current_On] = 1;//Включение таймера тока.

        if(v->g_Timers[Timer_Current] > v->g_Delays[Position_Stop_Delay])
        {
          v->g_Timers[Timer_Current_On] = 0;
      GO_TO(v, INIT_STATE, VKO_POS_CHECK);
        }

      }
      else
      {
        v->g_Timers[Timer_Current_On] = 0;//Выключение таймера тока.
      }

    break;

    case VKO_POS_CHECK://Запоминание позиции в состоянии Открыто.

      GO_TO(v, INIT_STATE, DOOR_LENGTH_CHECK);

    break;

    case DOOR_LENGTH_CHECK://Определение длины проёма.

      GO_TO(v, INIT_STATE, STOPPING_TO_VKO_POS);

    break;

  case STOPPING_TO_VKO_POS:

    POS_GE_AND_SE(v, v->g_Door_Length - v->g_Indents[Open_Indent], INIT_STATE, FIRST_OPENED);

  break;

    case FIRST_OPENED://Первое открытое состояние.

  ON_FLAG(v, VKO_BIT_OUT);

  v->g_Timers[Timer_VKO_On]=1;

  if(v->g_Timers[Timer_VKO] > v->g_Delays[VKO_On_Delay])
  {
   v->g_Timers[Timer_VKO_On]=0;
     GO_TO(v, INIT_STATE, SECOND_CLOSING);
  }
    break;


    case SECOND_CLOSING://Второе закрытие.

    RESET_FLAG(v, VKO_BIT_OUT);

    POS_GE_AND_SE(v, v->g_Indents[Close_Indent], INIT_STATE, SECOND_CLOSED);

    break;
    case SECOND_CLOSED://?????? ???????? ?????????.

    ON_FLAG(v, VKZ_BIT_OUT);

  v->g_Timers[Timer_VKZ_On]=1;

  if(v->g_Timers[Timer_VKZ] > v->g_Delays[VKZ_On_Delay])
  {
    v->g_Timers[Timer_VKZ_On]=0;
    GO_TO(v, WAIT_STATE, WAIT_STATE);
    v->g_VKO_Another_Block_Counter = 0;
    v->g_VKZ_Another_Block_Counter = 0;
    RESET_FLAG(v, VKZ_BIT_OUT);
    ON_FLAG(v, INIT_BIT_OUT);
  }
    break;
  }
}

static void PV_Coordinates_Init(BLOCK_STRUCT *v)
{

  switch(v->g_Sub_State)
  {
    case FIRST_CLOSING:

      v->g_Points[1] = -2000;
      v->g_Points[2] = v->g_SPDs[SPD_SYNCH];
      v->g_Points[9] = 2000;
      v->g_Points[10] = v->g_SPDs[SPD_SYNCH];
      v->g_Num_Of_Points = 1;
      v->g_Direction = CLOSE_DIRECTION;

    break;


    case VKZ_POS_CHECK:

      v->g_VKZ_Pos = *v->g_Position_Feed_Abs;

    break;

    case FIRST_CLOSED:

    v->g_Points[1] = v->g_Indents[Close_Indent];

      v->g_Direction = STOP_DIRECTION;

    break;

    case FIRST_OPENING:

      v->g_Points[1] = 2000;
      v->g_Points[2] = v->g_SPDs[SPD_SYNCH];
      v->g_Points[9] = 2000;
      v->g_Points[10] = v->g_SPDs[SPD_SYNCH];
      v->g_Num_Of_Points = 1;
      v->g_Direction = OPEN_DIRECTION;

    break;

    case VKO_POS_CHECK:

      v->g_VKO_Pos = *v->g_Position_Feed_Abs;

    break;

    case DOOR_LENGTH_CHECK:

      v->g_Door_Length = v->g_VKO_Pos - v->g_VKZ_Pos;

    break;

  case STOPPING_TO_VKO_POS:

  v->AR = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * 100) / 100;//длина участка разгона.
  v->AT = ((v->g_SPDs[SPD_MAX] - v->g_SPDs[SPD_MIN]) * 100) / 100;//длина участка торможения.

  if(v->Points_Changing_Enable)
  {

    //POS0
    v->g_Points[1] = v->g_Door_Length - v->g_Indents[Open_Indent];
    v->g_Points[2] = v->g_SPDs[SPD_MIN];
    //POS2
    v->g_Points[5] = v->g_Door_Length;
    v->g_Points[6] = v->g_SPDs[SPD_SYNCH];
    //POS1

    if(
      (v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT)))
      >
      v->g_Door_Length
      )
    {
      v->g_Points[3] = v->g_Door_Length;
    }
    else
    {
      v->g_Points[3] = v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT));
    }

    if(
      (v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT)))
      <
      (v->g_Door_Length - v->g_Indents[Open_Indent])
      )
    {
      v->g_Points[3] = v->g_Door_Length - v->g_Indents[Open_Indent];
    }
    else
    {
      v->g_Points[3] = v->g_Points[1] + (((v->g_Points[5] - v->g_Points[1]) * v->AR) / (v->AR + v->AT));
    }


    if(
      (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
      >
      v->g_SPDs[SPD_MAX]
      )
    {
      v->g_Points[4] = v->g_SPDs[SPD_MAX];
    }
    else
    {
      v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
    }

    if(
      (((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT))
      <
      v->g_SPDs[SPD_MIN]
      )
    {
      v->g_Points[4] = v->g_SPDs[SPD_MIN];
    }
    else
    {
      v->g_Points[4] = ((v->g_Points[5] - v->g_Points[1]) * v->g_SPDs[SPD_MAX]) / (v->AR + v->AT);
    }



    v->g_Points[7] = 0;
    v->g_Points[8] = 0;

    v->g_Points[9] = v->g_Door_Length;
    v->g_Points[10] = v->g_SPDs[SPD_MAX];
    v->g_Num_Of_Points = 3;


    v->g_Direction = CLOSE_DIRECTION;
  }

  v->Points_Changing_Enable = 0;

  break;

    case FIRST_OPENED://Первое открытое состояние.

      v->g_Direction = STOP_DIRECTION;


    break;


    case SECOND_CLOSING:

      OPEN_CLOSE_MOVE(v, v->g_Indents[Close_Indent], *v->g_Position_Feed, CLOSE_DIRECTION);

    break;

    case SECOND_CLOSED://Второе закрытое состояние.

      v->g_Direction = STOP_DIRECTION;

    break;
  }
}



static void Mooving_Open(BLOCK_STRUCT *v)
{

  VKO_VKZ_CHECK(v);

  switch(v->g_Sub_State)
  {
    case OPENING://Открытие.

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;


    case RVM_IN_OPENING:

      GO_TO(v, RVM_STATE, OPENING_RVM);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

    case OPENING_AFTER_RVM:

      RESET_FLAG(v, RVM_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;

    case STOP_IN_OPENING:

      GO_TO(v, STOP_STATE, OPENING_STOP);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

    case OPENING_AFTER_STOP:

      RESET_FLAG(v, STOP_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;


    case BLOCK_IN_OPENING:

      GO_TO(v, BLOCK_STATE, OPENING_BLOCK);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;


    case OPENING_AFTER_BLOCK:

      RESET_FLAG(v, BLOCK_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;

    case ALARM_WAITING_OF_OPENING:

      if(v->g_Discrete_Output & VKO_BIT_OUT)//Движение в зоке VKO.
      {
        GO_TO(v, ALARM_STATE, ALARM_END);
      }

    break;


    case ALARM_STOP_AND_CLOSING:

      GO_TO(v, ALARM_STATE, ALARM_STOP_IN_OPENING);

    break;


    case FOTO_IN_OPENING:

      GO_TO(v, FOTO_STATE, OPENING_FOTO);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

    case OPENING_AFTER_FOTO:

    RESET_FLAG(v, FOTO_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;
  }


}

static void PV_Coordinates_Open(BLOCK_STRUCT *v)
{

  switch(v->g_Sub_State)
  {
    case OPENING://Открытие.

      OPEN_CLOSE_MOVE(v, *v->g_Position_Feed, v->g_Door_Length - v->g_Indents[Open_Indent], OPEN_DIRECTION);

    break;

    case RVM_IN_OPENING:

      v->g_POSs[RVM_POS] = *v->g_Position_Feed;
      v->g_SPDs[RVM_SPD] = *v->g_Speed_Feed;

    break;

    case OPENING_AFTER_RVM:

      OPEN_CLOSE_MOVE(v, v->g_POSs[STOP_INDENT_POS_END], v->g_Door_Length - v->g_Indents[Open_Indent], OPEN_DIRECTION);

    break;

    case STOP_IN_OPENING:

      v->g_POSs[STOP_POS] = *v->g_Position_Reff;
      v->g_SPDs[STOP_SPD] = *v->g_Speed_Reff;

    break;

    case OPENING_AFTER_STOP:

      OPEN_CLOSE_MOVE(v, v->g_POSs[STOP_INDENT_POS_END], v->g_Door_Length - v->g_Indents[Open_Indent], OPEN_DIRECTION);

    break;


    case BLOCK_IN_OPENING:

      v->g_POSs[BLOCK_POS] = *v->g_Position_Feed;
      v->g_SPDs[BLOCK_SPD] = *v->g_Speed_Feed;

    break;


    case OPENING_AFTER_BLOCK:

      OPEN_CLOSE_MOVE(v, v->g_POSs[STOP_INDENT_POS_END], v->g_Door_Length - v->g_Indents[Open_Indent], OPEN_DIRECTION);

    break;

    case ALARM_WAITING_OF_OPENING:


    break;


    case ALARM_STOP_AND_CLOSING:

      v->g_POSs[ALARM_POS] = *v->g_Position_Feed;
      v->g_SPDs[ALARM_SPD] = *v->g_Speed_Feed;

    break;


    case FOTO_IN_OPENING:

      v->g_POSs[FOTO_POS] = *v->g_Position_Feed;
      v->g_SPDs[FOTO_SPD] = *v->g_Speed_Feed;

    break;


    case OPENING_AFTER_FOTO:

      OPEN_CLOSE_MOVE(v, v->g_POSs[STOP_INDENT_POS_END], v->g_Door_Length - v->g_Indents[Open_Indent], OPEN_DIRECTION);

    break;
  }
}



static void Mooving_Close(BLOCK_STRUCT *v)
{
  VKO_VKZ_CHECK(v);

  switch(v->g_Sub_State)
  {

    case CLOSING://Открытие.

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;


    case RVM_IN_CLOSING:

      GO_TO(v, RVM_STATE, CLOSING_RVM);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

    case CLOSING_AFTER_RVM:

      RESET_FLAG(v, RVM_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;

    case STOP_IN_CLOSING:

      GO_TO(v, STOP_STATE, CLOSING_STOP);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

    case CLOSING_AFTER_STOP:

      RESET_FLAG(v, STOP_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;


    case BLOCK_IN_CLOSING:

      GO_TO(v, BLOCK_STATE, CLOSING_BLOCK);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

    case CLOSING_AFTER_BLOCK:

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;

    case ALARM_WAITING_OF_CLOSING:

      if(v->g_Discrete_Output & VKZ_BIT_OUT)//Движение в зоке VKO.
      {
        GO_TO(v, ALARM_STATE, ALARM_END);
      }

    break;


    case ALARM_STOP_AND_OPENING:

      GO_TO(v, ALARM_STATE, ALARM_STOP_IN_CLOSING);

    break;

    case FOTO_IN_CLOSING:

      GO_TO(v, FOTO_STATE, CLOSING_FOTO);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

    case CLOSING_AFTER_FOTO:

  RESET_FLAG(v, FOTO_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;
  }

  FOTO_CHECK(v);

}

static void PV_Coordinates_Close(BLOCK_STRUCT *v)
{

  switch(v->g_Sub_State)
  {
    case CLOSING://Открытие.

      OPEN_CLOSE_MOVE(v, v->g_Indents[Close_Indent], *v->g_Position_Feed, CLOSE_DIRECTION);

    break;

    case RVM_IN_CLOSING:

      v->g_POSs[RVM_POS] = *v->g_Position_Feed;
      v->g_SPDs[RVM_SPD] = *v->g_Speed_Feed;

    break;

    case CLOSING_AFTER_RVM:

      OPEN_CLOSE_MOVE(v, v->g_Indents[Close_Indent], v->g_POSs[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;

    case STOP_IN_CLOSING:

      v->g_POSs[STOP_POS] = *v->g_Position_Reff;
      v->g_SPDs[STOP_SPD] = *v->g_Speed_Reff;

    break;

    case CLOSING_AFTER_STOP:

      OPEN_CLOSE_MOVE(v, v->g_Indents[Close_Indent], v->g_POSs[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;


    case BLOCK_IN_CLOSING:

      v->g_POSs[BLOCK_POS] = *v->g_Position_Feed;
      v->g_SPDs[BLOCK_SPD] = *v->g_Speed_Feed;

    break;

    case CLOSING_AFTER_BLOCK:

      OPEN_CLOSE_MOVE(v, v->g_Indents[Close_Indent], v->g_POSs[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;

    case ALARM_WAITING_OF_OPENING:


    break;


    case ALARM_STOP_AND_CLOSING:

      v->g_POSs[ALARM_POS] = *v->g_Position_Feed;
      v->g_SPDs[ALARM_SPD] = *v->g_Speed_Feed;

    break;

    case FOTO_IN_CLOSING:

      v->g_POSs[FOTO_POS] = *v->g_Position_Feed;
      v->g_SPDs[FOTO_SPD] = *v->g_Speed_Feed;

    break;

    case CLOSING_AFTER_FOTO:

      OPEN_CLOSE_MOVE(v, v->g_Indents[Close_Indent], v->g_POSs[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;

  }
}



static void Mooving_Stop(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_STOP:

      POS_GE_AND_SE_OR_Min_SPD(v, v->g_POSs[STOP_POS_END], STOP_STATE, OPENING_STOP_INDENT);

    break;

    case OPENING_STOP_INDENT:

      POS_GE_AND_SE(v, v->g_POSs[STOP_INDENT_POS_END], STOP_STATE, STOP_END);

    break;

    case CLOSING_STOP:

      POS_GE_AND_SE_OR_Min_SPD(v, v->g_POSs[STOP_POS_END], STOP_STATE, CLOSING_STOP_INDENT);

    break;

    case CLOSING_STOP_INDENT:

      POS_GE_AND_SE(v, v->g_POSs[STOP_INDENT_POS_END], STOP_STATE, STOP_END);

    break;

    case STOP_END://КОНЕЦ

      GO_TO(v, WAIT_STATE, WAIT_STATE);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;

  }

}

static void PV_Coordinates_Stop(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_STOP:

      STOPPING_MOVE(v, v->g_POSs[STOP_POS], v->g_SPDs[STOP_SPD], v->g_AR_AT_POSs[STOP_AT_POS], v->g_AR_AT_SPDs[STOP_AT_SPD], OPEN_DIRECTION);

    break;


    case OPENING_STOP_INDENT:

      INDENT_MOVE(v, v->g_Indents[STOP_Indent], CLOSE_DIRECTION);

    break;


    case CLOSING_STOP:

      STOPPING_MOVE(v, v->g_POSs[STOP_POS], v->g_SPDs[STOP_SPD], v->g_AR_AT_POSs[STOP_AT_POS], v->g_AR_AT_SPDs[STOP_AT_SPD], CLOSE_DIRECTION);

    break;


    case CLOSING_STOP_INDENT:

      INDENT_MOVE(v, v->g_Indents[STOP_Indent], OPEN_DIRECTION);

    break;


    case STOP_END:

      v->g_Direction = STOP_DIRECTION;

    break;

  }
}



static void Mooving_RVM(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_RVM:

      POS_GE_AND_SE_OR_Min_SPD(v, v->g_POSs[STOP_POS_END], RVM_STATE, OPENING_RVM_INDENT);

    break;

    case OPENING_RVM_INDENT:

      POS_GE_AND_SE(v, v->g_POSs[STOP_INDENT_POS_END], RVM_STATE, RVM_END);

    break;

    case CLOSING_RVM:

      POS_GE_AND_SE_OR_Min_SPD(v, v->g_POSs[STOP_POS_END], RVM_STATE, CLOSING_RVM_INDENT);

    break;

    case CLOSING_RVM_INDENT:

      POS_GE_AND_SE(v, v->g_POSs[STOP_INDENT_POS_END], RVM_STATE, RVM_END);

    break;


    case RVM_END://КОНЕЦ

      GO_TO(v, WAIT_STATE, WAIT_STATE);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;
  }

}

static void PV_Coordinates_RVM(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_RVM:

      STOPPING_MOVE(v, v->g_POSs[RVM_POS], v->g_SPDs[RVM_SPD], v->g_AR_AT_POSs[RVM_AT_POS], v->g_AR_AT_SPDs[RVM_AT_SPD], OPEN_DIRECTION);

    break;


    case OPENING_RVM_INDENT:

      INDENT_MOVE(v, v->g_Indents[RVM_Indent], CLOSE_DIRECTION);

    break;

    case CLOSING_RVM:

      STOPPING_MOVE(v, v->g_POSs[RVM_POS], v->g_SPDs[RVM_SPD], v->g_AR_AT_POSs[RVM_AT_POS], v->g_AR_AT_SPDs[RVM_AT_SPD], CLOSE_DIRECTION);

    break;


    case CLOSING_RVM_INDENT:

      INDENT_MOVE(v, v->g_Indents[RVM_Indent], OPEN_DIRECTION);

    break;


    case RVM_END:

      v->g_Direction = STOP_DIRECTION;

    break;

  }
}



static void Mooving_BLOCK(BLOCK_STRUCT *v)
{



}

static void PV_Coordinates_BLOCK(BLOCK_STRUCT *v)
{
  v->g_Direction = STOP_DIRECTION;
}



static void Mooving_ALARM(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case ALARM_STOP_IN_OPENING:

      POS_GE_AND_SE_OR_Min_SPD(v, v->g_POSs[STOP_POS_END], ALARM_STATE, ALARM_CLOSING);

    break;

    case ALARM_CLOSING:

      POS_GE_AND_SE(v, v->g_Indents[Close_Indent], ALARM_STATE, ALARM_END);

    break;

    case ALARM_STOP_IN_CLOSING:

      POS_GE_AND_SE_OR_Min_SPD(v, v->g_POSs[STOP_POS_END], ALARM_STATE, ALARM_OPENING);

    break;

    case ALARM_OPENING:

      POS_GE_AND_SE(v, (v->g_Door_Length - v->g_Indents[Open_Indent]), ALARM_STATE, ALARM_END);

    break;


    case ALARM_END://КОНЕЦ
      //Задержку до того пока не сбросится BLOCK делать тут или нет ??? скорее всего тут .. надо подумать еще..

    GO_TO(v, WAIT_STATE, WAIT_STATE);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;
  }

}

static void PV_Coordinates_ALARM(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case ALARM_STOP_IN_OPENING:

      STOPPING_MOVE(v, v->g_POSs[ALARM_POS], v->g_SPDs[ALARM_SPD], v->g_AR_AT_POSs[ALARM_AT_POS], v->g_AR_AT_SPDs[ALARM_AT_SPD], OPEN_DIRECTION);

    break;


    case ALARM_CLOSING:

      OPEN_CLOSE_MOVE(v, v->g_Indents[Close_Indent], v->g_POSs[STOP_POS_END], CLOSE_DIRECTION);

    break;

    case ALARM_STOP_IN_CLOSING:

      STOPPING_MOVE(v, v->g_POSs[ALARM_POS], v->g_SPDs[ALARM_SPD], v->g_AR_AT_POSs[ALARM_AT_POS], v->g_AR_AT_SPDs[ALARM_AT_SPD], CLOSE_DIRECTION);

    break;


    case ALARM_OPENING:

      OPEN_CLOSE_MOVE(v, v->g_POSs[STOP_POS_END], v->g_Door_Length - v->g_Indents[Open_Indent], CLOSE_DIRECTION);

    break;


    case ALARM_END:

      v->g_Direction = STOP_DIRECTION;

    break;
  }
}


static void Mooving_FOTO(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {

    case CLOSING_FOTO:

      POS_GE_AND_SE_OR_Min_SPD(v, v->g_POSs[STOP_POS_END], FOTO_STATE, CLOSING_FOTO_INDENT);

    break;

    case CLOSING_FOTO_INDENT:

      POS_GE_AND_SE(v, v->g_POSs[STOP_INDENT_POS_END], FOTO_STATE, FOTO_END);

    break;


    case FOTO_END://КОНЕЦ

    GO_TO(v, WAIT_STATE, WAIT_STATE);

      v->g_Timers[Timer_VKO_VKZ_Another_Block] = 0;
      v->g_Timers[Timer_Current] = 0;
      v->g_Timers[Timer_Position] = 0;
      v->g_Timers[Timer_Command] = 0;

    break;
  }

}

static void PV_Coordinates_FOTO(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_FOTO:

      STOPPING_MOVE(v, v->g_POSs[FOTO_POS], v->g_SPDs[FOTO_SPD], v->g_AR_AT_POSs[FOTO_AT_POS], v->g_AR_AT_SPDs[FOTO_AT_SPD], OPEN_DIRECTION);

    break;


    case OPENING_FOTO_INDENT:

      INDENT_MOVE(v, v->g_Indents[FOTO_Indent], CLOSE_DIRECTION);

    break;

    case CLOSING_FOTO:

      STOPPING_MOVE(v, v->g_POSs[FOTO_POS], v->g_SPDs[FOTO_SPD], v->g_AR_AT_POSs[FOTO_AT_POS], v->g_AR_AT_SPDs[FOTO_AT_SPD], CLOSE_DIRECTION);

    break;


    case CLOSING_FOTO_INDENT:

      INDENT_MOVE(v, v->g_Indents[FOTO_Indent], OPEN_DIRECTION);

    break;


    case FOTO_END:

      v->g_Direction = STOP_DIRECTION;

    break;
  }
}



static void (*Mooving []) (BLOCK_STRUCT *v) = {
  Mooving_Wait,
  Mooving_Init,
  Mooving_Open,
  Mooving_Close,
  Mooving_Stop,
  Mooving_RVM,
  Mooving_BLOCK,
  Mooving_ALARM,
  Mooving_FOTO
};

static void (*PV_Coordinates []) (BLOCK_STRUCT *v) = {
  PV_Coordinates_Wait,
  PV_Coordinates_Init,
  PV_Coordinates_Open,
  PV_Coordinates_Close,
  PV_Coordinates_Stop,
  PV_Coordinates_RVM,
  PV_Coordinates_BLOCK,
  PV_Coordinates_ALARM,
  PV_Coordinates_FOTO
};



void Init(void)
{
  GO_TO(v, INIT_STATE, FIRST_CLOSING);
}

void Exec(void)
{
if (!*v->Enable)
  {
    v->g_Discrete_Output=0;
    v->g_Num_Of_Points=0;
    v->g_Direction=0;
    v->n_State_Out=0;
    v->n_Sub_State_Out=0;
    return;
  }
  Timers(v);
  Mooving[v->g_State](v);
  PV_Coordinates[v->g_State](v);
  v->n_State_Out = v->g_State;
  v->n_Sub_State_Out = v->g_Sub_State;

}

