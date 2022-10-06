
void Init(void)
{
}

void Exec(void)
{
  v->Out = ((float)((unsigned short)*v->In) - v->Offset) * v->Gain;
}

