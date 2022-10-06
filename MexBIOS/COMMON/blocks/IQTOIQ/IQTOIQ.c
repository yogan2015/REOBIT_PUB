
void Init(void)
{
}

void Exec(void)
{
  v->Out = _IQtoIQ(*v->In, v->Format1, v->Format2);
}

