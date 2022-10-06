
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->b_fall = (*v->a < v->al);
  v->b_trig = (v->b_fall && !v->b_falll);

  if (*v->RST) {
    v->Hold = *v->a;
  } else {
    if (v->b_trig) {v->Holdl = v->al;};
    if (v->Holdl > *v->a) {
      v->Hold = v->Holdl;
    } else {
      v->Hold = *v->a;
    };
  };

  v->al = *v->a;
  v->b_falll = v->b_fall;
  v->d1_sign = v->b_fall * 2 - 1;
}

