
void Init(void)
{
}

void Exec(void)
{
  v->Out = __IQmpy(*v->In, v->Gain, v->Format);
}

