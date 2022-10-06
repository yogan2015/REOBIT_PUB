void Init(void)
{
v->Out = 0;
}

void Exec(void)
{
long Tmp, Timeout;

if (*v->R)
{
    v->Out = 0;
    v->Timer = 0;
    return;

}

if ((!*v->Freq)||(!v->Step)) { v->Out = 0; return; }

Tmp = v->Out;
Timeout = _IQ1div(_IQ24(0.25),_IQ24mpy(*v->Freq, v->SampleTime));

if (++v->Timer >= Timeout)
{
Tmp= (Tmp <= 0) ? (_IQabs(Tmp) + v->Step) : -Tmp ;
v->Timer = 0;

}

v->Out = (Tmp >= v->MaxOut) ? v->Step : Tmp ;


}
