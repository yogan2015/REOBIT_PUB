
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
static float Temp = 0;
  Temp = *v->mTheta - v->Theta;
  if (Temp < -0.5) v->Rev++;
  if (Temp >  0.5) v->Rev--;
  v->Theta = *v->mTheta;

  v->Pos = v->Rev  + *v->mTheta;
}

