#define pi __IQ(3.141592653589,16)

void Init(void)
{

}

void Exec(void)
{
if (((v->P1_prev_rad)!=(v->P1_rad))&&
    (v->state!=0))  {
     v->state=0;
     v->P0_rad = *v->Pfeed;
     v->P0_prev_rad = *v->Pfeed;
     v->t=0;
} // EOF Поменялось задание в процессе движения

v->P1_rad=*v->Pref;
switch (v->state) {
case 0:
        if (((v->P1_rad)-(v->P0_rad))==0) {
            break;
        } //EOF Задание не поменялось
        if ((*v->t_max)<=__IQ(0.0002,16)) {
          v->t_maxH=__IQ(0.0002,16);
        } // EOF Время отрицательное
        else {
          v->t_maxH=*v->t_max;
        } // EOF Время в диапазоне
    // расчет предельных значений кривой

    v->Vmax= (_IQ16div(((v->P1_rad)-(v->P0_rad)),(v->t_maxH)))<<1; //  Vmax=Amax*t_max*2/3*pi
    v->Amax= _IQ16mpy((_IQ16div(((v->P1_rad)-(v->P0_rad)),(_IQ16mpy((v->t_maxH),(v->t_maxH))))), (__IQ(9.4247779607694,16)));     //  Amax=((P1-P0)*3pi)/t_max^2
    v->Jmax=_IQ16mpy((_IQ16div((v->Amax),(v->t_maxH))),(__IQ(7.25197456937,16))); //  Jmax=Amax/t_max * CONST
    if ((abs(v->Vmax))>(*v->V_lim))  {  // если превышает скорость

      v->Vmax=_IQ16mpy((_IQ16div((*v->V_avr),(v->Vmax))),(abs(v->Vmax))); // Vmax=(V_lim/Vmax)*absf(Vmax);
      v->t_maxH=(_IQ16div(((v->P1_rad)-(v->P0_rad)),(v->Vmax)))<<1; // Пересчет времени
      v->Amax= _IQ16mpy((_IQ16div(((v->P1_rad)-(v->P0_rad)),(_IQ16mpy((v->t_maxH),(v->t_maxH))))), (__IQ(9.4247779607694,16)));   //  Amax=((P1-P0)*3pi)/t_max^2// Amax
      v->Jmax=_IQ16mpy((_IQ16div((v->Amax),(v->t_maxH))),(__IQ(7.25197456937,16)));   //  Jmax=Amax/t_max * CONST
    } // EOF превышает допустимую скорость
    if ((abs(v->Amax))>(*v->A_lim))  {  // если превышает ускорение
       (v->Amax)=_IQ16mpy((_IQ16div((*v->A_avr),(v->Amax))),(abs(v->Amax)));  // Amax=(A_lim/Amax)*absf(Amax);
       (v->t_maxH)=_IQ16sqrt((_IQ16mpy((_IQ16div(((v->P1_rad)-(v->P0_rad)),(v->Amax))),(__IQ(9.4247779607694,16)))));   // Пересчет времени
       (v->Vmax)=(_IQ16div(((v->P1_rad)-(v->P0_rad)),(v->t_maxH)))<<1;                                   //  Vmax=Amax*t_max*2/3*pi
       (v->Jmax)=_IQ16mpy((_IQ16div((v->Amax),(v->t_maxH))),(__IQ(7.25197456937,16)));                   //  Jmax=Amax/t_max * CONST
    } // EOF превышает допустимое ускорение


        v->k1=_IQ16div((_IQ16mpy((v->Amax),(_IQ16mpy((v->t_maxH),(v->t_maxH))))),__IQ(1421.223033756,16));
        v->k2=_IQ16div((__IQ(18.849555921534,16)),(v->t_maxH));
        v->k3=_IQ16mpy((_IQ16mpy((v->Amax),(_IQ16mpy((v->t_maxH),(v->t_maxH))))),__IQ(0.018997721932,16));
        v->k4=_IQ16div((__IQ(6.28318530,16)),(v->t_maxH));
        v->k5=_IQ16div((_IQ16mpy((v->Amax),(v->t_maxH))),(__IQ(9.4247779607694,16)));
        v->P0_prev_rad=v->P0_rad;
        v->P1_prev_rad=v->P1_rad;
        v->state=1;
        break;
case 1:
        v->t=v->t+v->SampleTime;
        v->P0_rad= _IQ16mpy(_IQ16sin((_IQ16mpy((v->k2),(v->t)))),(v->k1))-
                   _IQ16mpy(_IQ16sin((_IQ16mpy((v->k4),(v->t)))),(v->k3))+
                   _IQ16mpy((v->k5),(v->t))+
                   v->P0_prev_rad;
        if (((v->Model)&1)==1) {
            (v->V0_rad)=(_IQ16cos(_IQ16div(_IQ16mpy(__IQ(18.849555921534,16),(v->t)),(v->t_maxH)))-
                         _IQ16mpy((__IQ(9.0,16)),(_IQ16cos(_IQ16div(_IQ16mpy(__IQ(6.283185307178,16),(v->t)),(v->t_maxH)))))+
                         __IQ(8.0,16));
            (v->V0_rad)=_IQ16mpy((v->V0_rad),(_IQ16div((_IQ16mpy((v->Amax),(v->t_maxH))),(__IQ(75.398223686136,16)))));
            (v->V)=(v->V0_rad);
        } // EOF Расчет кривой Скорости
        else                {
             (v->V)=(v->Vmax);
        } //EOE Показывать Максимальную скорость на участке

        if (((v->Model)&2)==2) {
            (v->A0_rad)=_IQ16sin(_IQ16div((_IQ16mpy((__IQ(6.283185307178,16)),(v->t))),(v->t_maxH)))-
                        _IQ16mpy(_IQ16sin(_IQ16div((_IQ16mpy((__IQ(6.283185307178,16)),(v->t))),(v->t_maxH))),_IQ16cos(_IQ16div((_IQ16mpy((__IQ(12.566370614356,16)),(v->t))),(v->t_maxH))));
            (v->A0_rad)=_IQ16mpy((v->A0_rad),((v->Amax)>>1));
            (v->A)=(v->A0_rad);
        } // EOF Расчет кривой Ускорения
        else                {
            (v->A)=(v->Amax);
        } // EOE Показывать Максимальное ускорение на участке
        (v->J)=(v->Jmax);  //EOE Показывать Максимальный рывок на участке

        if ((v->t)>=(v->t_maxH))  {
            v->state=2;
        }  // EOF Переход на ожидание смены положения;
        break;
case 2:
        v->P0_rad=v->P1_rad;
        v->t=0;
        v->state=0;
        v->V=0;
        v->A=0;
        v->J=0;
        break;
}   // EOC

v->P=v->P0_rad;
v->T=v->t_maxH;
}

