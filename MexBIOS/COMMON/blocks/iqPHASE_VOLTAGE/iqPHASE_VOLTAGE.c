
#define ONE_THIRD  _IQ(0.33333333333333)
#define TWO_THIRD  _IQ(0.66666666666667)
#define INV_SQRT3  _IQ(0.57735026918963)

void Init(void)
{

}

void Exec(void)
{
  _iq MfuncV1 = *v->V1;
  _iq MfuncV2 = *v->V2;
  _iq MfuncV3 = *v->V3;

  if ((short)*v->Dir)
  {
    MfuncV1 = -MfuncV1;
    MfuncV2 = -MfuncV2;
    MfuncV3 = -MfuncV3;
  }

  // scale the incomming Modulation functions with the DC bus voltage value
  MfuncV1 = _IQ24mpy(*v->DcBus, MfuncV1);
  MfuncV2 = _IQ24mpy(*v->DcBus, MfuncV2);
  MfuncV3 = _IQ24mpy(*v->DcBus, MfuncV3);

  // calculate the 3 Phase voltages
  v->Va = _IQ24mpy(TWO_THIRD, MfuncV1) -
          _IQ24mpy(ONE_THIRD, MfuncV2) -
          _IQ24mpy(ONE_THIRD, MfuncV3);

  v->Vb = _IQ24mpy(TWO_THIRD, MfuncV2) -
          _IQ24mpy(ONE_THIRD, MfuncV1) -
          _IQ24mpy(ONE_THIRD, MfuncV3);

  v->Vc = _IQ24mpy(TWO_THIRD, MfuncV3) -
          _IQ24mpy(ONE_THIRD, MfuncV1) -
          _IQ24mpy(ONE_THIRD, MfuncV2);

  // Voltage transformation (a,b,c)  ->  (Alpha,Beta)
  v->Valpha = v->Va;
  v->Vbeta  = _IQ24mpy(v->Va + (v->Vb << 1), INV_SQRT3);
}



