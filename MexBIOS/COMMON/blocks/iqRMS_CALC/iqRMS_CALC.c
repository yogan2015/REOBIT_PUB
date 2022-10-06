
void Init(void)
{

}

void Exec(void)
{
  long Value = *v->In >> 9;

  v->Timer = v->Timer + 1;
  v->Summ  = v->Summ + _IQ15mpy(Value, Value);

  if (_IQabs(*v->Angle - v->PrevAngle) > _IQ24(0.5))
  {
    if (v->Timer > v->Timeout) v->Rms = *v->In;
    else v->Rms = _IQ15sqrt(_IQ1div(v->Summ, v->Timer << 1));
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

