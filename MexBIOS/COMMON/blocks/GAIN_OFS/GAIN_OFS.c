
void Init(void)
{
}

void Exec(void)
{
  v->Out = (*v->In - v->Offset) * v->Gain;
}

