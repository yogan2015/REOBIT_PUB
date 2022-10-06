 #define  DC      InArr[0]
  #define  FL      InArr[1]
  #define  SM_C    InArr[2]
  #define  AM_C    InArr[3]
  #define  AM_O    InArr[4]
  #define  SM_O    InArr[5]
  #define  DM_O    InArr[6]
  #define  DO      InArr[7]



  #define  Vsyn    InArr[8]
  #define  Vmin    InArr[9]
  #define  Vmax    InArr[10]

  #define  Fhld    InArr[11]
  #define  Fmin    InArr[12]
  #define  Fmax    InArr[13]



  #define inSB1 *v->CC & 0x1
  #define inSB2 *v->CC & 0x2

  #define inCcmd (*v->CC & 0x4)>>2
  #define inOcmd (*v->CC & 0x8)>>3

   #define inAPP (*v->CC & 0x10)>>4

  #define inFRVM (*v->CC & 0x20)>>5

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
  #define SW12CMDFLT  0x1000 // shift 12
  #define SW13SPDIVFLG  0x2000 // shift 13
  #define SWOoP  0x4000 // shift 14
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
  #define VKOAREA (v->Len - DO-10)
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

static void PATH     (BLOCK_STRUCT *v, long *


Arr, long *InArr);
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
if ((_IQabs(*v->CS)>0 ) && (_IQabs(*v->CS)<2 )) *v->CS = 2;

if (*v->R)
  v->SW = 0;
else

WORD(v, OutArr, InArr);

if (v->SW & SW0RDY )
{

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

  v->SD =/*(_IQtoIQ(*v->CSS,20,0) / 4)>150 ?  150 :*/( _IQtoIQ(*v->CSS,20,0) / v->div );
   if (_IQabs(v->SD) > 200)  v->SD = 200; else v->SD = v->SD;

  if (_IQtoIQ(*v->CSS,20,0)!=0)  v->SD *= v->DR; else v->SD = 0;


  inAppPT  += (inAPP) ? ( (inAppPT  < v->PTM)? 1:0 ) : ( (inAppPT  < 1)   ? 0 : -1 );
  inOcmdPT += (inOcmd)? ( (inOcmdPT < v->PTM)? 1:0 ) : ( (inOcmdPT < 1)   ? 0 : -1 );
  inCcmdPT += (inCcmd)? ( (inCcmdPT < v->PTM)? 1:0 ) : ( (inCcmdPT < 1)   ? 0 : -1 );
  SB1PT    += (inSB1) ? ( (SB1PT    < v->PTM)? 1:0 ) : ( (SB1PT    < 1)   ? 0 : -1 );
  SB2PT    += (inSB2) ? ( (SB2PT    < v->PTM)? 1:0 ) : ( (SB2PT    < 1)   ? 0 : -1 );


  SB12PT   += (inSB2 && inSB1) ? ( (SB12PT    < v->PTM)? 1:0 ) : ( (SB12PT    < 1)   ? 0 : -1 );





  if ((inAppPT >= v->PTM/2)                      != APPCMD) v->SW ^=SW3APP; // APP to SW


  if ( (((SB1PT  >= v->PTM/2) && ((SB2PT  < v->PTM/2))) || (inCcmdPT >= v->PTM/2) && !(inFRVM)) != CLCMD ) v->SW ^=SW4CL; // CLOSE to SW

  if ( (((SB2PT  >= v->PTM/2) && ((SB1PT  < v->PTM/2))) || (inOcmdPT >= v->PTM/2) ) != OPCMD ) v->SW ^=SW5OP; // OPEN to SW




  if ( ((inOcmdPT || SB2PT ) && CLCMD) || ((inCcmdPT || SB1PT )&& OPCMD) ) v->SW &= ERCMD;
  if ((SB2PT >= v->PTM/2)) {v->RVM = 0; v->SW &= 0xFFFFFBFF;}//||(SB1PT >= v->PTM/2)

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




  }

if ((*v->SpdDiv <= 0) || (v->Flag == 0)) *v->SpdDiv = 100;


 return;
}

static void OUTWRITE (BLOCK_STRUCT *v, long *OutArr, long *InArr)
{
     /* *****************************
        ENDPOINTS OUT
  ****************************** */


  //if (CLCMD) v->SW &= 0xFFFFFFBF;
 // if (OPCMD) v->SW &= 0xFFFFFF7F;
  v->RVM = ((v->SW & SW8RVM)>>8);
  if (inFRVM) v->RVM = 1;
  v->VKZ = ((v->SW & SW7VKZ)>>7);
  v->VKO = ((v->SW & SW6VKO)>>6);
   if ( (v->VKZ && OPCMD) || (v->VKO && CLCMD)) v->SW &= -193;
  if (v->RVM ) v->RS = 2;

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
if (BLOCKED && ( !OPCMD && !CLCMD)) v->DR = 1;





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

  v->RS= ((v->SW & SW2IE)&&(!BLOCKED)) ? 0 : 2 ;

  if (v->SW & SW2IE)
  {
    /* *****************************
        PVCURVE MODE SPECIAL
        all function for normal work is in another functions and in RS mode setup in line above
        this state is need for RVM

    ****************************** */


if (CLCMD && ((*v->CI > _IQ22(0.5))&&(*v->CP >0)&&(*v->CP <DC+20)))v->OFFSET = *v->CP + 1;
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
if (v->SW & SW6VKO) v->SW &= 0xFFFFFBFF;





  }
    else
  {
    /* *****************************
        INIT MODE
        commands forimng later, this state is need for normal work control and switch STATE WORD SW
    ****************************** */

  if (v->Len < _Len_Min ) v->REG |= 0x10; else v->REG &= 0xFFFFFFEF;
  if (OPCMD && STOPED && !(v->SW & SW6VKO) && (*v->CI > _IQ22(0.5)) ) {v->SW |= SW6VKO; return;}
  if (STOPED && CLCMD)
  {
  if ((v->REG & 0x20 ) == 0)
  {
    v->REG |=0x20;
    v->RP = 1;
    return;
  }
  else
  {

   if ((*v->CP >= -5 )&&(*v->CP <= 5 )&&(v->RP == 1))
    {

    v->REG |= 0x4 ; v->RP = 0;v->SW |= SW7VKZ;

    if ((v->SW & SW1LEN)&& (v->REG & 0x4) ){

  v->RS = 0; v->RP = 0;   v->SW |= SW2IE;



       if (v->Len >=1200) {InArr[10] = 580;}
  else if (v->Len >=1000) {InArr[10] = 540; }
  else if (v->Len >=900)  {InArr[10] = 515; }
  else if (v->Len >=800)  {InArr[10] = 490; }
  else if (v->Len >=750)  {InArr[10] = 475; }
  else if (v->Len >=700)  {InArr[10] = 460; }
  else if (v->Len >=600)  {InArr[10] = 430; }
  else if (v->Len >=550)  {InArr[10] = 410; }
  else if (v->Len >=500)  {InArr[10] = 390; }
  else if (v->Len >=470)  {InArr[10] = 380; }
  else if (v->Len >=450)  {InArr[10] = 365; }
  else if (v->Len >=400)  {InArr[10] = 330; }
  else if (v->Len >=350)  {InArr[10] = 250; }
  else if (v->Len >=325)  {InArr[10] = 240; }
  else {InArr[10] = 200; }


  //??????????? ???????? ????????
if (InArr[10] >= 460) InArr[10] = 430;


 InArr[10] = *v->SpdDiv *InArr[10]/100;
v->Flag = 0;
  return;


    return;
    }

  }

  if ((*v->CI > _IQ22(0.15))&&(v->REG & 0x4)&&(*v->CP >0) ) v->OFFSET = *v->CP + 1;


  }
  }
  else v->RP = 0;
  if (STOPED && OPCMD && ILSf && (v->REG & 0x4) )
  {
    if (*v->CP >= 300)  v->Len = *v->CP;



  if ((v->Len >= _Len_Min )&& (v->REG & 0x4) )
  { v->SW |= SW6VKO;v->RS = 0;  v->RP = 0;  v->SW |= SW2IE;
    //??????????? ???????????? ???????? ???????? ?????? ?? ?????????? ????? ??????


       if (v->Len >=1200) {InArr[10] = 580;}
  else if (v->Len >=1000) {InArr[10] = 540; }
  else if (v->Len >=900)  {InArr[10] = 515; }
  else if (v->Len >=800)  {InArr[10] = 490; }
  else if (v->Len >=750)  {InArr[10] = 475; }
  else if (v->Len >=700)  {InArr[10] = 460; }
  else if (v->Len >=600)  {InArr[10] = 430; }
  else if (v->Len >=550)  {InArr[10] = 410; }
  else if (v->Len >=500)  {InArr[10] = 390; }
  else if (v->Len >=470)  {InArr[10] = 380; }
  else if (v->Len >=450)  {InArr[10] = 365; }
  else if (v->Len >=400)  {InArr[10] = 330; }
  else if (v->Len >=350)  {InArr[10] = 250; }
  else if (v->Len >=325)  {InArr[10] = 240; }
  else {InArr[10] = 200; }


  //??????????? ???????? ????????
if (InArr[10] >= 460) InArr[10] = 430;

 InArr[10] = *v->SpdDiv *InArr[10]/100;
v->Flag = 0;
  return;}

  }





  }

}

static void WORD (BLOCK_STRUCT *v, long *OutArr, long *InArr)
{
 static int MRT = 0; // MANUAL REVERSE TIMER

 v->SW |= SW0RDY; // READY to SW
 if ( ((v->Len >= _Len_Min )&&(v->Len<=_Len_Max) ) != ( (v->SW & SW1LEN)>>1) ) v->SW ^= SW1LEN; // LENGHT CHECK

 if (( v->SW & SW2IE) >>2)  //END POINT SET
 {
 if ( (*v->CP > VKOAREA ) != ( (v->SW & SW6VKO)>>6) ) v->SW ^= SW6VKO;
   if ( (*v->CP < VKZAREA ) != ( (v->SW & SW7VKZ)>>7) ) v->SW ^= SW7VKZ;
 }


if (!BREAKING) INREAD(v, InArr);

 TIMERS(v, OutArr, InArr);

  if ( ( (v->MT >= v->MMT) && (v->SW & SW2IE) ) != ( (v->SW & SW11OM)>>11) ) v->SW ^= SW11OM;
  if ( (v->ST >= v->NST) != ( (v->SW & SW9STP)>>9) ) {v->SW ^= SW9STP; v->REG &= 0xFFFFFFF7;}

  if (v->SW & SW2IE)
  {
   /* *****************************
        BLOCK CHECK
  ****************************** */

  if ( ((*v->CI > _IQ22(0.5))||(*v->CS >-5)) && CLCMD && !v->VKO && !v->VKZ && (*v->CP > DC+v->OFFSET+FL+SM_C)&& (v->MT > _IQ24(1.0) ) )//
  {
     v->MRT = (v->MRT < _IQ24(100.0))  ? (v->MRT + v->SampleTime) : MRT;
    if ((v->MRT >= _IQ24(0.25)) ) v->SW |= SW10BLCK; else v->SW &= 0xFFFFFBFF;

  }
    else
    v->MRT = 0;
  }
 return;
}


static void TIMERS (BLOCK_STRUCT *v, long *OutArr, long *InArr)
{
  /* *****************************
        MOVE TIMER
  ****************************** */
  v->MT = ( (v->MT <= _IQ24(100.0) ) && ( CLCMD || OPCMD ) ) ? (v->MT + v->SampleTime):(v->MT);

  /* *****************************
        STOP TIMER
  ****************************** */

 v->ST = ( /*(v->MT >= _IQ24(1.0))&&*/( v->ST <= _IQ24(100.0) ) && ( CLCMD || OPCMD ) && ( _IQabs(*v->CS) < 10 ) && (PCMD == (CLCMD + (OPCMD << 1)) ) ) ? (v->ST + v->SampleTime):(v->ST);
  if ( _IQabs(*v->CS) >= 10 ) v->ST = 0;
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

  if (!( CLCMD || OPCMD ) && (LockFlag == 0))
    LockFlag  = *v->CP;

    if (!( CLCMD || OPCMD ))
    {
      OutArr[0] = LockFlag;
    }
  else LockFlag = 0;
    if (STOPED && OPCMD && !ILSf && !(v->REG & 0x4) )
  {
    OutArr[0] = LockFlag;
  }
}
else
{
if ((v->SW & SW8RVM)&& (v->NS != 1))
{
    v->NS = 1;
    OutArr[0] = *v->CP;
    OutArr[1] = 50;
       OutArr[2] =  0;                OutArr[3] =  0;
       OutArr[4] =  0;                OutArr[5] =  0;
       OutArr[6] =  0;                OutArr[7] =  0;
       OutArr[8] =  0;                OutArr[9] =  0;
       OutArr[10] = 0;                OutArr[11] = 0;
       OutArr[12] = 0;                OutArr[13] = 0;
       OutArr[14] = 0;                OutArr[15] = 0;
       OutArr[16] = v->Len-DO;        OutArr[17] = 0;
return;
}


  if ((PCMD == 0)&&(CLCMD || OPCMD) )
  {


    if ((*v->CP <= (DC + v->OFFSET+1) ) || (*v->CP >= (v->Len - DO-1) ))
    {
      /* **********************************
      REFERENCE PATH
      INIT END, NO OLD CMD, HAVE NEW CMD, we are directly at END POINT
      *********************************** */

      v->RS = 0;
      v->NS = 9;

      OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;
      OutArr[16] = v->Len - DO;    OutArr[17] = 50;

      OutArr[2] = OutArr[0] + FL/2;  OutArr[3] = Vsyn;  // FAST LOCK
      OutArr[4] = OutArr[2] + FL/2;  OutArr[5] = Vmin;  // FAST LOCK
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

          OutArr[2] = ((OutArr[0] + FL/2) > (REFARR[6] - 10)) ? (REFARR[6] - 10): (OutArr[0] + FL/2);
          OutArr[4] = ((OutArr[2] + FL/2) > (REFARR[6] - 10)) ? (REFARR[6] - 2) : (OutArr[2] + FL/2);

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


      OutArr[2] = OutArr[0] + FL/2;  OutArr[3] = Vsyn;  // FAST LOCK
      OutArr[4] = OutArr[2] + FL/2;  OutArr[5] = Vmin;  // FAST LOCK
      OutArr[6] = OutArr[4] + SM_C;  OutArr[7] = Vmin;  // SLOW LOCK
      OutArr[8] = OutArr[6] + AM_C;  OutArr[9] = Vmax;  // ACC MOVE

      OutArr[16] = *v->CP;    OutArr[17] = 50;
      OutArr[14] = OutArr[16] - DM_O;  OutArr[15] = Vmin;  // ACC TO FULL OPEN
      OutArr[12] = (OutArr[14]>REFARR[12]) ? (REFARR[12]) : (OutArr[14]-2) ; OutArr[13] = Vmin;
      OutArr[10] = OutArr[12] - AM_O;  OutArr[11] = Vmax;  // ACC MOVE

          }
      else
      {
        if (*v->CP >= REFARR[6])
        {
          v->NS = 7;
          SCALE = (REFARR[8]-(*v->CP-AM_C))*500/(REFARR[8]-REFARR[6]);
          OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;
          OutArr[2] = OutArr[0] + FL/2;  OutArr[3] = Vsyn;  // FAST LOCK
          OutArr[4] = OutArr[2] + FL/2;  OutArr[5] = Vmin;  // FAST LOCK
          OutArr[12] = *v->CP;    OutArr[13] = 50;


          OutArr[8] = ( (*v->CP-AM_O)>=REFARR[8] ) ? ( REFARR[8] ) : ( ( (REFARR[8]-AM_C*SCALE/1000) < (REFARR[6]+20)) ? (REFARR[6]) : (REFARR[8]-AM_C*SCALE/1000) );
          OutArr[6] = (OutArr[8]>REFARR[6]) ? REFARR[6] : OutArr[8];
          OutArr[10]= (*v->CP< (REFARR[6]+20))? (REFARR[6]) : ( (*v->CP-AM_O >OutArr[8]) ? (*v->CP-AM_O) : (OutArr[8]) );

          OutArr[7] = Vmin;
          OutArr[9] = ( (REFARR[9]-REFARR[9]*SCALE/1000) >Vmax ) ? (Vmax) : ( ( (REFARR[9]-REFARR[9]*SCALE/1000) <Vmin ) ? (Vmin) :(REFARR[9]-REFARR[9]*SCALE/1000) );
          OutArr[11]= OutArr[9];


       OutArr[14] = 0;                OutArr[15] = 0;
       OutArr[16] = v->Len-DO;        OutArr[17] = 50;


        }
        else
        {
         v->NS = 4 ;
        OutArr[0] = DC + v->OFFSET; OutArr[1]  = 50;
        OutArr[6] = *v->CP;    OutArr[7] = 50;

        OutArr[2] = ( (OutArr[6]-10) < REFARR[2] ) ? ( ( (OutArr[6]-10)<OutArr[0] ) ? (OutArr[0]) : (OutArr[6]-10) ) : (REFARR[2]);
        OutArr[4] = (OutArr[6]<= (REFARR[4]+20) ) ? (OutArr[2]) : (REFARR[4]+20);

        OutArr[3] = ( OutArr[2]< REFARR[2] ) ? 50 : Vsyn;
        OutArr[5] = ( (OutArr[4] < REFARR[4] ) && (OutArr[4] >= REFARR[2])  ) ? (Vsyn) : ( (OutArr[4] < REFARR[2] ) ? (50) : (Vmin) );


       OutArr[8] =  0;                OutArr[9] =  0;
       OutArr[10] = 0;                OutArr[11] = 0;
       OutArr[12] = 0;                OutArr[13] = 0;
       OutArr[14] = 0;                OutArr[15] = 0;
       OutArr[16] = v->Len-DO;        OutArr[17] = 0;
        }
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

      OutArr[2] = OutArr[0] + FL/2;  OutArr[3] = Vsyn;  // FAST LOCK
      OutArr[4] = OutArr[2] + FL/2;  OutArr[5] = Vmin;  // FAST LOCK
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



        if (v->DR == 1)
        {
       OutArr[3] =  50;
       OutArr[2] = _IQtoIQ(*v->CPS,20,0)+v->SD;
     if (OutArr[2] > v->Len-DO) OutArr[2] = v->Len-DO;
       OutArr[0] =*v->CP;
       OutArr[1] = _IQtoIQ(*v->CSS,21,0)+1;
        }
        if (v->DR == -1)
        {
       OutArr[1] =  50;
       OutArr[0] = _IQtoIQ(*v->CPS,20,0)+v->SD;
     if (OutArr[0] < DC+v->OFFSET) OutArr[0] =  DC+v->OFFSET;
       OutArr[2] = *v->CP;
       OutArr[3] = _IQtoIQ(*v->CSS,21,0)-1;
        }
       OutArr[4] =  0;                OutArr[5] =  0;
       OutArr[6] =  0;                OutArr[7] =  0;
       OutArr[8] =  0;                OutArr[9] =  0;
       OutArr[10] = 0;                OutArr[11] = 0;
       OutArr[12] = 0;                OutArr[13] = 0;
       OutArr[14] = 0;                OutArr[15] = 0;
       OutArr[16] = v->Len-DO;        OutArr[17] = Vmax;
      }
      else
      v->RS = 2;
      {
       OutArr[0] = *v->CP;
       OutArr[1] = 50;
      }

    }


  }

}
}


