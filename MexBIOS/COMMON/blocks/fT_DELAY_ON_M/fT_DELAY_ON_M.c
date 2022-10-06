
void Init(void)
{
}

void Exec(void)
{
  if (!(short)*v->In || (v->Time_Del_ON < 0) ) { v->Out = 0; v->Time = 0; return; }
  v->Time += v->SampleTime;
  if (v->Time >= v->Time_Del_ON)
  {
    v->Out = *v->In;
    v->Time = v->Time_Del_ON;
  }
}

