
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
static long ADC_H, ADC_C = 0;


if (*v->ADC_Heatsink <= 0 ) ADC_H = 0; else ADC_H = *v->ADC_Heatsink;
if (*v->ADC_CPU <= 0 ) ADC_C = 0; else ADC_C = *v->ADC_CPU;



v->k = _IQ6(
            (ADC_H <= 617)  ? 17.218  : (
            (ADC_H <= 3330) ? 41.0509 :
                              15.6006   )
           );
v->b = _IQ6(
            (ADC_H <= 617)  ? 925.235  : (
            (ADC_H <= 3330) ? 1358.908 : (
            (ADC_H <= 3760) ? 2574.10  :
                              2414.81    )
                                         )
           );

v->k1 = _IQ6(
            (ADC_C <= 850)  ? 22.1307 : (
            (ADC_C <= 3460) ? 41.0509 :
                              15.5496   )
           );
v->b1 = _IQ6(
            (ADC_C <= 850)  ? 1253.144  : (
            (ADC_C <= 2580) ? 1564.1625 : (
            (ADC_C <= 3460) ? 1358.908  :
                              2441.299    )
                                          )
           );

 ADC_H = _IQ6(ADC_H);
 ADC_C = _IQ6(ADC_C);
v->T_HeatSink = _IQ6div((ADC_H - v->b),v->k );
v->T_CPU = _IQ6div((ADC_C - v->b1),v->k1 );

}

