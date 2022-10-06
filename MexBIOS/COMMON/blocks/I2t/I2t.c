
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
static int Current = 0;
Current = *v->Cur;
if (Current >= *v->CurNom) v->I2t += _IQ24rsmpy(_IQ24rsmpy(_IQ24rsmpy((Current-*v->CurNom),(Current+*v->CurNom)),v->SampleTime),v->K_Acc);
if (Current < *v->CurNom) v->I2t += _IQ24rsmpy(_IQ24rsmpy(_IQ24rsmpy((Current-*v->CurNom),(Current+*v->CurNom)),v->SampleTime),v->K_Dec);

if (v->I2t > _IQ24(127.0))
v->I2t =  _IQ24(127.0);
if (v->I2t < _IQ24(0.0))
v->I2t =  _IQ24(0.0);


}
//I2t_VAL =_IQ24mpy(v->Time,_IQ24mpy((*v->CurRMS-Inom),(*v->CurRMS+Inom)));

