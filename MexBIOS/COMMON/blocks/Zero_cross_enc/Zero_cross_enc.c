
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
if (v->Init_State == 0)
  {
    if (!*v->R) return;
    v->Init_State = 1;
    v->pEnc_pos = *v->Enc_pos;
  }

if ((v->N > (v->Rotate_range - 1)) || (v->N < (-1 * v->Rotate_range)))
  {
    v->N = 0;
  }
if (((*v->Enc_pos < 90) & (*v->Enc_pos >= 0)) & ((v->pEnc_pos < 360) & (v->pEnc_pos > 270)))
  {
    v->Flag = 1;
    v->N = v->N + 1;
  }
if (((*v->Enc_pos < 360) & (*v->Enc_pos > 270)) & ((v->pEnc_pos < 90) & (v->pEnc_pos >= 0)))
  {
    v->Flag = 2;
    v->N = v->N - 1;
  }
if (v->Flag == 1)
 {
   v->Calc_pos = *v->Enc_pos + (360 * v->N);
  }
if (v->Flag == 2)
  {
    v->Calc_pos = *v->Enc_pos + (360 * v->N);
  }
  v->pEnc_pos = *v->Enc_pos;
}

