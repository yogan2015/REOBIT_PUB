
#define Discret_Input_SB1 ((*v->Input_Signal_Word & 0x1)>>0)
#define Discret_Input_SB2 ((*v->Input_Signal_Word & 0x2)>>1)
#define Discret_Input_Close ((*v->Input_Signal_Word & 0x4)>>2)
#define Discret_Input_Open  ((*v->Input_Signal_Word & 0x8)>>3)
#define Discret_Input_Type  ((*v->Input_Signal_Word & 0x10)>>4)
#define Discret_Input_Close_Direction  ((*v->Input_Signal_Word & 0x20)>>5)
#define Discret_Input_No_Power_Open  ((*v->Input_Signal_Word & 0x40)>>6)
#define Discret_Input_Open_SlowDown  ((*v->Input_Signal_Word & 0x80)>>7)
#define Discret_Input_App ((*v->Input_Signal_Word & 0x100)>>8)


#define DC Par[0]
#define AB Par[1]
#define BC Par[2]
#define CD Par[3]
#define DE Par[4]
#define FG Par[5]
#define GH Par[6]
#define HI Par[7]
#define DO Par[8]
#define Fpark Par[9]
#define Fmax Par[10]
#define Vmin Par[11]
#define Vmax Par[12]
#define L Par[13]
#define OFFSET Par[14]
#define Target_Force_Limit Par[15]
#define Target_Speed_Limit Par[16]
#define Target_Postition Par[17]
#define Setup_Word Par[18]

#define Current_Door_Position *v->CP
#define Drive_RMS_Current *v->CI
#define Drive_Speed *v->CS
#define Move_Timer v->MT
#define Move_Reverse_Timer v->MRT
#define Move_Stop_Timer v->MST
#define Stop_Delay v->SD
//#define Press_Time_Maximum v->PTM
#define Iternal_Data_Registrer v->IDR
#define System_Word v->SW
#define Reverse_Delay v->RVMD
#define Sample_Time __IQ(v->SampleTime,24)
#define Previous_Command (Iternal_Data_Registrer & 0x3)
#define Current_Command (System_Word & 0x3 )
#define Drive_Stop_Current v->DSC
#define Drive_Reverse_Stop_Current v->DRSC
#define Drive_Stop_Speed v->DSS

#define VKOAREA (L - DO-2)
#define VKZAREA (DC+5+OFFSET)

#define Reset_Sensor v->RS
#define Safe_Park_Cur v->SPC

#define Reverse_zone (VKZAREA + AB+BC)
#define Vs ((((Setup_Word & 0x78)>>3)+1)*10)



#define A_Point (DC+OFFSET)
#define B_Point (A_Point + AB)
#define C_Point (B_Point + BC)
#define D_Point (C_Point + CD)
#define E_Point (D_Point + DE)
#define F_Point (L - DO-HI-GH-FG)
#define G_Point (L - DO-HI-GH)
#define H_Point (L - DO-HI)
#define I_Point (L - DO)





static void INITIALIZE (BLOCK_STRUCT *v, long *Par);
static void Discret_Input_READ(BLOCK_STRUCT *v, long *Par);
static void DOOR_STATE (BLOCK_STRUCT *v, long *Par);
static void INIT_MODE (BLOCK_STRUCT *v, long *Par);
static void WORK_MODE (BLOCK_STRUCT *v, short *Path, short *Path_Speed, long *Par);
static void PATH (BLOCK_STRUCT *v, short *Path, short *Path_Speed, long *Par);


void Init(void)
{

}
void Exec(void)
{


  //{ A_Point,B_Point,C_Point,D_Point,E_Point,F_Point,G_Point,H_Point,I_Point};
    static short Path[9] = {0,0,0,0,0,0,0,0,0};
    static short Path_Speed[9] = {0,0,0,0,0,0,0,0,0};

    long *Par= (long *)(*v->Buf) ;

    //��������� �������������

if (!(System_Word & 0x80000000)) { INITIALIZE(v, Par); System_Word |= 0x80000000; return;} // ������������� � ��������� ����� � � ����������

    //������ ������� ������
    Discret_Input_READ(v, Par);
    //��������������� ��������� ������� ������
    if (System_Word == 0) { L = 0; return;} // ������������� ������ ������ � 0
    DOOR_STATE(v, Par);
    //��� ���������� ������� � ������� �����
    if (System_Word & 0x10000000)     PATH(v, Path, Path_Speed, Par); //  WORK_MODE(v, Path, Path_Speed, Par);
    //����� � ����� �������������
    //else
    INIT_MODE(v, Par);


    v->VKZ = System_Word & 0x4; // ���
    v->VKO = System_Word & 0x8; // ���
    v->RVM = System_Word & 0x10; // ���

    //������� ���������
    v->P = Target_Postition;
    //������� ��������
    v->V = Target_Speed_Limit;
    //������� ����
    v->I =Target_Force_Limit;



}
static void INITIALIZE (BLOCK_STRUCT *v, long *Par)
{
  v->P = 0;
  v->V = 0;
  v->I = 0;
  v->SW = 0;
  v->VKZ= 0;
  v->VKO = 0;
  v->RVM = 0;
  Iternal_Data_Registrer = 0;
  Discret_Input_READ(v, Par);

}
static void DOOR_STATE(BLOCK_STRUCT *v, long *Par)
{

     //�������� ��������� ������ ������ ������������� ������ �� ����������� ������ ������ 25�� ����������� ������ �������� ��� 325�� ������������ - 1200��
  if (((L >=300)&&(L <=1225)) != ((System_Word & 0x40000000 ) >> 30)) System_Word ^=0x40000000;
  //������ ��������
  if (((System_Word & 0x1) || (System_Word & 0x2)) && (Move_Timer < _IQ24(100.0))) Move_Timer += Sample_Time;
  if (!((System_Word & 0x1) || (System_Word & 0x2)) ) Move_Timer = 0;
  //������� ����� ��������� ��������
  Iternal_Data_Registrer &=0xFFFFE0FF;
  //��������� ������ ���������� ��������
  if (((Previous_Command != Current_Command)&& (Current_Command == 0) ) != (Iternal_Data_Registrer & 0x100)>>8) Iternal_Data_Registrer ^= 0x100;
  //��������� ������ ����� ����������� ��������
  if (((Previous_Command != Current_Command)&& (Current_Command ) && (Previous_Command)) != (Iternal_Data_Registrer & 0x200)>>9) Iternal_Data_Registrer ^= 0x200;
  //��������� ������ ������ ��������
  if (((Previous_Command != Current_Command)&& (Previous_Command ==0)) != (Iternal_Data_Registrer & 0x400)>>10) Iternal_Data_Registrer ^= 0x400;
  //��������� ������ ����������� ��������
  if (((Previous_Command == Current_Command)&& (Current_Command)) != (Iternal_Data_Registrer & 0x800)>>11) Iternal_Data_Registrer ^= 0x800;
  //��������� ����� ��������
  if (((Previous_Command == Current_Command)&& (Current_Command == 0)) != (Iternal_Data_Registrer & 0x1000)>>12) Iternal_Data_Registrer ^= 0x1000;
  //�������� ������� ���������
  if ((Iternal_Data_Registrer & 0x800)&& (Drive_RMS_Current >= Drive_Stop_Current) && (Drive_Speed <= Drive_Stop_Speed ) )
  {
    Move_Stop_Timer  = ( Move_Stop_Timer < Stop_Delay ) ? Move_Stop_Timer + Sample_Time : Move_Stop_Timer; // ������ ����� ��� ������������ ������� ���������
    if (( Move_Stop_Timer >= Stop_Delay ) != ((System_Word & 0x40)>>6 ))
      System_Word ^= 0x40; // ��������� ���� ���������
  }
  else if ((Drive_Speed > Drive_Stop_Speed )||(Move_Timer == 0)) { Move_Stop_Timer = 0;  System_Word&= 0xFFFFFFBF;}
  //�������� ��� ��������� �������������
  if (System_Word &0x10000000)
  {
    //��������� �������� �����
    if ( ( Current_Door_Position < VKZAREA ) != ( (System_Word & 0x4)>>2) ) System_Word ^= 0x4; //���
    if ( ( Current_Door_Position > VKOAREA ) != ( (System_Word & 0x8)>>3) ) System_Word ^= 0x8; //���
    //�������� ���������� ��� ��������
    if (( Drive_RMS_Current > Drive_Reverse_Stop_Current) && (System_Word & 0x1) && ((System_Word & 0x8)>>2) && ( Current_Door_Position > Reverse_zone )  )  //TODO ����� �������� �� �������� � 1 �������
    {
      Move_Reverse_Timer  = ( Move_Reverse_Timer < _IQ24(100.0) ) ? Move_Reverse_Timer + Sample_Time : Move_Reverse_Timer; // ������ ����� ��� ������������ ������� ����������
      if (( Move_Reverse_Timer >= Reverse_Delay ) != ((System_Word & 0x20)>>5 )) System_Word ^= 0x20; // ��������� ���� ����������
      if (System_Word & 0x20) System_Word |= 0x10;  // ��������� ���� ������� ���
    }
    else Move_Reverse_Timer = 0;
  }

}
static void Discret_Input_READ(BLOCK_STRUCT *v, long *Par)
{

  static short Discret_Input_SB1_Press_Timer = 0;
  static short Discret_Input_SB2_Press_Timer = 0;
  static short Press_Time_Maximum = 1000;
v->Out = Discret_Input_SB2_Press_Timer;

  if (!System_Word)
  {
    Discret_Input_SB1_Press_Timer = 0;
    Discret_Input_SB2_Press_Timer = 0;
    return;
  }
  //��������� ���������� �������
  if (( Iternal_Data_Registrer & 0x1 )!= ( System_Word & 0x1 )) Iternal_Data_Registrer ^=0x1;
  if (( Iternal_Data_Registrer & 0x2 )!= ( System_Word & 0x2 )) Iternal_Data_Registrer ^=0x2;

  //������ �������� ������ �� �������� ��� ������
  Discret_Input_SB1_Press_Timer  += (Discret_Input_SB1)  ? ( (Discret_Input_SB1_Press_Timer < Press_Time_Maximum)  ? 1:0 )  : ( (Discret_Input_SB1_Press_Timer < 1) ? 0 : -1 );
  Discret_Input_SB2_Press_Timer  += (Discret_Input_SB2)  ? ( (Discret_Input_SB2_Press_Timer >= Press_Time_Maximum)  ? 0:1 )  : ( (Discret_Input_SB2_Press_Timer < 1) ? 0 : -1 );

  //��������� ���������� � ����������� ������� �� �������
   if (Discret_Input_Close!= (Iternal_Data_Registrer & 0x4)>>2) Iternal_Data_Registrer ^=0x4;
  if (Discret_Input_Open != (Iternal_Data_Registrer & 0x8)>>3) Iternal_Data_Registrer ^=0x8;

  //��������� ���������� � ����������� ������ � ������
   if ((Discret_Input_SB1_Press_Timer >= (Press_Time_Maximum/2)) != (Iternal_Data_Registrer & 0x10)>>4) Iternal_Data_Registrer ^=0x10;
  if ((Discret_Input_SB2_Press_Timer >= (Press_Time_Maximum/2)) != (Iternal_Data_Registrer & 0x20)>>5) Iternal_Data_Registrer ^=0x20;

  //��������� �������������
  if (Discret_Input_App  != ((System_Word & 0x20000000)>>29 ) ) System_Word ^=0x20000000;

  //�������� ��� ���������� ����� ������
  if (((Iternal_Data_Registrer & 0x10) != 0) && ((Iternal_Data_Registrer & 0x20)!= 0))
  {
    System_Word = 0; //���������������
    return;
  }
  else
  {
    //�������� ���������� ������ � ��������� ������� �� ��������

    if (((Iternal_Data_Registrer & 0x10) !=0) || ((Iternal_Data_Registrer & 0x4) !=0) ) System_Word |=0x1; else System_Word &= 0xFFFFFFFE;
    if (((Iternal_Data_Registrer & 0x20) !=0) || ((Iternal_Data_Registrer & 0x8) !=0) ) System_Word |=0x2; else System_Word &= 0xFFFFFFFD;

    // ���� ��������� �������� ������
    if ((System_Word & 0x3) == 0x3 )
    {
      //������� ������� �������
      System_Word &= 0xFFFFFFFC;
      //������������� � ����������� � �����������
      if (Setup_Word & 0x1)
      {
        if ((Iternal_Data_Registrer & 0x4)!=(System_Word & 0x1)<<2) System_Word ^=0x1;
        if ((Iternal_Data_Registrer & 0x8)!=(System_Word & 0x2)<<2) System_Word ^=0x2;
      }
      else
      {
        if ((Iternal_Data_Registrer & 0x10)!=((System_Word & 0x1)<<4)) System_Word ^=0x1;
        if ((Iternal_Data_Registrer & 0x20)!=((System_Word & 0x2)<<4)) System_Word ^=0x2;
      }
    }
  }
  return;
}
static void INIT_MODE (BLOCK_STRUCT *v, long *Par)
{
  static short Lock_Position = 0;
  //�������� //������ �������
  if ((Iternal_Data_Registrer & 0x1000) || (Iternal_Data_Registrer & 0x100))
  {
  if (Lock_Position == 9999)
    if ((Iternal_Data_Registrer & 0x40) == 0)
      Lock_Position = Current_Door_Position;
    else
      Lock_Position = (Current_Door_Position > A_Point) ? Current_Door_Position: A_Point;

    Target_Postition = Lock_Position;
    Target_Speed_Limit = Vs;
    Target_Force_Limit = Fmax;

    if ((Iternal_Data_Registrer & 0x40) != 0)
    {
        if ((Current_Door_Position > VKZAREA))  //������ ���
            System_Word &= 0xFFFFFFFB;
        else   System_Word |= 0x4;
    }

  }



  //����������� �������� //����� ������� //������ ��������
  if ((Iternal_Data_Registrer & 0x800) || (Iternal_Data_Registrer & 0x200) || (Iternal_Data_Registrer & 0x400))
  {
  Lock_Position = 9999;
  if ((System_Word & 0x1)&&!(System_Word & 0x2))
    //�������� ��� �������� � �������������
    {
      //������ ���
      System_Word &= 0xFFFFFFF7;
      //��������� ������� ����� ��������
      Target_Postition = ((Iternal_Data_Registrer & 0x40) == 0) ? -2000: A_Point;
      //��������� ������� �������� ��������
      Target_Speed_Limit = Vs;
      //��������� �������� ������ ��� ��������
      Target_Force_Limit = (Move_Stop_Timer >=Stop_Delay ) ? Fpark : Fmax;
      //�������� ��� ����� � �������������
      if (System_Word & 0x40)
      {
        //�������� ��� ����� ������� ��������� �� ���������� � ���������� ��� ������
        if ((Iternal_Data_Registrer & 0x40) == 0)
        {
          Reset_Sensor = 1;
          Iternal_Data_Registrer |= 0x40;
        }
        else
        {
          //�������� ��� ����� ������� ��������� ������ �������
          if ((Current_Door_Position >= -5 )&&(Current_Door_Position <= 5 ))
          {
            //������������� � ��� ��� ���� ������
            Iternal_Data_Registrer |= 0x80;
            //������� ����� ������� ���������
            Reset_Sensor = 0;
            //������������� ���
            System_Word |= 0x4;
            Target_Postition = A_Point;
          }
          //�������� ����������� ������������ ���� � ������ �������
          if ((Drive_RMS_Current > Safe_Park_Cur)&&(Iternal_Data_Registrer & 0x80)&&(Current_Door_Position >0) ) OFFSET = Current_Door_Position + 1;
          Target_Postition = A_Point;
          //�������� ���������� �� ������ ������ ������
          if ((System_Word & 0x40000000) && (Iternal_Data_Registrer & 0x80))
          {
            if (((Setup_Word & 0x2) && (System_Word & 0x20000000)) || (!(Setup_Word & 0x2))) // �������� ������������� ������� ��� ��� ��������� �������������

              {
              System_Word |= 0x10000000; // ��������� ����� ��������� �������������
                //������� ������� �������
                System_Word &= 0xFFFFFFFC;
                //������� ����� ��������� ��������
                Iternal_Data_Registrer &=0xFFFFE0FF;
                //��������� ����� ��������
                Iternal_Data_Registrer |= 0x1000;

              }

          }

        }
      }
    }


  if (!(System_Word & 0x1)&&(System_Word & 0x2))
    //�������� ��� �������� � �������������
    {
      //������ ���
      System_Word &= 0xFFFFFFFB;
      //��������� ������� ����� ��������
      Target_Postition = (System_Word & 0x40000000) ? L : 2000;
      //��������� ������� �������� ��������
      Target_Speed_Limit = Vs;
      //��������� �������� ������ ��� ��������
      Target_Force_Limit = (Move_Stop_Timer >=Stop_Delay ) ? Fpark : Fmax;
      //�������� ��� ����� � ������������� ���� ���������� ���������� ������ ������
      if ((System_Word & 0x40) && !(System_Word & 0x40000000) && (Iternal_Data_Registrer & 0x80)) L = Current_Door_Position;
      //�������� ��� ����� � ������������� ���� ������ ������ ����������
      if ((System_Word & 0x40) && (System_Word & 0x40000000) && (Iternal_Data_Registrer & 0x80))
      {
        System_Word |= 0x8; // ���
        System_Word |= 0x10000000; // ��������� ����� ��������� �������������
        //������� ������� �������
        System_Word &= 0xFFFFFFFC;
        //������� ����� ��������� ��������
        Iternal_Data_Registrer &=0xFFFFE0FF;
        //��������� ����� ��������
        Iternal_Data_Registrer |= 0x1000;
      }
    }
  }



  if ((System_Word & 0x40000000) && !(Setup_Word & 0x4))
  {
    //����������� ������������ �������� �������� ������ �� ���������� ����� ������

       if (L >=1200) Vmax = 580;
  else if (L >=1000) Vmax = 540;
  else if (L >=900)  Vmax = 515;
  else if (L >=800)  Vmax = 490;
  else if (L >=750)  Vmax = 475;
  else if (L >=700)  Vmax = 460;
  else if (L >=600)  Vmax = 430;
  else if (L >=550)  Vmax = 410;
  else if (L >=500)  Vmax = 390;
  else if (L >=470)  Vmax = 380;
  else if (L >=450)  Vmax = 365;
  else if (L >=400)  Vmax = 330;
  else if (L >=350)  Vmax = 250;
  else if (L >=325)  Vmax = 240;

  //����������� �������� ��������
  Vmin = Vmax /3;


  }

  return;
}
static void WORK_MODE (BLOCK_STRUCT *v, short *Path, short *Path_Speed, long *Par)
{
  static char Direction = 0;
  static char WorkStage = 0;
  static long  Time = 0;
  static char j = 0;
  static long MovePos = 0;
  static float Am = 0;
  static float t = 0;
  static long V_t = 0;
  static float A_t = 0;
  static float J_t = 0;
  static long P_t = 0;
  static char BR_WS= 0;
  static float BR_Y = 0;
  static long BR_T = 0;
  static char S_Curve_State_Stage = 0;
  static short Lock_Position = 9999;

#define SVref (float)Path_Speed[j]
#define SPref (float)Path[j]

//��������� ���� ��������� ��������� ������ �������
  if (((v->IDR & 0x18000)>>15) != WorkStage)
  {
    v->IDR &= 0xFFFE7FFF;
    v->IDR |= WorkStage<<15;
  }
  //��������� ���� ��������� ��������� ������ �������
    if (((v->IDR & 0x6000)>>13) != S_Curve_State_Stage)
    {
      v->IDR &= 0xFFFF9FFF;
      v->IDR |= S_Curve_State_Stage<<13;
    }
    //�������� //������ �������
    if ((Iternal_Data_Registrer & 0x1000) || (Iternal_Data_Registrer & 0x100))
    {
        if (Lock_Position == 9999)
            Lock_Position = (Current_Door_Position > A_Point) ? ((Current_Door_Position < I_Point)?Current_Door_Position: I_Point): A_Point;

          Target_Postition = Lock_Position;
          Target_Speed_Limit = Vs;
          Target_Force_Limit = Fmax;

  if (Drive_RMS_Current >= Safe_Park_Cur)
    {
      Time += v->SampleTime;
      if ( Time > _IQ24(2.0) ) Target_Force_Limit =  Fpark ;
    }
  return;
}

if ((!(System_Word & 0x1)&&(System_Word & 0x2)) ) Direction = 1; else //��������
if ((!(System_Word & 0x2)&&(System_Word & 0x1)) ) Direction = -1; //��������

Target_Force_Limit = (! (System_Word & 0x10)) ? Fmax : Fpark;

//������ �������
if (Iternal_Data_Registrer & 0x100)
{

BR_Y = v->SCY ;
BR_T = Time;
BR_WS = WorkStage;

WorkStage = 3;
S_Curve_State_Stage = 2;
J_t = -J_t;

}

//����� �������
if (Iternal_Data_Registrer & 0x200)
{
  Lock_Position = 9999;
  //����������� ���������� ���������
  PATH(v, Path, Path_Speed, Par);

}


//������ ��������
if (Iternal_Data_Registrer & 0x400)
{
  Lock_Position = 9999;
  // ��������� ������� ��� �������� �-������ S_Curve_State_Stage = 0;
  //����������� ���������� ���������
  PATH(v, Path, Path_Speed, Par);


  if ((Direction > 0 ) && (Current_Door_Position >= I_Point))
   {
    j = 8;


   }
  if ((Direction < 0 ) && (Current_Door_Position <= A_Point))
  {
    j = 0;

  }

  Target_Postition = Path[j];
  Target_Speed_Limit = Path_Speed[j];


  return;
}

  //����������� ��������
if (Iternal_Data_Registrer & 0x800)
{






  if (Path_Speed[j] == 0) Path_Speed[j]  = 10;




switch (S_Curve_State_Stage)
  {
  case 0:
  MovePos = (SPref - P_t ) * Direction;

    if (MovePos == 0) S_Curve_State_Stage = 2;
    else
    {
      Am = fabs(0.75*(SVref - V_t)*(SVref + V_t)/MovePos);



      t = (MovePos * 0.66667)/(SVref + V_t);

          if (V_t  <  SVref) A_t=Am;
          if (V_t  >  SVref) A_t=-Am;

          J_t= A_t/ t;
          S_Curve_State_Stage=1;
          v->SCY=0;
          V_t=SVref;
          P_t=SPref;
    }
  case 1:
    switch (WorkStage)
    {
      case 0: (v->SCY) = (J_t) * (Time);          if ((Time)>=t) WorkStage++;  else  break;
      case 1: (v->SCY) = A_t;               if ((Time)>=t*2) WorkStage++;  else  break;
      case 2: (v->SCY) = -(J_t) * (Time) + (J_t) * (t*3);

      if ((Time)>=t*3)
      {
        WorkStage = 0;
        S_Curve_State_Stage = 2;
        v->SCY = 0;
        A_t = 0;
      }
      break;


      case 3: v->SCY = J_t*Time;
      switch (BR_WS) // ������������ ��� ������ ������� �� ����� ������
      {
      case 0: v->SCY += (BR_Y+BR_Y); break; // ��������� ��� ��������� ����� += � �� ������ ���� -=
      case 1: v->SCY += (A_t - (J_t) * (BR_T)); break;
      case 2: v->SCY = -(J_t) * (Time) + (J_t) * (t*3);  break;
      }
      if ((v->SCY>=-1)&&(v->SCY<=1))
      {
        WorkStage = 0;
        S_Curve_State_Stage = 0;
        v->SCY = 0;
        A_t = 0;
        BR_T = 0;
        BR_WS = 0;
        BR_Y = 0;
        P_t = v->SCY2;
        V_t = v->SCY1;
        j++;
        if (Direction <0 )   j = 0;
      }
      break;

    }
    break;
  case 2:
    if ((Direction == -1)|| (v->SCY2 <= (float)Path[0]))
           {
           if  ((j) == 0)
             {(S_Curve_State_Stage)=0;  Direction=0;}
             else
             {(S_Curve_State_Stage)=1; j--;}
           }
    if (Direction ==  1)
       {
       if  (((j) >= 8)|| (v->SCY2 >= L ))
            {(S_Curve_State_Stage)=0;  Direction=0; }
       else
       {(S_Curve_State_Stage)=1; j++;}

       }
      break;

  }
}
v->SCY1    = ((S_Curve_State_Stage) == 0) ? V_t :((v->SCY1) + (v->SCY)*(v->SampleTime));
v->SCY2    = ((S_Curve_State_Stage) == 0) ? P_t :((v->SCY2) + (v->SCY1)*(v->SampleTime) * (Direction));
Time  = ((S_Curve_State_Stage) == 0) ? 0      :((Time)+(v->SampleTime));

Target_Postition=__IQ(v->SCY2,20);
Target_Speed_Limit=__IQ(v->SCY1,21);
v->A=__IQ(v->SCY,21);
v->Out1 = j;

}


static void PATH (BLOCK_STRUCT *v, short *Path, short *Path_Speed, long *Par)
{
  static short Reference_Path[9] = {0,0,0,0,0,0,0,0,0};
  static short Reference_Path_Speed[9] = {0,0,0,0,0,0,0,0,0};
  static char i = 0;
  static char j = 0;
  static char k = 0;

#define y1 Reference_Path_Speed[i-1]
#define y2 Reference_Path_Speed[i]
#define y3 0
#define x1 Reference_Path[i-1]
#define x2 Reference_Path[i]
#define x3 Current_Door_Position

   //���������� ������������ ������ ����� ����������� ������ ��� ������������� ���� ��� ������� ���������
  if ((Reference_Path[0] != A_Point)||(Reference_Path[1] != B_Point)||(Reference_Path[2] != C_Point)||(Reference_Path[3] != D_Point)||(Reference_Path[4] != E_Point)||(Reference_Path[5] != F_Point)||(Reference_Path[6] != G_Point)||(Reference_Path[7] != H_Point)||(Reference_Path[8] != I_Point))
  {
    Reference_Path[0] = A_Point; Reference_Path[1] = B_Point; Reference_Path[2] = C_Point; Reference_Path[3] = D_Point;
    Reference_Path[4] = E_Point; Reference_Path[5] = F_Point; Reference_Path[6] = G_Point; Reference_Path[7] = H_Point;
    Reference_Path[8] = I_Point;
    Reference_Path_Speed[0] = 0; Reference_Path_Speed[1] = Vmin*1.5; Reference_Path_Speed[2] = Vmin; Reference_Path_Speed[3] = Vmin;
    Reference_Path_Speed[4] = Vmax; Reference_Path_Speed[5] = Vmax; Reference_Path_Speed[6] = Vmin; Reference_Path_Speed[7] = Vmin;
    Reference_Path_Speed[8] = 0;

    //������ ������������� ���� ������� ������ �������
    while (i <8)
    {
      if ((Reference_Path_Speed[i] != Reference_Path_Speed[i+1])&&(Reference_Path[i] != Reference_Path[i+1])) // �������� �� ������� �������
      {
        //����������� � ������ ������������� tga
        if ( k < abs(((Reference_Path_Speed[i+1] - Reference_Path_Speed[i])/(Reference_Path[i+1]-Reference_Path[i]))) )
           k = abs(((Reference_Path_Speed[i+1] - Reference_Path_Speed[i])/(Reference_Path[i+1]-Reference_Path[i]))) ;
      }
      i++;
    }
    i = 0;
  }



  //����������� �������� ���������
  if ((!(System_Word & 0x1)&&(System_Word & 0x2)) )//��������
  {
    j = 0; i = 0; k = abs(k); // ������������� ��������� �������
    if (Current_Door_Position < Reference_Path[0]) {while (j<=8) {Path[j] = Reference_Path[0]; j++;}} // �������� �� ������� ������� �������� ���������
    else
    {
      if (Current_Door_Position > Reference_Path[8]) {while (j<=8) {Path[j] = Reference_Path[8]; j++;}}// �������� �� ������� ������� �������� ���������
          else
          {

            while ( (i <8)&&(Current_Door_Position>(Reference_Path[i]-1)) ) i++;     //�� ������ ������� � ���������� i ����� ����� �������� �������� ������� ��������� � ��������� �����
            Path[j] = Current_Door_Position; // ������������� ��������� ������ ����� ������� �������
            Path_Speed[j++] = 0;
            do
            {
              if ((Path[j]>x2)||((y1-y2-k*x1+k*x2)==0)||(Path_Speed[j] > y2 )) i++; // ��� ������ ������ ������ ������� �� ����������� ����������� �������� ����� ��� ������� ���� ����� ����������� ����� �� ��������� ��������� ����� ���� ����� �����������(������� � ������������ ����������)

              Path[j] = -(x1*y2-x2*y1-x1*y3+x2*y3+k*x1*x3-k*x2*x3)/(y1-y2-k*x1+k*x2);//����������� ����� ������� � � ������������ ����� ������� ���������� �����
              Path_Speed[j] = k*( Path[j] - x3)+y3; // ������ �������� � ���������� ����� ��������

            }while ((Path[j]>x2)&&(i<=8)&&(Path_Speed[j])>Reference_Path[i]); // �������� ��� ����������� ����� ����� �� ������������ ����� ���������� �������.
              j++; // � j ����� ��������� ����� ��� ����������� � i ����� ������� �����
            while (j<9)
            {
              Path[j] = Reference_Path[i];
              Path_Speed[j] = Reference_Path_Speed[i];
              if (i<8) i++;
              j++;
            }

          }
    }
  }

  if (((System_Word & 0x1)&&!(System_Word & 0x2)) )//��������
  {
      j = 0;
      if (k > 0) k = -k;

    if (Current_Door_Position < Reference_Path[0]) {while (j<=8) {Path[j] = Reference_Path[0]; j++;}} // �������� �� ������� ������� �������� ���������
        else
        {
          if (Current_Door_Position > Reference_Path[8]) {while (j<=8) {Path[j] = Reference_Path[8]; j++;}}// �������� �� ������� ������� �������� ���������
              else
              {
                j = 8;
                i = 8;
                while ( (i >=0)&&(Current_Door_Position<(Reference_Path[i]+1)) ) i--;
                Path[j] = Current_Door_Position; // ������������� ��������� ������ ����� ������� �������
                Path_Speed[j--] = 0;
                do
                {
                  if ((Path[j]<x2)||((y1-y2-k*x1+k*x2)==0)||(Path_Speed[j] > y2 )) i--; // ��� ������ ������ ������ ������� �� ����������� ����������� �������� ����� ��� ������� ���� ����� ����������� ����� �� ��������� ��������� ����� ���� ����� �����������(������� � ������������ ����������)

                  Path[j] = -(x1*y2-x2*y1-x1*y3+x2*y3+k*x1*x3-k*x2*x3)/(y1-y2-k*x1+k*x2);//����������� ����� ������� � � ������������ ����� ������� ���������� �����
                  Path_Speed[j] = k*( Path[j] - x3)+y3; // ������ �������� � ���������� ����� ��������

                }while ((Path[j]<x2)&&(i>0)&&(Path_Speed[j])>Reference_Path[i]); // �������� ��� ����������� ����� ����� �� ������������ ����� ���������� �������.
                j--; // � j ����� ��������� ����� ��� ����������� � i ����� ������� �����
                while (j>=0)
                {
                  Path[j] = Reference_Path[i];
                  Path_Speed[j] = Reference_Path_Speed[i];
                  if (i>0) i--;
                  j--;
                }
              }
        }

  }


  v->Out = i;
  v->Out1 = Path[*v->In];

}
