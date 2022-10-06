#define FORWARD_EULER 0
#define BACKWARD_EULER 1
#define TRAPEZOIDAL 2
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
 if ( !*v->En )
 {
   v->Out = 0;
   v->prevIn = 0;
   v->prevOut = 0;
   v->Init_Condition = 0;
   return;
 }

 switch (v->Method)
 {
   case FORWARD_EULER:
   //y(n) = y(n-1) + K*[t(n) - t(n-1)]*u(n-1)
     if ( (v->Out >= *v->Sat) && !*v->Res)
     {
       v->Out = *v->Sat;
     }
     else
     {
       switch (v->Init_Condition)
       {
         case 0:
           v->Out = v->prevOut + _IQ24mpy(v->SampleTime, v->prevIn) + *v->Init_Value;
           v->prevIn = *v->In;
           v->prevOut = v->Out;
           v->Init_Condition = 1;
         break;

         case 1:
         if (v->ResetType)
          {
            v->Out = v->prevOut + _IQ24mpy(v->SampleTime, v->prevIn);
            v->prevIn = *v->In;
            v->prevOut = v->Out;
          }
          else
          {
            v->Out = (v->prevOut + _IQ24mpy(v->SampleTime, v->prevIn) % __IQ(1.0, 24) ); //limit to 1
            v->prevIn = *v->In;
            v->prevOut = v->Out;
          }
         break;
        }
     }
     if ( *v->Res && v->ResetType  )
     {
       v->prevIn = 0;
       v->prevOut = 0;
     }
   break;

   case BACKWARD_EULER:
    //y(n) = y(n-1) + K*[t(n) - t(n-1)]*u(n)
     if ( (v->Out >= *v->Sat) && !*v->Res)
     {
       v->Out = *v->Sat;
     }
     else
     {
       switch (v->Init_Condition)
       {
         case 0:
           v->Out = v->prevOut + _IQ24mpy(v->SampleTime, *v->In) + *v->Init_Value;
           v->prevOut = v->Out;
           v->Init_Condition = 1;
         break;

         case 1:
         if (v->ResetType)
         {
           v->Out = v->prevOut + _IQ24mpy(v->SampleTime, *v->In);
           v->prevIn = *v->In;
           v->prevOut = v->Out;
         }
         else
         {
           v->Out = (v->prevOut + _IQ24mpy(v->SampleTime, *v->In) % __IQ(1.0, 24) );
           v->prevIn = *v->In;
           v->prevOut = v->Out;

         }
         break;
        }
     }
     if ( *v->Res && v->ResetType  )
     {
       v->prevIn = 0;
       v->prevOut = 0;
     }
   break;

   case TRAPEZOIDAL:
   //y(n) = y(n-1) + K*[t(n)-t(n-1)]*[u(n)+u(n-1)]/2
     if ( (v->Out >= *v->Sat) && !*v->Res)
     {
       v->Out = *v->Sat;
     }
     else
     {
       switch (v->Init_Condition)
       {
         case 0:
           v->Out = v->prevOut + _IQ24mpy(v->SampleTime >> 1, (v->prevIn + *v->In) ) + *v->Init_Value;
           v->prevIn = *v->In;
           v->prevOut = v->Out;
           v->Init_Condition = 1;
         break;

         case 1:
         if (v->ResetType)
         {
           v->Out = v->prevOut + _IQ24mpy(v->SampleTime >> 1, (v->prevIn + *v->In) );
           v->prevIn = *v->In;
           v->prevOut = v->Out;
         }
         else
         {
           v->Out = (v->prevOut + _IQ24mpy(v->SampleTime >> 1, (v->prevIn + *v->In) ) % __IQ(1.0, 24) );
           v->prevIn = *v->In;
           v->prevOut = v->Out;
         }
         break;
        }
     }

     if ( *v->Res && v->ResetType  )
     {
       v->prevIn = 0;
       v->prevOut = 0;
     }
   break;
 }


}
