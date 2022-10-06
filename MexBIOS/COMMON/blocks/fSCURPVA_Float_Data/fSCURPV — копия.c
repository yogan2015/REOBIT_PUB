// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  #define S_Pref   Data[0+ (v->N_t << 1)]
  #define S_Vref   Data[1+ (v->N_t << 1)]
  int *Data;

  float Am;
  float Abr;


  Data = (int *)(*v->Buf) ;

  S_Pref= __IQtoF(S_Pref,0);
  S_Vref= __IQtoF(S_Vref,0);


  if ((short)*v->R)
      {
        if (*v->R == 3)
        {
          v->N_t = (*v->En <0) ? (*v->N-1) : 0 ;
            Data = (int *)(*v->Buf) ;

      S_Pref= __IQtoF(S_Pref,0);
      S_Vref= __IQtoF(S_Vref,0);

    v->BRY = v->Y ;
    v->BRT = v->Time;
    v->BRWS = v->WorkStage;

      v->WorkStage = 3;
      v->InitStage = 2;
      v->J_t = -v->J_t;



        return;
        } else
        {
        Data=(int *)(*v->Buf) ;
        S_Pref= __IQtoF(S_Pref,0);
        S_Vref= __IQtoF(S_Vref,0);
        v->Y2   =  ((short)*v->R & 0x2) ?(*v->En*S_Pref) : 0 ; //  Посчитанный путь(интеграл по времени)
        v->P_t  =  ((short)*v->R & 0x2) ?(*v->En*S_Pref) : 0 ; //  Расчетный путь
        v->P    =  ((short)*v->R & 0x2) ?(*v->En*__IQ(S_Pref,20)) : 0 ;// Значение отправляемое на выход

        v->Y1   =  ((short)*v->R & 0x2) ? S_Vref : 0 ;// посчитанная скорость( интеграл по времени)
        v->V_t  =  ((short)*v->R & 0x2) ? S_Vref : 0 ;// расчетная скорость конца участка
        v->V    =  ((short)*v->R & 0x2) ? __IQ(S_Vref,21) : 0 ;// значение отправляемое на выход

        v->N_t  =  ((short)*v->R & 0x2) ?(((*v->En+1)>>1)*(*v->N-1)) : 0 ;
        v->InitStage = 0; //  машина состояния (0- расчет направления, 1 - Расчет точек конца участка, времени перемещения, 2- подсчет интегралов (участков), 3- определение конца кривой или же продолжение.
        v->WorkStage=0; // машина состояния расчета интеграла пути трапецеидальной формы ускорения
        v->Time=0; // начальное время интегрирования.
        v->Y=0; // посчитанное ускорение( интеграл по времени)
        v->A_t =0; //  расчетное ускорение
        v->A=0;// ускорение - Выход переменной блока.
        v->Dir=0;// направление движения
        v->_en = 0;//  предыдущее значение входа *v->En
        v->MovePos = 0;
        v->t = 0;
        v->J_t = 0;// расчетный рывок
        v->Time = 0;

        return;
        }
      }

  switch(v->InitStage)
  {
     case 0:


       if (((short)*v->En  == 1)&&((v->_en)!=(*v->En)))
       {v->Dir = 1; v->InitStage = 1;
         v->N_t = ((v->Y2 >= Data[(v->N_t_max - 1)<<1])) ? (v->N_t_max - 1) : 0;

       }
       if (((short)*v->En  == -1)&&((v->_en)!=(*v->En)))
       {v->Dir = -1; v->InitStage = 1;
        v->N_t = (v->Y2 <= Data[0]  ) ? 0 : *v->N-1;}

       v->_en=*v->En;
       break;

    case 1:
//Расчет максимального ускорения, рывка, времени участка
        v->WorkStage = 0;
        v->Time=0;

        v->MovePos  = (S_Pref - v->P_t) * v->Dir;
        if (v->MovePos == 0) {v->InitStage=3; return;}
        Am = fabs(0.75*(S_Vref - v->V_t)*(S_Vref + v->V_t)/(v->MovePos));

        v->t= (v->MovePos * 0.666667) / (v->V_t + S_Vref);

        if (v->V_t  <  S_Vref) v->A_t=Am;
        if (v->V_t  >  S_Vref) v->A_t=-Am;

        v->J_t= v->A_t/ v->t;
        v->InitStage=2;
        v->Y=0;
        v->V_t=S_Vref;
        v->P_t=S_Pref;

        return;

    case 2:                            // формирование ускорения трапециодальной формы
        switch(v->WorkStage)
          {
            case 0: (v->Y) = (v->J_t) * (v->Time);                  if ((v->Time)>=v->t)         v->WorkStage++;  else  break;
            case 1: (v->Y) = (v->A_t);                              if ((v->Time)>=(v->t*2))     v->WorkStage++;  else  break;
            case 2: (v->Y) = - (v->J_t) * (v->Time) + (v->J_t)*(v->t*3);


            if ((v->Time)>=(v->t*3))
              {
              (v->WorkStage)=0; v->InitStage=3; v->Y=0; v->A_t=0;v->BRT=0;  break;
              }
            else  break;


      case 3: (v->Y) = (v->J_t) * (v->Time)  ; // (v->BRWS > 0) ? ( (v->BRWS > 1) ?  :(v->A_t * 3) ) :
      switch (v->BRWS)
      {
      case 0:
      v->Y += (v->BRY + v->BRY ); break;
      case 1:
      v->Y += (v->A_t - (v->J_t) * (v->BRT));break;
      case 2:
      (v->Y) = -(-v->J_t) * (v->Time)+ (-v->J_t)*(v->t*3)  ;break;


}
        if ((v->Y>=-1)&&(v->Y<=1))
              {
              (v->WorkStage)=0; v->InitStage=1; v->Y=0; v->A_t=0;v->BRT=0; v->BRWS = 0; v->BRY = 0;
              v->P_t = v->Y2; v->V_t = v->Y1; v->N_t ++;
              if (v->Dir < 0 )
              { v->N_t = 0;}



              break;
              }
            else  break;


          }
    break;
    case 3:
          if ((v->Dir == -1)|| (v->Y2 <= Data[0]))
           {
             if  ((v->N_t) == 0)
               {(v->InitStage)=0;  v->Dir=0;}
               else
               {(v->InitStage)=1; v->N_t=v->N_t-1;}
           }
          if (v->Dir ==  1)
           {
             if  (((v->N_t) >= (*v->N-1))|| (v->Y2 >= Data[(v->N_t_max - 1)<<1]) )
             {(v->InitStage)=0;  v->Dir=0; }
             else
             {(v->InitStage)=1; v->N_t=v->N_t+1;}

           }
    break;

}

v->Y1    = ((v->InitStage) == 0) ? v->V_t :((v->Y1) + (v->Y)*(v->SampleTime));
v->Y2    = ((v->InitStage) == 0) ? v->P_t :((v->Y2) + (v->Y1)*(v->SampleTime) * (v->Dir));
v->Time  = ((v->InitStage) == 0) ? 0      :((v->Time)+(v->SampleTime));

v->P=__IQ(v->Y2,20);
v->V=__IQ(v->Y1,21);
v->A=__IQ(v->Y,21);

v->No = S_Pref;
v->N1 = v->N_t;

}


