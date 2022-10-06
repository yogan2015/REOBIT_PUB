
void Init(void)
{
}

void Exec(void)
{
  if (v->Tr != v->PrevTr)
  {
    v->Kr     = _IQ24div(v->SampleTime, v->Tr);
    v->Kt     = _IQ24div(_IQ24(0.5/M_PI), _IQ24mpy(v->BaseFreq, v->Tr));
    v->K      = _IQ24mpy(v->SampleTime, v->BaseFreq);
    v->PrevTr = v->Tr;
  }

  v->IMDs += _IQ24mpy(v->Kr, *v->IDs - v->IMDs);

  if (v->IMDs == 0) v->Wslip = 0;
  else v->Wslip = _IQ24div(_IQ24mpy(*v->IQs, v->Kt), v->IMDs);

  v->We = *v->Wr + v->Wslip;
  v->Theta += _IQ24mpy(v->K, v->We);

  if ((short)*v->R)
  {
    v->IMDs  = 0;
    v->Theta = 0;
    v->We    = 0;
    v->Wslip = 0;
    return;
  }

  if (v->Theta > _IQ24(1.0)) v->Theta -= _IQ24(1.0);
  else if (v->Theta < _IQ24(0)) v->Theta += _IQ24(1.0);
}


