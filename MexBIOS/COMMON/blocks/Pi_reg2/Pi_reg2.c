
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
float Dmod;

v->Vy2=v->Vy2+(*v->modul-v->Vy2)*v->Kf1*(*v->DCX)*v->SampleTime;

Dmod=(v->Umodz-v->Vy2)*(*v->DCX);

v->Vy1=v->Vy1+Dmod*(*v->DCX)*v->KPI*v->SampleTime;
if(v->Vy1>v->Umodmax)v->Vy1=v->Umodmax;
if(v->Vy1<-v->Umodmax)v->Vy1=-v->Umodmax;

v->Vreg=v->Vy1+Dmod*v->KPP;
if(v->Vreg>v->Umodmax)v->Vreg=v->Umodmax;
if(v->Vreg<-v->Umodmax)v->Vreg=-v->Umodmax;

v->Ua=*v->Uacos*v->Vreg*(*v->DCX);
v->Ub=*v->Uasin*v->Vreg*(*v->DCX);

}

