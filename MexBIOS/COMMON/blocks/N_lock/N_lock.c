
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->locked = !(abs(*v->In) >= v->l_loose) && ((abs(*v->In) <= v->l_narrow) || v->locked);
  v->Out = v->locked;
}

