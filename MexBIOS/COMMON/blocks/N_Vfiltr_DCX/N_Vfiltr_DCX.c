
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
float Vacos, Vasin;
v->Amod=sqrt((*v->Va)*(*v->Va)+(*v->Vb)*(*v->Vb));
if(v->Amod<0.01)v->Amod=0.01;

Vacos=(*v->Va)/v->Amod;
Vasin=(*v->Vb)/v->Amod;
//Интегратор угла

v->yangl=v->yangl+(314.1593-(v->yregul)*v->Kinteg*(*v->DCX))*(v->SampleTime);
if(v->yangl>2*3.1415926)v->yangl=0;

//ВЫХОДНЫЕ SIN, COS
v->ykor=(v->yangl)-(v->yregul);
v->Acos=cos(v->ykor);
v->Asin=sin(v->ykor);
//Рассогласование по углу
v->deltafi=((Vacos)*(v->Asin)-(Vasin)*(v->Acos))*(*v->DCX);

// ПИ_регулятор

v->yreg=v->yreg+(v->deltafi*v->Kang)*(v->SampleTime);
if(v->yreg>2*3.1415926)v->yreg=2*3.1415926;
v->yregul=v->yreg+(v->deltafi)*0.1;
}

