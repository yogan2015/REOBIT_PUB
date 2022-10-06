
void Init(void)
{
}

void Exec(void)
{
  if (v->Tr != v->PrevTr)
  {
    v->Kr     = v->SampleTime / v->Tr;
    v->Kt     = 0.5 / (M_PI * v->BaseFreq * v->Tr);
    v->K      = v->SampleTime * v->BaseFreq;
    v->PrevTr = v->Tr;
  }

  v->IMDs += v->Kr * (*v->IDs - v->IMDs);

  if (v->IMDs == 0) v->Wslip = 0;
  else v->Wslip = (*v->IQs * v->Kt) / v->IMDs;

  v->We = *v->Wr + v->Wslip;
  v->Theta += v->K * v->We;

  if ((short)*v->R)
  {
    v->IMDs  = 0;
    v->Theta = 0;
    v->We    = 0;
    v->Wslip = 0;
    return;
  }

  if (v->Theta > 1.0) v->Theta -= 1.0;
  else if (v->Theta < 0.0) v->Theta += 1.0;
}


