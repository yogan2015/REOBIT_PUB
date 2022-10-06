
void Init(void)
{
}

void Exec(void)
{
  long DeltaStep;

  if ((short)R || (Out == In)) { Out = In; DelayCount = 0; return; }

  DeltaStep = (labs(Out) < labs(In)) ? Acc : Dec;
  if (DeltaStep == 0) { Out = In; return; }

  if (DelayCount < DelayMax) { DelayCount++; return; }
  DelayCount = 0;

  if (Out < In)
  {
    Out += DeltaStep;
    if (Out > In) Out = In;
  }
  else
  {
    Out -= DeltaStep;
    if (Out < In) Out = In;
  }
}




