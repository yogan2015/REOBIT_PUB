
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
v->Amod=sqrt((*v->Va)*(*v->Va)+(*v->Vb)*(*v->Vb));
if(v->Amod<0.01)v->Amod=0.01;

v->Vacos=(*v->Va)/v->Amod;
v->Vasin=(*v->Vb)/v->Amod;
//Интегратор угла

v->yangl=v->yangl+(v->Omega-(v->yregul)*v->Kinteg*(*v->DCX))*(v->SampleTime);
if(v->yangl>v->Api2)v->yangl=0;

//ВЫХОДНЫЕ SIN, COS
v->ykor=(v->yangl)-(v->yregul);
v->Acos=cos(v->ykor);
v->Asin=sin(v->ykor);
//Рассогласование по углу
v->deltafi=((v->Vacos)*(v->Asin)-(v->Vasin)*(v->Acos))*(*v->DCX);

// ПИ_регулятор

v->yreg=v->yreg+(v->deltafi*v->Kang)*(v->SampleTime);
if(v->yreg>v->Api2)v->yreg=v->Api2;
v->yregul=v->yreg+(v->deltafi)*0.1;
}

