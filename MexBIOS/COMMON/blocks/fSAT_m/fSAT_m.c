
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
float deadZone;

if (fabsf(*v->In) >= v->X_Satur)
{
  deadZone = *v->In;
}
else
{
  deadZone = 0;
}

  v->Out = (deadZone - v->X_Offset) * v->Gain + v->Y_Offset;
  if (v->Out > v->Y_Satur_Pos) v->Out = v->Y_Satur_Pos;
  if (v->Out < v->Y_Satur_Neg) v->Out = v->Y_Satur_Neg;

}

