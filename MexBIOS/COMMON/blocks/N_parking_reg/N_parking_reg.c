
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->RST)
  {
    v->r_1 = 0;
    v->r_2 = 0;
    v->r_3 = 0;
    v->r_4 = 0;
    v->n_r = 0;
  }
  if (*v->set)
  {
    if (!*v->RST) v->reinited = 1;
    if(v->n_r < 4)
    {
      v->n_r += 1;
      switch (v->n_r)
      {
        case 1:  v->r_1 = *v->Val; break;
        case 2:  v->r_2 = *v->Val; break;
        case 3:  v->r_3 = *v->Val; break;
        case 4:  v->r_4 = *v->Val; break;
      }
    }
  }
  if (v->reinited)
  {
    v->reg_1 = v->r_1;
    v->reg_2 = v->r_2;
    v->reg_3 = v->r_3;
    v->reg_4 = v->r_4;
    v->n_reg = v->n_r;
  } else {
    v->reg_1 = v->init_1;
    v->reg_2 = v->init_2;
    v->reg_3 = v->init_3;
    v->reg_4 = v->init_4;
  }
}

