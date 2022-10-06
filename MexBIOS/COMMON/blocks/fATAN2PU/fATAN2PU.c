
void Init(void)
{
}

void Exec(void)
{
  if ((*v->In1 == 0) && (*v->In2 == 0)) v->Out = 0;  
  else v->Out = atan2pu(*v->In1, *v->In2);	
}

