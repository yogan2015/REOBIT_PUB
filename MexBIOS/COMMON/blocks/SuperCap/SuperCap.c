
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
float ars, ipr, dpr, nDCX;

if(v->Tnc>0.05)v->pp=0;
v->Tnc=v->Tnc+v->pp*v->SampleTime;


ars=1/(v->Rs*v->Cfar);
dpr=*v->Ud-v->yv1;

v->yv1=v->yv1+dpr*ars*v->SampleTime;


v->Id1=(dpr)/v->Rs;
if(v->pp>0){v->Id1=0; v->yv1=600;}


v->Ud1=v->yv1;

}

