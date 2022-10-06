
// Do not initialize inputs!
void Init(void)
{
  v->g = 0;
}

void Exec(void)
{
  float gc;
if (*v->RST) {
  v->g = 0;
} else {
  gc = v->g1 + v->K_p * (*v->e - v->e1) + v->K_i * v->T_d * *v->e + v->K_d / v->T_d * (*v->e - 2 * v->e1 + v->e2);
  if (gc>=v->UI_Max) {
    gc = v->UI_Max;
  }
  if (gc<=v->UI_Min) {
    gc = v->UI_Min;
  }
  v->g = gc;
};
v->g1 = v->g;
v->e2 = v->e1;
v->e1 = *v->e;
}

