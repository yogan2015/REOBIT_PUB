
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{

  if(!(*v->Manual_Control))
  {
    if(v->Timer_On_Off)
    {
      v->Timer += v->SampleTime;
    }
    else
    {
      v->Timer = 0;
    }

    v->Analog_Output = *v->Omega_Feed_Back;

    if(MBS_getData(v->Protect_Word))
    {
      v->Timer_On_Off = 0;
      MBS_setData(v->Alarm_Output, 1, 0);
      MBS_setData(v->Pusk_Output, 0, 0);
      MBS_setData(v->Omega_Reference, 0, 0);
      MBS_setData(v->PWM_Enable, 0, 0);
    }
    else
    {
      MBS_setData(v->Alarm_Output, 0, 0);
      if(MBS_getData(v->PWM_Enable))
      {
        if(v->Stopping)
        {
          MBS_setData(v->Omega_Reference, 0, 0);
          if(labs(*v->Omega_Feed_Back) < _IQ(0.05))
          {
              MBS_setData(v->PWM_Enable, 0, 0);
              v->Stopping = 0;
          }
          if(MBS_getData(v->Pusk_Input))
          {
            v->Timer_On_Off = 1;
          }
          else
          {
            if((v->Timer < v->PWM_On_Delay) && (v->Timer > 0))
            {
              MBS_setData(v->PWM_Enable, 1, 0);
              v->Stopping = 0;
            }
            v->Timer_On_Off = 0;
          }
        }
        else
        {
          MBS_setData(v->Omega_Reference, *v->Analog_Input, 0);
          MBS_setData(v->Pusk_Output, 1, 0);
          if(MBS_getData(v->Stop_Input))
          {
            v->Timer_On_Off = 1;
          }
          else
          {
            if((v->Timer < v->PWM_On_Delay) && (v->Timer > 0))
            {
              if(v->Vibeg)
              {
                MBS_setData(v->PWM_Enable, 0, 0);
              }
              else
              {
                v->Stopping = 1;
              }
            }
            v->Timer_On_Off = 0;
          }
        }
      }
      else
      {
        MBS_setData(v->Omega_Reference, 0, 0);
        MBS_setData(v->Pusk_Output, 0, 0);
        if(MBS_getData(v->Pusk_Input))
        {
          v->Timer_On_Off = 1;
        }
        else
        {
          if((v->Timer < v->PWM_On_Delay) && (v->Timer > 0))
          {
            MBS_setData(v->PWM_Enable, 1, 0);
          }
          v->Timer_On_Off = 0;
        }
      }
    }
  }
}


