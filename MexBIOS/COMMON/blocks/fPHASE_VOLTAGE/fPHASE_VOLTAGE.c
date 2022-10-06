
#define ONE_THIRD  (0.33333333333333)
#define TWO_THIRD  (0.66666666666667)
#define INV_SQRT3  (0.57735026918963)

void Init(void)
{

}

void Exec(void)
{
  float MfuncV1 = *v->V1;
  float MfuncV2 = *v->V2;
  float MfuncV3 = *v->V3;

  if ((short)*v->Dir)
  {
    MfuncV1 = -MfuncV1;
    MfuncV2 = -MfuncV2;
    MfuncV3 = -MfuncV3;
  }

  // scale the incomming Modulation functions with the DC bus voltage value
  MfuncV1 = *v->DcBus * MfuncV1;
  MfuncV2 = *v->DcBus * MfuncV2;
  MfuncV3 = *v->DcBus * MfuncV3;

  // calculate the 3 Phase voltages
  v->Va = TWO_THIRD * MfuncV1 - ONE_THIRD * MfuncV2 - ONE_THIRD * MfuncV3;
  v->Vb = TWO_THIRD * MfuncV2 - ONE_THIRD * MfuncV1 - ONE_THIRD * MfuncV3;
  v->Vc = TWO_THIRD * MfuncV3 - ONE_THIRD * MfuncV1 - ONE_THIRD * MfuncV2;

  // Voltage transformation (a,b,c)  ->  (Alpha,Beta)
  v->Valpha = v->Va;
  v->Vbeta  = (v->Va + v->Vb * 2.0) * INV_SQRT3;
}



