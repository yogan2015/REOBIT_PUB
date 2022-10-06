
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->En && !v->Flag) v->Flag = 1;

  if (v->Flag != 0) v->Time += v->SampleTime;
  if ((v->Time > v->Time_Pulse_ON)  && (v->Flag == 1)) { v->Time = 0; v->Flag = 2; }
  if ((v->Time > v->Time_Pulse_OFF) && (v->Flag == 2)) { v->Time = 0; v->Flag = 1; }

  if (!(short)*v->En) { v->Time = 0; v->Out = 0; v->Flag = 0; }
  else if (v->Flag == 1) v->Out = (short)*v->Inv ? 0 : v->Ampl;
  else if (v->Flag == 2) v->Out = (short)*v->Inv ? v->Ampl : 0;
  else v->Out = 0;
}

