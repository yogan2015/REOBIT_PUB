
void Init(void)
{
}

void Exec(void)
{
  v->Out = __IQmpy((long)((unsigned short)*v->In) - v->Offset, v->Gain, v->Format);
}

