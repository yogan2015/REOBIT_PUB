
void Init(void)
{
}

void Exec(void)
{
  v->Out = *v->In;
  if (v->Out > *v->Pos) v->Out = *v->Pos;
  if (v->Out < *v->Neg) v->Out = *v->Neg;
}

