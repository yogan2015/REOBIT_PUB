#define _2pi 6.283185307179
#define _2pidiv 0.159154943092
#define Sin_Base_Gain 1.44632763
#define Cos_Base_Gain 1.44683856
#define Sin_Base_Offset 0
#define Cos_Base_Offset 14
#define fi_X_Base 5.53556627
#define fi_Y_Base 5.44044572
#define delta_fi_Base 0.09512055
#define clockwise 1
#define counter_clockwise 2


#ifndef __BORLANDC__
#include "stm32f4xx.h"
#include "boards.h"
#endif

void Init(void)
{

}

void Exec(void)
{
#ifndef __BORLANDC__

switch (v->State)
  {
  case 0:
    v->CNT = 0;
    v->Angle = 0;
    v->Flag = 0;
  v->rotation = 0;
    v->Time = _IQ24(0.0);

    //Cos scale
    v->cos_out = _IQ24mpy((_IQtoIQ(*v->cos, v->Format, 24) - v->MidOffs_cos), v->MidGain_cos);

    //Sin Scale
    v->sin_out = _IQ24mpy((_IQtoIQ(*v->sin, v->Format, 24) -  v->MidOffs_sin), v->MidGain_sin);

    //Sin with orth correction scale
    v->sin_out_korr = _IQ24div((v->sin_out - _IQ24mpy(v->cos_out, _IQ24sin(-v->delta_fi))),_IQ24cos(-v->delta_fi));

    //vosstavlivaem 1 garmoniku sinusa
    v->SinHarm1 = Read_SinCorr(_IQsat((_IQsat
    (_IQ24mpy((v->sin_out_korr + _IQ24(1.0)), _IQ24(0.5)),
    _IQ24(0.999), _IQ24(0.0))>>14), 1023, 0)) << 15;

   //vosstavlivaem 1 garmoniku cosinusa
    v->CosHarm1 = Read_CosCorr(_IQsat((_IQsat
    (_IQ24mpy((v->cos_out + _IQ24(1.0)), _IQ24(0.5)),
    _IQ24(0.999), _IQ24(0.0))>>14), 1023, 0)) << 15;

    //Sin Correction
    v->sin_korr = v->sin_out_korr - _IQ24mpy(v->sin_out_korr - v->SinHarm1, *v->Gain_Of_Sin_3rd_Harm);

     //Cos Correction
    v->cos_korr = v->cos_out - _IQ24mpy(v->cos_out - v->CosHarm1, *v->Gain_Of_Cos_3rd_Harm);

    //Angel Calc
    v->theta = (_IQ24atan2PU(v->sin_korr, v->cos_korr) + v->Angle_Offset) % 16777216;

    if ((v->Start) && !(*v->Protect))
    {
     v->Time = _IQ24(0.0);
     v->State = 1;
    }
  break;

  case 1: //Aligment

    v->CorrectionErr = 0;
    v->theta = _IQ24(0.0);
    v->Flag = 1; //when Flag = 1 we need to reset pos and speed contorllers and ref: Id = var, Iq = 0;
    if (v->Flag != v->PrevFlag)
    {
      //Reset MaxMin
      v->Max_sin = 0;
      v->Max_cos = 0;
      v->Min_sin = __IQ(1.0, v->Format );
      v->Min_cos = __IQ(1.0, v->Format );
    }
    v->Time += v->SampleTime;
    if (v->Time > *v->Aligment_Time)
    {
      v->Time = _IQ24(0.0);
      v->State = 2;
      v->rotation = clockwise;
    }
     v->PrevFlag = v->Flag;
  break;

  case 2: //gain offset calculation

    //Max of sin calc
    if ((*v->sin) > (v->Max_sin)) v->Max_sin = *v->sin;
    //Max of cos calc
    if ((*v->cos) > (v->Max_cos)) v->Max_cos = *v->cos;
    //Min of sin calc
    if ((*v->sin) < (v->Min_sin)) v->Min_sin = *v->sin;
    //Min of cos calc
    if ((*v->cos) < (v->Min_cos)) v->Min_cos = *v->cos;

    v->Time += v->SampleTime;

    //electric angle counter (Reference)
    if (v->Time > *v->Angle_Ref_Time) //Time_1 vremya v techenie kotorogo derzhim 1 edinicy el ugla
    {
      v->Time = _IQ24(0.0);
    if (v->rotation == clockwise) v->Angle++;
    if (v->rotation == counter_clockwise) v->Angle--;
    }
  //if clockwise rotation
  if (v->rotation == clockwise)
  {
    //if rotor turned on 360 el degrees
      if (v->Angle == __IQ(1.0, v->Format))
      {
        v->Time = _IQ24(0.0);
        v->Angle = 0;
        v->CNT++;
      }
  }
  //if counter clockwise rotation
  if (v->rotation == counter_clockwise)
  {
  //if rotor turned on 360 el degrees
      if (v->Angle == __IQ(0.0, v->Format))
      {
        v->Time = _IQ24(0.0);
        v->Angle = __IQ(1.0, v->Format);
        v->CNT ++;
    }
  }

    v->theta = (v->Angle << (24 - v->Format) );

    // if rotor turned on reference mechanical degree
    if (v->CNT == *v->Zp)
    {
      v->Time = _IQ24(0.0);
      v->State = 3;
    }

  break;

  case 3: //Calc SinCos phase error
    v->Angle = 0;
  v->theta = _IQ24(0.0);
    v->Time += v->SampleTime;
    if (v->Time > *v->Aligment_Time)
    {
      if (v->rotation == clockwise)
      {
        //Gain and offset calc
        v->Offs_sin = ((v->Max_sin + v->Min_sin) >> 1);
        v->Offs_cos = ((v->Max_cos + v->Min_cos) >> 1);
        v->Gain_sin =  _IQ24div(_IQ24(1.0), _IQtoIQ(((v->Max_sin - v->Min_sin)>>1), v->Format, 24));
        v->Gain_cos =  _IQ24div(_IQ24(1.0), _IQtoIQ(((v->Max_cos - v->Min_cos)>>1), v->Format, 24));
        //Sin and cos scale
        v->sin_out = _IQ24mpy((_IQtoIQ(*v->sin - v->Offs_sin, v->Format,24)), v->Gain_sin);
        v->cos_out = _IQ24mpy((_IQtoIQ(*v->cos - v->Offs_cos, v->Format,24)), v->Gain_cos);
        //Phase correction calc
        v->fi_x1 = _IQ24(_2pi) - __IQ(acosf(__IQtoF(v->cos_out, 24)), 24);
        v->fi_y1 = _IQ24(_2pi) + __IQ(asinf(__IQtoF(v->sin_out, 24)), 24);

        v->Time = _IQ24(0.0);
        v->CNT = 0;
        v->State = 4;
      }
      if (v->rotation == counter_clockwise)
      {
        v->Time = _IQ24(0.0);
        v->CNT = 0;
        v->State = 5;
      }
    }
  break;

  case 4:
  v->theta = _IQ24(0.25); //turn on 90 electrical degrees clockwise
  v->Time += v->SampleTime;
  if (v->Time > _IQ24(1.0))
  {
    v->Angle = __IQ(1.0, v->Format);
    v->theta = _IQ24(0.0); //turn back on 90 electrical degrees
    if (v->Time > _IQ24(2.0))
    {
      v->Time = _IQ24(0.0);
      v->rotation = counter_clockwise;
      //Reset MaxMin
      v->Max_sin = 0;
      v->Max_cos = 0;
      v->Min_sin = __IQ(1.0, v->Format );
      v->Min_cos = __IQ(1.0, v->Format );
      v->State = 2;
    }
  }
  break;

  case 5:
    v->MidOffs_sin = _IQ24mpy(_IQtoIQ(v->Offs_sin + ((v->Max_sin + v->Min_sin) >> 1), v->Format, 24), _IQ24(0.5));
    v->MidOffs_cos = _IQ24mpy(_IQtoIQ(v->Offs_cos + ((v->Max_cos + v->Min_cos) >> 1), v->Format, 24), _IQ24(0.5));
    v->MidGain_sin = _IQ24mpy(v->Gain_sin + _IQ24div(_IQ24(1.0), _IQtoIQ(((v->Max_sin - v->Min_sin)>>1), v->Format, 24)), _IQ24(0.5));
    v->MidGain_cos = _IQ24mpy(v->Gain_cos + _IQ24div(_IQ24(1.0), _IQtoIQ(((v->Max_cos - v->Min_cos)>>1), v->Format, 24)), _IQ24(0.5));
   //Gain and offset calc
    v->Offs_sin = ((v->Max_sin + v->Min_sin) >> 1);
    v->Offs_cos = ((v->Max_cos + v->Min_cos) >> 1);
    v->Gain_sin =  _IQ24div(_IQ24(1.0), _IQtoIQ(((v->Max_sin - v->Min_sin)>>1), v->Format, 24));
    v->Gain_cos =  _IQ24div(_IQ24(1.0), _IQtoIQ(((v->Max_cos - v->Min_cos)>>1), v->Format, 24));
    //Sin and cos scale
    v->sin_out = _IQ24mpy((_IQtoIQ(*v->sin - v->Offs_sin, v->Format,24)), v->Gain_sin);
    v->cos_out = _IQ24mpy((_IQtoIQ(*v->cos - v->Offs_cos, v->Format,24)), v->Gain_cos);
    //Phase correction calc
    v->fi_x1 = _IQ24mpy(v->fi_x1 + _IQ24(_2pi) - __IQ(acosf(__IQtoF(v->cos_out, 24)), 24), _IQ24(0.5));
    v->fi_y1 = _IQ24mpy(v->fi_y1 +_IQ24(_2pi) + __IQ(asinf(__IQtoF(v->sin_out, 24)), 24), _IQ24(0.5));
    v->delta_fi = v->fi_x1 - v->fi_y1;
    v->State = 6;

    v->Angle_Offset = _IQ24(1.0) - _IQ24div(v->fi_x1, _IQ24(_2pi));

  break;

 case 6:
      //Errors of gain and offset calculation check
      if (  ( (v->Gain_sin > *v->GainErr) && (v->Gain_sin < (_IQ24(1.0) + *v->GainErr)) )
      && ( (v->Gain_cos > *v->GainErr) && (v->Gain_cos < (_IQ24(1.0) + *v->GainErr)) )
      && ( (v->Offs_sin > -*v->OffsetErr) && (v->Offs_sin < *v->OffsetErr) )
      && ( (v->Offs_cos > -*v->OffsetErr) && (v->Offs_cos < *v->OffsetErr) ) )
      {
        v->PrevFlag = 0;
        v->Start = 0;
        v->State = 7;
      }
      else
      {
        v->CorrectionErr = 1;
        v->State = 8;
      }
  break;

  case 7:

      v->Time += v->SampleTime;
      MBS_setData(v->Index, 1, 0); //WriteToEeproom
      if (v->Time >= _IQ24(0.0004)) //delay for command to write
      {
        MBS_setData(v->Index, 0, 0);
        v->State = 0;
        v->Time = _IQ24(0.0);
      }
  break;

  case 8:
    v->Start = 0;
    v->theta = _IQ24(0.0);

    v->Time += v->SampleTime;

    if (v->Time > _IQ24(5.0))
    {
      v->PrevFlag = 0;

      v->Time = _IQ24(0.0);
      v->CorrectionErr = 0;
      v->MidOffs_sin = _IQtoIQ(Sin_Base_Offset, v->Format , 24);
      v->MidOffs_cos = _IQtoIQ(Cos_Base_Offset, v->Format, 24);
      v->MidGain_sin = _IQ24(Sin_Base_Gain);
      v->MidGain_cos = _IQ24(Cos_Base_Gain);
      v->fi_x1 = _IQ24(fi_X_Base);
      v->fi_y1 = _IQ24(fi_Y_Base);
      v->delta_fi = _IQ24(delta_fi_Base);
      v->State = 0;
  }

  break;
  }
#endif

}
