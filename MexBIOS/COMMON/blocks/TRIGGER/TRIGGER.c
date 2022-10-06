

void Init(void)
{
  v->Q = v->Init_State;
}

void Exec(void)
{
   v->Time = 0;
   switch (v->CLK_Mode)
   {
   //Rising
    case 1: if(*v->CLK > v->CLK_Prev) v->Time = 1; break;
   //Falling
    case 2: if(*v->CLK < v->CLK_Prev) v->Time = 1; break;
   //Positive
    case 3: if(*v->CLK == 1) v->Time = 1; break;
   //Negative
    case 4: if(*v->CLK == 0) v->Time = 1; break;
   //Continuous
    case 5: v->Time = 1; break;
   }
   v->CLK_Prev = *v->CLK;

     if (v->Time)
    {
     switch (v->Type)
      {
    //D-TRIGGER
        case 0: v->Q = *v->D; break;
    //RS-TRIGGER
        case 1:
          if (v->RS_Priority)
          {
            if (*v->S) v->Q = 1;
            if (*v->R) v->Q = 0;
          }
          else
          {
            if (*v->R) v->Q = 0;
            if (*v->S) v->Q = 1;
          }
        break;
    //JK-TRIGGER
        case 2:
          if (*v->J && *v->K)
          {
            v->Q = !v->Q;
          }
          else
          {
            if (*v->J) v->Q = 1;
            if (*v->K) v->Q = 0;
          }
        break;
    //T-TRIGGER
        case 3: v->Q = !v->Q; break;
      }
     }
   v->nQ = !v->Q;
}

