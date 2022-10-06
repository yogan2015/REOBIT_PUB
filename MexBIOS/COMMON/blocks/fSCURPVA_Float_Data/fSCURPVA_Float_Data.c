  #define S_Pref   Data[0+ (v->N_t << 1)]
  #define S_Vref   Data[1+ (v->N_t << 1)]

  #define LASTPOINT 1
  #define FIRSTPOINT 0

  #define WAIT 0
  #define CALCMOVING 1
  #define MOVESECTION 2
  #define CALCSECTION 3
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  float *Data;
  float Am;


  Data = ((float *)(v->Buf) + 1) ;

if ((v->EnPrev!=*v->En)
   ||
   (v->NPrev!=*v->N)){ // Izmenilas Comanda ili N

   if  (*v->En == 1)        {  // Dvijenie Vpered
   v->Dir = 1;  // Dvijenie Vpered
   v->N_t=0;    // s 0 el.Massiva edem vpered
   v->InitStage = CALCMOVING;

   v->Y2   = S_Pref;            // Interator_Position  (float)
   v->P_t  = S_Pref;            // History_Position    (float)
   v->P    = S_Pref;            // Vihod_Position      (float)


   v->Y1   =  S_Vref;           // Integrator_Speed    (float)
   v->V_t  =  S_Vref;           // History_Speed       (float)
   v->V    =  S_Vref;           // Vihod_Speed         (float)

// Zapolnenie Nachalnih Tochec

// Zapolnenie Nachalnih Tochec
   } // EOF Ehat vpered

   else if (*v->En == -1)   { // Dvijenie Nazad
   v->InitStage = CALCMOVING;
   v->Dir  =   -1;            // Napravlenie
   v->N_t  = (*v->N)-1;         // s 0 el.Massiva edem vpered

   v->Y2   = S_Pref;            // Interator_Position  (float)
   v->P_t  = S_Pref;            // History_Position    (float)
   v->P    = S_Pref;            // Vihod_Position      (float)


   v->Y1   =  S_Vref;           // Integrator_Speed    (float)
   v->V_t  =  S_Vref;           // History_Speed       (float)
   v->V    =  S_Vref;           // Vihod_Speed         (float)

// Zapolnenie Nachalnih Tochec

// Zapolnenie Nachalnih Tochec
   } // EOF Ehat Nazad

   else if (*v->En == 0)    { // STOP
     if (v->EnPrev==1)        {v->NZeroState= LASTPOINT ;}
     else if (v->EnPrev==-1)  {v->NZeroState= FIRSTPOINT;}
         switch (v->NZeroState){
         case LASTPOINT:   // Uderjivat poslednuu Tochku
                          v->N_t = (*v->N)-1;
         break;
         case FIRSTPOINT:  // Uderjivat pervuyyu Tochku
                          v->N_t = 0;
         break;
         }// EOC LastPoint Fixed
     v->Dir=0; // Napravlenie STOP
     v->InitStage= WAIT ;
     } // EOF Udejivat Poziciu
} // EOF Izmenilas Comanda
  switch(v->InitStage)
  {
     case WAIT:         // WAIT

              v->Y2   = S_Pref;              // Interator_Position  (float)
              v->P_t  = S_Pref;              // History_Position    (float)
              v->P    = S_Pref;              // Vihod_Position      (float)


              v->Y1   =  S_Vref;             // Integrator_Speed    (float)
              v->V_t  =  S_Vref;             // History_Speed       (float)
              v->V    =  S_Vref;             // Vihod_Speed         (float)

              v->WorkStage = 0;               //
              v->Time=0;
              break;

     case CALCMOVING:   // CalcCoordinates

        v->WorkStage = 0;
        v->Time=0;

        v->MovePos  =   (S_Pref - v->P_t) * v->Dir;

        if (v->MovePos == 0) {
          v->InitStage  =  CALCSECTION;
        }
        else {
          Am = fabs(0.75*(S_Vref - v->V_t)*(S_Vref + v->V_t)/(v->MovePos));
          v->t= (v->MovePos * 0.666667) / (v->V_t + S_Vref);
          if       (v->V_t  <  S_Vref)   v->A_t=Am;
          else if  (v->V_t  >  S_Vref)   v->A_t=-Am;
          v->Y=0;
          v->Y1= v->V_t;
          v->J_t= v->A_t / v->t;
          v->V_t=S_Vref; // Fixed speed in the End Way
          v->P_t=S_Pref; // Fixed Position in the End Way
          v->InitStage = MOVESECTION;
         }
        break;

     case MOVESECTION:  // Moving
                      switch(v->WorkStage)
                      {
                            case 0: (v->Y) = (v->J_t) * (v->Time);                  if ((v->Time)>=v->t)         v->WorkStage++;  else  break;
                            case 1: (v->Y) = (v->A_t);                              if ((v->Time)>=(v->t*2.0))     v->WorkStage++;  else  break;
                            case 2: (v->Y) = - (v->J_t) * (v->Time) + (v->J_t)*(v->t*3.0);
                            if ((v->Time)>=(v->t*3.0)){
                                (v->WorkStage)=0;   v->InitStage = CALCSECTION ;   v->Y = 0;   v->A_t = 0;
                            }
                            break;
                      }
                      break;
     case CALCSECTION:  // CalcSection
                     if (v->Dir == -1) /*|| (v->Y2 <= Data[0])*/ {
                         if ((v->N_t) ==0){
                            (v->InitStage)  =  WAIT;         v->Dir=0;
                         }
                         else  {
                            (v->InitStage)  =  CALCMOVING;   v->N_t--;
                         }
                     }
                     else if (v->Dir ==  1) /*||(v->Y2 <= S_Pref))*/ {
                        if  ((v->N_t) >= (*v->N-1)) {
                            (v->InitStage)  =  WAIT;  v->Dir  =  0;
                        }
                        else {
                            (v->InitStage)  =  CALCMOVING; v->N_t++;
                        }
                     }
                     else if (v->Dir == 0) {
                        v->InitStage  =  WAIT;  v->Dir=0;
                     }
                     break;
   }





// Calc
v->Y1    = ((v->InitStage) != MOVESECTION) ? v->V_t :((v->Y1) + (v->Y)*(v->SampleTime));
v->Y2    = ((v->InitStage) != MOVESECTION) ? v->P_t :((v->Y2) + (v->Y1)*(v->SampleTime) * (v->Dir));
v->Time  = ((v->InitStage) != MOVESECTION) ? 0      :((v->Time)+(v->SampleTime));


// if (  ((v->InitStage) != MOVESECTION) && (v->Y2 >= Data[(v->N_t_max - 1)<<1]))  v->Y2 =  Data[(v->N_t_max - 1)<<1];

v->P = v->Y2;
v->V = v->Y1;
v->A = v->Y;

// Smena Komandi     //
v->EnPrev  = *v->En; //
v->NPrev   = *v->N;  //
//Smena Komandi      //
}



