
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->v_cos = _IQ24mpy(*v->v1_mag, *v->v1_cos) - _IQ24mpy(*v->v2_mag, *v->v2_cos);
  v->v_sin = _IQ24mpy(*v->v1_mag, *v->v1_sin) - _IQ24mpy(*v->v2_mag, *v->v2_sin);
}

