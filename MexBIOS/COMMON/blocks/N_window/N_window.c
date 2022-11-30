
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = (*v->In > *v->low) && (*v->In < *v->high);
}

