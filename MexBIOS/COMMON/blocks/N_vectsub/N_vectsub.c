
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->out_alpha  = _IQ24mpy(*v->Dec_Magn, *v->Dec_alpha) - _IQ24mpy(*v->Sub_Magn, *v->Sub_alpha);
  v->out_beta   = _IQ24mpy(*v->Dec_Magn, *v->Dec_beta)  - _IQ24mpy(*v->Sub_Magn, *v->Sub_beta);
}

