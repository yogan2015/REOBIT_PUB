
void Init(void)
{

}

void Exec(void)
{
long *InArr = (long *)(*v->In);
long  Index = (long)*v->Sel -1;


  if ((Index < 0) || (Index >= (v->Num))) v->Out = 0;

  else v->Out = InArr[Index];
}

