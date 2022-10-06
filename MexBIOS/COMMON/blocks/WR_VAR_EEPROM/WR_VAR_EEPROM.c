
void Init(void)
{
}

void Exec(void)
{
  v->Out = MBS_getData(v->Index);
  if ((short)*v->R) return;
  MBS_setData(v->Index, *v->In, v->Memory);
}


