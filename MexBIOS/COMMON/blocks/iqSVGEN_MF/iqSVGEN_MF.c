
#define PI_THIRD  _IQ24(1.04719755119660)    // This is 60 degree

void Init(void)
{

}

void Exec(void)
{
  _iq StepAngle, EntryOld;
  _iq dx, dy, dz, Gain;

  // Normalise the freq input to appropriate step angle
  // Here, 1 pu. = 60 degree
  StepAngle = _IQ24mpy(*v->Freq, _IQ15mpy(_IQ15(6.0) * v->BaseFreq, v->SampleTime));

  // Calculate new angle alpha
  EntryOld = v->Entry;
  v->Entry = v->Entry + StepAngle;
  if (v->Entry >= _IQ24(1.0)) v->Entry = v->Entry - _IQ24(1.0);
  if (v->Entry <  _IQ24(0.0)) v->Entry = v->Entry + _IQ24(1.0);

  dy = _IQ24sin(_IQ24mpy(v->Entry, PI_THIRD));            // dy = sin(NewEntry)
  dx = _IQ24sin(PI_THIRD - _IQ24mpy(v->Entry, PI_THIRD)); // dx = sin(60-NewEntry)
  dz = (_IQ24(1.0) - dx - dy) >> 1;                       // dz = (1 - dx - dy) * 0.5

  // Determine which sector
  if ((v->Entry - EntryOld) < 0)
  {
    if (v->SectorPointer < 5) v->SectorPointer++;
    else v->SectorPointer = 0;
  }

  switch(v->SectorPointer)
  {
    case 0: // Sector 1 calculations - a,b,c --> a,b,c
      v->Ta = dz;
      v->Tb = v->Ta + dx;
      v->Tc = _IQ24(1.0) - v->Ta;
      break;
    case 1: // Sector 2 calculations - a,b,c --> b,a,c  &  dx <--> dy
      v->Tb = dz;
      v->Ta = v->Tb + dy;
      v->Tc = _IQ24(1.0) - v->Tb;
      break;
    case 2: // Sector 3 calculations - a,b,c --> b,c,a
      v->Tb = dz;
      v->Tc = v->Tb + dx;
      v->Ta = _IQ24(1.0) - v->Tb;
      break;
    case 3: // Sector 4 calculations - a,b,c --> c,b,a  &  dx <--> dy
      v->Tc = dz;
      v->Tb = v->Tc + dy;
      v->Ta = _IQ24(1.0) - v->Tc;
      break;
    case 4: // Sector 5 calculations - a,b,c --> c,a,b
      v->Tc = dz;
      v->Ta = v->Tc + dx;
      v->Tb = _IQ24(1.0) - v->Tc;
      break;
    case 5: // Sector 6 calculations - a,b,c --> a,c,b  &  dx <--> dy
      v->Ta = dz;
      v->Tc = v->Ta + dy;
      v->Tb = _IQ24(1.0) - v->Ta;
      break;
  }

  // Convert the unsigned GLOBAL_Q format (ranged (0,1)) -> signed GLOBAL_Q format (ranged (-1,1))
  Gain = *v->Ampl;
  if (Gain < _IQ24(0.0)) Gain = _IQ24(0.0);
  if (Gain > _IQ24(1.0)) Gain = _IQ24(1.0);

  v->Ta = _IQ24mpy((v->Ta << 1) - _IQ(1.0), Gain);
  v->Tb = _IQ24mpy((v->Tb << 1) - _IQ(1.0), Gain);
  v->Tc = _IQ24mpy((v->Tc << 1) - _IQ(1.0), Gain);
}


