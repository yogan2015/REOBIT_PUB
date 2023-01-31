
void Init(void)
{

}

void Exec(void)
{  long Sine, Cosine;
   int B_Alpha, B_Beta, C_Alpha, C_Beta, A, B, C;

  A = *v->Alpha;
  //
  Sine   = _IQ24sinPU(*v->adj_B);
  Cosine = _IQ24cosPU(*v->adj_B);
  B_Alpha = _IQ24mpy(*v->Alpha, Cosine) - _IQ24mpy(*v->Beta, Sine);
  B_Beta  = _IQ24mpy(*v->Beta, Cosine) + _IQ24mpy(*v->Alpha, Sine);
  B = _IQ24mpy(_IQ24(-0.5), B_Alpha) + _IQ24mpy(_IQ24(0.86602540378444), B_Beta);

  Sine   = _IQ24sinPU(*v->adj_C);
  Cosine = _IQ24cosPU(*v->adj_C);
  C_Alpha = _IQ24mpy(*v->Alpha, Cosine) - _IQ24mpy(*v->Beta, Sine);
  C_Beta  = _IQ24mpy(*v->Beta, Cosine) + _IQ24mpy(*v->Alpha, Sine);
  C = _IQ24mpy(_IQ24(-0.5), C_Alpha) - _IQ24mpy(_IQ24(0.86602540378444), C_Beta);


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

