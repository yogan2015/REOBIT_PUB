
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (!*v->VAC_N) *v->VAC_N = 1;
  if (!*v->VDC_N) *v->VDC_N = 1;
  v->AC2DC = _IQ24mpy(_IQ24div(*v->VAC_N, *v->VDC_N), 20620042);
  v->DC2AC = _IQ24mpy(_IQ24div(*v->VDC_N, *v->VAC_N), 13650553);
  v->ONE_VOLT = _IQ24div(31242, *v->VDC_N);
}

