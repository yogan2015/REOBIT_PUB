
void Init(void)
{
}

void Exec(void)
{
  v->Out = __IQtoF(__IQ(*v->In, v->Format) % __IQ(v->Max, v->Format), v->Format);
}

