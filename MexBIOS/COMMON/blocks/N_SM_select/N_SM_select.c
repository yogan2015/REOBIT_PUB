
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->RST) v->Stage = 0;
  switch (v->Stage) {
  case 0: v->Stage = *v->S0;
  break;
  case 1: v->Stage = *v->S1;
  break;
  case 2: v->Stage = *v->S2;
  break;
  case 3: v->Stage = *v->S3;
  break;
  case 4: v->Stage = *v->S4;
  break;
  case 5: v->Stage = *v->S5;
  break;
  case 6: v->Stage = *v->S6;
  break;
  case 7: v->Stage = *v->S7;
  break;
  case 8: v->Stage = *v->S8;
  break;
  case 9: v->Stage = *v->S9;
  break;}
}

