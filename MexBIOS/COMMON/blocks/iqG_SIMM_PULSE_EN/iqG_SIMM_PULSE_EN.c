
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->En && !v->Flag) v->Flag = 1;

  if (v->Flag != 0) v->Time += v->SampleTime;
  if ((v->Time > v->Time_Pulse) && (v->Flag == 1)) { v->Time = 0; v->Flag = 2; }
  if ((v->Time > v->Time_Pulse) && (v->Flag == 2)) { v->Time = 0; v->Flag = 1; }

  if (!(short)*v->En) { v->Time = 0; v->Out = 0; v->Flag = 0; }
  else if (v->Flag == 1) v->Out = v->Ampl;
  else v->Out = 0;
}

