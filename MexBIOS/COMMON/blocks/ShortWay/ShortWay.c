
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{

int sRef, sFeed, delta_feed, delta_ref, delta_mid, sRefPrev;

sRef=*v->pos_ref;
sFeed=*v->pos_feed;
if (*v->En)
{
  if (*v->pos_Max  ==  *v->pos_Min)
  { // Esli min=max or 0=1 or 1=0 -> ShortWay
    delta_ref  = sRef  -   v->prevPos_ref;
    if (
        ((sRef)!=(v->prevPos_ref))||((*v->En) != (v->prevEn))
       )
    {
     if        (delta_ref   >=  _IQ24(0.5))
     {
                v->PosRef_One_Loop  = v->PosRef_One_Loop  -  _IQ24(1.0);
     }
     else if   (delta_ref  <   _IQ24(-0.5))
     { // Esli zadanie menshe OS
                v->PosRef_One_Loop  = v->PosRef_One_Loop  +  _IQ24(1.0);
     }
     v->PosRef_One_Loop_Out  =  v->PosRef_One_Loop + sRef;
    }
     if ((v->PosRef_One_Loop_Out  -  sFeed)  >= _IQ24(0.5))
     {
        v->PosRef_One_Loop = v->PosRef_One_Loop  -  _IQ24(1.0);
        v->PosRef_One_Loop_Out  =  v->PosRef_One_Loop + sRef;
     }
     else if    ((v->PosRef_One_Loop_Out  -  sFeed)  <   _IQ24(-0.5))
     {
        v->PosRef_One_Loop  = v->PosRef_One_Loop  +  _IQ24(1.0);
        v->PosRef_One_Loop_Out  =  v->PosRef_One_Loop + sRef;
     }
    v->prevPos_ref   = *v->pos_ref;
    v->prevPos_feed  = *v->pos_feed;
    } // EOF ShortWay
  else if (*v->pos_Max  >  *v->pos_Min)
  { // Esli  dis Sector Enable 0Y[posMin;posMax]
     delta_mid= ((((*v->pos_Max) - (*v->pos_Min))>>1) + (*v->pos_Min)+_IQ24(0.5))%((1<<24)-1);
     if ((sRef<(*v->pos_Max))&&(sRef>(*v->pos_Min)))
     {
      v->PosRef_One_Loop_Out = sRef;
      v->prevPos_ref   = *v->pos_ref;
      v->prevPos_feed  = *v->pos_feed;
     }
     else if(sRef == *v->pos_Max)    //этот случай возникает при работе по скорости, поэтому рассмотрим отдельно
     {
         if(*v->pos_feed > delta_mid)
         {
           v->PosRef_One_Loop_Out = 1 << 24;
         }
         else
         {
           v->PosRef_One_Loop_Out = sRef;
         }
     }
     else if(sRef == *v->pos_Min)    //этот случай возникает при работе по скорости, поэтому рассмотрим отдельно
     {
         if(*v->pos_feed > delta_mid)
         {
           v->PosRef_One_Loop_Out = 1 << 24;
         }
         else
         {
           v->PosRef_One_Loop_Out = sRef;
         }
     }
     else
     {
       if(delta_mid>(*v->pos_Max))      //если средняя точка мертвого сектора больше макс позиции (наш случай)
       {
          if((sRef  > (*v->pos_Max))&&(sRef < delta_mid))    //если заданная позиция больше правого предела но меньше средней точки
          {
            if(*v->pos_feed < delta_mid)      //если текущее положение меньше средней точки
                v->PosRef_One_Loop_Out =  *v->pos_Max;    //едем в правый предел
            else            //иначе
                v->PosRef_One_Loop_Out =  1 << 24;    //сначала уезжаем в 0
            v->prevPos_ref   = *v->pos_Max;
            v->prevPos_feed  = *v->pos_feed;
          }
          else if(sRef > delta_mid)    //если заданная позиция больше средней точки
          {
            if(*v->pos_feed < delta_mid && *v->pos_feed > *v->pos_Max)    //если текущая позиция меньше центра и больше правого предела
              v->PosRef_One_Loop_Out =  *v->pos_Max;
            else if(*v->pos_feed > delta_mid)       //если текущая позиция больше центра
              v->PosRef_One_Loop_Out =  1 << 24;    //уезжаем в 0
            else
              v->PosRef_One_Loop_Out =  *v->pos_Min;  //иначе едем в левый предел
            v->prevPos_ref   = *v->pos_Min;
            v->prevPos_feed  = *v->pos_feed;
          }
       }
       if   (delta_mid<(*v->pos_Min))
       {
          if   (
                 (sRef  < (*v->pos_Min))
                  &&
                 (sRef > delta_mid)
                )
          {
            v->PosRef_One_Loop_Out =  *v->pos_Min;
            v->prevPos_ref   = *v->pos_Min;
            v->prevPos_feed  = *v->pos_feed;
          }
          else
          {
            v->PosRef_One_Loop_Out =  *v->pos_Max;
            v->prevPos_ref   = *v->pos_Max;
            v->prevPos_feed  = *v->pos_feed;
          }
       }
     }


  } // EOF disSector EN and  "0" point INCLUDED in sector
  else if (*v->pos_Min  >  *v->pos_Max)
  {
    delta_mid= ((((*v->pos_Min) - (*v->pos_Max))>>1) + (*v->pos_Max))%((1<<24)-1);
    if (
        ( *v->pos_ref !=(v->prevPos_ref))
        ||
        ((*v->En) != (v->prevEn))
       )
    {
        sRefPrev = v->prevPos_ref;
      if ((sRef > (*v->pos_Max)) && (sRef < (*v->pos_Min)))
      {
        if  ((*v->pos_ref) <= delta_mid)
        {
        sRef = *v->pos_Max;
        }
        else if ((*v->pos_ref) > delta_mid)
        {
        sRef = *v->pos_Min;
        }

        if ((v->prevPos_ref > (*v->pos_Max)) && (v->prevPos_ref < (*v->pos_Min)))
        {
          if  ((v->prevPos_ref) <= delta_mid)
          {
            sRefPrev = *v->pos_Max;
          }
          else if ((v->prevPos_ref) > delta_mid)
          {
            sRefPrev = *v->pos_Min;
          }

         }
      }
      if (
          ((sRefPrev) >= (*v->pos_Min))
           &&
          (sRef   <=  (*v->pos_Max))
          )
      {
                v->PosRef_One_Loop  = v->PosRef_One_Loop  +  _IQ24(1.0);
      }
      else if (
               ((sRefPrev)  <=   (*v->pos_Max))
               &&
               (sRef >= (*v->pos_Min))
              )
      { // Esli zadanie menshe OS
                v->PosRef_One_Loop  = v->PosRef_One_Loop -  _IQ24(1.0);
      }
      v->PosRef_One_Loop_Out  =  sRef +  v->PosRef_One_Loop;
    }
    v->prevPos_ref   = *v->pos_ref;
  }
}
else if(!(*v->En))
  {
    v->PosRef_One_Loop_Out = sFeed=*v->pos_feed;

  }
/* If disSector EN and  "0" point INCLUDED in sector */


v->prevEn        = *v->En;
v->prevPos_ref   = *v->pos_ref;
v->prevPos_feed  = *v->pos_feed;
}

