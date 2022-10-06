
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
long Delta;

Delta= *v->Theta - v->OldTheta;
if (Delta >  _IQ24(0.166666666667)) Delta -= _IQ24(1.0);
else if (Delta < -_IQ24(0.166666666667)) Delta += _IQ24(1.0);

if (v->OldTheta!= *v->Theta)
{
  if (Delta>0) v->sign=1;
  if (Delta<0) v->sign=-1;
  v->thetta_corr= (*v->Theta);
}
v->OldTheta = *v->Theta;

if (!v->sign) { v->thetta_corr= (*v->Theta); return; }

v->thetta_corr= v->thetta_corr + (*v->freq * v->sign);

if (
    ((v->sign) > 0)
    &&
    (v->thetta_corr >= (*v->Theta + _IQ24(0.166666666667)))
   )
   {
     v->thetta_corr = *v->Theta;
     v->sign=0;
   }
else if (
    ((v->sign) < 0)
    &&
    (v->thetta_corr <= (*v->Theta - _IQ24(0.166666666667)))
    )
    {
     v->thetta_corr = *v->Theta;
     v->sign=0;
    }
}

