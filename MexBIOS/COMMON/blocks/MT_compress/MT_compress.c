
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = (_IQtoIQ(*v->a, 24, 8) << 16) | (_IQtoIQ(*v->b, 24, 8) & 0xFFFF);
}

