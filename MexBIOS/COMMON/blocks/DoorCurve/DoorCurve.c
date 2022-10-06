//DoorCurve

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
#define INIT_ANOTHER_BLOCK_BIT 64

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

//Points Defines
#define POS1 1
#define POS2 3
#define POS3 5
#define POS4 7
#define POS5 9
#define POS6 11
#define POS7 13
#define POS8 15
#define POS9 17

#define SPD1 2
#define SPD2 4
#define SPD3 6
#define SPD4 8
#define SPD5 10
#define SPD6 12
#define SPD7 14
#define SPD8 16
#define SPD9 18

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
#define SPD_MEDIUM 7
#define SPD_MIN 8
#define SPD_SYNCH 9
#define SPD_RVM_Level 10


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


//g_AR_AT_SLOW_POSs Defines
#define AR_SLOW_START_INDENT 1
#define AR_SLOW_END_INDENT 2
#define AT_SLOW_START_INDENT 3
#define AT_SLOW_END_INDENT 4


//g_AR_AT_SLOW_SPDs Defines
#define AR_SLOW_SPD 1
#define AT_SLOW_SPD 2

//Command_Type Defines
#define IMPULSE_OR_POSITIVE_TYPE_OF_COMMANDS 1
#define INIT_ANOTHER_BLOCK_BIT_CHECKING_NEED 2


float A_CL = 0;
float A_OP = 0;
float A_SLOW_CL = 0;
float A_SLOW_OP = 0;
float MAX = 0;

float point1_pos = 0;
float point1_spd = 0;
float point2_pos = 0;
float point2_spd = 0;
float a_point1 = 0;
float a_point2 = 0;
float intersection_point_spd = 0;
float intersection_point_pos = 0;
float max_slow_spd = 0;
float a_point = 0;

float *l_points = 0;
float *l_timers = 0;
float *l_delays = 0;
float *l_poss = 0;
float *l_spds = 0;
float *l_indents = 0;
float *l_current_levels = 0;
float *l_ar_at_poss = 0;
float *l_ar_at_spds = 0;
float *l_ar_at_slow_poss = 0;
float *l_ar_at_slow_spds = 0;


static void ON_FLAG(BLOCK_STRUCT *v, int FLAG)
{
  v->g_Discrete_Output |= FLAG;
}

static void RESET_FLAG(BLOCK_STRUCT *v, int FLAG)
{
  v->g_Discrete_Output &= ~FLAG;
}

float GET_A_CL(BLOCK_STRUCT *v)
{

  if((l_ar_at_poss[AR_POS] > 0) && (l_ar_at_spds[AR_SPD] > 0))
  {
    A_CL = l_ar_at_spds[AR_SPD] / l_ar_at_poss[AR_POS];
  }
  else if((l_ar_at_poss[AR_POS] > 0) && (l_ar_at_spds[AR_SPD] <= 0))
  {
    A_CL = 1 / l_ar_at_poss[AR_POS];
  }
  else if((l_ar_at_poss[AR_POS] <= 0) && (l_ar_at_spds[AR_SPD] > 0))
  {
    A_CL = l_ar_at_spds[AR_SPD];
  }
  else if((l_ar_at_poss[AR_POS] <= 0) && (l_ar_at_spds[AR_SPD] <= 0))
  {
    A_CL = 1;
  }

  return A_CL;
}

float GET_A_OP(BLOCK_STRUCT *v)
{

  if((l_ar_at_poss[AT_POS] > 0) && (l_ar_at_spds[AT_SPD] > 0))
  {
    A_OP = l_ar_at_spds[AT_SPD] / l_ar_at_poss[AT_POS];
  }
  else if((l_ar_at_poss[AT_POS] > 0) && (l_ar_at_spds[AT_SPD] <= 0))
  {
    A_OP = 1 / l_ar_at_poss[AT_POS];
  }
  else if((l_ar_at_poss[AT_POS] <= 0) && (l_ar_at_spds[AT_SPD] > 0))
  {
    A_OP = l_ar_at_spds[AT_SPD];
  }
  else if((l_ar_at_poss[AT_POS] <= 0) && (l_ar_at_spds[AT_SPD] <= 0))
  {
    A_OP = 1;
  }

  return A_OP;
}

float GET_A_SLOW_CL(BLOCK_STRUCT *v)
{

  if((l_ar_at_slow_poss[AR_SLOW_START_INDENT] > 0) && ((l_ar_at_slow_spds[AR_SLOW_SPD] - l_spds[SPD_MIN]) > 0))
  {
    A_SLOW_CL = (l_ar_at_slow_spds[AR_SLOW_SPD] - l_spds[SPD_MIN]) / l_ar_at_slow_poss[AR_SLOW_START_INDENT];
  }
  else if((l_ar_at_slow_poss[AR_SLOW_START_INDENT] > 0) && ((l_ar_at_slow_spds[AR_SLOW_SPD] - l_spds[SPD_MIN]) <= 0))
  {
    A_SLOW_CL = 1 / l_ar_at_slow_poss[AR_SLOW_START_INDENT];
  }
  else if((l_ar_at_slow_poss[AR_SLOW_START_INDENT] <= 0) && ((l_ar_at_slow_spds[AR_SLOW_SPD] - l_spds[SPD_MIN]) > 0))
  {
    A_SLOW_CL = (l_ar_at_slow_spds[AR_SLOW_SPD] - l_spds[SPD_MIN]);
  }
  else if((l_ar_at_slow_poss[AR_SLOW_START_INDENT] <= 0) && ((l_ar_at_slow_spds[AR_SLOW_SPD] - l_spds[SPD_MIN]) <= 0))
  {
    A_SLOW_CL = 1;
  }

  return A_SLOW_CL;
}

float GET_A_SLOW_OP(BLOCK_STRUCT *v)
{

  if((l_ar_at_slow_poss[AT_SLOW_END_INDENT] > 0) && ((l_ar_at_slow_spds[AT_SLOW_SPD] - l_spds[SPD_MIN]) > 0))
  {
    A_SLOW_OP = (l_ar_at_slow_spds[AT_SLOW_SPD] - l_spds[SPD_MIN]) / l_ar_at_slow_poss[AT_SLOW_END_INDENT];
  }
  else if((l_ar_at_slow_poss[AT_SLOW_END_INDENT] > 0) && ((l_ar_at_slow_spds[AT_SLOW_SPD] - l_spds[SPD_MIN]) <= 0))
  {
    A_SLOW_OP = 1 / l_ar_at_slow_poss[AT_SLOW_END_INDENT];
  }
  else if((l_ar_at_slow_poss[AT_SLOW_END_INDENT] <= 0) && ((l_ar_at_slow_spds[AT_SLOW_SPD] - l_spds[SPD_MIN]) > 0))
  {
    A_SLOW_OP = (l_ar_at_slow_spds[AT_SLOW_SPD] - l_spds[SPD_MIN]);
  }
  else if((l_ar_at_slow_poss[AT_SLOW_END_INDENT] <= 0) && ((l_ar_at_slow_spds[AT_SLOW_SPD] - l_spds[SPD_MIN]) <= 0))
  {
    A_SLOW_OP = 1;
  }

  return A_SLOW_OP;
}

float MAX_SLOW_SPD(BLOCK_STRUCT *v)
{
  if(l_ar_at_slow_spds[AR_SLOW_SPD] > l_ar_at_slow_spds[AT_SLOW_SPD])
  {
    MAX = l_ar_at_slow_spds[AR_SLOW_SPD];
  }
  else
  {
    MAX = l_ar_at_slow_spds[AT_SLOW_SPD];
  }

  return MAX;
}




static void NORMAL_MODE(BLOCK_STRUCT *v, float Start_POS, float End_Pos, int Direction)
{
  if(End_Pos - Start_POS > v->Position_Limit)
  {
    l_points[SPD1] = l_spds[SPD_MIN];
    l_points[SPD2] = l_ar_at_slow_spds[AR_SLOW_SPD];
    l_points[SPD3] = l_ar_at_slow_spds[AR_SLOW_SPD];
    l_points[SPD4] = l_spds[SPD_MAX];
    l_points[SPD5] = l_spds[SPD_MAX];
    l_points[SPD6] = l_ar_at_slow_spds[AT_SLOW_SPD];
    l_points[SPD7] = l_ar_at_slow_spds[AT_SLOW_SPD];
    l_points[SPD8] = l_spds[SPD_MIN];
    l_points[POS1] = Start_POS;
    l_points[POS2] = l_points[POS1] + l_ar_at_slow_poss[AR_SLOW_START_INDENT];
    l_points[POS3] = l_points[POS2] + l_ar_at_slow_poss[AR_SLOW_END_INDENT];
    l_points[POS8] = End_Pos;
    l_points[POS7] = l_points[POS8] - l_ar_at_slow_poss[AT_SLOW_END_INDENT];
    l_points[POS6] = l_points[POS7] - l_ar_at_slow_poss[AT_SLOW_START_INDENT];
    l_points[POS4] = l_points[POS3] + (l_points[SPD4] - l_points[SPD3]) / GET_A_CL(v);
    l_points[POS5] = l_points[POS6] - (l_points[SPD5] - l_points[SPD6]) / GET_A_OP(v);

    if(l_points[POS4] > l_points[POS5])
    {
      point1_pos = l_points[POS3];
      point1_spd = l_points[SPD3];
      point2_pos = l_points[POS6];
      point2_spd = l_points[SPD6];
      a_point1 = GET_A_CL(v);
      a_point2 = GET_A_OP(v);

      intersection_point_spd = (point2_pos - point1_pos + (point2_spd / a_point2) + (point1_spd / a_point1)) * (a_point2 * a_point1 / (a_point2 + a_point1));
      intersection_point_pos = point1_pos + ((intersection_point_spd - point1_spd) / a_point1);

      l_points[POS4] = intersection_point_pos;
      l_points[SPD4] = intersection_point_spd;
      l_points[POS5] = intersection_point_pos;
      l_points[SPD5] = intersection_point_spd;
    }

    max_slow_spd = MAX_SLOW_SPD(v);
    if((l_points[SPD4] < max_slow_spd) || (l_points[SPD5] < max_slow_spd))
    {

      l_points[SPD4] = max_slow_spd;
      l_points[SPD5] = max_slow_spd;

      if(max_slow_spd == l_ar_at_slow_spds[AR_SLOW_SPD])
      {
        l_points[POS4] = l_points[POS3];
        l_points[POS5] = l_points[POS3];
      }
      else
      {
        l_points[POS4] = l_points[POS6];
        l_points[POS5] = l_points[POS6];
      }
    }

    l_points[POS9] = v->g_Door_Length;
    l_points[SPD9] = l_spds[SPD_MAX];

    v->g_Num_Of_Points = 8;
    v->g_Direction = Direction;
  }
  else
  {
    v->g_Direction = STOP_DIRECTION;
  }
}

static void AFTER_STOPPING_MODE(BLOCK_STRUCT *v, float Start_POS, float End_Pos, int Direction)
{
  if(End_Pos - Start_POS > v->Position_Limit)
  {
    if(Direction == OPEN_DIRECTION)
    {
      l_points[SPD1] = l_spds[SPD_MIN];
      l_points[SPD2] = l_spds[SPD_MIN];
      l_points[SPD3] = l_spds[SPD_MIN];
      l_points[SPD4] = l_spds[SPD_MAX];
      l_points[SPD5] = l_spds[SPD_MAX];
      l_points[SPD6] = l_ar_at_slow_spds[AT_SLOW_SPD];
      l_points[SPD7] = l_ar_at_slow_spds[AT_SLOW_SPD];
      l_points[SPD8] = l_spds[SPD_MIN];
      l_points[POS1] = Start_POS;
      l_points[POS2] = Start_POS;
      l_points[POS3] = Start_POS;
      l_points[POS8] = End_Pos;
      l_points[POS7] = l_points[POS8] - l_ar_at_slow_poss[AT_SLOW_END_INDENT];
      l_points[POS6] = l_points[POS7] - l_ar_at_slow_poss[AT_SLOW_START_INDENT];
      l_points[POS4] = l_points[POS3] + (l_points[SPD4] - l_points[SPD3]) / GET_A_CL(v);
      l_points[POS5] = l_points[POS6] - (l_points[SPD5] - l_points[SPD6]) / GET_A_OP(v);

      if(l_points[POS4] > l_points[POS5])
      {
        point1_pos = l_points[POS3];
        point1_spd = l_points[SPD3];
        point2_pos = l_points[POS6];
        point2_spd = l_points[SPD6];
        a_point1 = GET_A_CL(v);
        a_point2 = GET_A_OP(v);

        intersection_point_spd = (point2_pos - point1_pos + (point2_spd / a_point2) + (point1_spd / a_point1)) * (a_point2 * a_point1 / (a_point2 + a_point1));
        intersection_point_pos = point1_pos + ((intersection_point_spd - point1_spd) / a_point1);
        l_points[POS4] = intersection_point_pos;
        l_points[SPD4] = intersection_point_spd;
        l_points[POS5] = intersection_point_pos;
        l_points[SPD5] = intersection_point_spd;
      }

      max_slow_spd = l_ar_at_slow_spds[AT_SLOW_SPD];
      if((l_points[SPD4] < max_slow_spd) || (l_points[SPD5] < max_slow_spd))
      {
        l_points[SPD4] = max_slow_spd;
        l_points[SPD5] = max_slow_spd;

        a_point = GET_A_CL(v);

        l_points[POS4] = l_points[POS3] + ((l_points[SPD4] - l_points[SPD3]) / a_point);
        l_points[POS5] = l_points[POS3] + ((l_points[SPD5] - l_points[SPD3]) / a_point);
        l_points[POS6] = l_points[POS5];
      }

      if(l_points[POS6] > l_points[POS7])
      {
        point1_pos = l_points[POS3];
        point1_spd = l_points[SPD3];
        point2_pos = l_points[POS8];
        point2_spd = l_points[SPD8];
        a_point1 = GET_A_CL(v);
        a_point2 = GET_A_SLOW_OP(v);

        intersection_point_spd = (point2_pos - point1_pos + (point2_spd / a_point2) + (point1_spd / a_point1)) * (a_point2 * a_point1 / (a_point2 + a_point1));
        intersection_point_pos = point1_pos + ((intersection_point_spd - point1_spd) / a_point1);
        l_points[POS4] = intersection_point_pos;
        l_points[POS5] = intersection_point_pos;
        l_points[POS6] = intersection_point_pos;
        l_points[POS7] = intersection_point_pos;
        if(intersection_point_spd < l_spds[SPD_MEDIUM])
        {
            l_points[SPD4] = l_spds[SPD_MEDIUM];
            l_points[SPD5] = l_spds[SPD_MEDIUM];
            l_points[SPD6] = l_spds[SPD_MEDIUM];
            l_points[SPD7] = l_spds[SPD_MEDIUM];
        }
        else
        {
            l_points[SPD4] = intersection_point_spd;
            l_points[SPD5] = intersection_point_spd;
            l_points[SPD6] = intersection_point_spd;
            l_points[SPD7] = intersection_point_spd;
        }
      }
    }
    else if (Direction == CLOSE_DIRECTION)
    {
      l_points[SPD1] = l_spds[SPD_MIN];
      l_points[SPD2] = l_ar_at_slow_spds[AR_SLOW_SPD];
      l_points[SPD3] = l_ar_at_slow_spds[AR_SLOW_SPD];
      l_points[SPD4] = l_spds[SPD_MAX];
      l_points[SPD5] = l_spds[SPD_MAX];
      l_points[SPD6] = l_spds[SPD_MIN];
      l_points[SPD7] = l_spds[SPD_MIN];
      l_points[SPD8] = l_spds[SPD_MIN];
      l_points[POS1] = Start_POS;
      l_points[POS2] = l_points[POS1] + l_ar_at_slow_poss[AR_SLOW_START_INDENT];
      l_points[POS3] = l_points[POS2] + l_ar_at_slow_poss[AR_SLOW_END_INDENT];
      l_points[POS8] = End_Pos;
      l_points[POS7] = End_Pos;
      l_points[POS6] = End_Pos;
      l_points[POS4] = l_points[POS3] + (l_points[SPD4] - l_points[SPD3]) / GET_A_CL(v);
      l_points[POS5] = l_points[POS6] - (l_points[SPD5] - l_points[SPD6]) / GET_A_OP(v);

      if(l_points[POS4] > l_points[POS5])
      {
        point1_pos = l_points[POS3];
        point1_spd = l_points[SPD3];
        point2_pos = l_points[POS6];
        point2_spd = l_points[SPD6];
        a_point1 = GET_A_CL(v);
        a_point2 = GET_A_OP(v);

        intersection_point_spd = (point2_pos - point1_pos + (point2_spd / a_point2) + (point1_spd / a_point1)) * (a_point2 * a_point1 / (a_point2 + a_point1));
        intersection_point_pos = point1_pos + ((intersection_point_spd - point1_spd) / a_point1);
        l_points[POS4] = intersection_point_pos;
        l_points[SPD4] = intersection_point_spd;
        l_points[POS5] = intersection_point_pos;
        l_points[SPD5] = intersection_point_spd;
      }

      max_slow_spd = l_ar_at_slow_spds[AR_SLOW_SPD];
      if((l_points[SPD4] < max_slow_spd) || (l_points[SPD5] < max_slow_spd))
      {
        l_points[SPD4] = max_slow_spd;
        l_points[SPD5] = max_slow_spd;

        a_point = GET_A_OP(v);

        l_points[POS4] = l_points[POS6] - ((l_points[SPD4] - l_points[SPD6]) / a_point);
        l_points[POS5] = l_points[POS6] - ((l_points[SPD5] - l_points[SPD6]) / a_point);
        l_points[POS3] = l_points[POS5];
      }

      if(l_points[POS2] > l_points[POS3])
      {
        point1_pos = l_points[POS1];
        point1_spd = l_points[SPD1];
        point2_pos = l_points[POS6];
        point2_spd = l_points[SPD6];
        a_point1 = GET_A_SLOW_CL(v);
        a_point2 = GET_A_OP(v);

        intersection_point_spd = (point2_pos - point1_pos + (point2_spd / a_point2) + (point1_spd / a_point1)) * (a_point2 * a_point1 / (a_point2 + a_point1));
        intersection_point_pos = point1_pos + ((intersection_point_spd - point1_spd) / a_point1);
        l_points[POS2] = intersection_point_pos;
        l_points[POS3] = intersection_point_pos;
        l_points[POS4] = intersection_point_pos;
        l_points[POS5] = intersection_point_pos;
        if(intersection_point_spd < l_spds[SPD_MEDIUM])
        {
            l_points[SPD2] = l_spds[SPD_MEDIUM];
            l_points[SPD3] = l_spds[SPD_MEDIUM];
            l_points[SPD4] = l_spds[SPD_MEDIUM];
            l_points[SPD5] = l_spds[SPD_MEDIUM];
        }
        else
        {
            l_points[SPD2] = intersection_point_spd;
            l_points[SPD3] = intersection_point_spd;
            l_points[SPD4] = intersection_point_spd;
            l_points[SPD5] = intersection_point_spd;
        }
      }
    }

    l_points[POS9] = v->g_Door_Length;
    l_points[SPD9] = l_spds[SPD_MAX];

    v->g_Num_Of_Points = 8;
    v->g_Direction = Direction;
  }
  else
  {
    v->g_Direction = STOP_DIRECTION;
  }
}

static void OPEN_CLOSE_MOVE(BLOCK_STRUCT *v, float Start_POS, float End_Pos, int Direction)
{

  if(v->Points_Changing_Enable)
  {
    if(
        ((v->g_State == OPEN_STATE) && (v->g_Sub_State == OPENING))
      ||
        ((v->g_State == CLOSE_STATE) && (v->g_Sub_State == CLOSING))
    )
    {
      NORMAL_MODE(v, Start_POS, End_Pos, Direction);
    }
    else
    {
      AFTER_STOPPING_MODE(v, Start_POS, End_Pos, Direction);
    }

    if(*v->g_Discrete_Input & COMMAND_BIT)
    {
      l_poss[STOP_INDENT_POS_END] = End_Pos;
    }
    else
    {
      l_poss[STOP_INDENT_POS_END] = Start_POS;
    }
  }

  v->Points_Changing_Enable = 0;
}

static void STOPPING_MOVE(BLOCK_STRUCT *v, int Start_POS, int Start_SPD, int STOPPING_AT_POS, int STOPPING_AT_SPD, int Direction)
{

  if(v->Points_Changing_Enable)
  {

    v->STOP_AT = ((Start_SPD - l_spds[SPD_MIN]) * STOPPING_AT_POS) / STOPPING_AT_SPD;

    if(Direction == OPEN_DIRECTION)
    {

        if((Start_POS + v->STOP_AT) > (v->g_Door_Length - l_indents[Open_Indent] ))
        {
        l_poss[STOP_POS_END] = v->g_Door_Length - l_indents[Open_Indent] ;
        }
        else
        {
        l_poss[STOP_POS_END] = Start_POS + v->STOP_AT;
        }

        l_points[POS1] = Start_POS;
        l_points[SPD1] = Start_SPD;
        l_points[POS2] = l_poss[STOP_POS_END];
        l_points[SPD2] = l_spds[SPD_MIN];

        l_points[POS3] = 0;
        l_points[SPD3] = 0;
        l_points[POS4] = 0;
        l_points[SPD4] = 0;
        l_points[POS5] = 0;
        l_points[SPD5] = 0;
        l_points[POS6] = 0;
        l_points[SPD6] = 0;
        l_points[POS7] = 0;
        l_points[SPD7] = 0;
        l_points[POS8] = 0;
        l_points[SPD8] = 0;

        l_points[POS9] = v->g_Door_Length;
        l_points[SPD9] = l_spds[SPD_MAX];
        v->g_Num_Of_Points = 2;
        v->g_Direction = Direction;
    }

    if(Direction == CLOSE_DIRECTION)
    {

      if((Start_POS - v->STOP_AT) < (l_indents[Close_Indent] ))
      {
        l_poss[STOP_POS_END] = l_indents[Close_Indent] ;
      }
      else
      {
        l_poss[STOP_POS_END] = Start_POS - v->STOP_AT;
      }

      l_points[POS1] = l_poss[STOP_POS_END];
      l_points[SPD1] = l_spds[SPD_MIN];
      l_points[POS2] = Start_POS;
      l_points[SPD2] = Start_SPD;

      l_points[POS3] = 0;
      l_points[SPD3] = 0;
      l_points[POS4] = 0;
      l_points[SPD4] = 0;
      l_points[POS5] = 0;
      l_points[SPD5] = 0;
      l_points[POS6] = 0;
      l_points[SPD6] = 0;
      l_points[POS7] = 0;
      l_points[SPD7] = 0;
      l_points[POS8] = 0;
      l_points[SPD8] = 0;

      l_points[POS9] = v->g_Door_Length;
      l_points[SPD9] = l_spds[SPD_MAX];
      v->g_Num_Of_Points = 2;
      v->g_Direction = Direction;
    }
  }

  if(*v->g_Speed_Feed <= l_spds[SPD_MIN])
  {
    l_poss[STOP_POS_END] = *v->g_Position_Feed;
  }

  v->Points_Changing_Enable = 0;
}

static void INDENT_MOVE(BLOCK_STRUCT *v, int Indent, int Direction)
{

  if(v->Points_Changing_Enable)
  {
    if(Direction == OPEN_DIRECTION)
    {
      if((l_poss[STOP_POS_END] + Indent) > (v->g_Door_Length - l_indents[Open_Indent] ))
      {
        l_poss[STOP_INDENT_POS_END] = v->g_Door_Length - l_indents[Open_Indent] ;
      }
      else
      {
        l_poss[STOP_INDENT_POS_END] = l_poss[STOP_POS_END] + Indent;
      }

      //POS0
      l_points[POS1] = l_poss[STOP_POS_END];
      l_points[SPD1] = l_spds[SPD_MIN];
      //POS2
      l_points[POS3] = l_poss[STOP_INDENT_POS_END];
      l_points[SPD3] = l_spds[SPD_MIN];

    }

    if(Direction == CLOSE_DIRECTION)
    {
      if((l_poss[STOP_POS_END] - Indent) < (l_indents[Close_Indent]))
      {
        l_poss[STOP_INDENT_POS_END] = l_indents[Close_Indent];
      }
      else
      {
        l_poss[STOP_INDENT_POS_END] = l_poss[STOP_POS_END] - Indent;
      }

      //POS0
      l_points[POS1] = l_poss[STOP_INDENT_POS_END];
      l_points[SPD1] = l_spds[SPD_MIN];
      //POS2
      l_points[POS3] = l_poss[STOP_POS_END];
      l_points[SPD3] = l_spds[SPD_MIN];
    }

  //POS1

  l_points[POS2] = (l_points[POS1] + l_points[POS3]) / 2;
  l_points[SPD2] = ((l_points[POS2] - l_points[POS1]) * l_ar_at_spds[AR_AT_INDENT_SPD]) / l_ar_at_poss[AR_AT_INDENT_POS];

  if(l_points[SPD2] > l_spds[SPD_MAX])
  {
    l_points[SPD2] = l_spds[SPD_MAX];
  }
  else if(l_points[SPD2] < l_spds[SPD_MEDIUM])
  {
    l_points[SPD2] = l_spds[SPD_MEDIUM];
  }

  l_points[POS4] = 0;
  l_points[SPD4] = 0;
  l_points[POS5] = 0;
  l_points[SPD5] = 0;
  l_points[POS6] = 0;
  l_points[SPD6] = 0;
  l_points[POS7] = 0;
  l_points[SPD7] = 0;
  l_points[POS8] = 0;
  l_points[SPD8] = 0;

  l_points[POS9] = v->g_Door_Length;
  l_points[SPD9] = l_spds[SPD_MAX];
  v->g_Num_Of_Points = 3;
  v->g_Direction = Direction;
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

    l_timers[Timer_VKO_VKZ_Another_Block_On] = 1; //Включение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.

    if(l_timers[Timer_VKO_VKZ_Another_Block] > l_delays[VKO_VKZ_Another_Block_Change_Delay])
    {
      l_timers[Timer_VKO_VKZ_Another_Block_On] = 0; //Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.

      //////VKZ_Counter//////
      if((v->g_Discrete_Input_Prev & VKZ_ANOTHER_BLOCK_BIT) < (*v->g_Discrete_Input & VKZ_ANOTHER_BLOCK_BIT))//Если сигнал VKZ от другого блока изменил состояние из 0 в 1.
      {
        v->g_VKZ_Another_Block_Counter++; //Увеличение счётчика срабатывания сигнала VKZ от другого блока на 1.
      }

      //////VKO_Counter//////
      if((v->g_Discrete_Input_Prev & VKO_ANOTHER_BLOCK_BIT) < (*v->g_Discrete_Input & VKO_ANOTHER_BLOCK_BIT))//Если сигнал VKO изменил состояние из 0 в 1.
      {
        v->g_VKO_Another_Block_Counter++; //Увеличение счётчика срабатывания сигнала VKO от другого блока на 1.
      }

      v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.

    }

  }
  else
  {
    l_timers[Timer_VKO_VKZ_Another_Block_On] = 0; //Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.
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
    l_timers[Timer_VKO_VKZ_Another_Block_On] = 1; //Включение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.

    if(l_timers[Timer_VKO_VKZ_Another_Block] > l_delays[VKO_VKZ_Another_Block_Change_Delay])
    {
      l_timers[Timer_VKO_VKZ_Another_Block_On] = 0; //Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.
      v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.
    }
  }
  else
  {
    l_timers[Timer_VKO_VKZ_Another_Block_On] = 0; //Отключение таймера на исключение дребезга в контактах сигналов VKO или VKZ от другого блока.
  }
}

static void VKO_VKZ_CHECK(BLOCK_STRUCT *v)
{

  if(v->g_Discrete_Input_Prev & COMMAND_BIT)
  {
    if(
        (*v->g_Position_Feed >= (l_indents[Close_Indent] + l_indents[VKZ_AREA_Indent]))
      &&
        (v->g_Discrete_Output & VKZ_BIT_OUT)
    )
    {
      l_timers[Timer_VKZ_On] = 1; //Включение таймера тока.

      if(l_timers[Timer_VKZ] > l_delays[VKZ_On_Delay])
      {
        l_timers[Timer_VKZ_On] = 0;
        RESET_FLAG(v, VKZ_BIT_OUT);
      }

    }
    else
    {
      l_timers[Timer_VKZ_On] = 0;
    }

    if(
        (*v->g_Position_Feed >= (v->g_Door_Length - l_indents[Open_Indent] - v->Position_Limit))
      &&
        (*v->g_Position_Feed <= (v->g_Door_Length - l_indents[Open_Indent] + v->Position_Limit))
      &&
        (!(v->g_Discrete_Output & VKO_BIT_OUT))
    )
    {
      l_timers[Timer_VKO_On] = 1; //Включение таймера тока.

      if(l_timers[Timer_VKO] > l_delays[VKO_On_Delay])
      {
        l_timers[Timer_VKO_On] = 0;
        ON_FLAG(v, VKO_BIT_OUT);
      }
    }
    else if(
        (*v->g_Position_Feed <= ((v->g_Door_Length - l_indents[Open_Indent]) - l_indents[VKO_AREA_Indent]))
      &&
        (v->g_Discrete_Output & VKO_BIT_OUT)
    )
    {
      l_timers[Timer_VKO_On] = 1; //Включение таймера тока.
      if(l_timers[Timer_VKO] > l_delays[VKO_On_Delay])
      {
        l_timers[Timer_VKO_On] = 0;
        RESET_FLAG(v, VKO_BIT_OUT);
      }
    }
    else
    {
      l_timers[Timer_VKO_On] = 0;
    }
  }
  else
  {
    if(
        (*v->g_Position_Feed <= ((v->g_Door_Length - l_indents[Open_Indent]) - l_indents[VKO_AREA_Indent]))
      &&
        (v->g_Discrete_Output & VKO_BIT_OUT)
    )
    {
      l_timers[Timer_VKO_On] = 1; //Включение таймера тока.
      if(l_timers[Timer_VKO] > l_delays[VKO_On_Delay])
      {
        l_timers[Timer_VKO_On] = 0;
        RESET_FLAG(v, VKO_BIT_OUT);
      }
    }
    else
    {
      l_timers[Timer_VKO_On] = 0;
    }

    if(
        (*v->g_Position_Feed >= (l_indents[Close_Indent] - v->Position_Limit))
      &&
        (*v->g_Position_Feed <= (l_indents[Close_Indent] + v->Position_Limit))
      &&
        (!(v->g_Discrete_Output & VKZ_BIT_OUT))
    )
    {
      l_timers[Timer_VKZ_On] = 1; //Включение таймера тока.
      if(l_timers[Timer_VKZ] > l_delays[VKZ_On_Delay])
      {
        l_timers[Timer_VKZ_On] = 0;
        ON_FLAG(v, VKZ_BIT_OUT);
      }
    }
    else if(
        (*v->g_Position_Feed >= (l_indents[Close_Indent] + l_indents[VKZ_AREA_Indent]))
      &&
        (v->g_Discrete_Output & VKZ_BIT_OUT)
    )
    {
      l_timers[Timer_VKZ_On] = 1; //Включение таймера тока.

      if(l_timers[Timer_VKZ] > l_delays[VKZ_On_Delay])
      {
        l_timers[Timer_VKZ_On] = 0;
        RESET_FLAG(v, VKZ_BIT_OUT);
      }
    }
    else
    {
      l_timers[Timer_VKZ_On] = 0;
    }
  }
}

static void RVM_CHECK(BLOCK_STRUCT *v)
{
  if(v->g_State == OPEN_STATE)
  {
    if(
        (*v->g_Current_Feed > l_current_levels[Current_Open_RVM_Level]) //Условие, что ток возрос выше уставки RVM.
      &&
        (*v->g_Speed_Feed < l_spds[SPD_RVM_Level])
      )
    {
      l_timers[Timer_Current_On] = 1; //Включение таймера тока.

      if(l_timers[Timer_Current] > l_delays[Current_RVM_Delay])
      {
        l_timers[Timer_Current_On] = 0;
        ON_FLAG(v, RVM_BIT_OUT);
        GO_TO(v, OPEN_STATE, RVM_IN_OPENING);
      }
    }
    else
    {
      l_timers[Timer_Current_On] = 0; //Выключение таймера тока.
    }
  }

  if(v->g_State == CLOSE_STATE)
  {
    if(
        (*v->g_Current_Feed > l_current_levels[Current_Close_RVM_Level]) //Условие, что ток возрос выше уставки RVM.
      &&
        (*v->g_Speed_Feed < l_spds[SPD_RVM_Level])
      )
    {
      l_timers[Timer_Current_On] = 1; //Включение таймера тока.

      if(l_timers[Timer_Current] > l_delays[Current_RVM_Delay])
      {
        l_timers[Timer_Current_On] = 0;
        ON_FLAG(v, RVM_BIT_OUT);
        GO_TO(v, CLOSE_STATE, RVM_IN_CLOSING);
      }
    }
    else
    {
      l_timers[Timer_Current_On] = 0; //Выключение таймера тока.
    }
  }
}

static void STOP_CHECK(BLOCK_STRUCT *v)
{
  if(
    ((*v->g_Discrete_Input & COMMAND_BIT) != (v->g_Discrete_Input_Prev & COMMAND_BIT))
  )//Условие, что произошла смена команды.
  {
    l_timers[Timer_Command_On] = 1; //Включение таймера смены команды.

    if(l_timers[Timer_Command] > l_delays[Command_Change_Delay])//Условие, что прошло время для изменения команды.
    {
      l_timers[Timer_Command_On] = 0;
      if(v->g_State == OPEN_STATE)
      {
        ON_FLAG(v, STOP_BIT_OUT);
        GO_TO(v, OPEN_STATE, STOP_IN_OPENING);
        v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.
      }
      if(v->g_State == CLOSE_STATE)
      {
        ON_FLAG(v, STOP_BIT_OUT);
        GO_TO(v, CLOSE_STATE, STOP_IN_CLOSING);
        v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.
      }
    }
  }
  else
  {
    l_timers[Timer_Command_On] = 0;
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
        (*v->g_Current_Feed > l_current_levels[Current_VKZ_Block_Level])
      &&
        ((*v->g_Position_Feed - l_indents[Close_Indent]) > l_indents[VKZ_Block_Indent])
    )
    {
      l_timers[Timer_Current_On] = 1;

      if(l_timers[Timer_Current] > l_delays[Current_VKZ_Block_Delay])
      {
        l_timers[Timer_Current_On] = 0;
        ON_FLAG(v, BLOCK_BIT_OUT);
      }
    }
    else
    {
      l_timers[Timer_Current] = 0;
    }
  }

  if(
      (v->g_Discrete_Output & VKZ_BIT_OUT)
    &&
      (v->g_Discrete_Output & BLOCK_BIT_OUT)
  )
  {
    if(
        (*v->g_Current_Feed < l_current_levels[Current_VKZ_Block_Level])
      &&
        ((*v->g_Position_Feed - l_indents[Close_Indent]) < l_indents[VKZ_Block_Indent])
    )
    {
      l_timers[Timer_Current_On] = 1;

      if(l_timers[Timer_Current] > l_delays[Current_VKZ_Block_Delay])
      {
        l_timers[Timer_Current_On] = 0;
        RESET_FLAG(v, BLOCK_BIT_OUT);
      }
    }
    else
    {
      l_timers[Timer_Current] = 0;
    }
  }

  if((*v->g_Discrete_Input & BLOCK_BIT) != (v->g_Discrete_Input_Prev & BLOCK_BIT))
  {
    l_timers[Timer_Block_On] = 1;

    if(l_timers[Timer_Block] > l_delays[Block_Change_Delay])
    {
      l_timers[Timer_Block_On] = 0;

      v->g_Discrete_Input_Prev = *v->g_Discrete_Input;

      if(v->g_Discrete_Input_Prev & COMMAND_BIT)
      {
        GO_TO(v, OPEN_STATE, OPENING);
      }
    }
  }
  else
  {
    l_timers[Timer_Block_On] = 0;
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
    l_timers[Timer_Foto_On] = 1; //Включение таймера смены команды.

    if(l_timers[Timer_Foto] > l_delays[Foto_Change_Delay])//Условие, что прошло время для изменения команды.
    {
      l_timers[Timer_Foto_On] = 0;

      if(*v->g_Discrete_Input & FOTO_BIT)
      {
        ON_FLAG(v, FOTO_BIT_OUT);
      }

      if(v->g_State == CLOSE_STATE)
      {
        GO_TO(v, CLOSE_STATE, FOTO_IN_CLOSING);
      }


      v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.
    }
  }
  else
  {
    l_timers[Timer_Foto_On] = 0;
  }
}
/*
static void BLOCK_ALARM_FOTO_CHECK(BLOCK_STRUCT *v)
{

}
*/

static void POS_GE_AND_SE_OR_Min_SPD(BLOCK_STRUCT *v, int POS, int State, int Sub_State)
{
  if(((*v->g_Position_Feed >= (POS - v->Position_Limit)) && (*v->g_Position_Feed <= (POS + v->Position_Limit))) || (*v->g_Speed_Feed <= l_spds[SPD_MIN]))//???????????????????????
  {
    l_timers[Timer_Position_On] = 1;

    if(l_timers[Timer_Position] > l_delays[Position_Stop_Delay])
    {
      l_timers[Timer_Position_On] = 0;
      GO_TO(v, State, Sub_State);
    }
  }
  else
  {
    l_timers[Timer_Position_On] = 0;
  }
}

static void POS_GE_AND_SE(BLOCK_STRUCT *v, int POS, int State, int Sub_State)
{
  if(((*v->g_Position_Feed >= (POS - v->Position_Limit)) && (*v->g_Position_Feed <= (POS + v->Position_Limit))))
  {
    l_timers[Timer_Position_On] = 1;

    if(l_timers[Timer_Position] > l_delays[Position_Stop_Delay])
    {
      l_timers[Timer_Position_On] = 0;
      GO_TO(v, State, Sub_State);
    }
  }
  else
  {
    l_timers[Timer_Position_On] = 0;
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
  if(l_timers[Timer_VKO_VKZ_Another_Block_On])
  {
    l_timers[Timer_VKO_VKZ_Another_Block] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_VKO_VKZ_Another_Block] = 0;
  }


  if(l_timers[Timer_VKO_On])
  {
    l_timers[Timer_VKO] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_VKO] = 0;
  }


  if(l_timers[Timer_VKZ_On])
  {
    l_timers[Timer_VKZ] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_VKZ] = 0;
  }



  if(l_timers[Timer_Current_On])
  {
    l_timers[Timer_Current] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_Current] = 0;
  }



  if(l_timers[Timer_Position_On])
  {
    l_timers[Timer_Position] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_Position] = 0;
  }



  if(l_timers[Timer_Command_On])
  {
    l_timers[Timer_Command] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_Command] = 0;
  }



  if(l_timers[Timer_Block_On])
  {
    l_timers[Timer_Block] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_Block] = 0;
  }



  if(l_timers[Timer_Alarm_On])
  {
    l_timers[Timer_Alarm] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_Alarm] = 0;
  }



  if(l_timers[Timer_Foto_On])
  {
    l_timers[Timer_Foto] += v->Timer_Discrete;
  }
  else
  {
    l_timers[Timer_Foto] = 0;
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
    l_timers[Timer_Command_On] = 1; //Включение таймера смены команды.

    if(l_timers[Timer_Command] > l_delays[Command_Change_Delay])//Условие, что прошло время для изменения команды.
    {
      l_timers[Timer_Command_On] = 0; //Выключение таймера смены команды.

      v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.

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
    if((l_timers[Timer_Command] != 0))//Условие что смена была, но на время короче чем время для изменения команды.
    {
      l_timers[Timer_Command_On] = 0;

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
      l_timers[Timer_Command_On] = 0;
    }
    else
    {
      l_timers[Timer_Command_On] = 1;
    }

    if (l_timers[Timer_Command] >= l_delays[Command_Change_Delay])
    {
      v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.
    }
  }
  else
  {
    if (!(v->g_Discrete_Input_Prev & COMMAND_BIT))
    {
      l_timers[Timer_Command_On] = 0;
    }
    else
    {
      l_timers[Timer_Command_On] = 1;
    }

    if (l_timers[Timer_Command] >= l_delays[Command_Change_Delay])
    {
      v->g_Discrete_Input_Prev = *v->g_Discrete_Input; //Сохранение состояния.
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

  if(v->Command_Type & IMPULSE_OR_POSITIVE_TYPE_OF_COMMANDS)
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
    case FIRST_CLOSING: //Первое закрытие.

      RESET_FLAG(v, INIT_BIT_OUT);
      if(*v->g_Current_Feed > l_current_levels[Current_Close_Stop_Level]) //Условие, что ток возрос выше уставки нахождения упора.
      {
        l_timers[Timer_Current_On] = 1; //Включение таймера тока.

        if(l_timers[Timer_Current] > l_delays[Position_Stop_Delay])
        {
          l_timers[Timer_Current_On] = 0;
          GO_TO(v, INIT_STATE, VKZ_POS_CHECK);
        }

      }
      else
      {
        l_timers[Timer_Current_On] = 0; //Выключение таймера тока.
      }

    break;

    case VKZ_POS_CHECK: //Запоминание позиции в состоянии Закрыто.

      GO_TO(v, INIT_STATE, POSITION_RESET_ON);

    break;

    case POSITION_RESET_ON: //Подача сигнала на сброс позиции.

      ON_FLAG(v, RESET_POSITION_BIT_OUT);
      GO_TO(v, INIT_STATE, POSITION_RESET_OFF);

    break;

    case POSITION_RESET_OFF: //Сброс сигнала на сброс позиции.

      RESET_FLAG(v, RESET_POSITION_BIT_OUT);
      GO_TO(v, INIT_STATE, FIRST_CLOSED);

    break;

    case FIRST_CLOSED: // Первое закрытие.


      ON_FLAG(v, VKZ_BIT_OUT);

      l_timers[Timer_VKZ_On]  = 1;

      if(l_timers[Timer_VKZ] > l_delays[VKZ_On_Delay])
      {
      l_timers[Timer_VKZ_On]=0;

      if((*v->g_DIP & ALARM_TYPE_BIT) && (v->Command_Type & INIT_ANOTHER_BLOCK_BIT_CHECKING_NEED))
      {
        if(*v->g_Discrete_Input & INIT_ANOTHER_BLOCK_BIT) // внутренняя дверь дожидается инициализации внешней двери
        {
          GO_TO(v, INIT_STATE, FIRST_OPENING);
        }
      }
      else // Внешняя дверь дожидается закрытия внутренней
      {
        if(*v->g_Discrete_Input & VKZ_ANOTHER_BLOCK_BIT)
        {
          GO_TO(v, INIT_STATE, FIRST_OPENING);
        }
      }
      }

    break;

    case FIRST_OPENING: //Первое открытие.


      RESET_FLAG(v, VKZ_BIT_OUT);
      if(*v->g_Current_Feed > l_current_levels[Current_Open_Stop_Level]) //Условие, что ток возрос выше уставки нахождения упора.
      {
        l_timers[Timer_Current_On] = 1; //Включение таймера тока.

        if(l_timers[Timer_Current] > l_delays[Position_Stop_Delay])
        {
          l_timers[Timer_Current_On] = 0;
          GO_TO(v, INIT_STATE, VKO_POS_CHECK);
        }

      }
      else
      {
        l_timers[Timer_Current_On] = 0; //Выключение таймера тока.
      }

    break;

    case VKO_POS_CHECK: //Запоминание позиции в состоянии Открыто.

      GO_TO(v, INIT_STATE, DOOR_LENGTH_CHECK);

    break;

    case DOOR_LENGTH_CHECK: //Определение длины проёма.

      GO_TO(v, INIT_STATE, STOPPING_TO_VKO_POS);

    break;

    case STOPPING_TO_VKO_POS:

      POS_GE_AND_SE(v, v->g_Door_Length - l_indents[Open_Indent], INIT_STATE, FIRST_OPENED);

    break;

    case FIRST_OPENED: //Первое открытое состояние.

      ON_FLAG(v, VKO_BIT_OUT);

      l_timers[Timer_VKO_On]=1;

      if(l_timers[Timer_VKO] > l_delays[VKO_On_Delay])
      {
        l_timers[Timer_VKO_On]=0;
        GO_TO(v, INIT_STATE, SECOND_CLOSING);
      }
    break;


    case SECOND_CLOSING: //Второе закрытие.

      RESET_FLAG(v, VKO_BIT_OUT);

      POS_GE_AND_SE(v, l_indents[Close_Indent], INIT_STATE, SECOND_CLOSED);

    break;

    case SECOND_CLOSED: //?????? ???????? ?????????.

      ON_FLAG(v, VKZ_BIT_OUT);

      l_timers[Timer_VKZ_On]=1;

      if(l_timers[Timer_VKZ] > l_delays[VKZ_On_Delay])
      {
        l_timers[Timer_VKZ_On]=0;
        v->g_VKO_Another_Block_Counter = 0;
        v->g_VKZ_Another_Block_Counter = 0;
        v->g_Discrete_Input_Prev = *v->g_Discrete_Input;
        GO_TO(v, WAIT_STATE, WAIT_STATE);
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

      l_points[POS1] = -2000;
      l_points[SPD1] = l_spds[SPD_SYNCH];
      l_points[POS9] = 2000;
      l_points[SPD9] = l_spds[SPD_SYNCH];
      v->g_Num_Of_Points = 1;
      v->g_Direction = CLOSE_DIRECTION;

    break;


    case VKZ_POS_CHECK:

      v->g_VKZ_Pos = *v->g_Position_Feed_Abs;

    break;

    case FIRST_CLOSED:

      l_points[POS1] = l_indents[Close_Indent];

      v->g_Direction = STOP_DIRECTION;

    break;

    case FIRST_OPENING:

      l_points[POS1] = 2000;
      l_points[SPD1] = l_spds[SPD_SYNCH];
      l_points[POS9] = 2000;
      l_points[SPD9] = l_spds[SPD_SYNCH];
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

      v->AR = ((l_spds[SPD_MAX] - l_spds[SPD_MIN]) * 100) / 100; //длина участка разгона.
      v->AT = ((l_spds[SPD_MAX] - l_spds[SPD_MIN]) * 100) / 100; //длина участка торможения.

      if(v->Points_Changing_Enable)
      {

        //POS0
        l_points[POS1] = v->g_Door_Length - l_indents[Open_Indent];
        l_points[SPD1] = l_spds[SPD_MIN];
        //POS2
        l_points[POS3] = v->g_Door_Length;
        l_points[SPD3] = l_spds[SPD_SYNCH];
        //POS1

        if(
            (l_points[POS1] + (((l_points[POS3] - l_points[POS1]) * v->AR) / (v->AR + v->AT)))
          >
            v->g_Door_Length
        )
        {
          l_points[POS2] = v->g_Door_Length;
        }
        else
        {
          l_points[POS2] = l_points[POS1] + (((l_points[POS3] - l_points[POS1]) * v->AR) / (v->AR + v->AT));
        }

        if(
            (l_points[POS1] + (((l_points[POS3] - l_points[POS1]) * v->AR) / (v->AR + v->AT)))
          <
            (v->g_Door_Length - l_indents[Open_Indent])
        )
        {
          l_points[POS2] = v->g_Door_Length - l_indents[Open_Indent];
        }
        else
        {
          l_points[POS2] = l_points[POS1] + (((l_points[POS3] - l_points[POS1]) * v->AR) / (v->AR + v->AT));
        }


        if(
            (((l_points[POS3] - l_points[POS1]) * l_spds[SPD_MAX]) / (v->AR + v->AT))
          >
            l_spds[SPD_MAX]
        )
        {
          l_points[SPD2] = l_spds[SPD_MAX];
        }
        else
        {
          l_points[SPD2] = ((l_points[POS3] - l_points[POS1]) * l_spds[SPD_MAX]) / (v->AR + v->AT);
        }

        if(
            (((l_points[POS3] - l_points[POS1]) * l_spds[SPD_MAX]) / (v->AR + v->AT))
          <
            l_spds[SPD_MIN]
        )
        {
          l_points[SPD2] = l_spds[SPD_MIN];
        }
        else
        {
          l_points[SPD2] = ((l_points[POS3] - l_points[POS1]) * l_spds[SPD_MAX]) / (v->AR + v->AT);
        }



        l_points[POS4] = 0;
        l_points[SPD4] = 0;

        l_points[POS9] = v->g_Door_Length;
        l_points[SPD9] = l_spds[SPD_MAX];
        v->g_Num_Of_Points = 3;


        v->g_Direction = CLOSE_DIRECTION;
      }

      v->Points_Changing_Enable = 0;

    break;

    case FIRST_OPENED: //Первое открытое состояние.

      v->g_Direction = STOP_DIRECTION;


    break;


    case SECOND_CLOSING:

      OPEN_CLOSE_MOVE(v, l_indents[Close_Indent], *v->g_Position_Feed, CLOSE_DIRECTION);

    break;

    case SECOND_CLOSED: //Второе закрытое состояние.

      v->g_Direction = STOP_DIRECTION;

    break;
  }
}



static void Mooving_Open(BLOCK_STRUCT *v)
{

  VKO_VKZ_CHECK(v);

  switch(v->g_Sub_State)
  {
    case OPENING: //Открытие.

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;


    case RVM_IN_OPENING:

      GO_TO(v, RVM_STATE, OPENING_RVM);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;

    case OPENING_AFTER_RVM:

      RESET_FLAG(v, RVM_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;

    case STOP_IN_OPENING:

      GO_TO(v, STOP_STATE, OPENING_STOP);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;

    case OPENING_AFTER_STOP:

      RESET_FLAG(v, STOP_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKO_BIT_OUT);

    break;


    case BLOCK_IN_OPENING:

      GO_TO(v, BLOCK_STATE, OPENING_BLOCK);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

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

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

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
    case OPENING: //Открытие.

      OPEN_CLOSE_MOVE(v, *v->g_Position_Feed, v->g_Door_Length - l_indents[Open_Indent], OPEN_DIRECTION);

    break;

    case RVM_IN_OPENING:

      l_poss[RVM_POS] = *v->g_Position_Feed;
      l_spds[RVM_SPD] = *v->g_Speed_Feed;

    break;

    case OPENING_AFTER_RVM:

      OPEN_CLOSE_MOVE(v, l_poss[STOP_INDENT_POS_END], v->g_Door_Length - l_indents[Open_Indent], OPEN_DIRECTION);

    break;

    case STOP_IN_OPENING:

      l_poss[STOP_POS] = *v->g_Position_Reff;
      l_spds[STOP_SPD] = *v->g_Speed_Reff;

    break;

    case OPENING_AFTER_STOP:

      OPEN_CLOSE_MOVE(v, l_poss[STOP_INDENT_POS_END], v->g_Door_Length - l_indents[Open_Indent], OPEN_DIRECTION);

    break;


    case BLOCK_IN_OPENING:

      l_poss[BLOCK_POS] = *v->g_Position_Feed;
      l_spds[BLOCK_SPD] = *v->g_Speed_Feed;

    break;


    case OPENING_AFTER_BLOCK:

      OPEN_CLOSE_MOVE(v, l_poss[STOP_INDENT_POS_END], v->g_Door_Length - l_indents[Open_Indent], OPEN_DIRECTION);

    break;

    case ALARM_WAITING_OF_OPENING:


    break;


    case ALARM_STOP_AND_CLOSING:

      l_poss[ALARM_POS] = *v->g_Position_Feed;
      l_spds[ALARM_SPD] = *v->g_Speed_Feed;

    break;


    case FOTO_IN_OPENING:

      l_poss[FOTO_POS] = *v->g_Position_Feed;
      l_spds[FOTO_SPD] = *v->g_Speed_Feed;

    break;


    case OPENING_AFTER_FOTO:

      OPEN_CLOSE_MOVE(v, l_poss[STOP_INDENT_POS_END], v->g_Door_Length - l_indents[Open_Indent], OPEN_DIRECTION);

    break;
  }
}



static void Mooving_Close(BLOCK_STRUCT *v)
{
  VKO_VKZ_CHECK(v);

  switch(v->g_Sub_State)
  {

    case CLOSING: //Открытие.

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;


    case RVM_IN_CLOSING:

      GO_TO(v, RVM_STATE, CLOSING_RVM);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;

    case CLOSING_AFTER_RVM:

      RESET_FLAG(v, RVM_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;

    case STOP_IN_CLOSING:

      GO_TO(v, STOP_STATE, CLOSING_STOP);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;

    case CLOSING_AFTER_STOP:

      RESET_FLAG(v, STOP_BIT_OUT);

      OPENING_CLOSING_ALGORITHM(v, WAIT_STATE, WAIT_STATE, VKZ_BIT_OUT);

    break;


    case BLOCK_IN_CLOSING:

      GO_TO(v, BLOCK_STATE, CLOSING_BLOCK);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

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

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

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
    case CLOSING: //Открытие.

      OPEN_CLOSE_MOVE(v, l_indents[Close_Indent], *v->g_Position_Feed, CLOSE_DIRECTION);

    break;

    case RVM_IN_CLOSING:

      l_poss[RVM_POS] = *v->g_Position_Feed;
      l_spds[RVM_SPD] = *v->g_Speed_Feed;

    break;

    case CLOSING_AFTER_RVM:

      OPEN_CLOSE_MOVE(v, l_indents[Close_Indent], l_poss[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;

    case STOP_IN_CLOSING:

      l_poss[STOP_POS] = *v->g_Position_Reff;
      l_spds[STOP_SPD] = *v->g_Speed_Reff;

    break;

    case CLOSING_AFTER_STOP:

      OPEN_CLOSE_MOVE(v, l_indents[Close_Indent], l_poss[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;


    case BLOCK_IN_CLOSING:

      l_poss[BLOCK_POS] = *v->g_Position_Feed;
      l_spds[BLOCK_SPD] = *v->g_Speed_Feed;

    break;

    case CLOSING_AFTER_BLOCK:

      OPEN_CLOSE_MOVE(v, l_indents[Close_Indent], l_poss[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;

    case ALARM_WAITING_OF_OPENING:


    break;


    case ALARM_STOP_AND_CLOSING:

      l_poss[ALARM_POS] = *v->g_Position_Feed;
      l_spds[ALARM_SPD] = *v->g_Speed_Feed;

    break;

    case FOTO_IN_CLOSING:

      l_poss[FOTO_POS] = *v->g_Position_Feed;
      l_spds[FOTO_SPD] = *v->g_Speed_Feed;

    break;

    case CLOSING_AFTER_FOTO:

      OPEN_CLOSE_MOVE(v, l_indents[Close_Indent], l_poss[STOP_INDENT_POS_END], CLOSE_DIRECTION);

    break;

  }
}



static void Mooving_Stop(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_STOP:

      POS_GE_AND_SE_OR_Min_SPD(v, l_poss[STOP_POS_END], STOP_STATE, OPENING_STOP_INDENT);

    break;

    case OPENING_STOP_INDENT:

      POS_GE_AND_SE(v, l_poss[STOP_INDENT_POS_END], STOP_STATE, STOP_END);

    break;

    case CLOSING_STOP:

      POS_GE_AND_SE_OR_Min_SPD(v, l_poss[STOP_POS_END], STOP_STATE, CLOSING_STOP_INDENT);

    break;

    case CLOSING_STOP_INDENT:

      POS_GE_AND_SE(v, l_poss[STOP_INDENT_POS_END], STOP_STATE, STOP_END);

    break;

    case STOP_END: //КОНЕЦ

      GO_TO(v, WAIT_STATE, WAIT_STATE);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;

  }

}

static void PV_Coordinates_Stop(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_STOP:

      STOPPING_MOVE(v, l_poss[STOP_POS], l_spds[STOP_SPD], l_ar_at_poss[STOP_AT_POS], l_ar_at_spds[STOP_AT_SPD], OPEN_DIRECTION);

    break;


    case OPENING_STOP_INDENT:

      INDENT_MOVE(v, l_indents[STOP_Indent], CLOSE_DIRECTION);

    break;


    case CLOSING_STOP:

      STOPPING_MOVE(v, l_poss[STOP_POS], l_spds[STOP_SPD], l_ar_at_poss[STOP_AT_POS], l_ar_at_spds[STOP_AT_SPD], CLOSE_DIRECTION);

    break;


    case CLOSING_STOP_INDENT:

      INDENT_MOVE(v, l_indents[STOP_Indent], OPEN_DIRECTION);

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

      POS_GE_AND_SE_OR_Min_SPD(v, l_poss[STOP_POS_END], RVM_STATE, OPENING_RVM_INDENT);

    break;

    case OPENING_RVM_INDENT:

      POS_GE_AND_SE(v, l_poss[STOP_INDENT_POS_END], RVM_STATE, RVM_END);

    break;

    case CLOSING_RVM:

      POS_GE_AND_SE_OR_Min_SPD(v, l_poss[STOP_POS_END], RVM_STATE, CLOSING_RVM_INDENT);

    break;

    case CLOSING_RVM_INDENT:

      POS_GE_AND_SE(v, l_poss[STOP_INDENT_POS_END], RVM_STATE, RVM_END);

    break;


    case RVM_END: //КОНЕЦ

      GO_TO(v, WAIT_STATE, WAIT_STATE);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;
  }

}

static void PV_Coordinates_RVM(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_RVM:

      STOPPING_MOVE(v, l_poss[RVM_POS], l_spds[RVM_SPD], l_ar_at_poss[RVM_AT_POS], l_ar_at_spds[RVM_AT_SPD], OPEN_DIRECTION);

    break;


    case OPENING_RVM_INDENT:

      INDENT_MOVE(v, l_indents[RVM_Indent], CLOSE_DIRECTION);

    break;

    case CLOSING_RVM:

      STOPPING_MOVE(v, l_poss[RVM_POS], l_spds[RVM_SPD], l_ar_at_poss[RVM_AT_POS], l_ar_at_spds[RVM_AT_SPD], CLOSE_DIRECTION);

    break;


    case CLOSING_RVM_INDENT:

      INDENT_MOVE(v, l_indents[RVM_Indent], OPEN_DIRECTION);

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

      POS_GE_AND_SE_OR_Min_SPD(v, l_poss[STOP_POS_END], ALARM_STATE, ALARM_CLOSING);

    break;

    case ALARM_CLOSING:

      POS_GE_AND_SE(v, l_indents[Close_Indent], ALARM_STATE, ALARM_END);

    break;

    case ALARM_STOP_IN_CLOSING:

      POS_GE_AND_SE_OR_Min_SPD(v, l_poss[STOP_POS_END], ALARM_STATE, ALARM_OPENING);

    break;

    case ALARM_OPENING:

      POS_GE_AND_SE(v, (v->g_Door_Length - l_indents[Open_Indent]), ALARM_STATE, ALARM_END);

    break;


    case ALARM_END: //КОНЕЦ
      //Задержку до того пока не сбросится BLOCK делать тут или нет ??? скорее всего тут .. надо подумать еще..

      GO_TO(v, WAIT_STATE, WAIT_STATE);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;
  }

}

static void PV_Coordinates_ALARM(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case ALARM_STOP_IN_OPENING:

      STOPPING_MOVE(v, l_poss[ALARM_POS], l_spds[ALARM_SPD], l_ar_at_poss[ALARM_AT_POS], l_ar_at_spds[ALARM_AT_SPD], OPEN_DIRECTION);

    break;


    case ALARM_CLOSING:

      OPEN_CLOSE_MOVE(v, l_indents[Close_Indent], l_poss[STOP_POS_END], CLOSE_DIRECTION);

    break;

    case ALARM_STOP_IN_CLOSING:

      STOPPING_MOVE(v, l_poss[ALARM_POS], l_spds[ALARM_SPD], l_ar_at_poss[ALARM_AT_POS], l_ar_at_spds[ALARM_AT_SPD], CLOSE_DIRECTION);

    break;


    case ALARM_OPENING:

      OPEN_CLOSE_MOVE(v, l_poss[STOP_POS_END], v->g_Door_Length - l_indents[Open_Indent], CLOSE_DIRECTION);

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

      POS_GE_AND_SE_OR_Min_SPD(v, l_poss[STOP_POS_END], FOTO_STATE, CLOSING_FOTO_INDENT);

    break;

    case CLOSING_FOTO_INDENT:

      POS_GE_AND_SE(v, l_poss[STOP_INDENT_POS_END], FOTO_STATE, FOTO_END);

    break;


    case FOTO_END: //КОНЕЦ

      GO_TO(v, WAIT_STATE, WAIT_STATE);

      l_timers[Timer_VKO_VKZ_Another_Block] = 0;
      l_timers[Timer_Current] = 0;
      l_timers[Timer_Position] = 0;
      l_timers[Timer_Command] = 0;

    break;
  }

}

static void PV_Coordinates_FOTO(BLOCK_STRUCT *v)
{
  switch(v->g_Sub_State)
  {
    case OPENING_FOTO:

      STOPPING_MOVE(v, l_poss[FOTO_POS], l_spds[FOTO_SPD], l_ar_at_poss[FOTO_AT_POS], l_ar_at_spds[FOTO_AT_SPD], OPEN_DIRECTION);

    break;


    case OPENING_FOTO_INDENT:

      INDENT_MOVE(v, l_indents[FOTO_Indent], CLOSE_DIRECTION);

    break;

    case CLOSING_FOTO:

      STOPPING_MOVE(v, l_poss[FOTO_POS], l_spds[FOTO_SPD], l_ar_at_poss[FOTO_AT_POS], l_ar_at_spds[FOTO_AT_SPD], CLOSE_DIRECTION);

    break;


    case CLOSING_FOTO_INDENT:

      INDENT_MOVE(v, l_indents[FOTO_Indent], OPEN_DIRECTION);

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
    GO_TO(v, INIT_STATE, FIRST_CLOSING);
    return;
  }

  l_points = (float *)v->g_Points;
  l_timers = (float *)v->g_Timers;
  l_delays = (float *)v->g_Delays;
  l_poss = (float *)v->g_POSs;
  l_spds = (float *)v->g_SPDs;
  l_indents = (float *)v->g_Indents;
  l_current_levels = (float *)v->g_Current_Levels;
  l_ar_at_poss = (float *)v->g_AR_AT_POSs;
  l_ar_at_spds = (float *)v->g_AR_AT_SPDs;
  l_ar_at_slow_poss = (float *)v->g_AR_AT_SLOW_POSs;
  l_ar_at_slow_spds = (float *)v->g_AR_AT_SLOW_SPDs;

  Timers(v);
  Mooving[v->g_State](v);
  PV_Coordinates[v->g_State](v);
  v->n_State_Out = v->g_State;
  v->n_Sub_State_Out = v->g_Sub_State;

}


