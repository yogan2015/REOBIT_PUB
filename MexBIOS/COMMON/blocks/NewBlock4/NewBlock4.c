
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Flag_mem = MBS_getData(v->Index);
  if (v->Init_State == 0)
    {
      if (!*v->R) return;
      v->Init_State = 1;
      v->pEnc_pos = *v->Enc_pos;
     // v->Out = v->Flag_mem;
    }
  if ((*v->Enc_pos < 0.02) & (v->pEnc_pos > 15.98))
    {
      v->Flag = 1;
    }
  if ((*v->Enc_pos > 15.98) & (v->pEnc_pos < 0.02))
    {
      v->Flag = 2;
    }
  if (v->Flag == 1)
    {
      v->Calc_pos = *v->Enc_pos + 16;
    }
  if (v->Flag == 2)
    {
      v->Calc_pos = *v->Enc_pos;
    }
  v->pEnc_pos = *v->Enc_pos;


  if (v->Flag != v->Flag_mem)
    {
      MBS_setData(v->Index, v->Flag, v->Memory);
    }
}

