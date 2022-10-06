
void Init(void)
{
}

void Exec(void)
{
if(*v->En) {
// Reset Min, Max
  if ((*v->En)!=(v->EnPrev)) {
      v->Max_sin=0;  v->Max_cos=0;  v->Min_sin=4096;  v->Min_cos=4096;
  } // Reset Min, Max
// SIN MAX
  if ((*v->sin) > (v->Max_sin)) {
      v->Max_sin = *v->sin;
  }// EOF CALC sin_max
// cos MAX
  if ((*v->cos) > (v->Max_cos)) {
      v->Max_cos = *v->cos;
  }// EOF CALC cos_max
// sin MIN
  if ((*v->sin) < (v->Min_sin)) {
      v->Min_sin = *v->sin;
  }// EOF CALC sin_min
// cos MIN
  if ((*v->cos) < (v->Min_cos)) {
  v->Min_cos = *v->cos;
  }// EOF CALC sin_min
v->Offs_sin=((v->Max_sin)+(v->Min_sin))>>1;
v->Offs_cos=((v->Max_cos)+(v->Min_cos))>>1;
v->Gain_sin=((((v->Max_sin)-(v->Min_sin))>>1)<=(v->GainSat)) ?
            _IQtoIQ(v->GainSat,11,24) :
            _IQtoIQ((((v->Max_sin)-(v->Min_sin))>>1),11,24);
v->Gain_cos=((((v->Max_cos)-(v->Min_cos))>>1)<=(v->GainSat)) ?
            _IQtoIQ(v->GainSat,11,24) :
            _IQtoIQ((((v->Max_cos)-(v->Min_cos))>>1),11,24);

v->Gain_sin = _IQ24div(_IQ24(1.0),v->Gain_sin);
v->Gain_cos = _IQ24div(_IQ24(1.0),v->Gain_cos);

v->sin_out= _IQ24(0.0);
v->cos_out= _IQ24(1.0);
v->EnPrev = *v->En;
return;
} // EOF Calc Offs Gain

v->sin_out = _IQ24mpy((_IQtoIQ(((*v->sin) - v->Offs_sin),11,24)),v->Gain_sin);
v->cos_out = _IQ24mpy((_IQtoIQ(((*v->cos) - v->Offs_cos),11,24)),v->Gain_cos);
v->EnPrev = *v->En;

}



