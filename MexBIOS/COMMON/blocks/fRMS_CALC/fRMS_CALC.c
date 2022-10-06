
void Init(void)
{

}

void Exec(void)
{
  v->Timer = v->Timer + 1;
  v->Summ  = v->Summ + ((*v->In) * (*v->In));

  if (fabs(*v->Angle - v->PrevAngle) > 0.5)
  {
    if (v->Timer > v->Timeout) v->Rms = *v->In;
    else v->Rms = sqrt(v->Summ / v->Timer);
    v->Timer = 0;
    v->Summ  = 0;
  }
  else if (v->Timer > v->Timeout)
  {
    v->Timer = v->Timeout;
    v->Rms   = *v->In;
  }
  v->PrevAngle = *v->Angle;
}

