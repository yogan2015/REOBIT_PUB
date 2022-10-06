
void Init(void)
{
}

void Exec(void)
{
  float Delta;

  v->Counter ++;
  if (v->Counter > (v->Period -1))
  {
  v->Counter = 0;
  }
  switch (v->Counter)
  {
    case 0:
      Delta = ((v->x1 - 8.0*v->x2 + 8.0*v->x3 - v->x4)/ (12 * v->SampleTime));
      if (Delta < -0.5) Delta += 1.0;
      if (Delta >  0.5) Delta -= 1.0;
      v->Speed =  Delta;
    break;

    case 1:
    v->x1 = *v->Angle;
    break;

    case 2:
    v->x2 = *v->Angle;
    break;

    case 3:
    v->x3 = *v->Angle;
    break;

    case 4:
    v->x4 = *v->Angle;
    break;
   }

}


