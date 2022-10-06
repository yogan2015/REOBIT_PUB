
void Init(void)
{
}

void Exec(void)
{
  v->Out = MBS_getData(v->Index);
  if ((short)*v->R || (*v->In == v->Out)) return;
  MBS_setData(v->Index, *v->In, v->Memory);
}


