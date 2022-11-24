
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->mean_A = _IQ24mpy(v->mean_A, (v->k)) + _IQ24mpy(*v->raw_A, 16777216 - v->k);
  v->mean_B = _IQ24mpy(v->mean_B, (v->k)) + _IQ24mpy(*v->raw_B, 16777216 - v->k);
  v->Out_A = _IQ24mpy((*v->raw_A - v->mean_A), v->gain);
  v->Out_B = _IQ24mpy(_IQ24mpy(v->Out_A + ((*v->raw_B - v->mean_B) << 1), 9686330), v->gain);
}

