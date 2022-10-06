
#define State1 1
#define State2 2
#define State3 3
#define State4 4
#define State5 5
#define State6 6
#define State7 7
#define State8 8
#define State9 9
#define State10 10
#define State11 11
#define State12 12
#define State13 13
#define State14 14


#define State15 15
#define State16 16

  #define  DC      (InArr[0] )
  #define  LD      InArr[1]
  #define  SM_C    InArr[2]
  #define  AM_CP    InArr[3]
  #define  AM_OP    InArr[4]
  #define  SM_O    InArr[5]
  #define  DM_O    InArr[6]
  #define  DO      (InArr[7] )
  #define  E_CL    InArr[17]
  #define  E_OP    InArr[18]
  #define  Vlockh    InArr[19]
  #define  V_Reach InArr[20]
  #define  ENTER_VKZ_REACH InArr[21]

#define AM_C (AM_CP*(v->Len-DO-DC-LD-SM_C-SM_O-DM_O)/100)
#define AM_O (AM_OP*(v->Len-DO-DC-LD-SM_C-SM_O-DM_O)/100)

  #define  Vsyn    InArr[8]
  #define  Vmin    InArr[9]
  #define  Vmax    InArr[10]

  #define  Fhld    InArr[11]
  #define  Fmin    InArr[12]
  #define  Fmax    InArr[13]
  #define  RVMIgnoreArea InArr[14] + LD



  #define inSB1 *v->CC & 0x1
  #define inSB2 *v->CC & 0x2

  #define inCcmd (*v->CC & 0x4)>>2
  #define inOcmd (*v->CC & 0x8)>>3

   #define inAPP (*v->CC & 0x10)>>4

  #define inpFRVM (*v->CC & 0x20)>>5
  #define inFRVM v->FReVM
  #define SW0RDY 0x1 // shift 0
  #define SW1LEN 0x2 // shift 1
  #define SW2IE  0x4  // shift 2
  #define SW3APP 0x8 // shift 3
  #define SW4CL  0x10  // shift 4
  #define SW5OP  0x20 // shift 5
  #define SW6VKO  0x40 // shift 6
  #define SW7VKZ  0x80 // shift 7
  #define SW8RVM  0x100 // shift 8
  #define SW9STP  0x200 // shift 9
  #define SW10BLCK  0x400 // shift 10
  #define SW11OM  0x800 // shift 11
  #define SW12CMDLDT  0x1000 // shift 12
  #define SW13SPDIVLDG  0x2000 // shift 13
  #define SW14FRVMLDG  0x4000 // shift 14


  #define ERCMD 0xFFFFFFCF;

  #define CLCMD ((v->SW & SW4CL)>>4)
  #define OPCMD ((v->SW & SW5OP)>>5)
  #define APPCMD ((v->SW & SW3APP)>>3)
  #define STOPED ((v->SW & SW9STP)>>9)
  #define BLOCKED ((v->SW & SW10BLCK)>>10)

  #define _Len_Min 300
  #define _Len_Max 2000
  #define VKOAREA (v->Len - DO )
  #define VKZAREA (DC)


  //REG MAP
// bit     mean
//0,1      PrevCMD
//2        INIT ZERO FOUND(IZF)
//3      BREAKING
//4     INIT LENTH SERCH (ILS)
//5     POSITION RESETED

#define PCMD (v->REG & 0x3)
#define IZFf (v->REG & 0x4)
#define BrFl (v->REG & 0x8)
#define ILSf (v->REG & 0x10)
#define RPF   (v->REG & 0x20)
#define PrevEnPWMFlag (v->REG & 0x40)
#define IZF ((v->REG & 0x4)>>2)
#define ILS ((v->REG & 0x10)>>4)
#define BREAKING ((v->REG & 0x8)>>3)
#define PrevEnPWM (PrevEnPWMFlag>>6)

static void PATH     (BLOCK_STRUCT *v, long *Arr, long *InArr);
static void OUTWRITE (BLOCK_STRUCT *v, long *OutArr, long *InArr);
static void MODE     (BLOCK_STRUCT *v, long *InArr);
static void WORD     (BLOCK_STRUCT *v, long *OutArr, long *InArr);
static void INREAD   (BLOCK_STRUCT *v, long *InArr);
static void TIMERS   (BLOCK_STRUCT *v, long *OutArr, long *InArr);
static void OUTINIT  (BLOCK_STRUCT *v)                           ;


// Do not initialize inputs!


//#define ENTER_VKZ_REACH (RVMIgnoreArea)
#define ENTER_VKO_REACH (v->Len - InArr[15])
#define Reach_Cur  InArr[16]
#define EXIT_VKZ  VKZAREA
#define EXIT_VKO  VKOAREA

  static int LockFlag = 0;

//For COMMAND
#define Reach_Open 1
#define Reach_Close 2
#define RP_Config 3
#define VKO_INIT 4
#define VKZ_INIT 5
#define Reach_END 6
//For RP_State
#define RP_On 1
#define RP_Off 2


  static int VKOpos = 9999;
  static int VKZpos = 9999;
  static int Vminh = 0;
  static int Vmaxh = 0;
void Init(void)
{
OUTINIT(v);
}

void Exec(void)
    {

      long *InArr  = (long *)(*v->Par);
      long *OutArr = (long *)(*v->Ref);

      static short inFRVMPT    = 0;

      if ((labs(*v->CS)>0 ) && (labs(*v->CS)<2 )) *v->CS = 2;


     if (*v->R)
      {
         v->SW = 0;
         v->RS = 1;
        }
     else
      {
          WORD(v, OutArr, InArr);
        }

        if (v->SW & SW0RDY )
        {
         inFRVMPT  += (inpFRVM) ? ( (inFRVMPT  < v->PTM)? 1:0 ) : ( (inFRVMPT  < 1)   ? 0 : -1 );
         if ((inFRVMPT >= v->PTM/2 )&& (*v->CP > DC+LD+SM_C) && (v->SW & SW2IE) ) inFRVM = 1;
         if (inFRVM && v->VKO &&(inFRVMPT < v->PTM/2 ) ) inFRVM = 0;



      MODE(v, InArr);

      PATH(v, OutArr, InArr);

      OUTWRITE(v, OutArr, InArr);



        }
        else
        {
         v->SW = 0;
         OUTINIT(v);
         v->Len = 0;
         v->REG = 0;
         v->CFT = 0;
         return;
        }


    }

static void OUTINIT (BLOCK_STRUCT *v)
{
  v->VKZ = 0; v->VKO = 0; v->RVM= 0; v->RS = 1;  v->SW = 0;  v->DR = 0; v->FR = 50; v->REG = 0;  ; return;
}

 static void INREAD (BLOCK_STRUCT *v, long *InArr)
    {
     static short SB1PT    = 0;
     static short SB2PT    = 0;
     static short SB12PT   = 0;
     static short inCcmdPT = 0;
     static short inOcmdPT = 0;
     static short inAppPT  = 0;
     static int PRTIME     = 0;
     static int SB1ProtectTimer = 0;
     static int SB2ProtectTimer = 0;
     static const int protectSBFaultTime_2m = 600000;

     if (CLCMD != (v->REG&0x1)    ) v->REG ^= 0x1;
     if (OPCMD != (v->REG&0x2)>>1 ) v->REG ^= 0x2;

     v->SD =(_IQtoIQ(*v->CSS,20,0) / 4)>150 ?  150 :( _IQtoIQ(*v->CSS,20,0) / v->div );
     if (labs(v->SD) > 200)  v->SD = 200; else v->SD = v->SD;

     if (_IQtoIQ(*v->CSS,20,0)!=0)  v->SD *= v->DR; else v->SD = 0;



     inAppPT  += (inAPP) ? ( (inAppPT  < v->PTM)? 1:0 ) : ( (inAppPT  < 1)   ? 0 : -1 );
     inOcmdPT += (inOcmd)? ( (inOcmdPT < v->PTM)? 1:0 ) : ( (inOcmdPT < 1)   ? 0 : -1 );
     inCcmdPT += (inCcmd)? ( (inCcmdPT < v->PTM)? 1:0 ) : ( (inCcmdPT < 1)   ? 0 : -1 );
     SB1PT    += (inSB1) ? ( (SB1PT    < v->PTM)? 1:0 ) : ( (SB1PT    < 1)   ? 0 : -1 );
     SB2PT    += (inSB2) ? ( (SB2PT    < v->PTM)? 1:0 ) : ( (SB2PT    < 1)   ? 0 : -1 );

     SB1ProtectTimer    += (inSB1) ? ( (SB1ProtectTimer    < protectSBFaultTime_2m)? 1:0 ) : ( (SB1ProtectTimer    < 1)   ? 0 : -1 );
     SB2ProtectTimer    += (inSB2) ? ( (SB2ProtectTimer    < protectSBFaultTime_2m)? 1:0 ) : ( (SB2ProtectTimer    < 1)   ? 0 : -1 );


     if ((SB1ProtectTimer < (protectSBFaultTime_2m /2)) || (SB2ProtectTimer < (protectSBFaultTime_2m /2)))                           // ???? ?????? ????????
     SB12PT   += (inSB2 && inSB1) ? ( (SB12PT    < v->PTM)? 1:0 ) : ( (SB12PT    < 1)   ? 0 : -1 );

     if ((inAppPT >= ((v->PTM/2)))                      != APPCMD) v->SW ^=SW3APP; // APP to SW


     if ( (( inCcmdPT >= (v->PTM/2)) && !(inFRVM || v->RVM)&&((v->SW & SW7VKZ) == 0)) != CLCMD ) v->SW ^=SW4CL; // CLOSE to SW
     if ( (( inOcmdPT >= (v->PTM/2))                       &&((v->SW & SW6VKO) == 0)) != OPCMD ) v->SW ^=SW5OP; // OPEN to SW

     if (  ( ( inOcmdPT >= (v->PTM/2))  && ( inCcmdPT >= (v->PTM/2)) ) ) v->SW &= ERCMD;  // OD & ZD ot stancii i net SB1 ili SB2 - to trem comandy

     if ((SB1PT < protectSBFaultTime_2m /2) || (SB2PT < protectSBFaultTime_2m /2))
      {

         if ((SB1PT  >= (v->PTM/2)) ||(SB2PT  >= (v->PTM/2)) )
        {
             if (( ((SB1PT  >= (v->PTM/2)) && (SB2PT  < (v->PTM/2))) &&((v->SW & SW7VKZ) == 0)) != CLCMD) // nagata knopka SB1, net SB1 i net VKZ
          {
                 v->SW &= ERCMD;              // snyat' vse comandy
                 if ((v->SW & SW7VKZ) == 0) v->SW ^=SW4CL;               // postavit' zacrit'
                }
                if (( ((SB2PT  >= (v->PTM/2)) && (SB1PT  < (v->PTM/2))) ) != OPCMD)  // nagata knopka SB2, net SB1 i net VKO
        {
                 v->SW &= ERCMD;              // snyat' vse comandy
                 if ((v->SW & SW6VKO) == 0) v->SW ^=SW5OP;              // postavit' otcrit'
                }
            }
            if ((SB2PT >= (v->PTM/2)))
      {   // sbros RVM esli otkrit ot knopki
             v->RVM = 0;
             inFRVM = 0;
             v->SW &= 0xFFFFFBFF;
            }

        }
         if (v->RVM)
        {
         v->SW &= ~SW4CL;
         }

        if (inFRVM)
        {
       v->SW &= ERCMD;
         v->SW |=SW5OP;
         }

     /* *************************
        MANUAL RESET
     ************************** */
     if (((SB1PT < protectSBFaultTime_2m /2) || (SB2PT < protectSBFaultTime_2m /2)))
        {
         if (SB12PT  >= (v->PTM/2)) PRTIME += (PRTIME < _IQ24(2.0) ) ? v->SampleTime : 0; else PRTIME = 0;
         if (( PRTIME >= _IQ24(1.5) )||((v->Len <= _Len_Min )&&((v->SW & SW2IE)>>2)))
            {
             v->SW = 0; PRTIME = 0;
             if (v->Len != 0) v->Flag = 1;
             v->Len = 0;
             v->OldLen = 0;
            }

        }

        if (v->Reset_Init == 1) // åñëè óñòàíîâëåí ôëàã Reset_Init ñáðîñ ïðîªìà
        {
         v->SW = 0; PRTIME = 0;
         if (v->Len != 0) v->Flag = 1;
         v->Len = 0;
         v->OldLen = 0;
         v->Reset_Init = 0;
        }



     return;
    }

static void OUTWRITE (BLOCK_STRUCT *v, long *OutArr, long *InArr)
    {
     /* *****************************
        ENDPOINTS OUT
     ****************************** */

     v->RVM = ((v->SW & SW8RVM)>>8);
     v->VKZ = ((v->SW & SW7VKZ)>>7);
     v->VKO = ((v->SW & SW6VKO)>>6);
     if (v->VKO ) v->RS = 0;

     if ( (v->VKZ && OPCMD) || (v->VKO && CLCMD)) v->SW &= -193;// ???Â?? ???µ ????????????????!! ???Â?? ???????Â???µ ???????µ?Ç???????? ?????? ?????Ç???¿?µ ?????????µ??????

     if ((v->RVM )) v->RS = 2;

     if ( !( CLCMD || OPCMD ) || (PCMD != (CLCMD + (OPCMD << 1)) ) )
        {
         v->MT = 0;
         v->ST = 0;
        }


     /* *****************************
        PVCURVE DIRECTION
     ****************************** */


     if (!BREAKING)
        {
         if CLCMD v->DR = -1;
         if OPCMD v->DR = 1;
         if ( !OPCMD && !CLCMD) v->DR = ((( v->SW & SW2IE) >>2)|| v->Reach) ? 0 : 1; // no command in init and reverse should set 1 to DR out for stand
        }
        else
        {
         if (labs(*v->CS <=5)  ) v->CFT += v->SampleTime;
         if ( v->CFT > v->CFTM )
         { v->DR = 0; v->REG = 0; v->CFT = 0;  }
         else
         v->DR = v->DR;

        }

        if ((v->RS == 2)&&(( v->SW & SW2IE) >>2)&&!(v->Reach) ) v->DR = 1;

        if ((OutArr[0] < DC )&& (( v->SW & SW2IE) >>2) ) OutArr[0] = DC;

        if ( !OPCMD && !CLCMD && v->Reach) v->DR = 1;
        return;
    }

     static void MODE ( BLOCK_STRUCT *v, long *InArr )
    {
     static int CLOSE_SAFE_CUR_TIMER = 0;
     static int Vmed = 0;
     static int A,B,C,D,E = 0;

     v->RS= ((v->SW & SW2IE)&&(!BLOCKED)&&!(v->Reach)) ? 0 : 2 ;

     if (v->SW & SW2IE)
        {
         /* *****************************
         PVCURVE MODE SPECIAL
         all function for normal work is in another functions and in RS mode setup in line above
         this state is need for RVM

         if (inFRVM) v->RVM = 1;
         else

         ****************************** */


         /*if (CLCMD && ((*v->CI > _IQtoIQ(Fmin,0,22))&&(*v->CP >0)&&(*v->CP <DC+20)))
            {
             CLOSE_SAFE_CUR_TIMER = ( (CLOSE_SAFE_CUR_TIMER <= _IQ24(100.0) )  ) ? (CLOSE_SAFE_CUR_TIMER + v->SampleTime):(CLOSE_SAFE_CUR_TIMER);
             if (CLOSE_SAFE_CUR_TIMER >= _IQ24(0.125));
            }
         else*/ CLOSE_SAFE_CUR_TIMER = 0;

         if (BLOCKED && CLCMD  )
            {
             v->RS = (v->SW & SW8RVM) ? 0 : 2;
             v->SW |= SW8RVM;
             v->SW &= 0xFFFFFFCF;
             v->REG = 0;

            }
            if ( OPCMD )
            {
             v->SW &= 0xFFFFFEFF;
             v->RS = 0;

             // if (STOPED) v->RS = 2;

            }
            if (v->SW & SW6VKO)
            {
             v->SW &= 0xFFFFFAFF; // ???????Â???µ ?Ä?¿?????? ?±?¿????????????????
            }
        }
        else
    {
      /* *****************************
      INIT MODE
      commands forimng later, this state is need for normal work control and switch STATE WORD SW
      ****************************** */


      if (v->SW & SW8RVM)
      {
      v->SW &= ~SW7VKZ;
      v->SW &= ~CLCMD;
      }

      if (OPCMD)
      {
      v->SW &= ~SW8RVM;
      v->REG &= ~0x80;
      }

      if (CLCMD && STOPED && (labs(*v->CI) > _IQtoIQ(E_CL,0,22)))   // (*v->CI > v->VKZInitCur))
      {
        if ((v->REG & 0x40) )VKZpos = *v->Pos_No_reset;
        if ((v->REG & 0x4) == 0) // ?????? ?????? ??????? ?????????
        {
          v->REG |=0x4;
          v->RP = 1;
          return;
        }
        if ( ( (*v->CP >= -7 )&&(*v->CP <= 7 )&&((v->RP == 1) ||(v->REG & 0x10))) )
        {
          v->RP = 0;
          v->SW |= SW7VKZ;
          if (!(v->REG & 0x40) )VKZpos = *v->Pos_No_reset;
          v->REG |= 0x10; //???? ??? ????? ????????
          v->REG |= 0x20; // ???? ???????
          return;
        }
      }
      if (OPCMD && STOPED && (labs(*v->CI) > _IQtoIQ(E_OP,0,22) ))   //(*v->CI > v->VKOInitCur ))
      {
        v->SW |= SW6VKO;
        VKOpos = *v->Pos_No_reset;
        v->REG |= 0x40; //???? ? ????????
      }

      if ((v->REG & 0x40) && (v->REG & 0x20))
      {
        v->Len = labs(VKOpos - VKZpos);

        if (v->OldLen !=0 ) // ???? ??????????? ????????? ??????
        {
          if ((v->Len < v->OldLen+v->OLRANGE)&&(v->Len > v->OldLen-v->OLRANGE) )// ?????? ? ????????
          {
            v->SW |= SW1LEN; // LENGHT set
            //v->REG &= ~0x80;
          }
          else
          {
            v->REG |= 0x80; //?????????? ???? ??? ?? ?? ?????? ? ?????????? ?????? ? ??????
            v->SW &= ~SW6VKO;
            v->SW &= ~SW7VKZ;
            v->SW|= SW8RVM;

            v->Len = 0;
            v->REG &= ~0x20;
            v->REG &= ~0x10;
            v->REG &= ~0x40;
            v->REG &= ~0x4;
                    }
        }
        else // ????? ?????????
        {
          if ((v->Len >= _Len_Min )&&(v->Len<=_Len_Max)) v->SW |= SW1LEN; // LENGHT set
          else
          {
            v->REG &= ~0x20;
            v->REG &= ~0x40;
            v->REG &= ~0x4;
          }
        }

        if ((v->SW & SW1LEN))
        {
          v->RS = 0; v->RP = 0;   v->SW |= SW2IE;
          if (v->OldLen < _Len_Min  )     v->OldLen = v->Len;

          if ((v->Len - LD  ) > (1200  ) )   {Vmax = 580; Vmed = 220; }
          else if ((v->Len - LD  ) > (1000  ) )   {Vmax = 540; Vmed = 210; }
          else if ((v->Len - LD  ) > (900   ) )   {Vmax = 515; Vmed = 203; }
          else if ((v->Len - LD  ) > (800  ) )    {Vmax = 490; Vmed = 197; }
          else if ((v->Len - LD  ) > (750  ) )    {Vmax = 475; Vmed = 192; }
          else if ((v->Len - LD  ) > (700  ) )    {Vmax = 460; Vmed = 190; }
          else if ((v->Len - LD  ) > (600  ) )    {Vmax = 430; Vmed = 182; }
          else if ((v->Len - LD  ) > (550  ) )    {Vmax = 410; Vmed = 180; }
          else if ((v->Len - LD  ) > (500  ) )    {Vmax = 390; Vmed = 178; }
          else if ((v->Len - LD  ) > (470  ) )    {Vmax = 380; Vmed = 168; }
          else if ((v->Len - LD  ) > (450  ) )    {Vmax = 365; Vmed = 164; }
          else if ((v->Len - LD  ) > (400  ) )    {Vmax = 330; Vmed = 154; }
          else if ((v->Len - LD  ) > (350  ) )    {Vmax = 250; Vmed = 130; }
          else if ((v->Len - LD  ) > (325  ) )    {Vmax = 240; Vmed = 127; }
          else                                    {Vmax = 220; Vmed = 125; }


          if (v->VminCalc)
          {
            A = LD + SM_C;
            B = DM_O+SM_O;
            D = AM_C;
            E = AM_O;
            C = v->Len - DC - DO - A - B - D - E;
            Vmin = (Vmed * v->Len - Vmax * (C+D+E))/(A+B-D-E);
            if (Vmin < 50) Vmin = 50;
          }

          if (Vmin > Vmax ) Vmin = Vmax;
          Vmaxh = v->SpdDiv * Vmax/100;
          Vminh = v->SpdDiv * Vmin/100;
          v->Flag = 0;
        }
      }

    }

  }

  static void WORD (BLOCK_STRUCT *v, long *OutArr, long *InArr)
  {
    ////v->Last_State = 0;
    // static int MRT = 0; // MANUAL REVERSE TIMER
    v->SW |= SW0RDY; // READY to SW
    if (inFRVM != (v->SW & SW14FRVMLDG)) v->SW ^= SW14FRVMLDG;
    if ( ((v->Len >= _Len_Min )&&(v->Len<=_Len_Max) ) != ( (v->SW & SW1LEN)>>1) ) v->SW ^= SW1LEN; // LENGHT CHECK

    if (( v->SW & SW2IE) >>2)  //END POINT SET
    {

      if  (OPCMD &&(*v->CP >= (ENTER_VKO_REACH) )&& !( v->SW & SW6VKO)&& !v->UPOR)
      {
        v->Reach = 1;
        LockFlag = 0;
        v->COMMAND = Reach_Open;
        if (OPCMD  &&  (labs(*v->CI) >= _IQtoIQ(Reach_Cur,0,22))) // Reach Open state
        {
          v->Reach_Cur_Timer+=v->SampleTime;
        }
        else  v->Reach_Cur_Timer = 0;
        if (v->Reach_Cur_Timer >= v->NST)
        {
        v->Reach_Open_Pos = *v->CP;
        v->UPOR = 1;
        v->Reach_Cur_Timer = 0;
        }


      }


      if  (*v->CP < (EXIT_VKO-10) ) v->SW &= ~SW6VKO;

      if  (CLCMD &&(*v->CP < ENTER_VKZ_REACH )&& !( v->SW & SW7VKZ) && !v->UPOR)
      {
        v->Reach = 1;
        LockFlag = 0;
        v->COMMAND = Reach_Close;

        if (CLCMD && (labs(*v->CI) >= _IQtoIQ(Reach_Cur,0,22)) )  // Reach close state
        {
          v->Reach_Cur_Timer+=v->SampleTime;
        }
        else  v->Reach_Cur_Timer = 0;
        if (v->Reach_Cur_Timer >= v->NST)
        {
          v->Reach_Close_Pos = *v->CP;
          v->UPOR = 1;
          v->Reach_Cur_Timer = 0;
        }
      }
        if  (*v->CP > (EXIT_VKZ+10) ) v->SW &= ~SW7VKZ;

        /*if (
        (!(*v->CP >= ENTER_VKO_REACH) && !(*v->CP < ENTER_VKZ_REACH))
        ||
        ((*v->CP >= ENTER_VKO_REACH) && (CLCMD || !OPCMD))
        ||
        ((*v->CP < ENTER_VKZ_REACH) && (OPCMD || !CLCMD))
        )
        {
          v->Reach = 0;
        }*/
    }


    switch(v->COMMAND)
    {
      case Reach_Open:

    v->LockFlag_Out = 0;
      if(v->UPOR)
      {
        if(v->Reach_Open_Pos - v->Len >= v->OLRANGE)
        {
          v->Reset_Init = 1;
        }

        if(v->Reach_Open_Pos - v->Len < v->OLRANGE)
        {
          v->Len = v->Reach_Open_Pos;
        }
        v->COMMAND = VKO_INIT;
      }

      if((!OPCMD) && (!(v->SW & SW6VKO)))
      {

        if(*v->CP - v->Len >= v->OLRANGE)
        {
          v->Reset_Init = 1;
          v->COMMAND = Reach_END;
      v->LockFlag_Out = 1;
        }

        if(*v->CP - v->Len < v->OLRANGE)
        {
          if(*v->CP - v->Len >= 0)
          {
            v->Len = *v->CP;
          }
          v->COMMAND = Reach_END;
      v->LockFlag_Out = 1;
        }
        //v->Delta = labs(*v->CP - v->Len);
      }

      break;

      case Reach_Close:

    v->LockFlag_Out = 0;
      if(v->UPOR)
      {
        if(v->Reach_Close_Pos > 0)
        {
          v->COMMAND = RP_Config;
          v->RP_State = RP_On;
          v->Flag_01 = 1;
        }

        if(v->Reach_Close_Pos <= 0)
        {
          v->COMMAND = RP_Config;
          v->RP_State = RP_On;
          v->Flag_02 = 1;
        }
      }

      if(!CLCMD && !(v->SW & SW7VKZ))
      {

        if(*v->CP > 0)
        {
          v->COMMAND = Reach_END;
          v->LockFlag_Out = 1;
        }

        if(*v->CP <= 0)
        {
          v->COMMAND = RP_Config;
          v->RP_State = RP_On;
          v->Flag_02 = 1;
        }
      }

      break;

      case RP_Config:

      switch(v->RP_State)
      {
        case RP_On:

        v->RP = 1;
        v->RP_State = RP_Off;
        break;

        case RP_Off:

        v->RP = 0;
        v->RP_State = 0;
        if(v->Flag_01)
        {
          v->Len = v->Len - v->Reach_Close_Pos;
          v->Flag_01 = 0;
        }

        if(v->Flag_02)
        {
          //v->Len = v->OldLen;
          v->Flag_02 = 0;
        }
        break;
      }

      if(v->RP_State == 0)
      {
        if(v->UPOR)
        {
          v->COMMAND = VKZ_INIT;
        }
        else
        {
          v->COMMAND = Reach_END;
      v->LockFlag_Out = 1;
        }
      }

      break;

      case VKO_INIT:
      v->SW |= SW6VKO;
      v->UPOR = 0;
      v->COMMAND = Reach_END;
      break;

      case VKZ_INIT:
      v->SW |= SW7VKZ;
      v->UPOR = 0;
      v->COMMAND = Reach_END;

      //v->Last_State +=v->SampleTime;
      break;

    case Reach_END:

    v->Reach = 0;
    v->Last_State = 1;
    v->REG &= ~(0x3);
    v->COMMAND = 0;
    break;
    }



    if (!BREAKING)
    {
      INREAD(v, InArr);
      ////v->Last_State = State1;
    }

    TIMERS(v, OutArr, InArr);

    if ( ( (v->MT >= v->MMT) && (v->SW & SW2IE) ) != ( (v->SW & SW11OM)>>11) ) v->SW ^= SW11OM;
    if (  (v->ST >= v->NST)   != ( (v->SW & SW9STP)>>9) ) {v->SW ^= SW9STP; v->REG &= 0xFFFFFFF7;}

    if (v->SW & SW2IE)
    {
      /* *****************************
      BLOCK CHECK  /*
      ****************************** */
      if ( (inFRVM || ((*v->CI > _IQtoIQ(Fhld,0,22)) && (*v->CS > -v->RVMCS))) && CLCMD && !v->VKO && !v->VKZ && (*v->CP > RVMIgnoreArea)  )//&& (v->MT > _IQ24(1.0))
      {
        v->MRT = (v->MRT < _IQ24(100.0))  ? (v->MRT + v->SampleTime) : v->MRT; ///
        if ((v->MRT >= v->NST) ) v->SW |= SW10BLCK; else v->SW &= 0xFFFFFBFF;

      }
      else
      v->MRT = (v->MRT > _IQ24(0.0))  ? (v->MRT - v->SampleTime) : 0; ///

    }

    return;
  }


  static void TIMERS (BLOCK_STRUCT *v, long *OutArr, long *InArr)
  {
    /* *****************************
        MOVE TIMER
    ****************************** */
    v->MT = ( (v->MT <= _IQ24(100.0) ) && ( (CLCMD&&(!(v->SW & SW7VKZ)) )|| (OPCMD&& !(v->SW & SW6VKO)) )  ) ? (v->MT + v->SampleTime):(v->MT);

    /* *****************************
        STOP TIMER  || (CLCMD && (v->SW & SW7VKZ))  || (OPCMD && (v->SW & SW6VKO)   /*(v->MT >= _IQ24(1.0))&&
    ****************************** */

    v->ST = ( (((v->SW & SW2IE)==0) || (v->Reach == 1))&&(v->MT >= _IQ24(1.0))&& !(v->SW & SW6VKO) && !(v->SW & SW7VKZ) && ( v->ST <= _IQ24(100.0) ) && ( CLCMD || OPCMD ) && ( labs(*v->CS) < v->STPCSabs ) && (PCMD == (CLCMD + (OPCMD << 1)) ) ) ? (v->ST + v->SampleTime):(v->ST);
    if ( labs(*v->CS) >= v->STPCSabs ) v->ST = 0;
    if (v->SW & SW2IE)
    {
      if ((*v->CP <= 0+DC) || (*v->CP >= OutArr[(v->NS-1)<<1]))
      {
        v->ST = 0;
      }
    }

    if ( !( CLCMD || OPCMD ) || (PCMD != (CLCMD + (OPCMD << 1)) ) )
    {
      v->MT = 0; v->ST = 0;
    }

    return;
  }

  static void PATH (BLOCK_STRUCT *v, long *OutArr, long *InArr)
  {
    static int REFARR[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    static int Vlock = 50;
    static int PathType = 0;
    static int i,j,k = 0;



    Vlock = 50;
    if (( !((v->SW & SW2IE)>>2)  ) || ((v->Reach)&& (OPCMD || CLCMD)))
    {
      v->RS = 2;
      v->NS = 1;
      OutArr[0] = 2000;
	  if (v->Reach)
	  {
	  OutArr[1] = V_Reach;
	  }
	  else
      {
		  OutArr[1] = Vsyn;
	  }
      OutArr[16] = 2000;
      PathType = 0;


      if ((!( CLCMD || OPCMD ) || ((v->SW & SW6VKO) || (v->SW & SW7VKZ) )) && (LockFlag == 0) )
      {
          LockFlag  = *v->CP;
        if (v->SW & SW6VKO)
        {
          LockFlag -= DO ;
          ////v->Last_State = State11;
        }

          if (v->SW & SW7VKZ)
        {
          LockFlag += DC ;
          ////v->Last_State = State12;
        }

      }

      if (!( CLCMD || OPCMD ) || ((v->SW & SW6VKO) || (v->SW & SW7VKZ) ))
      {////v->Last_State = State13;
        OutArr[0] = LockFlag;
        OutArr[16] = LockFlag;
      }
      else LockFlag = 0;

      if (STOPED && OPCMD && !ILSf && !(v->REG & 0x4) )
      {////v->Last_State = State14;
        OutArr[0] = LockFlag;
        OutArr[16] = LockFlag;
      }

    }
    else
    {
      if ((v->SW & SW8RVM)&& (v->NS != 1))
      {

        v->NS = 1;
        v->SW &= ERCMD;
        OutArr[0] = *v->CP-(v->dhRVM);
        OutArr[1] = Vlock;
        OutArr[2] =  *v->CP-(v->dhRVM);                OutArr[3] =  Vlock;
        OutArr[4] =  *v->CP-(v->dhRVM);                OutArr[5] =  Vlock;
        OutArr[6] =  *v->CP-(v->dhRVM);                OutArr[7] =  Vlock;
        OutArr[8] =  *v->CP-(v->dhRVM);                OutArr[9] =  Vlock;
        OutArr[10] = *v->CP-(v->dhRVM);                OutArr[11] = Vlock;
        OutArr[12] = *v->CP-(v->dhRVM);                OutArr[13] = Vlock;
        OutArr[14] = *v->CP-(v->dhRVM);                OutArr[15] = Vlock;
        OutArr[16] = v->Len-DO+1;             OutArr[17] = Vlock;
        return;
      }
      if (!*v->EnPWM)
      {
        v->NS = 1;
        v->RS = 2;
        v->SW &= ERCMD;
        OutArr[0] = *v->CP;
        OutArr[1] = Vlock;
        OutArr[2] =  *v->CP;                OutArr[3] =  Vlock;
        OutArr[4] =  *v->CP;                OutArr[5] =  Vlock;
        OutArr[6] =  *v->CP;                OutArr[7] =  Vlock;
        OutArr[8] =  *v->CP;                OutArr[9] =  Vlock;
        OutArr[10] = *v->CP;                OutArr[11] = Vlock;
        OutArr[12] = *v->CP;                OutArr[13] = Vlock;
        OutArr[14] = *v->CP;                OutArr[15] = Vlock;
        OutArr[16] = v->Len-DO;             OutArr[17] = Vlock;
        return;
      }



      #define y1 REFARR[i-1]
      #define y2 REFARR[i+1]
      #define y3 0
      #define x1 REFARR[i-2]
      #define x2 REFARR[i]
      #define x3 *v->CP


      if ((PCMD == 0)&&(CLCMD || OPCMD) )
      {
        v->NS = 9;
        /* **********************************
        REFERENCE PATH
        INIT END, NO OLD CMD, HAVE NEW CMD, we are directly at END POINT
        *********************************** */
        v->RS = 0;
        REFARR[0] = DC; REFARR[1]  = Vlock;
        REFARR[16] = v->Len - DO+1;    REFARR[17] = Vlock;
        if (LD <= DC)
        {
          REFARR[2] = DC+1;
          REFARR[4] = REFARR[2]+1;
          REFARR[6] = REFARR[4] + SM_C-2;
        }
        else
        {
          REFARR[2] = LD/2;
          REFARR[4] = LD;
          REFARR[6] = REFARR[4] + SM_C;
        }
        REFARR[3] = Vlockh;  // FAST LOCK
        REFARR[5] = Vminh;  // FAST LOCK

        REFARR[7] = Vminh; // SLOW LOCK
        REFARR[8] = REFARR[6] + AM_C;  REFARR[9] = Vmaxh;  // ACC MOVE

        REFARR[14] = REFARR[16] - DM_O;  REFARR[15] = Vminh;  // ACC TO FULL OPEN
        REFARR[12] = REFARR[14] - SM_O;  REFARR[13] = Vminh;  // SLOW MOVE OPEN
        REFARR[10] = REFARR[12] - AM_O;  REFARR[11] = Vmaxh;  // ACC MOVE
        /*if(v->Flag_01 == 1)// åñëè ôëàã 01 óñòàíîâëåí ñ÷èòàåì ñ Delta ñìåùàåì âñå òî÷êè ìàññèâà.
        {////v->Last_State = State15;
        REFARR[0] = DC + v->Delta; REFARR[1]  = Vlock;
        REFARR[16] = v->Len - DO + 1 + v->Delta;    REFARR[17] = Vlock;
        if (LD <= DC){
        REFARR[2] = DC + 1 + v->Delta;
        REFARR[4] = REFARR[2] + 1 + v->Delta;
        REFARR[6] = REFARR[4] + SM_C - 2 + v->Delta;
          }
        else{
        REFARR[2] = LD/2 + v->Delta;
        REFARR[4] = LD + v->Delta;
        REFARR[6] = REFARR[4] + SM_C + v->Delta;
        }
        REFARR[3] = Vminh;  // FAST LOCK
        REFARR[5] = Vminh;  // FAST LOCK

        REFARR[7] = Vminh;  // SLOW LOCK
        REFARR[8] = REFARR[6] + AM_C + v->Delta;  REFARR[9] = Vmaxh;  // ACC MOVE

        REFARR[14] = REFARR[16] - DM_O + v->Delta;  REFARR[15] = Vminh;  // ACC TO FULL OPEN
        REFARR[12] = REFARR[14] - SM_O + v->Delta;  REFARR[13] = Vminh;  // SLOW MOVE OPEN
        REFARR[10] = REFARR[12] - AM_O + v->Delta;  REFARR[11] = Vmaxh;  // ACC MOVE
        }
          else
          {////v->Last_State = State16;
          REFARR[0] = DC; REFARR[1]  = Vlock;
            REFARR[16] = v->Len - DO+1;    REFARR[17] = Vlock;
          if (LD <= DC){
            REFARR[2] = DC+1;
            REFARR[4] = REFARR[2]+1;
             REFARR[6] = REFARR[4] + SM_C-2;
          }
          else{
            REFARR[2] = LD/2;
          REFARR[4] = LD;
           REFARR[6] = REFARR[4] + SM_C;
          }
          REFARR[3] = Vminh;  // FAST LOCK
            REFARR[5] = Vminh;  // FAST LOCK

            REFARR[7] = Vminh; // SLOW LOCK
            REFARR[8] = REFARR[6] + AM_C;  REFARR[9] = Vmaxh;  // ACC MOVE

            REFARR[14] = REFARR[16] - DM_O;  REFARR[15] = Vminh;  // ACC TO FULL OPEN
            REFARR[12] = REFARR[14] - SM_O;  REFARR[13] = Vminh;  // SLOW MOVE OPEN
            REFARR[10] = REFARR[12] - AM_O;  REFARR[11] = Vmaxh;  // ACC MOVE
          }*/


        for (i = 0; i<=17;i++)
        {
          OutArr[i] = REFARR[i];
        }

        k = 2;
        i = 0;


        /* **********************************
        SCALED PATH
        INIT END, NO OLD CMD, HAVE NEW CMD, we are not at END POINT
        *********************************** */
        if (OPCMD)
        {
          OutArr[0] = *v->CP; OutArr[1]  = Vlock;
          OutArr[16] = v->Len - DO+1;    OutArr[17] = Vlock;
          i = 2;
          j = 2;
          k = 2;

          while ((*v->CP > REFARR[i])&&(i < 16)) i+=2;

          OutArr[j] = 0; OutArr[j+1] = 0;

          do
          {
            if (((OutArr[j]>x2)    || // ?????????µ?????? ?Ç?Â?? ?????????Ç???Â?????????? ?Â???Ç???? ???µ???µ???µ?Ç?µ?????? ???µ ?????¿?????µ ?Ç?µ?? ???¿?µ???????É???? ?Â???Ç???? ?????Â??, ???µ ???Ë?????¿?????µ?Â???? ?? ???µ?????Ë?? ???Å???? ?? ????????????
            ((y1-y2-k*x1+k*x2)==0)|| // ?£???É???Â?? ???Â ???µ?¿?µ?????? ???? ?????¿??
            (OutArr[j] < 0 ) ||(OutArr[j+1] < 0)||
            (OutArr[j+1] > ((y1>=y2)? y1:y2) ))  && // ?????????µ?????? ?Ç?Â?? ?????????????Â?? ???????Ç?µ?Â?????? ???µ ?±???¿?????µ ?Ç?µ?? ???????????????¿???????? ?????????????Â?? ???Ç?????Â????
            (i<16))            //
            i+=2;            //
            OutArr[j] = -(x1*y2-x2*y1-x1*y3+x2*y3+k*x1*x3-k*x2*x3)/(y1-y2-k*x1+k*x2);//

            //if(k*( OutArr[j] - x3)+y3 < 50)
            //{
            //  OutArr[j+1] = 50; //
            //}
            //else
            //{
            OutArr[j+1] = k*( OutArr[j] - x3)+y3; //
            //}

          }
          while (((OutArr[j]>x2)||(OutArr[j] < 0 ) ||(OutArr[j+1] < 0)||(OutArr[j+1] > ((y1>=y2)? y1:y2) ) )&& (i<16)); //

          while (j<=14)
          { // ?£???????¿?µ???????µ ?????Â???????µ???????? ??????????????

            if ((j < i) && (OutArr[2] < REFARR[16] ) )
            {
              OutArr[j] = OutArr[2];
              OutArr[j+1] = OutArr[3];
            }
              else
            {
              OutArr[j] = REFARR[i];
              OutArr[j+1] = REFARR[i+1];
              if (i<=14)i+=2;
            }

            j+=2;


          }// eof ?£???????¿?µ???????µ ?????Â???????µ???????? ??????????????
        }
        if (CLCMD)
        {
          OutArr[16] = *v->CP; OutArr[17]  = Vlock; // ???¿?? ?¿???±?????? ?????????µ?????? ?????Ç?¿???????? ?Â???Ç???? ?????????? ?Â?µ?????É?µ?? ?????£???Æ????
          OutArr[0] = 0/*DC*/;    OutArr[1] = Vlock;
          i = 14;
          j = 14;
          k = -2;

          while ((*v->CP < REFARR[i])&&(i >2 )) i-=2; // ???????µ???µ?¿?µ?????µ ?±?¿???????????µ?? ?Â???Ç???? ???Â???¿???????????? ??????????????
          i+=2; // ?????????µ???Æ???? ???? ?????????????¿?µ?????µ ?????????µ??????
          do
          {

            if (((OutArr[j]<x1)    || // ?????????µ?????? ?Ç?Â?? ?????????Ç???Â?????????? ?Â???Ç???? ???µ???µ???µ?Ç?µ?????? ???µ ?????¿?????µ ?Ç?µ?? ???¿?µ???????É???? ?Â???Ç???? ?????Â??, ???µ ???Ë?????¿?????µ?Â???? ?? ???µ?????Ë?? ???Å???? ?? ????????????
            ((y1-y2-k*x1+k*x2)==0)|| // ?£???É???Â?? ???Â ???µ?¿?µ?????? ???? ?????¿??
            (OutArr[j] < 0 ) ||(OutArr[j+1] < 0)||

            (OutArr[j+1] > ((y1>=y2)? y1:y2) ))  && // ?????????µ?????? ?Ç?Â?? ?????????????Â?? ???????Ç?µ?Â?????? ???µ ?±???¿?????µ ?Ç?µ?? ???????????????¿???????? ?????????????Â?? ???Ç?????Â????
            (i>2))            //
            i-=2;            //
            OutArr[j] = -(x1*y2-x2*y1-x1*y3+x2*y3+k*x1*x3-k*x2*x3)/(y1-y2-k*x1+k*x2);//
            OutArr[j+1] = k*( OutArr[j] - x3)+y3; //

          }
          while (((OutArr[j]<x1)||(OutArr[j] < 0 ) ||(OutArr[j+1] < 0)||(OutArr[j+1] > ((y1>=y2)? y1:y2) ) )&& (i>2)); //
          while (j>0)
          { // ?£???????¿?µ???????µ ?????Â???????µ???????? ??????????????

            if ((j >= i) && (OutArr[14] > REFARR[0] ) )
            {
              OutArr[j] = OutArr[14];
              OutArr[j+1] = OutArr[15];
            }
            else
            {
              OutArr[j] = REFARR[i-2];
              OutArr[j+1] = REFARR[i-1];
              if (i>2)i-=2;
            }

            j-=2;


          }// eof ?£???????¿?µ???????µ ?????Â???????µ???????? ??????????????

        }

      }
      else
      {



    if((v->Reach == 0) && (v->Last_State == 1))
    {
      /* **********************************
          BREAK PATH
          *********************************** */

          v->SW &= ERCMD; v->REG &= 0xFFFFFFFC;

          if (labs(*v->CS) > Vminh)
          {
            v->RS = 3;
            v->NS = 1;
            v->REG |= 0x8;

            if (v->DR == 1)
            {
              OutArr[3] =  50;
              OutArr[2] =*v->CP + v->SD; //_IQtoIQ(*v->CPS,20,0)+ v->SD + ( _IQtoIQ(*v->CPS,20,0) - *v->CP) ;
              if (OutArr[2] > v->Len-DO) OutArr[2] = v->Len-DO;
              OutArr[0] =_IQtoIQ(*v->CPS,20,0);
              OutArr[1] = labs(*v->CS); //_IQtoIQ(*v->CSS,21,0)+1;
            }
            // EOF DR=1
            if (v->DR == -1)
            {
              OutArr[1] =  50;
              OutArr[0] = *v->CP + v->SD;//_IQtoIQ(*v->CPS,20,0)+ v->SD + ( _IQtoIQ(*v->CPS,20,0) - *v->CP) ;
              if (OutArr[0] < DC) OutArr[0] =  DC;
              OutArr[2] = _IQtoIQ(*v->CPS,20,0);
              OutArr[3] = labs(*v->CS);// _IQtoIQ(*v->CSS,21,0)-1;
            } // EOF DR=-1

            OutArr[4] =  0;                OutArr[5] =  0;
            OutArr[6] =  0;                OutArr[7] =  0;
            OutArr[8] =  0;                OutArr[9] =  0;
            OutArr[10] = 0;                OutArr[11] = 0;
            OutArr[12] = 0;                OutArr[13] = 0;
            OutArr[14] = 0;                OutArr[15] = 0;
            OutArr[16] = v->Len-DO;        OutArr[17] = Vsyn;

            if ((*v->En_Vandal)==1)
            {
               OutArr[3] = 50;
               OutArr[2] = *v->CP;
               OutArr[0] = *v->CP;
               OutArr[1] = 50;
               OutArr[4] =  *v->CP;                OutArr[5] =  Vlock;
               OutArr[6] =  *v->CP;                OutArr[7] =  Vlock;
               OutArr[8] =  *v->CP;                OutArr[9] =  Vlock;
               OutArr[10] = *v->CP;                OutArr[11] = Vlock;
               OutArr[12] = *v->CP;                OutArr[13] = Vlock;
               OutArr[14] = *v->CP;                OutArr[15] = Vlock;
               OutArr[16] = v->Len-DO;             OutArr[17] = Vsyn;
               v->RS = 2;
               v->NS = 1;
            } // EOF Vandal
          } // EOF Esli Reset 3
          else

          {
            v->RS = 2;
            v->NS = 1;
            OutArr[0] = *v->CP;
            OutArr[1] = Vlock;
            OutArr[2] =  *v->CP;                OutArr[3] =  Vlock;
            OutArr[4] =  *v->CP;                OutArr[5] =  Vlock;
            OutArr[6] =  *v->CP;                OutArr[7] =  Vlock;
            OutArr[8] =  *v->CP;                OutArr[9] =  Vlock;
            OutArr[10] = *v->CP;                OutArr[11] = Vlock;
            OutArr[12] = *v->CP;                OutArr[13] = Vlock;
            OutArr[14] = *v->CP;                OutArr[15] = Vlock;
            OutArr[16] =  v->Len-DO;            OutArr[17] = Vsyn;
          }

      v->Last_State = 0;
    }


        if ((PCMD != (CLCMD + (OPCMD << 1)) )  ) // && ( _IQtoIQ(*v->CSS,21,0) > 50 ) && !BREAKING
        {
          /* **********************************
          BREAK PATH
          *********************************** */

          v->SW &= ERCMD; v->REG &= 0xFFFFFFFC;

          if (labs(*v->CS) > Vminh)
          {
            v->RS = 3;
            v->NS = 1;
            v->REG |= 0x8;

            if (v->DR == 1)
            {
              OutArr[3] =  50;
              OutArr[2] =*v->CP + v->SD; //_IQtoIQ(*v->CPS,20,0)+ v->SD + ( _IQtoIQ(*v->CPS,20,0) - *v->CP) ;
              if (OutArr[2] > v->Len-DO) OutArr[2] = v->Len-DO;
              OutArr[0] =_IQtoIQ(*v->CPS,20,0);
              OutArr[1] = labs(*v->CS); //_IQtoIQ(*v->CSS,21,0)+1;
            }
            // EOF DR=1
            if (v->DR == -1)
            {
              OutArr[1] =  50;
              OutArr[0] = *v->CP + v->SD;//_IQtoIQ(*v->CPS,20,0)+ v->SD + ( _IQtoIQ(*v->CPS,20,0) - *v->CP) ;
              if (OutArr[0] < DC) OutArr[0] =  DC;
              OutArr[2] = _IQtoIQ(*v->CPS,20,0);
              OutArr[3] = labs(*v->CS);// _IQtoIQ(*v->CSS,21,0)-1;
            } // EOF DR=-1

            OutArr[4] =  0;                OutArr[5] =  0;
            OutArr[6] =  0;                OutArr[7] =  0;
            OutArr[8] =  0;                OutArr[9] =  0;
            OutArr[10] = 0;                OutArr[11] = 0;
            OutArr[12] = 0;                OutArr[13] = 0;
            OutArr[14] = 0;                OutArr[15] = 0;
            OutArr[16] = v->Len-DO;        OutArr[17] = Vsyn;

            if ((*v->En_Vandal)==1)
            {
               OutArr[3] = 50;
               OutArr[2] = *v->CP;
               OutArr[0] = *v->CP;
               OutArr[1] = 50;
               OutArr[4] =  *v->CP;                OutArr[5] =  Vlock;
               OutArr[6] =  *v->CP;                OutArr[7] =  Vlock;
               OutArr[8] =  *v->CP;                OutArr[9] =  Vlock;
               OutArr[10] = *v->CP;                OutArr[11] = Vlock;
               OutArr[12] = *v->CP;                OutArr[13] = Vlock;
               OutArr[14] = *v->CP;                OutArr[15] = Vlock;
               OutArr[16] = v->Len-DO;             OutArr[17] = Vsyn;
               v->RS = 2;
               v->NS = 1;
            } // EOF Vandal
          } // EOF Esli Reset 3
          else

          {
            v->RS = 2;
            v->NS = 1;
            OutArr[0] = *v->CP;
            OutArr[1] = Vlock;
            OutArr[2] =  *v->CP;                OutArr[3] =  Vlock;
            OutArr[4] =  *v->CP;                OutArr[5] =  Vlock;
            OutArr[6] =  *v->CP;                OutArr[7] =  Vlock;
            OutArr[8] =  *v->CP;                OutArr[9] =  Vlock;
            OutArr[10] = *v->CP;                OutArr[11] = Vlock;
            OutArr[12] = *v->CP;                OutArr[13] = Vlock;
            OutArr[14] = *v->CP;                OutArr[15] = Vlock;
            OutArr[16] =  v->Len-DO;            OutArr[17] = Vsyn;
          }

        }

      }

    }
  }





