
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (fabs(*v->pos - v->p_pos)<=0.05)
  {
     v->error = 1;
     v->compens += v->p_spd * v->Td * v->mult;
     v->intpos = v->p_pos + v->compens;
  } else {
     v->error = 0;
     v->p_pos = *v->pos;
     v->p_spd = *v->spd;
     v->intpos = *v->pos;
     v->compens = 0;
  }
  v->delt = v->compens;
  v->fixspeed = v->p_spd;
}

