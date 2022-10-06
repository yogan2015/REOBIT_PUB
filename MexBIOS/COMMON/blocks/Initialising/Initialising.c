#ifndef __BORLANDC__
#include "stm32f4xx.h"

#ifdef CAN_IC
#include "board_can_ic.h"
#endif

#ifdef FLUORITE
#include "board_fluorite.h"
#endif

#define Resoulver_Checked 0x00000001
#define Aligment_Checked 0x00000002

//First_State
#define Resoulver_Initing 0
#define Aligment_Initing 1
#define Work_State 3

//State Current_Offset_Initing
#define Current_Offset_Reset_On 1
#define Current_Offset_Init 2

//State Resoulver_Initing
#define Resoulver_Min_Max_Reset 3
#define Resoulver_Min_Max_Setting_Plus 4
#define Resoulver_Min_Max_Setting_Zero 5
#define Resoulver_Min_Max_Setting_Minus 6
#define Resoulver_Min_Max_Second_Setting_Zero 7
#define Resoulver_Gain_Offset_Div_Command_Set 8
#define Resoulver_Gain_Offset_Div_Command_Reset 9
#define Resoulver_Gain_Offset_Check 10
#define Resoulver_Min_Max_Remember 11

//Sub_State Resoulver_Min_Max_Remember
#define Resoulver_Calibrate_Set 12
#define Offset_DR1_Set 13
#define Offset_DR2_Set 14
#define Gain_DR1_Set 15
#define Gain_DR2_Set 16
#define Zp_Set 17
#define Initialising_Frequency_Set 18
#define Min_Resistance_Set 19
#define Offset_DR_Max_Set 20
#define Offset_DR_Min_Set 21
#define Gain_DR_Max_Set 22
#define Gain_DR_Min_Set 23
#define Sin_Cos_MAG_Delta_Set 24

//State Aligment_Initing
#define Aligment_Check_On 25
#define Aligment_Set 26
#define Aligment_Check_Off 27

//State
#define State_Set 28
#define PWM_ON 29


#endif
// Do not initialize inputs!
void Init(void)
{
#ifndef __BORLANDC__
  v->State = Resoulver_Min_Max_Reset;
  v->Sub_State = Resoulver_Calibrate_Set;
  v->Resistance_Inited = 0;
  v->Resoulver_Inited = 0;
  v->Aligment_Inited = 0;
  v->Thetha_Prev = 0;
  v->Timer_On_Off = 0;
  v->Current_Offset_State_Prev = 1;
  v->Resoulver_Min_Max_Sum = 0;

#endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  if(v->Timer_On_Off)
  {
    v->Timer += v->SampleTime;
  }
  else
  {
    v->Timer = 0;
  }

  v->Resistance_Inited = (*v->Resistance > MBS_getData(v->Min_Resistance)) ? 1 : 0;
  v->Current_Offset_Inited = (MBS_getData(v->Current_Offset_State)) ? 1 : 0;
  v->Resoulver_Inited = (MBS_getData(v->First_State) & Resoulver_Checked) ? 1 : 0;
  v->Aligment_Inited = (MBS_getData(v->First_State) & Aligment_Checked) ? 1 : 0;


  if(v->Current_Offset_State_Prev != MBS_getData(v->Current_Offset_State))
  {
    if(!v->Current_Offset_Inited)
    {
      v->State = Current_Offset_Reset_On;
      v->Sub_State = Resoulver_Calibrate_Set;
    }
  }
  else
  {
    switch(v->State)
    {
      case Current_Offset_Reset_On:
        v->Current_Offset_Reset = 1;
        v->State = Current_Offset_Init;
      break;

      case Current_Offset_Init:
        v->Current_Offset_Reset = 0;
        if(*v->Current_Offset_Reseted)
        {
          if(!MBS_getMemSt())
          {
            v->State = Resoulver_Min_Max_Reset;
            MBS_setData(v->Current_Offset_State, 1, 1);
          }
        }
      break;
    }
  }

  if((v->Resistance_Inited) && (v->Current_Offset_Inited) && (amc1210.Status == AMC1210_WORK))
  {

    if(v->First_State_Prev != MBS_getData(v->First_State))
    {
      if(v->Resoulver_Inited)
      {
        v->State = Aligment_Check_On;
        v->Sub_State = Resoulver_Calibrate_Set;
      }
      else
      {
        v->State = Resoulver_Min_Max_Reset;
        v->Sub_State = Resoulver_Calibrate_Set;
      }
    }

    switch(MBS_getData(v->First_State))
    {
      case Resoulver_Initing:
        switch(v->State)
        {
          case Resoulver_Min_Max_Reset:
            MBS_setData(v->Resoulver_Calibrate, 0, 0);
            v->Timer_On_Off = 1;
            if(v->Timer > v->Switch_Delay)
            {
              v->Timer_On_Off = 0;
              v->State = PWM_ON;
            }
          break;

          case PWM_ON:
            MBS_setData(v->PWM_Enable, 1, 0);
            v->Timer_On_Off = 1;
            if(v->Timer > v->Aligment_Delay)
            {
              v->Timer_On_Off = 0;
              v->State = Resoulver_Min_Max_Setting_Plus;
            }
          break;

          case Resoulver_Min_Max_Setting_Plus:
            MBS_setData(v->Resoulver_Calibrate, 1, 0);
            MBS_setData(v->Resoulver_Initialising_Frequency, MBS_getData(v->Initialising_Frequency), 0);
            if(*v->Thetha_From_Resoulver < v->Thetha_Prev)
            {
              v->Counter++;
              v->Resoulver_Min_Max_Sum = 1;
            }
            else
            {
                v->Resoulver_Min_Max_Sum = 0;
            }

            v->Thetha_Prev = *v->Thetha_From_Resoulver;

            if(v->Counter > MBS_getData(v->Zp))
            {

              v->Resoulver_Min_Max_Sum = 0;
              v->Timer_On_Off = 0;
              v->Counter = 0;
              v->State = Resoulver_Min_Max_Setting_Zero;
            }
          break;

          case Resoulver_Min_Max_Setting_Zero:
            MBS_setData(v->Resoulver_Calibrate, 1, 0);
            MBS_setData(v->PWM_Enable, 1, 0);
            MBS_setData(v->Resoulver_Initialising_Frequency, _IQ(0), 0);
            if(*v->Thetha_From_Resoulver == v->Thetha_Prev)
            {
              v->Timer_On_Off = 1;
            }
            else
            {
              v->Timer_On_Off = 0;
            }

            v->Thetha_Prev = *v->Thetha_From_Resoulver;

            if(v->Timer > v->Switch_Delay)
            {
              v->Timer_On_Off = 0;
              v->State = Resoulver_Min_Max_Setting_Minus;
            }
          break;

          case Resoulver_Min_Max_Setting_Minus:
            MBS_setData(v->Resoulver_Calibrate, 1, 0);
            MBS_setData(v->PWM_Enable, 1, 0);
            MBS_setData(v->Resoulver_Initialising_Frequency, -(MBS_getData(v->Initialising_Frequency)), 0);
            if(*v->Thetha_From_Resoulver > v->Thetha_Prev)
            {
              v->Counter++;
              v->Resoulver_Min_Max_Sum = 1;
            }
            else
            {
                v->Resoulver_Min_Max_Sum = 0;
            }

            v->Thetha_Prev = *v->Thetha_From_Resoulver;

            if(v->Counter > MBS_getData(v->Zp))
            {
              v->Timer_On_Off = 0;
              v->Counter = 0;
              MBS_setData(v->PWM_Enable, 0, 0);
              MBS_setData(v->Resoulver_Initialising_Frequency, _IQ(0), 0);
              v->Thetha_Prev = 0;
              v->State = Resoulver_Min_Max_Second_Setting_Zero;
              v->Resoulver_Min_Max_Sum = 0;
            }
          break;

          case Resoulver_Min_Max_Second_Setting_Zero:
            MBS_setData(v->Resoulver_Calibrate, 1, 0);
            MBS_setData(v->PWM_Enable, 1, 0);
            MBS_setData(v->Resoulver_Initialising_Frequency, _IQ(0), 0);
            if(*v->Thetha_From_Resoulver == v->Thetha_Prev)
            {
              v->Timer_On_Off = 1;
            }
            else
            {
              v->Timer_On_Off = 0;
            }

            v->Thetha_Prev = *v->Thetha_From_Resoulver;

            if(v->Timer > v->Switch_Delay)
            {
              v->Timer_On_Off = 0;
              v->State = Resoulver_Gain_Offset_Div_Command_Set;
            }
          break;

          case Resoulver_Gain_Offset_Div_Command_Set:
            v->Resoulver_Gain_Offset_Div = 1;
            v->Timer_On_Off = 1;

            if(v->Timer > v->Switch_Delay)
            {
              v->Timer_On_Off = 0;
              v->State = Resoulver_Gain_Offset_Div_Command_Reset;
            }
            break;

          case Resoulver_Gain_Offset_Div_Command_Reset:
            v->Resoulver_Gain_Offset_Div = 0;
            v->Timer_On_Off = 1;

            if(v->Timer > v->Switch_Delay)
            {
              v->Timer_On_Off = 0;
              v->State = Resoulver_Gain_Offset_Check;
            }
            break;

          case Resoulver_Gain_Offset_Check:
          if(
        (MBS_getData(v->Offset_DR1) < MBS_getData(v->Offset_DR_Max))
        &&
        (MBS_getData(v->Offset_DR1) > MBS_getData(v->Offset_DR_Min))
        &&
        (MBS_getData(v->Offset_DR2) < MBS_getData(v->Offset_DR_Max))
        &&
        (MBS_getData(v->Offset_DR2) > MBS_getData(v->Offset_DR_Min))
        &&
        (MBS_getData(v->Gain_DR1) < MBS_getData(v->Gain_DR_Max))
        &&
        (MBS_getData(v->Gain_DR1) > MBS_getData(v->Gain_DR_Min))
        &&
        (MBS_getData(v->Gain_DR2) < MBS_getData(v->Gain_DR_Max))
        &&
        (MBS_getData(v->Gain_DR2) > MBS_getData(v->Gain_DR_Min))
        )
      {
        v->State = Resoulver_Min_Max_Remember;
        v->Sub_State = Resoulver_Calibrate_Set;
      }
      else
      {
        v->State = Resoulver_Min_Max_Reset;
      }
      break;

          case Resoulver_Min_Max_Remember:
            switch(v->Sub_State)
            {
              case Resoulver_Calibrate_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Resoulver_Calibrate, 2, 1);
                  v->Sub_State = Offset_DR1_Set;
                }
              break;

              case Offset_DR1_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Offset_DR1, MBS_getData(v->Offset_DR1), 1);
                  v->Sub_State = Offset_DR2_Set;
                }
              break;

              case Offset_DR2_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Offset_DR2, MBS_getData(v->Offset_DR2), 1);
                  v->Sub_State = Gain_DR1_Set;
                }
              break;

              case Gain_DR1_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Gain_DR1, MBS_getData(v->Gain_DR1), 1);
                  v->Sub_State = Gain_DR2_Set;
                }
              break;

              case Gain_DR2_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Gain_DR2, MBS_getData(v->Gain_DR2), 1);
                  v->Sub_State = Zp_Set;
                }
              break;

              case Zp_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Zp, MBS_getData(v->Zp), 1);
                  v->Sub_State = Initialising_Frequency_Set;
                }
              break;

              case Initialising_Frequency_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Initialising_Frequency, MBS_getData(v->Initialising_Frequency), 1);
                  v->Sub_State = Min_Resistance_Set;
                }
              break;

              case Min_Resistance_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Min_Resistance, MBS_getData(v->Min_Resistance), 1);
                  v->Sub_State = Offset_DR_Max_Set;
                }
              break;

              case Offset_DR_Max_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Offset_DR_Max, MBS_getData(v->Offset_DR_Max), 1);
                  v->Sub_State = Offset_DR_Min_Set;
                }
              break;

              case Offset_DR_Min_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Offset_DR_Min, MBS_getData(v->Offset_DR_Min), 1);
                  v->Sub_State = Gain_DR_Max_Set;
                }
              break;

              case Gain_DR_Max_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Gain_DR_Max, MBS_getData(v->Gain_DR_Max), 1);
                  v->Sub_State = Gain_DR_Min_Set;
                }
              break;

              case Gain_DR_Min_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Gain_DR_Min, MBS_getData(v->Gain_DR_Min), 1);
                  v->Sub_State = Sin_Cos_MAG_Delta_Set;
                }
              break;

              case Sin_Cos_MAG_Delta_Set:
                if(!MBS_getMemSt())
                {
                  MBS_setData(v->Sin_Cos_MAG_Delta, MBS_getData(v->Sin_Cos_MAG_Delta), 1);
                  v->Sub_State = State_Set;
                }
              break;

              case State_Set:
                if(!MBS_getMemSt())
                {
                  v->State = Aligment_Check_On;
                  v->Sub_State = Resoulver_Calibrate_Set;
                  MBS_setData(v->First_State, (MBS_getData(v->First_State) | Resoulver_Checked), 1);
                }
              break;
            }
          break;
        }
      break;

      case Aligment_Initing:
        switch(v->State)
        {
          case Aligment_Check_On:
            MBS_setData(v->PWM_Enable, 1, 0);
            v->Timer_On_Off = 1;
            if(v->Timer > v->Aligment_Delay)
            {
              v->Timer_On_Off = 0;
              v->State = Aligment_Set;
            }
          break;

          case Aligment_Set:
            if(!MBS_getMemSt())
            {
              v->State = Aligment_Check_Off;
              MBS_setData(v->Resoulver_Aligment, *v->Thetha_From_Resoulver, 1);
            }
          break;

          case Aligment_Check_Off:
            v->State = State_Set;
            MBS_setData(v->PWM_Enable, 0, 0);
          break;

          case State_Set:
            if(!MBS_getMemSt())
            {
              v->State = Resoulver_Min_Max_Reset;
              v->Sub_State = Resoulver_Calibrate_Set;
              MBS_setData(v->First_State, (MBS_getData(v->First_State) | Aligment_Checked), 1);
            }
          break;
        }
      break;

      case Work_State:
        if(v->Resoulver_Alarm)
        {
          //�������� ������� �� ����� ������.
          if(
              (*v->Sin_Cos_MAG < (_IQ13(1.0) + MBS_getData(v->Sin_Cos_MAG_Delta)))
              &&
              (*v->Sin_Cos_MAG > (_IQ13(1.0) - MBS_getData(v->Sin_Cos_MAG_Delta)))
            )
          {
            v->Resoulver_Alarm = 0;
          }
        }
        else
        {
          if(
              (*v->Sin_Cos_MAG > (_IQ13(1.0) + MBS_getData(v->Sin_Cos_MAG_Delta)))
              ||
              (*v->Sin_Cos_MAG < (_IQ13(1.0) - MBS_getData(v->Sin_Cos_MAG_Delta)))
            )
          {
            v->Resoulver_Alarm = 1;
          }
        }
      break;
    }
  }

  v->First_State_Prev = MBS_getData(v->First_State);
  v->Current_Offset_State_Prev = MBS_getData(v->Current_Offset_State);
#endif

}

