
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
v->Usa=(2*(*v->Vab)+(*v->Vbc))*v->otr;
v->Usb=(*v->Vbc)*v->Sqr3;

v->Valpha=v->Usa+(*v->Va)*v->Ktrans;
v->Vbeta=v->Usb+(*v->Vb)*v->Ktrans;
}

