
void Init(void)
{
  v->Cnt = v->StartValue;
}

void Exec(void)
{
  v->Pulse = 0;

  if ((short)*v->Stop) v->PassCounter = 0;
  else if (v->WorkMode) { if (v->State) v->Cnt = v->Cnt + v->Step; }
  else if (++v->PassCounter >= v->PassCount) { v->Cnt = v->Cnt + v->Step; v->PassCounter = 0; }
  v->State = (short)*v->Stop;

  if ((short)*v->R) { v->Cnt = v->StartValue; v->PassCounter = 0; }

  if (v->Cnt > v->PosMax) { v->Pulse = 1; v->Cnt = v->NegMax; } else
  if (v->Cnt < v->NegMax) { v->Pulse = 1; v->Cnt = v->PosMax; }
}


