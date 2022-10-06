
void Init(void)
{
}

void Exec(void)
{
  float DeltaStep;

  if ((short)*v->R) { v->Out = ((short)*v->R & 0x2) ? *v->In : 0; v->DelayCount = 0; return; }
  if (v->Out == *v->In) { v->DelayCount = 0; return; }

  DeltaStep = (fabs(v->Out) < fabs(*v->In)) ? *v->Acc : *v->Dec;
  if (DeltaStep == 0) { v->Out = *v->In; return; }

  if (v->DelayCount < v->DelayMax) { v->DelayCount++; return; }
  v->DelayCount = 0;

  if (v->Out < *v->In)
  {
    v->Out += DeltaStep;
    if (v->Out > *v->In) v->Out = *v->In;
  }
  else
  {
    v->Out -= DeltaStep;
    if (v->Out < *v->In) v->Out = *v->In;
  }
}




