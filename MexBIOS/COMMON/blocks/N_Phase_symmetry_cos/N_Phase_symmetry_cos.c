
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Phase_A = *v->Phase;
  v->Phase_B = (*v->Phase + 4.1887902047863909846168578443727);
  v->Phase_C = (*v->Phase + 2.0943951023931954923084289221863);
  if (v->Phase_A > 6.283185307179586476925286766559)
  {
    v->Phase_A = v->Phase_A - 6.283185307179586476925286766559;
  }
  if (v->Phase_B > 6.283185307179586476925286766559)
  {
    v->Phase_B = v->Phase_B - 6.283185307179586476925286766559;
  }
  if (v->Phase_C > 6.283185307179586476925286766559)
  {
    v->Phase_C = v->Phase_C - 6.283185307179586476925286766559;
  }
  v->Phase_A = cos(v->Phase_A) * *v->k;
  v->Phase_B = cos(v->Phase_B) * *v->k;
  v->Phase_C = cos(v->Phase_C) * *v->k;
}

