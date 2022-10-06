
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
if (*v->Enable == 0)
{
  v->r = v->r - v->Td * v->Ramp_DOWN;
} else {
  v->r = v->r + v->Td * v->Ramp_UP;
}
if (v->r > 1) v->r = 1;
if (v->r < 0) v->r = 0;
v->Ramp = v->r;
}

