
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
//���������� ����

if (*v->HOLD == 0)
{
v->yangl=v->yangl+(314.1593 - (v->yregul)*v->Kinteg)*(v->SampleTime);
};
if(v->yangl > 6.283185)v->yangl = v->yangl - 6.283185;

//�������� SIN, COS
v->ykor=(v->yangl)-(v->yregul);
v->Acos=cos(v->ykor);
v->Asin=sin(v->ykor);
//��������������� �� ����
v->deltafi=(Vacos)*(v->Asin)-(Vasin)*(v->Acos);

// ��_���������

v->yreg=v->yreg+(v->deltafi*v->Kang)*(v->SampleTime);
if(v->yreg > 6.283185) v->yreg = 6.283185;
v->yregul=v->yreg+(v->deltafi)*0.1;

}

