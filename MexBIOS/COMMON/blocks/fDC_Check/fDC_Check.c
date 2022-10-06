void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->R)
  {
    v->UOut = 0;
    v->PrevOut = 0;
    v->Alarm = 0;
    v->Timer = 0;
    v->Status = 0;
    return;
  }

  if(v->PrevMode != *v->Mode)
  {
    v->Alarm = 0;
    v->Timer = 0;
    v->Status = 0;
    v-> UOut = *v->Udc;
    v->PrevOut = v->UOut;
  }

  if(v->Alarm)
  {
    v->Status = 0;
    v->Timer = 0;
  }
  else
  {
    if ((*v->Mode == 1) || (*v->Mode == 2))
    {
      if(v->Timer > (3 * v->Tf))
      {
        v->Status = 0;
      }
      else
      {
        v->Status = 1;
        v->Timer += v->SampleTime;

        if(*v->Mode == 1)
        {
          v->Tf = *v->TfCharge;
        }
        else if(*v->Mode == 2)
        {
          v->Tf = *v->TfDisCharge;
        }

        if (v->Tf != v->PrevTf)
        {
          v->K1 = v->SampleTime / (v->Tf + v->SampleTime);
          v->K2 = v->Tf        / (v->Tf + v->SampleTime);
          v->PrevTf = v->Tf;
        }

        if(*v->Mode == 1)
        {
          v->UOut = *v->Urst * v->K1 + v->PrevOut * v->K2;
        }
        else if(*v->Mode == 2)
        {
          v->UOut = v->PrevOut * v->K2;
        }

        v->PrevOut = v->UOut;
        v-> Percent_U = ((*v->Udc / v->UOut) * 100) - 100;

        if(v->Percent_U > v->HighLevel)
        {
          v->Alarm = 1;
        }
        else if(v->Percent_U < v->LowLevel)
        {
          v->Alarm = 1;
        }
      }
    }
    else
    {
      v->Timer = 0;
    }
  }

  v-> Udc_out = *v-> Udc;
  v->PrevMode = *v->Mode;
}

