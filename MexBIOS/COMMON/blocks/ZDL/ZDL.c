
void Init(void)
{

}

void Exec(void)
{
  v->Out = v->Signal;
  v->Signal = *v->In;
}

