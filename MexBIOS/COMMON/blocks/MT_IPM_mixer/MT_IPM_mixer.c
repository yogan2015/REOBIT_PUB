
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (!*v->SWAP)
  {
    v->_a0 = *v->a0;  v->_b0 = *v->b0;
    v->_a1 = *v->a1;  v->_b1 = *v->b1;
    v->_a2 = *v->a2;  v->_b2 = *v->b2;
    v->_a3 = *v->a3;  v->_b3 = *v->b3;
  } else
  {
    v->_a0 = *v->b0;  v->_b0 = *v->a0;
    v->_a1 = *v->b1;  v->_b1 = *v->a1;
    v->_a2 = *v->b2;  v->_b2 = *v->a2;
    v->_a3 = *v->b3;  v->_b3 = *v->a3;
  }
}

