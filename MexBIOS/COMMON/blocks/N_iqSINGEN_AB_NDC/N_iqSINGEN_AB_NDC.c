
void Init(void)
{

}

void Exec(void)
{   int A, B, C;

  A = *v->Alpha;
  B = _IQ24mpy(_IQ24(-0.5), *v->Alpha) + _IQ24mpy(_IQ24(0.86602540378444), *v->Beta);
  C = _IQ24mpy(_IQ24(-0.5), *v->Alpha) - _IQ24mpy(_IQ24(0.86602540378444), *v->Beta);


  A = _IQ24mpy( *v-> Kdc, A + 16777216) - 16777216;
  B = _IQ24mpy( *v-> Kdc, B + 16777216) - 16777216;
  C = _IQ24mpy( *v-> Kdc, C + 16777216) - 16777216;
  //A = 16777216 - (A << 1);
  //B = 16777216 - (B << 1);
  //C = 16777216 - (C << 1);

   v->A_TOP =  16777216 + (__IQmpy(*v->K, A - 16777216, 24)>>1);
   v->A_BOT = -16777216 + (__IQmpy(*v->K, A + 16777216, 24)>>1);

   v->B_TOP =  16777216 + (__IQmpy(*v->K, B - 16777216, 24)>>1);
   v->B_BOT = -16777216 + (__IQmpy(*v->K, B + 16777216, 24)>>1);

   v->C_TOP =  16777216 + (__IQmpy(*v->K, C - 16777216, 24)>>1);
   v->C_BOT = -16777216 + (__IQmpy(*v->K, C + 16777216, 24)>>1);
}
