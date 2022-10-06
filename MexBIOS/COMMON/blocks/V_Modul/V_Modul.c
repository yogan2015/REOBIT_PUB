
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
v->Amodul=sqrt((*v->Va)*(*v->Va)+(*v->Vb)*(*v->Vb));
if(v->Amodul<0.01)v->Amodul=0.01;

v->Yst=v->Yst+(v->Amodul-v->Yst)*v->ktf*v->SampleTime;
v->Modul=v->Yst;
}

