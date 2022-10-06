  #define  DC      (InArr[0]+v->Belt)
  #define  LD      InArr[1]
  #define  SM_C    InArr[2]
  #define  AM_CP    InArr[3]
  #define  AM_OP    InArr[4]
  #define  SM_O    InArr[5]
  #define  DM_O    InArr[6]
  #define  DO      (InArr[7]+v->Belt)

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
  #define SWOoP  0x8000 // shift 15
  #define SWOoP  0x10000 // shift 16
  #define SWOoP  0x20000 // shift 17
  #define SWOoP  0x40000 // shift 18


  #define ERCMD 0xFFFFFFCF;

  #define CLCMD ((v->SW & SW4CL)>>4)
  #define OPCMD ((v->SW & SW5OP)>>5)
  #define APPCMD ((v->SW & SW3APP)>>3)
  #define STOPED ((v->SW & SW9STP)>>9)
  #define BLOCKED ((v->SW & SW10BLCK)>>10)

  #define _Len_Min 170
  #define _Len_Max 2000
  #define VKOAREA (v->Len - DO -2)
  #define VKZAREA (DC+5+v->OFFSET)


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
#define IZF ((v->REG & 0x4)>>2)
#define ILS ((v->REG & 0x10)>>4)
#define BREAKING ((v->REG & 0x8)>>3)

static void PATH     (BLOCK_STRUCT *v, long *Arr, long *InArr);
static void OUTWRITE (BLOCK_STRUCT *v, long *OutArr, long *InArr);
static void MODE     (BLOCK_STRUCT *v, long *InArr);
static void WORD     (BLOCK_STRUCT *v, long *OutArr, long *InArr);
static void INREAD   (BLOCK_STRUCT *v, long *InArr);
static void TIMERS   (BLOCK_STRUCT *v, long *OutArr, long *InArr);
static void OUTINIT  (BLOCK_STRUCT *v)                           ;


// Do not initialize inputs!




void Init(void)
{
OUTINIT(v);
}

void Exec(void)
{

long *InArr  = (long *)(*v->Par);
long *OutArr = (long *)(*v->Ref);
  static short inFRVMPT    = 0;
if ((_IQabs(*v->CS)>0 ) && (_IQabs(*v->CS)<2 )) *v->CS = 2;


if (*v->R)
  v->SW = 0;
else

WORD(v, OutArr, InArr);

if (v->SW & SW0RDY )
{
inFRVMPT  += (inpFRVM) ? ( (inFRVMPT  < v->PTM)? 1:0 ) : ( (inFRVMPT  < 1)   ? 0 : -1 );
if ((inFRVMPT >= v->PTM/2 )&& (*v->CP > DC+v->OFFSET+LD+SM_C) && (v->SW & SW2IE) ) inFRVM = 1;
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
      v->OFFSET = 0;


    v->CFT = 0;
      for (v->i = 0; v->i<=17; v->i++) OutArr[v->i] =0;  v->i = 0;
    return;
}
/*if (CLCMD != (v->REG&0x1)    ) v->REG ^= (v->REG&0x1);
if (OPCMD != (v->REG&0x2)>>1 ) v->REG ^= (v->REG&0x2);*/

}

static void OUTINIT (BLOCK_STRUCT *v)
{
  v->VKZ = 0; v->VKO = 0; v->RVM= 0; v->SW = 0;  v->DR = 0; v->FR = 50; v->REG = 0; v->OFFSET = 0 ; return;
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


  if (CLCMD != (v->REG&0x1)    ) v->REG ^= 0x1;
  if (OPCMD != (v->REG&0x2)>>1 ) v->REG ^= 0x2;

  v->SD =(_IQtoIQ(*v->CSS,20,0) / 4)>150 ?  150 :( _IQtoIQ(*v->CSS,20,0) / v->div );
   if (_IQabs(v->SD) > 200)  v->SD = 200; else v->SD = v->SD;

  if (_IQtoIQ(*v->CSS,20,0)!=0)  v->SD *= v->DR; else v->SD = 0;


  inAppPT  += (inAPP) ? ( (inAppPT  < v->PTM)? 1:0 ) : ( (inAppPT  < 1)   ? 0 : -1 );
  inOcmdPT += (inOcmd)? ( (inOcmdPT < v->PTM)? 1:0 ) : ( (inOcmdPT < 1)   ? 0 : -1 );
  inCcmdPT += (inCcmd)? ( (inCcmdPT < v->PTM)? 1:0 ) : ( (inCcmdPT < 1)   ? 0 : -1 );
  SB1PT    += (inSB1) ? ( (SB1PT    < v->PTM)? 1:0 ) : ( (SB1PT    < 1)   ? 0 : -1 );
  SB2PT    += (inSB2) ? ( (SB2PT    < v->PTM)? 1:0 ) : ( (SB2PT    < 1)   ? 0 : -1 );

  v->Out=inAppPT;
  v->Out1=inOcmdPT;
  v->Out2=inCcmdPT;
  v->Out3=SB1PT;
  v->Out4=SB2PT;


  SB12PT   += (inSB2 && inSB1) ? ( (SB12PT    < v->PTM)? 1:0 ) : ( (SB12PT    < 1)   ? 0 : -1 );





  if ((inAppPT >= v->PTM/2)                      != APPCMD) v->SW ^=SW3APP; // APP to SW


  if ( ((((SB1PT  >= v->PTM/2) && ((SB2PT  < v->PTM/2))) || (inCcmdPT >= v->PTM/2) )&& !(inFRVM)&&((v->SW & SW7VKZ) == 0)) != CLCMD ) v->SW ^=SW4CL; // CLOSE to SW

  if ( ((((SB2PT  >= v->PTM/2) && ((SB1PT  < v->PTM/2))) || (inOcmdPT >= v->PTM/2))&&(v->SW & SW6VKO) == 0 ) != OPCMD ) v->SW ^=SW5OP; // OPEN to SW




  if ( ((inOcmdPT || SB2PT ) && CLCMD) || ((inCcmdPT || SB1PT )&& OPCMD) ) v->SW &= ERCMD;
  if ((SB2PT >= v->PTM/2)) {v->RVM = 0; inFRVM = 0; v->SW &= 0xFFFFFBFF;}//||(SB1PT >= v->PTM/2)

  /*if ((SB2PT >= v->PTM/2) && !(OPCMD)) {v->SW &= 0xFFFFFBFF; v->SW |= SW5OP;}
  if ((SB1PT >= v->PTM/2) && !(CLCMD)) {v->SW &= 0xFFFFFBFF; v->SW |= SW4CL;}*/


 // if (CLCMD && OPCMD   )    v->SW &= ERCMD; //INCORRECT COMMAND*/

     if (inFRVM)
  {    v->SW &= ERCMD;
      v->SW |=SW5OP;

  }

 /* *****************************
        MANUAL RESET
  ****************************** */

  if (SB12PT  >= v->PTM/2) PRTIME += (PRTIME < _IQ24(2.0) ) ? v->SampleTime : 0; else PRTIME = 0;
  if (( PRTIME >= _IQ24(1.5) )||((v->Len <= _Len_Min )&&((v->SW & SW2IE)>>2)))
  {
  v->SW = 0; PRTIME = 0;
  if (v->Len != 0) v->Flag = 1;
  v->Len = 0;
  v->OldLen = 0;





  }




 return;
}

static void OUTWRITE (BLOCK_STRUCT *v, long *OutArr, long *InArr)
{
     /* *****************************
        ENDPOINTS OUT
  ****************************** */




if ((v->SW & SW6VKO)&& !v->VKZ && v->NS == 1 && !(CLCMD || OPCMD)  )v->RS = 3;
if (v->VKO ) v->RS = 0;
  //if (CLCMD) v->SW &= 0xFFFFFFBF;
 // if (OPCMD) v->SW &= 0xFFFFFF7F;
  v->RVM = ((v->SW & SW8RVM)>>8);
  v->VKZ = ((v->SW & SW7VKZ)>>7);
  v->VKO = ((v->SW & SW6VKO)>>6);

   if ( (v->VKZ && OPCMD) || (v->VKO && CLCMD)) v->SW &= -193;

  if ((v->RVM )) v->RS = 2;

 if ( !( CLCMD || OPCMD ) || (PCMD != (CLCMD + (OPCMD << 1)) ) )  { v->MT = 0; v->ST = 0; }


  /* *****************************
        PVCURVE DIRECTION
  ****************************** */


 if (!BREAKING)
{
if CLCMD v->DR = -1;
if OPCMD v->DR = 1;

if ( !OPCMD && !CLCMD) v->DR = (( v->SW & SW2IE) >>2) ? 0 : 1; // no command in init and reverse should set 1 to DR out for stand

}
else
{
if (_IQabs(*v->CS <=5)  ) v->CFT += v->SampleTime;
if (v->CFT > _IQ24(0.125))
{ v->DR = 0; v->REG = 0; v->CFT = 0;  }
else
v->DR = v->DR;
}
//if (BLOCKED && ( !OPCMD && !CLCMD)) v->DR = 1;
// �������� ��
if ((v->RS == 2)&&(( v->SW & SW2IE) >>2) ) v->DR = 1;




v->FR = (v->MT < _IQ24(0.35) ) ? Fmax: Fmin;

if (STOPED ) v->FR = Fhld;
if (OPCMD) v->FR = (v->MT < _IQ24(6.0) ) ? Fmax : Fmin;
//if (OPCMD && (v->MT > _IQ24(1.0)) &&  !((v->SW & SW2IE)>>2)  ) v->FR = Fhld;

if (v->VKO && OPCMD ) v->FR = Fmin;
if(v->VKZ && CLCMD) v->FR = Fmin;





//if (!OPCMD && !CLCMD) {OutArr[17] = Vmax; OutArr[1] = Vmax;}
if ((OutArr[0] < DC + v->OFFSET )&& (( v->SW & SW2IE) >>2) ) OutArr[0] = DC + v->OFFSET;
 return;
}

static void MODE ( BLOCK_STRUCT *v, long *InArr )
{
static int CLOSE_SAFE_CUR_TIMER = 0;
static int Vmed = 0;
static int A,B,C,D,E = 0;

  v->RS= ((v->SW & SW2IE)&&(!BLOCKED)) ? 0 : 2 ;

  if (v->SW & SW2IE)
  {
    /* *****************************
        PVCURVE MODE SPECIAL
        all function for normal work is in another functions and in RS mode setup in line above
        this state is need for RVM


    if (inFRVM) v->RVM = 1;
 else

    ****************************** */


if (CLCMD && ((*v->CI > _IQtoIQ(Fmin,0,22)/v->HtoA)&&(*v->CP >0)&&(*v->CP <DC+20)))
{
CLOSE_SAFE_CUR_TIMER = ( (CLOSE_SAFE_CUR_TIMER <= _IQ24(100.0) )  ) ? (CLOSE_SAFE_CUR_TIMER + v->SampleTime):(CLOSE_SAFE_CUR_TIMER);
if (CLOSE_SAFE_CUR_TIMER >= _IQ24(0.125)) v->OFFSET = *v->CP + 1;
}
else CLOSE_SAFE_CUR_TIMER = 0;

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
v->SW &= 0xFFFFFBFF;
  v->OFFSET = 0;
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

    if (CLCMD && STOPED && (*v->CI > v->VKZInitCur))
    {
if ((v->REG & 0x40) )v->VKZpos = *v->Pos_No_reset;
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

      if (!(v->REG & 0x40) )v->VKZpos = *v->Pos_No_reset;
      v->REG |= 0x10; //???? ??? ????? ????????
      v->REG |= 0x20; // ???? ???????


           return;
         }


    }
    if (OPCMD && STOPED && (*v->CI > v->VKOInitCur))
    {
      v->SW |= SW6VKO;
      v->VKOpos = *v->Pos_No_reset;
      v->REG |= 0x40; //???? ? ????????


    }

    if ((v->REG & 0x40) && (v->REG & 0x20))
    {
     v->Len = abs(v->VKOpos - v->VKZpos);
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

               if ((v->Len - LD  ) > (1200-v->Belt ) )   {Vmax = 580; Vmed = 220; }
          else if ((v->Len - LD  ) > (1000-v->Belt ) )   {Vmax = 540; Vmed = 210; }
          else if ((v->Len - LD  ) > (900 -v->Belt ) )   {Vmax = 515; Vmed = 203; }
          else if ((v->Len - LD  ) > (800-v->Belt ) )    {Vmax = 490; Vmed = 197; }
          else if ((v->Len - LD  ) > (750-v->Belt ) )    {Vmax = 475; Vmed = 192; }
          else if ((v->Len - LD  ) > (700-v->Belt ) )    {Vmax = 460; Vmed = 190; }
          else if ((v->Len - LD  ) > (600-v->Belt ) )    {Vmax = 430; Vmed = 182; }
          else if ((v->Len - LD  ) > (550-v->Belt ) )    {Vmax = 410; Vmed = 180; }
          else if ((v->Len - LD  ) > (500-v->Belt ) )    {Vmax = 390; Vmed = 178; }
          else if ((v->Len - LD  ) > (470-v->Belt ) )    {Vmax = 380; Vmed = 168; }
          else if ((v->Len - LD  ) > (450-v->Belt ) )    {Vmax = 365; Vmed = 164; }
          else if ((v->Len - LD  ) > (400-v->Belt ) )    {Vmax = 330; Vmed = 154; }
          else if ((v->Len - LD  ) > (350-v->Belt ) )    {Vmax = 250; Vmed = 130; }
          else if ((v->Len - LD  ) > (325-v->Belt ) )    {Vmax = 240; Vmed = 127; }
          else                                           {Vmax = 220; Vmed = 125; }




if (v->VminCalc){
         A = LD + SM_C;
         B = DM_O+SM_O;
         D = AM_C;
         E = AM_O;
         C = v->Len - DC - DO - A - B - D - E;

         Vmin = (Vmed * v->Len - Vmax * (C+D+E))/(A+B-D-E);

        if (Vmin < 50) Vmin = 50;

}
        if (Vmin > Vmax ) Vmin = Vmax;
        Vmax = v->SpdDiv * Vmax/100;
        Vmin = v->SpdDiv * Vmin/100;

        v->Flag = 0;
        }
    }







  }

}

static void WORD (BLOCK_STRUCT *v, long *OutArr, long *InArr)
{
// static int MRT = 0; // MANUAL REVERSE TIMER
static int MRT2 = 0;
 v->SW |= SW0RDY; // READY to SW
 if (inFRVM != (v->SW & SW14FRVMLDG)) v->SW ^= SW14FRVMLDG;
 if ( ((v->Len >= _Len_Min )&&(v->Len<=_Len_Max) ) != ( (v->SW & SW1LEN)>>1) ) v->SW ^= SW1LEN; // LENGHT CHECK

 if (( v->SW & SW2IE) >>2)  //END POINT SET
 {
if  (*v->CP > VKOAREA ) v->SW |= SW6VKO; // if ( (*v->CP > VKOAREA ) != ( (v->SW & SW6VKO)>>6) ) v->SW ^= SW6VKO;
if  (*v->CP < VKOAREA-10 ) v->SW &= ~SW6VKO;
if  (*v->CP < VKZAREA )  v->SW |= SW7VKZ; //   if ( (*v->CP < VKZAREA ) != ( (v->SW & SW7VKZ)>>7) ) v->SW ^= SW7VKZ;
if  (*v->CP > VKZAREA+10 ) v->SW &= ~SW7VKZ;
 }


if (!BREAKING) INREAD(v, InArr);

 TIMERS(v, OutArr, InArr);

  if ( ( (v->MT >= v->MMT) && (v->SW & SW2IE) ) != ( (v->SW & SW11OM)>>11) ) v->SW ^= SW11OM;
  if (  (v->ST >= v->NST)   != ( (v->SW & SW9STP)>>9) ) {v->SW ^= SW9STP; v->REG &= 0xFFFFFFF7;}

  if (v->SW & SW2IE)
  {
   /* *****************************
        BLOCK CHECK  /*
  ****************************** */
 if ( (inFRVM || ((*v->CI > _IQtoIQ(Fhld,0,22)/v->HtoA) && (*v->CS > -v->RVMCS))) && CLCMD && !v->VKO && !v->VKZ && (*v->CP > RVMIgnoreArea)  )//&& (v->MT > _IQ24(1.0))
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

 v->ST = ( ((v->SW & SW2IE)==0)&&(v->MT >= _IQ24(1.0))&& !(v->SW & SW6VKO) && !(v->SW & SW7VKZ) && ( v->ST <= _IQ24(100.0) ) && ( CLCMD || OPCMD ) && ( _IQabs(*v->CS) < v->STPCSabs ) && (PCMD == (CLCMD + (OPCMD << 1)) ) ) ? (v->ST + v->SampleTime):(v->ST);
  if ( _IQabs(*v->CS) >= v->STPCSabs ) v->ST = 0;
  if (v->SW & SW2IE)
  {
    if ((*v->CP <= 0+DC+v->OFFSET) || (*v->CP >= OutArr[(v->NS-1)<<1]))
    {
      v->ST = 0;
    }
  }
  if ( !( CLCMD || OPCMD ) || (PCMD != (CLCMD + (OPCMD << 1)) ) )  { v->MT = 0; v->ST = 0; }


return;
}

static void PATH (BLOCK_STRUCT *v, long *OutArr, long *InArr)
{
  static int REFARR[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  static int SCALE = 0;

  static int LockFlag = 0;


  if ( !((v->SW & SW2IE)>>2)  )
{
  v->RS = 2;
  v->NS = 1;
    OutArr[0] = 2000;
    OutArr[1] = Vsyn;
    OutArr[16] = 2000;


  if ((!( CLCMD || OPCMD ) || ((v->SW & SW6VKO) || (v->SW & SW7VKZ) )) && (LockFlag == 0) )
  {
    LockFlag  = *v->CP;
  if (v->SW & SW6VKO) LockFlag -= DO ;
  if (v->SW & SW7VKZ) LockFlag += DC ;

  }
    if (!( CLCMD || OPCMD ) || ((v->SW & SW6VKO) || (v->SW & SW7VKZ) ))
    {
      OutArr[0] = LockFlag;
      OutArr[16] = LockFlag;
    }
  else LockFlag = 0;
      if (STOPED && OPCMD && !ILSf && !(v->REG & 0x4) )
  {
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
    OutArr[0] = *v->CP;
    OutArr[1] = 50;
       OutArr[2] =  *v->CP;                OutArr[3] =  50;
       OutArr[4] =  *v->CP;                OutArr[5] =  50;
       OutArr[6] =  *v->CP;                OutArr[7] =  50;
       OutArr[8] =  *v->CP;                OutArr[9] =  50;
       OutArr[10] = *v->CP;                OutArr[11] = 50;
       OutArr[12] = *v->CP;                OutArr[13] = 50;
       OutArr[14] = *v->CP;                OutArr[15] = 50;
       OutArr[16] = v->Len-DO;             OutArr[17] = 50;
return;
}
if ((*v->In == 4))
{
      v->RS = 0;
      v->NS = 9;
      v->REG = 0;
      v->SW &= ERCMD;

      OutArr[0] = *v->CP ; OutArr[1]  = 50;
      OutArr[16] = v->Len - DO - v->Belt;    OutArr[17] = 50;

      OutArr[2] = OutArr[0] + LD/2;  OutArr[3] = Vmin;  // FAST LOCK
      OutArr[4] = OutArr[2] + LD/2;  OutArr[5] = Vmin;  // FAST LOCK
      OutArr[6] = OutArr[4] + SM_C;  OutArr[7] = Vmin;  // SLOW LOCK
      OutArr[8] = OutArr[6] + AM_C;  OutArr[9] = Vmax;  // ACC MOVE

      OutArr[14] = OutArr[16] - DM_O;  OutArr[15] = Vmin;  // ACC TO FULL OPEN
      OutArr[12] = OutArr[14] - SM_O;  OutArr[13] = Vmin;  // SLOW MOVE OPEN
      OutArr[10] = OutArr[12] - AM_O;  OutArr[11] = Vmax;  // ACC MOVE
return;
}
if ((*v->In == 5))
{
      v->RS = 0;
      v->NS = 9;
      v->REG = 0;
      v->SW &= ERCMD;

      OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;


      OutArr[2] = OutArr[0] + LD/2;  OutArr[3] = Vmin;  // FAST LOCK
      OutArr[4] = OutArr[2] + LD/2;  OutArr[5] = Vmin;  // FAST LOCK
      OutArr[6] = OutArr[4] + SM_C;  OutArr[7] = Vmin;  // SLOW LOCK
      OutArr[8] = OutArr[6] + AM_C;  OutArr[9] = Vmax;  // ACC MOVE

      OutArr[16] = *v->CP-DO;    OutArr[17] = 50;
      OutArr[14] = OutArr[16] - DM_O;  OutArr[15] = Vmin;  // ACC TO FULL OPEN
      OutArr[12] = (OutArr[14]>REFARR[12]) ? (REFARR[12]) : (OutArr[14]-2) ; OutArr[13] = Vmin;
      OutArr[10] = OutArr[12] - AM_O;  OutArr[11] = Vmax;  // ACC MOVE
return;
}
  if ((PCMD == 0)&&(CLCMD || OPCMD) )
  {


    if ((*v->CP <= (DC + v->OFFSET) ) || (*v->CP >= (v->Len - DO) ))
    {
      /* **********************************
      REFERENCE PATH
      INIT END, NO OLD CMD, HAVE NEW CMD, we are directly at END POINT
      *********************************** */

      v->RS = 0;
      v->NS = 9;

      OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;
      OutArr[16] = v->Len - DO;    OutArr[17] = 50;

      OutArr[2] = LD/2;  OutArr[3] = Vmin;  // FAST LOCK
      if (OutArr[2] < OutArr[0])OutArr[2] = OutArr[0]+1;
      OutArr[4] = OutArr[2] + LD/2;  OutArr[5] = Vmin;  // FAST LOCK

      OutArr[6] = OutArr[4] + SM_C;  OutArr[7] = Vmin;  // SLOW LOCK
      OutArr[8] = OutArr[6] + AM_C;  OutArr[9] = Vmax;  // ACC MOVE

      OutArr[14] = OutArr[16] - DM_O;  OutArr[15] = Vmin;  // ACC TO FULL OPEN
      OutArr[12] = OutArr[14] - SM_O;  OutArr[13] = Vmin;  // SLOW MOVE OPEN
      OutArr[10] = OutArr[12] - AM_O;  OutArr[11] = Vmax;  // ACC MOVE

      REFARR[0] = OutArr[0]; REFARR[1] = OutArr[1];
      REFARR[2] = OutArr[2]; REFARR[3] = OutArr[3];
      REFARR[4] = OutArr[4]; REFARR[5] = OutArr[5];
      REFARR[6] = OutArr[6]; REFARR[7] = OutArr[7];
      REFARR[8] = OutArr[8]; REFARR[9] = OutArr[9];
      REFARR[10] = OutArr[10]; REFARR[11] = OutArr[11];
      REFARR[12] = OutArr[12]; REFARR[13] = OutArr[13];
      REFARR[14] = OutArr[14]; REFARR[15] = OutArr[15];
      REFARR[16] = OutArr[16]; REFARR[17] = OutArr[17];

      SCALE = 0;

    }
    else
    {
      /* **********************************
      SCALED PATH
      INIT END, NO OLD CMD, HAVE NEW CMD, we are not at END POINT
      *********************************** */
      OutArr[0] = *v->CP;  OutArr[1] = 50;

      if (OPCMD)
      {
        if (*v->CP <= REFARR[6])
        {
          SCALE = (*v->CP - REFARR[0])*1000 / (REFARR[6]- REFARR[0]);
          v->NS = 9;

          OutArr[6] = (OutArr[0]>=(REFARR[6]-10)) ? (OutArr[0]+20): REFARR[6];

          OutArr[2] = ((OutArr[0] + LD/2) > (REFARR[6] - 10)) ? (REFARR[6] - 10): (OutArr[0] + LD/2);
          OutArr[4] = ((OutArr[2] + LD/2) > (REFARR[6] - 10)) ? (REFARR[6] - 2) : (OutArr[2] + LD/2);

          OutArr[3] = ((REFARR[3]-(REFARR[3]*SCALE/1000))<Vmin) ? Vmin :(REFARR[3]-(REFARR[3]*SCALE/1000));
          OutArr[5] = ((REFARR[5]-(REFARR[5]*SCALE/1000))<Vmin) ? Vmin :(REFARR[5]-(REFARR[5]*SCALE/1000));
          OutArr[7] = ((REFARR[7]-(REFARR[7]*SCALE/1000))<Vmin) ? Vmin :(REFARR[7]-(REFARR[7]*SCALE/1000));

            OutArr[8] = OutArr[6] + AM_C;  OutArr[9] = Vmax;  // ACC MOVE
            OutArr[16] = v->Len - DO;    OutArr[17] = 50;
            OutArr[14] = OutArr[16] - DM_O;  OutArr[15] = Vmin;  // ACC TO FULL OPEN
            OutArr[12] = OutArr[14] - SM_O;  OutArr[13] = Vmin;  // SLOW MOVE OPEN
            OutArr[10] = OutArr[12] - AM_O;  OutArr[11] = Vmax;  // ACC MOVE


        }
        else
        {
          if (*v->CP <= REFARR[12])
          {
            SCALE = (*v->CP + AM_C - REFARR[10])*500 / (REFARR[12]- REFARR[10]);
            v->NS = 7;
            OutArr[10] = v->Len - DO;    OutArr[11] = 50;
            OutArr[9] = Vmin;  // ACC TO FULL OPEN
            OutArr[7] = Vmin;

            OutArr[6] = (OutArr[0] >= (REFARR[12] - 10)) ? (OutArr[0] + 20) : REFARR[12];
            OutArr[8] = ( (OutArr[10] - DM_O)<OutArr[6] ) ? OutArr[6]+1 : (OutArr[10] - DM_O);
            OutArr[4] = (OutArr[0]>=(OutArr[6]-20)) ? (OutArr[6]-5) : ( ((OutArr[6]-AM_O)>(OutArr[0]+5)) ? ( (SCALE>0) ? (OutArr[6]-(AM_O-(AM_O*SCALE/1000))) : (REFARR[10]) ) : (OutArr[6]-(OutArr[6]-OutArr[0])/2) ) ;

            OutArr[2] = ((OutArr[0]+AM_C) >(OutArr[4]-1)) ? (OutArr[4]) : (OutArr[0]+AM_C);

            OutArr[3] = (OutArr[2]<(OutArr[4]-1))? Vmax : ( ((REFARR[9]-(REFARR[9]*SCALE/1000)<Vmin) ? (Vmin) : (REFARR[9]-(REFARR[9]*SCALE/1000))) );
            OutArr[5] = OutArr[3];


       OutArr[12] = v->Len - DO;    OutArr[13] = 50;
       OutArr[14] = v->Len - DO;    OutArr[15] = 50;
       OutArr[16] = v->Len - DO;    OutArr[17] = 50;

          }
          else
          {

            SCALE = (*v->CP - REFARR[12])*1000 / (REFARR[16]- REFARR[12]);
            v->NS = 3;
            OutArr[2] = ( (OutArr[4]-DM_O) <OutArr[0]) ? (OutArr[0]+1) : (OutArr[4]-DM_O);
            OutArr[3] = ((REFARR[15]-(REFARR[15]*SCALE/1000))<50) ? 50 : (REFARR[15]-(REFARR[15]*SCALE/1000));
            OutArr[4] = v->Len - DO;    OutArr[5] = 50;


       OutArr[6] =  0;                OutArr[7] =  0;
       OutArr[8] =  0;                OutArr[9] =  0;
       OutArr[10] = 0;                OutArr[11] = 0;
       OutArr[12] = 0;                OutArr[13] = 0;
       OutArr[14] = 0;                OutArr[15] = 0;
       OutArr[16] = v->Len-DO;        OutArr[17] = 0;
          }
        }



      }
      if (CLCMD)
      {
          if (*v->CP >= REFARR[12])
          {
        v->NS = 9;
      OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;


            OutArr[2] = LD/2;  OutArr[3] = Vmin;  // FAST LOCK
      if (OutArr[2] < OutArr[0])OutArr[2] = OutArr[0]+1;
      OutArr[4] = OutArr[2] + LD/2;  OutArr[5] = Vmin;  // FAST LOCK
      OutArr[6] = OutArr[4] + SM_C;  OutArr[7] = Vmin;  // SLOW LOCK
      OutArr[8] = OutArr[6] + AM_C;  OutArr[9] = Vmax;  // ACC MOVE

      OutArr[16] = *v->CP;    OutArr[17] = 50;
      OutArr[14] = OutArr[16] - DM_O;  OutArr[15] = Vmin;  // ACC TO FULL OPEN
      OutArr[12] = (OutArr[14]>REFARR[12]) ? (REFARR[12]) : (OutArr[14]-2) ; OutArr[13] = Vmin;
      OutArr[10] = OutArr[12] - AM_O;  OutArr[11] = Vmax;  // ACC MOVE

          }
        if (*v->CP >= REFARR[6]){
          v->NS = 7;
          OutArr[0] = DC + v->OFFSET;  OutArr[1]  = 50;
          OutArr[12] = *v->CP;    OutArr[13] = 50;
      OutArr[2] = LD/2;  OutArr[3] = Vmin;  // FAST LOCK
      if (OutArr[2] < OutArr[0])OutArr[2] = OutArr[0]+1;
          OutArr[4] = OutArr[2] + LD/2;  OutArr[5] = Vmin;  // FAST LOCK

           OutArr[10] = OutArr[12] - ((OutArr[12]-OutArr[4])/3);
            OutArr[8] = OutArr[10] - ((OutArr[10]  - OutArr[4])/2);
            OutArr[6] = OutArr[8] - ((OutArr[8]  - OutArr[4])/2);

              if (*v->CP >= REFARR[8]){

                OutArr[7] = Vmin;
                OutArr[9] =((Vmax/2)>Vmin) ? Vmax/2 :Vmin; //
                OutArr[11]= Vmax*2/3;
              }// cp >ref8
              else {
              SCALE = *v->CP *100 / REFARR[8];
                OutArr[7] = Vmin;
                OutArr[9] =Vmax * SCALE /200; //
                OutArr[11]= Vmax * SCALE /200;
              }//cp<ref8


          } // cp>ref6
        else
        {

         v->NS = 4 ;
        OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;
        OutArr[6] = *v->CP;    OutArr[7] = 50;

       OutArr[4] = OutArr[6] - ((OutArr[6]  - OutArr[0])/2);
     OutArr[2] = OutArr[4] - ((OutArr[4]  - OutArr[0])/2);

     OutArr[5] = Vmin*70/100;
     OutArr[3] = 50;



       OutArr[8] =  0;                OutArr[9] =  0;
       OutArr[10] = 0;                OutArr[11] = 0;
       OutArr[12] = 0;                OutArr[13] = 0;
       OutArr[14] = 0;                OutArr[15] = 0;
       OutArr[16] = v->Len-DO;        OutArr[17] = 0;
        }
      }
    }

  }
  else
  {
        /* **********************************
        IN MOVE PATH CORRECTION

        need to know on which line OutArr we are and what is movement direction for change not used lines

      *********************************** */
      if (OutArr[16] != v->Len-DO)
    {
            v->NS = 9;

      OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;
      OutArr[16] = v->Len - DO;    OutArr[17] = 50;

      OutArr[2] = LD/2;  OutArr[3] = Vmin;  // FAST LOCK
      if (OutArr[2] < OutArr[0])OutArr[2] = OutArr[0]+1;
      OutArr[4] = OutArr[2] + LD/2;  OutArr[5] = Vmin;  // FAST LOCK
      OutArr[6] = OutArr[4] + SM_C;  OutArr[7] = Vmin;  // SLOW LOCK
      OutArr[8] = OutArr[6] + AM_C;  OutArr[9] = Vmax;  // ACC MOVE

      OutArr[14] = OutArr[16] - DM_O;  OutArr[15] = Vmin;  // ACC TO FULL OPEN
      OutArr[12] = OutArr[14] - SM_O;  OutArr[13] = Vmin;  // SLOW MOVE OPEN
      OutArr[10] = OutArr[12] - AM_O;  OutArr[11] = Vmax;  // ACC MOVE
    return;
    }




    if ((PCMD != (CLCMD + (OPCMD << 1)) )  ) // && ( _IQtoIQ(*v->CSS,21,0) > 50 ) && !BREAKING
    {
     /* **********************************
        BREAK PATH
      *********************************** */

          v->NS = 1;        v->REG |= 0x8;
    v->SW &= ERCMD; v->REG &= 0xFFFFFFFC;
       if (_IQabs(*v->CS) >30)
       {
       v->RS = 3;



  if (v->DR == 1)  {

      OutArr[3] =  50;
      OutArr[2] = _IQtoIQ(*v->CPS,20,0)+v->SD;
      if (OutArr[2] > v->Len-DO) OutArr[2] = v->Len-DO;
      OutArr[0] =*v->CP;
      OutArr[1] = _IQtoIQ(*v->CSS,21,0)+1;
  } // EOF DR=1
  if (v->DR == -1) {

      OutArr[1] =  50;
      OutArr[0] = _IQtoIQ(*v->CPS,20,0)+v->SD;
      if (OutArr[0] < DC+v->OFFSET) OutArr[0] =  DC+v->OFFSET;
      OutArr[2] = *v->CP;
      OutArr[3] = _IQtoIQ(*v->CSS,21,0)-1;
      } // EOF DR=-1

      OutArr[4] =  0;                OutArr[5] =  0;
      OutArr[6] =  0;                OutArr[7] =  0;
      OutArr[8] =  0;                OutArr[9] =  0;
      OutArr[10] = 0;                OutArr[11] = 0;
      OutArr[12] = 0;                OutArr[13] = 0;
      OutArr[14] = 0;                OutArr[15] = 0;
      OutArr[16] = v->Len-DO;        OutArr[17] = Vmax;

  if ((*v->En_Vandal)==1) {
       OutArr[3] = 50;
       OutArr[2] = *v->CP;
       OutArr[0] = *v->CP;
       OutArr[1] = 50;
       OutArr[4] =  *v->CP;                OutArr[5] =  50;
       OutArr[6] =  *v->CP;                OutArr[7] =  50;
       OutArr[8] =  *v->CP;                OutArr[9] =  50;
       OutArr[10] = *v->CP;                OutArr[11] = 50;
       OutArr[12] = *v->CP;                OutArr[13] = 50;
       OutArr[14] = *v->CP;                OutArr[15] = 50;
       OutArr[16] = v->Len-DO;              OutArr[17] = Vmax;
       v->RS = 2;
   } // EOF Vandal
} // EOF Esli Reset 3
      else
      {
      v->RS = 2;
      OutArr[0] = *v->CP;
      OutArr[1] = 50;
      OutArr[2] =  *v->CP;                OutArr[3] =  50;
      OutArr[4] =  *v->CP;                OutArr[5] =  50;
      OutArr[6] =  *v->CP;                OutArr[7] =  50;
      OutArr[8] =  *v->CP;                OutArr[9] =  50;
      OutArr[10] = *v->CP;                OutArr[11] = 50;
      OutArr[12] = *v->CP;                OutArr[13] = 50;
      OutArr[14] = *v->CP;                OutArr[15] = 50;
      OutArr[16] =  v->Len-DO;            OutArr[17] = Vmax;
      }

    }


  }

}
}




