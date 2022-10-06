
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Phase_A = *v->Phase;
  v->Phase_B = (*v->Phase + 2.0943951023931954923084289221863);
  v->Phase_C = (*v->Phase + 4.1887902047863909846168578443727);
  if (v->Phase_B > 6.283185307179586476925286766559)
  {
    v->Phase_B = v->Phase_B - 6.283185307179586476925286766559;
  }
  if (v->Phase_C > 6.283185307179586476925286766559)
  {
    v->Phase_C = v->Phase_C - 6.283185307179586476925286766559;
  }
}

