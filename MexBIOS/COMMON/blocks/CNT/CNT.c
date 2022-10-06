
void Init(void)
{
  v->Index = v->StartValue;
}

void Exec(void)
{
  v->Pulse = 0;

  if ((short)*v->Stop) v->PassCounter = 0;
  else if (v->WorkMode) { if (v->State) v->Index = v->Index + v->Step; }
  else if (++v->PassCounter >= v->PassCount) { v->Index = v->Index + v->Step; v->PassCounter = 0; }
  v->State = (short)*v->Stop;

  if ((short)*v->R) { v->Index = v->StartValue; v->PassCounter = 0; }
  else if (v->Index > v->PosMax) { v->Pulse = 1; v->Index = v->NegMax; }
  else if (v->Index < v->NegMax) { v->Pulse = 1; v->Index = v->PosMax; }

  switch(v->OutMode)
  {
    case 0: v->Cnt = v->Index; break;
    case 1: v->Cnt = 1L << v->Index; break;
    case 2: v->Cnt = ~(1L << v->Index); break;
  }
}


