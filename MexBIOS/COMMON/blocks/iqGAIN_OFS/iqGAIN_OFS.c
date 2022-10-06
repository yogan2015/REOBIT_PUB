
void Init(void)
{
}

void Exec(void)
{
  v->Out = __IQmpy(*v->In - v->Offset, v->Gain, v->Format);
}

