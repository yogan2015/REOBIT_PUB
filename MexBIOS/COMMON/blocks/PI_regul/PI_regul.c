
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
v->Vy2=v->Vy2+(*v->modul-v->Vy2)*v->Kf1*(*v->DCX)*v->SampleTime;


v->Dmod=(v->Umodz-v->Vy2)*(*v->DCX);

v->Vy1=v->Vy1+v->Dmod*(*v->DCX)*v->KPI*v->SampleTime;
if(v->Vy1>380)v->Vy1=380;
if(v->Vy1<-380)v->Vy1=-380;

v->Vreg=v->Vy1+v->Dmod*v->KPP;
if(v->Vreg>380)v->Vreg=380;
if(v->Vreg<-380)v->Vreg=-380;

v->Ua=*v->Uacos*v->Vreg*(*v->DCX);
v->Ub=*v->Uasin*v->Vreg*(*v->DCX);

}

