#define IS v->Internal_Status
#define Mode_Fault_P 0x1
#define CUR_WAP_NUM 0x6
#define UDC_WAP_NUM 0x18
#define TEMP_WAP_NUM 0x60
#define FAST_CUR_AB 0x2
#define I2t 0x4
#define UDC_L 0x8
#define UDC_H 0x10
#define T_L 0x20
#define T_H 0x40
#define T_L_1 0x80
#define T_H_1 0x100


static void W_INIT  (BLOCK_STRUCT *v) ;
static void A_INIT  (BLOCK_STRUCT *v) ;
static void P_INIT  (BLOCK_STRUCT *v) ;
static void CUR_FORM  (BLOCK_STRUCT *v, long *WAP_CUR,long abs_Cur_A,long abs_Cur_B)  ;
static void UDC_FORM  (BLOCK_STRUCT *v, long *WAP_UDC)  ;
static void TEMP_FORM (BLOCK_STRUCT *v, long *WAP_TEMP, long *Temp_Buf) ;
static void TEMP_FORM_1 (BLOCK_STRUCT *v, long *WAP_TEMP_1, long *Temp_Buf) ;
// Do not initialize inputs!
void Init(void)
{
W_INIT(v);
A_INIT(v);
P_INIT(v);

}

void Exec(void)
{
long *WAP_CUR   = (long *)(*v->CUR_Settings);
long *WAP_UDC   = (long *)(*v->UDC_Settings);
long *WAP_TEMP  = (long *)(*v->TEMP_Settings);
long *WAP_TEMP_1  = (long *)(*v->TEMP_Settings_1);
long *Temp_Buf  = (long *)(*v->Temp_DSP);

static short w,a,p,i  = 0;

static long W_Value_tr [8], A_Value_tr [8], P_Value_tr [8] = {0,0,0,0,0,0,0,0};

static long abs_Cur_A, abs_Cur_B = 0;

abs_Cur_A = abs(*v->CurA);
abs_Cur_B = abs(*v->CurB);

if (!v->WAP_Num) // не включены защиты
{

W_INIT(v);
A_INIT(v);
P_INIT(v);


    return;
}

if (*v->R) // Сброс состояния блока
{

if (*v->R & 0x1) {v->Protect &= ~Mode_Fault_P;  v->Protect_tr &= ~Mode_Fault_P;}
if (*v->R & 0x2) {W_INIT(v);  for (i = 0; i < 8; i++ ) W_Value_tr[i] = 0; v->W_index = 0; v->W_iValue = 0; }
if (*v->R & 0x4) {A_INIT(v);  for (i = 0; i < 8; i++ ) A_Value_tr[i] = 0; v->A_index = 0; v->A_iValue = 0; }
if (*v->R & 0x8) {P_INIT(v);  for (i = 0; i < 8; i++ ) P_Value_tr[i] = 0; v->P_index = 0; v->P_iValue = 0; }
if (*v->R & 0xF) v->max_nST = 0; //Full Epic Reset


return;
}


if (!v->max_nST)
{
  if (v->WAP_Num & TEMP_WAP_NUM)
  {
  if (v->max_nST < _IQtoIQ(WAP_TEMP[4],v->Format_Temp,0)) v->max_nST =  _IQtoIQ(WAP_TEMP[4],v->Format_Temp,0);
  if (v->max_nST < _IQtoIQ(WAP_TEMP[10],v->Format_Temp,0)) v->max_nST =  _IQtoIQ(WAP_TEMP[10],v->Format_Temp,0);
  if (v->max_nST < _IQtoIQ(WAP_TEMP_1[4],v->Format_Temp,0)) v->max_nST =  _IQtoIQ(WAP_TEMP[4],v->Format_Temp,0);
  if (v->max_nST < _IQtoIQ(WAP_TEMP_1[10],v->Format_Temp,0)) v->max_nST =  _IQtoIQ(WAP_TEMP[10],v->Format_Temp,0);
  }
  if (v->WAP_Num &  UDC_WAP_NUM)
  {
  if (v->max_nST < _IQtoIQ(WAP_UDC[4],v->Format_Udc,0)) v->max_nST =  _IQtoIQ(WAP_UDC[4],v->Format_Udc,0);
  if (v->max_nST < _IQtoIQ(WAP_UDC[10],v->Format_Udc,0)) v->max_nST = _IQtoIQ(WAP_UDC[10],v->Format_Udc,0);
  }
  if (v->WAP_Num &  CUR_WAP_NUM)
  {
  if (v->max_nST < _IQtoIQ(WAP_CUR[4],v->Format_Cur,0)) v->max_nST =  _IQtoIQ(WAP_CUR[4],v->Format_Cur,0);
  if (v->max_nST < _IQtoIQ(WAP_CUR[10],v->Format_Cur,0)) v->max_nST =  _IQtoIQ(WAP_CUR[10],v->Format_Cur,0);
  }

  v->max_Cnt = v->max_nST;

return;
}



if (v->Cnt < v->max_Cnt)
v->Cnt ++;
else
{
   v->Cnt  = 0;
}

/*
for (i = 0; i<=14; i++ )
{
if (WAP_Over_Time[i] <= 0) WAP_Over_Time[i] = 0;
}
*/


if (v->WAP_Num &  CUR_WAP_NUM)  CUR_FORM(v,WAP_CUR, abs_Cur_A, abs_Cur_B);
if (v->WAP_Num &  UDC_WAP_NUM)  UDC_FORM(v,WAP_UDC);
if (v->WAP_Num & TEMP_WAP_NUM)
if (v->Temp_In_num >= 1) TEMP_FORM(v,WAP_TEMP, Temp_Buf);
if (v->Temp_In_num >= 2) TEMP_FORM_1(v,WAP_TEMP_1, Temp_Buf);


if ((*v->Mod_fault & Mode_Fault_P )!= (v->Protect & Mode_Fault_P )) v->Protect ^=  Mode_Fault_P  ;

v->Warning_tr |= v->Warning;

v->Alarm_tr |= v->Alarm;

v->Protect_tr |= v->Protect;


for (i = 0; i <= 8; i++ )
{
switch (i)
     {
        case 0 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & FAST_CUR_AB ))W_Value_tr[i] = (abs_Cur_A > *v->CurB) ? *v->CurA : abs_Cur_B;
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & FAST_CUR_AB  ))A_Value_tr[i] = (abs_Cur_A > *v->CurB) ? *v->CurA : abs_Cur_B;
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & FAST_CUR_AB  ))P_Value_tr[i] = (abs_Cur_A > *v->CurB) ? *v->CurA : abs_Cur_B;
        break;
        case 2 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & I2t ))W_Value_tr[i] = *v->CurRMS;
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & I2t  ))A_Value_tr[i] = *v->CurRMS;
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & I2t ))P_Value_tr[i] = *v->CurRMS;
        break;
        case 3 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & UDC_L ))W_Value_tr[i] = *v->Udc;
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & UDC_L ))A_Value_tr[i] = *v->Udc;
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & UDC_L ))P_Value_tr[i] = *v->Udc;
        break;
        case 4 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & UDC_H ))W_Value_tr[i] = *v->Udc;
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & UDC_H ))A_Value_tr[i] = *v->Udc;
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & UDC_H ))P_Value_tr[i] = *v->Udc;
        break;
        case 5 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & T_L ))W_Value_tr[i] = Temp_Buf[0];
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & T_L ))A_Value_tr[i] = Temp_Buf[0];
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & T_L ))P_Value_tr[i] = Temp_Buf[0];
        break;
        case 6 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & T_H ))W_Value_tr[i] = Temp_Buf[0];
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & T_H ))A_Value_tr[i] = Temp_Buf[0];
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & T_H))P_Value_tr[i] = Temp_Buf[0];
        break;
        case 7 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & T_L_1 ))W_Value_tr[i] = Temp_Buf[1];
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & T_L_1 ))A_Value_tr[i] = Temp_Buf[1];
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & T_L_1 ))P_Value_tr[i] = Temp_Buf[1];
        break;
        case 8 :
        if ((W_Value_tr[i]  == 0 )&&( v->Warning_tr & T_H_1 ))W_Value_tr[i] = Temp_Buf[1];
        if ((A_Value_tr[i]  == 0 )&&( v->Alarm_tr & T_H_1 ))A_Value_tr[i] = Temp_Buf[1];
        if ((P_Value_tr[i]  == 0 )&&( v->Protect_tr & T_H_1))P_Value_tr[i] = Temp_Buf[1];
        break;
     }
}


if (v->Disp_Cnt < v->Disp_Refresh_Period)
v->Disp_Cnt ++;
else
{
   if ((v->Warning_tr >> w ) & 0x1)
   {
     v->W_iValue = W_Value_tr[w];
     v->W_index = ++w;

   } else w++;
      if ((v->Alarm_tr >> a ) & 0x1)
   {
     v->A_iValue = A_Value_tr[a];
     v->A_index = ++a;


   } else a++;
         if ((v->Protect_tr >> p ) & 0x1)
   {
     v->P_iValue = P_Value_tr[p];
     v->P_index = ++p;


   } else p++;
   if (w >= 8) w = 0;
   if (a >= 8) a = 0;
   if (p >= 8) p = 0;
   v->Disp_Cnt  = 0;
}





return;
}

static void W_INIT  (BLOCK_STRUCT *v)
{
    v->Warning = 0;
    v->Warning_tr = 0;
}

static void A_INIT  (BLOCK_STRUCT *v)
{
    v->Alarm  = 0;
    v->Alarm_tr = 0;
}

static void P_INIT  (BLOCK_STRUCT *v)
{
    v->Protect  = 0;
    v->Protect_tr = 0;
}



static void CUR_FORM  (BLOCK_STRUCT *v, long *WAP_CUR, long abs_Cur_A, long abs_Cur_B)
{

static long I2t_VAL, I2t_CNT = 0;
long const Inom = __IQ(1.0,v->Format_Cur);
static long WCnt, ACnt, PCnt = 0;

  if ((v->WAP_Num & FAST_CUR_AB) && ( (v->Cnt %  (_IQtoIQ(WAP_CUR[4],v->Format_Cur,0)  ) ) == (_IQtoIQ(WAP_CUR[5],v->Format_Cur,0) ))       ) // Пиковые токовые защиты
  {


     if (((abs_Cur_A >= WAP_CUR[1])||(abs_Cur_B >= WAP_CUR[1]))&& (_IQtoIQ(WAP_CUR[0],v->Format_Cur,0)&0x1))

     {
       if (!(WCnt > 0))   WCnt++;
       else
           v->Warning |= FAST_CUR_AB;
     }
     else
     {
     v->Warning &= ~FAST_CUR_AB;  // warning
     WCnt = 0;
     }

     if (((abs_Cur_A >= WAP_CUR[2])||(abs_Cur_B >= WAP_CUR[2]))&&(_IQtoIQ(WAP_CUR[0],v->Format_Cur,0)&0x2))

     {
       if (!(ACnt > 0))   ACnt++;
       else
           v->Alarm |= FAST_CUR_AB;
     }
     else
     {
     v->Alarm &= ~FAST_CUR_AB;  // Alarm
     ACnt = 0;
     }

     if (((abs_Cur_A >= WAP_CUR[3])||(abs_Cur_B >= WAP_CUR[3]))&&(_IQtoIQ(WAP_CUR[0],v->Format_Cur,0)&0x3  ))

     {
       if (!(PCnt > 0))   PCnt++;
       else
           v->Protect |= FAST_CUR_AB;
     }
     else
     {
     v->Protect &= ~FAST_CUR_AB;  // Protect
     PCnt = 0;
     }




     v->Interrupt = 1;


  }
  if ((v->WAP_Num & I2t ) &&  ( (v->Cnt %  (_IQtoIQ(WAP_CUR[10],v->Format_Cur,0)  ) ) == (_IQtoIQ(WAP_CUR[11],v->Format_Cur,0) ))       )
  {
  v->Interrupt = 2;
  if ((*v->CurRMS > Inom )||(I2t_VAL>0))
  {
  if (!( ((v->Warning & I2t)&&((_IQtoIQ(WAP_CUR[6],v->Format_Cur,0)&0x7  ) ==1 )) || ((v->Alarm & I2t)&&((_IQtoIQ(WAP_CUR[6],v->Format_Cur,0)&0x7  ) <=3 )) || ((v->Protect & I2t)&&((_IQtoIQ(WAP_CUR[6],v->Format_Cur,0)&0x7  ) <=7 ))  ))I2t_CNT++;
  v->Time=(I2t_CNT * v->SampleTime);


//  I2t_VAL = _IQ24mpy(v->Time, _IQ24mpy(*v->CurRMS , *v->CurRMS ) - _IQ24mpy(Inom , Inom ) );
  I2t_VAL =_IQ24mpy(v->Time,_IQ24mpy((*v->CurRMS-Inom),(*v->CurRMS+Inom)));

  }
  else
  {
  I2t_VAL = 0;
  I2t_CNT = 0;
  }

     if (((I2t_VAL >= WAP_CUR[7])&&(_IQtoIQ(WAP_CUR[6],v->Format_Cur,0)&0x1  )) != ((v->Warning & I2t)>>2)) v->Warning ^= I2t;   // warning
     if (((I2t_VAL >= WAP_CUR[8])&&(_IQtoIQ(WAP_CUR[6],v->Format_Cur,0)&0x2  )) != ((v->Alarm & I2t)>>2))   v->Alarm ^= I2t; // alarm
     if (((I2t_VAL >= WAP_CUR[9])&&(_IQtoIQ(WAP_CUR[6],v->Format_Cur,0)&0x3  )) != ((v->Protect & I2t)>>2)) v->Protect ^= I2t;   // protect


  }


}
static void UDC_FORM  (BLOCK_STRUCT *v, long *WAP_UDC)
{

static long WCnt[2], ACnt[2], PCnt[2] = {0,0};


  if ((v->WAP_Num & UDC_L)&&( (v->Cnt %  (_IQtoIQ(WAP_UDC[4],v->Format_Udc,0)  ) ) == (_IQtoIQ(WAP_UDC[5],v->Format_Udc,0) ))       )
  {


  v->Interrupt = 3;




     if ((*v->Udc <= WAP_UDC[1])&&(_IQtoIQ(WAP_UDC[0],v->Format_Udc,0)&0x1  ))

     {
       if (WCnt[0] < v->UTTRO)   WCnt[0]++;
       else
           v->Warning |= UDC_L;
     }
     else
     {
     v->Warning &= ~UDC_L;  // warning
     WCnt[0] = 0;
     }


     if ((*v->Udc <= WAP_UDC[2])&&(_IQtoIQ(WAP_UDC[0],v->Format_Udc,0)&0x2  ))

     {
       if (ACnt[0] < v->UTTRO)   ACnt[0]++;
       else
           v->Alarm |= UDC_L;
     }
     else
     {
     v->Alarm &= ~UDC_L;  // Alarm
     ACnt[0] = 0;
     }

     if ((*v->Udc <= WAP_UDC[3])&&(_IQtoIQ(WAP_UDC[0],v->Format_Udc,0)&0x3  ))

     {
       if (PCnt[0] < v->UTTRO)   PCnt[0]++;
       else
           v->Protect |= UDC_L;
     }
     else
     {
     v->Protect &= ~UDC_L;  // Protect
     PCnt[0] = 0;
     }

  }

  if ((v->WAP_Num & UDC_H)&& ( (v->Cnt %  (_IQtoIQ(WAP_UDC[10],v->Format_Udc,0)  ) ) == (_IQtoIQ(WAP_UDC[11],v->Format_Udc,0) ))       )
  {
v->Interrupt = 4;



     if ((*v->Udc >= WAP_UDC[7])&&(_IQtoIQ(WAP_UDC[6],v->Format_Udc,0)&0x1  ))
     {
       if (!(WCnt[1] >=v->UTTRO))   WCnt[1]++;
       else
           v->Warning |= UDC_H;

     }
     else
     {
     v->Warning &= ~UDC_H;  // warning
     WCnt[1] = 0;
     }


     if ((*v->Udc >= WAP_UDC[8])&&(_IQtoIQ(WAP_UDC[6],v->Format_Udc,0)&0x2  ))

     {
       if (!(ACnt[1] >=v->UTTRO))   ACnt[1]++;
       else
           v->Alarm |= UDC_H;
     }
     else
     {
     v->Alarm &= ~UDC_H;  // Alarm
     ACnt[1] = 0;
     }

     if ((*v->Udc >= WAP_UDC[9])&&(_IQtoIQ(WAP_UDC[6],v->Format_Udc,0)&0x3  ))

     {
       if (!(PCnt[1] >=v->UTTRO))   PCnt[1]++;
       else
           v->Protect |= UDC_H;
     }
     else
     {
     v->Protect &= ~UDC_H;  // Protect
     PCnt[1] = 0;
     }





  }

}

static void TEMP_FORM (BLOCK_STRUCT *v, long *WAP_TEMP, long *Temp_Buf)
{

static long WCnt[2], ACnt[2], PCnt[2] = {0,0};

  if ((v->WAP_Num & T_L)&&( (v->Cnt %  (_IQtoIQ(WAP_TEMP[4],v->Format_Temp,0)  ) ) == (_IQtoIQ(WAP_TEMP[5],v->Format_Temp,0) ))       )
  {
  v->Interrupt = 5;
     if ((Temp_Buf[0] <= WAP_TEMP[1])&&(_IQtoIQ(WAP_TEMP[0],v->Format_Temp,0)&0x1  ))

     {
       if (!(WCnt[0] >=v->TTTRO))   WCnt[0]++;
       else
           v->Warning |= T_L;
     }
     else
     {
     v->Warning &= ~T_L;  // warning
     WCnt[0] = 0;
     }


     if ((Temp_Buf[0] <= WAP_TEMP[2])&&(_IQtoIQ(WAP_TEMP[0],v->Format_Temp,0)&0x2  ))

     {
       if (!(ACnt[0] >=v->TTTRO))   ACnt[0]++;
       else
           v->Alarm |= T_L;
     }
     else
     {
     v->Alarm &= ~T_L;  // Alarm
     ACnt[0] = 0;
     }

     if ((Temp_Buf[0] <= WAP_TEMP[3])&&(_IQtoIQ(WAP_TEMP[0],v->Format_Temp,0)&0x3  ))

     {
       if (!(PCnt[0] >=v->TTTRO))   PCnt[0]++;
       else
           v->Protect |= T_L;
     }
     else
     {
     v->Protect &= ~T_L;  // Protect
     PCnt[0] = 0;
     }




  }


  if ((v->WAP_Num & T_H)&& ( (v->Cnt %  (_IQtoIQ(WAP_TEMP[10],v->Format_Temp,0)  ) ) == (_IQtoIQ(WAP_TEMP[11],v->Format_Temp,0) ))       )
  {
v->Interrupt = 6;


     if ((Temp_Buf[0] >= WAP_TEMP[7])&&(_IQtoIQ(WAP_TEMP[6],v->Format_Temp,0)&0x1  ))

     {
       if (!(WCnt[1] >=v->TTTRO))   WCnt[1]++;
       else
           v->Warning |= T_H;
     }
     else
     {
     v->Warning &= ~T_H;  // warning
     WCnt[1] = 0;
     }


     if ((Temp_Buf[0] >= WAP_TEMP[8])&&(_IQtoIQ(WAP_TEMP[6],v->Format_Temp,0)&0x2  ))

     {
       if (!(ACnt[1] >=v->TTTRO))   ACnt[1]++;
       else
           v->Alarm |= T_H;
     }
     else
     {
     v->Alarm &= ~T_H;  // Alarm
     ACnt[1] = 0;
     }

     if ((Temp_Buf[0] >= WAP_TEMP[9])&&(_IQtoIQ(WAP_TEMP[6],v->Format_Temp,0)&0x3  ))

     {
       if (!(PCnt[1] >=v->TTTRO))   PCnt[1]++;
       else
           v->Protect |= T_H;
     }
     else
     {
     v->Protect &= ~T_H;  // Protect
     PCnt[1] = 0;
     }

}

  }



static void TEMP_FORM_1 (BLOCK_STRUCT *v, long *WAP_TEMP_1, long *Temp_Buf)
{


static long WCnt[2], ACnt[2], PCnt[2] = {0,0};


  if ((v->WAP_Num & T_L)&&( (v->Cnt %  (_IQtoIQ(WAP_TEMP_1[4],v->Format_Temp,0)  ) ) == (_IQtoIQ(WAP_TEMP_1[5],v->Format_Temp,0) ))       )
  {
  v->Interrupt = 7;


 if ((Temp_Buf[1] <= WAP_TEMP_1[1])&&(_IQtoIQ(WAP_TEMP_1[0],v->Format_Temp,0)&0x1  ))

     {
       if (!(WCnt[0] >=v->TTTRO))   WCnt[0]++;
       else
           v->Warning |= T_L_1;
     }
     else
     {
     v->Warning &= ~T_L_1;  // warning
     WCnt[0] = 0;
     }


     if ((Temp_Buf[1] <= WAP_TEMP_1[2])&&(_IQtoIQ(WAP_TEMP_1[0],v->Format_Temp,0)&0x2  ))

     {
       if (!(ACnt[0] >=v->TTTRO))   ACnt[0]++;
       else
           v->Alarm |= T_L_1;
     }
     else
     {
     v->Alarm &= ~T_L_1;  // Alarm
     ACnt[0] = 0;
     }

     if ((Temp_Buf[1] <= WAP_TEMP_1[3])&&(_IQtoIQ(WAP_TEMP_1[0],v->Format_Temp,0)&0x3  ))

     {
       if (!(PCnt[0] >=v->TTTRO))   PCnt[0]++;
       else
           v->Protect |= T_L_1;
     }
     else
     {
     v->Protect &= ~T_L_1;  // Protect
     PCnt[0] = 0;
     }


  }


  if ((v->WAP_Num & T_H)&& ( (v->Cnt %  (_IQtoIQ(WAP_TEMP_1[10],v->Format_Temp,0)  ) ) == (_IQtoIQ(WAP_TEMP_1[11],v->Format_Temp,0) ))       )
  {
v->Interrupt = 8;



 if ((Temp_Buf[1] >= WAP_TEMP_1[7])&&(_IQtoIQ(WAP_TEMP_1[6],v->Format_Temp,0)&0x1  ))

     {
       if (!(WCnt[1] >=v->TTTRO))   WCnt[1]++;
       else
           v->Warning |= T_H_1;
     }
     else
     {
     v->Warning &= ~T_H_1;  // warning
     WCnt[1] = 0;
     }


     if ((Temp_Buf[1] >= WAP_TEMP_1[8])&&(_IQtoIQ(WAP_TEMP_1[6],v->Format_Temp,0)&0x2  ))

     {
       if (!(ACnt[1] >=v->TTTRO))   ACnt[1]++;
       else
           v->Alarm |= T_H_1;
     }
     else
     {
     v->Alarm &= ~T_H_1;  // Alarm
     ACnt[1] = 0;
     }

     if ((Temp_Buf[1] >= WAP_TEMP_1[9])&&(_IQtoIQ(WAP_TEMP_1[6],v->Format_Temp,0)&0x3  ))

     {
       if (!(PCnt[1] >=v->TTTRO))   PCnt[1]++;
       else
           v->Protect |= T_H_1;
     }
     else
     {
     v->Protect &= ~T_H_1;  // Protect
     PCnt[1] = 0;
     }




  }



}
