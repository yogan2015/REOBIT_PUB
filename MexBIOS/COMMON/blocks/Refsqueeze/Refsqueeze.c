
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out_r_TOP = 1 + *v->k * (*v->In_r - 1)/2;
  v->Out_r_BOT = -1 + *v->k * (*v->In_r + 1)/2;
}

