
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out_r1_TOP = 1 + *v->k * (*v->In_r1 - 1)/2;
  v->Out_r1_BOT = -1 + *v->k * (*v->In_r1 + 1)/2;
  v->Out_r2_TOP = 1 + *v->k * (*v->In_r2 - 1)/2;
  v->Out_r2_BOT = -1 + *v->k * (*v->In_r2 + 1)/2;
  v->Out_r3_TOP = 1 + *v->k * (*v->In_r3 - 1)/2;
  v->Out_r3_BOT = -1 + *v->k * (*v->In_r3 + 1)/2;
}

