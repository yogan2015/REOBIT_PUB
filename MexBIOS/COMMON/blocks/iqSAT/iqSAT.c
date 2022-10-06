
void Init(void)
{
}

void Exec(void)
{
  v->Out = _IQsat(*v->In, v->Pos, v->Neg);
}

