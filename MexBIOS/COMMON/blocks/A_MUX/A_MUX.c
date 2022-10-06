
void Init(void)
{

}

void Exec(void)
{
  short Index = (short)*v->Sel;
  if ((Index < 0) || (Index >= (v->NumIn-1))) v->Out = 0;
  else v->Out = *(&v->In0)[Index];
}

