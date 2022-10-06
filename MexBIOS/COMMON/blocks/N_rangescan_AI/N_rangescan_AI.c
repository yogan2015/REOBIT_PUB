
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if ((short)*v->RST)
  {
    v->low_0  = *v->In_0;
    v->high_0 = *v->In_0;

    v->low_1  = *v->In_1;
    v->high_1 = *v->In_1;

    v->low_2  = *v->In_2;
    v->high_2 = *v->In_2;

    v->low_3  = *v->In_3;
    v->high_3 = *v->In_3;

    v->low_4  = *v->In_4;
    v->high_4 = *v->In_4;

    v->low_5  = *v->In_5;
    v->high_5 = *v->In_5;
  } else
  {
    if (*v->In_0 < v->low_0)  v->low_0  = *v->In_0;
    if (*v->In_0 > v->high_0) v->high_0 = *v->In_0;

    if (*v->In_1 < v->low_1)  v->low_1  = *v->In_1;
    if (*v->In_1 > v->high_1) v->high_1 = *v->In_1;

    if (*v->In_2 < v->low_2)  v->low_2  = *v->In_2;
    if (*v->In_2 > v->high_2) v->high_2 = *v->In_2;

    if (*v->In_3 < v->low_3)  v->low_3  = *v->In_3;
    if (*v->In_3 > v->high_3) v->high_3 = *v->In_3;

    if (*v->In_4 < v->low_4)  v->low_4  = *v->In_4;
    if (*v->In_4 > v->high_4) v->high_4 = *v->In_4;

    if (*v->In_5 < v->low_5)  v->low_5 = *v->In_5;
    if (*v->In_5 > v->high_5) v->high_5 = *v->In_5;

    v->OUT = 0;
    if ((v->high_0 - v->low_0) > v->treshold) v->OUT |= (1 << 0);
    if ((v->high_1 - v->low_1) > v->treshold) v->OUT |= (1 << 1);
    if ((v->high_2 - v->low_2) > v->treshold) v->OUT |= (1 << 2);
    if ((v->high_3 - v->low_3) > v->treshold) v->OUT |= (1 << 3);
    if ((v->high_4 - v->low_4) > v->treshold) v->OUT |= (1 << 4);
    if ((v->high_5 - v->low_5) > v->treshold) v->OUT |= (1 << 5);
  }
}
