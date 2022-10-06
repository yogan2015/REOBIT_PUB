
void Init(void)
{
}

void Exec(void)
{
  if (_IQabs(TargetValue - SetpointValue) > DeltStep)
  {
    if (++RampDelayCount >= RampDelayMax)
    {
      if (TargetValue >= SetpointValue)
      {
        SetpointValue += DeltStep;
        if (SetpointValue > RampHighLimit) SetpointValue = RampHighLimit;
       }
       else
       {
         SetpointValue -= DeltStep;
         if (SetpointValue < RampLowLimit) SetpointValue = RampLowLimit;
       }
       RampDelayCount = 0;
    }
  }
  else
  {
    SetpointValue = TargetValue;
  }
}




