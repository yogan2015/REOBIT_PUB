
#define PI_THIRD  1.04719755119660 // This is 60 degree

void Init(void)
{

}

void Exec(void)
{
  float StepAngle, EntryOld;
  float dx, dy, dz, Gain;

  // Normalise the freq input to appropriate step angle
  // Here, 1 pu. = 60 degree
  StepAngle = 6.0 * v->BaseFreq * v->SampleTime * (*v->Freq);

  // Calculate new angle alpha
  EntryOld = v->Entry;
  v->Entry = v->Entry + StepAngle;
  if (v->Entry >= 1.0) v->Entry = v->Entry - 1.0;
  if (v->Entry <  0.0) v->Entry = v->Entry + 1.0;

  dy = sin(v->Entry * PI_THIRD);            // dy = sin(NewEntry)
  dx = sin(PI_THIRD - v->Entry * PI_THIRD); // dx = sin(60-NewEntry)
  dz = (1.0 - dx - dy) * 0.5;               // dz = (1 - dx - dy) * 0.5

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
      v->Tc = 1.0 - v->Ta;
      break;
    case 1: // Sector 2 calculations - a,b,c --> b,a,c  &  dx <--> dy
      v->Tb = dz;
      v->Ta = v->Tb + dy;
      v->Tc = 1.0 - v->Tb;
      break;
    case 2: // Sector 3 calculations - a,b,c --> b,c,a
      v->Tb = dz;
      v->Tc = v->Tb + dx;
      v->Ta = 1.0 - v->Tb;
      break;
    case 3: // Sector 4 calculations - a,b,c --> c,b,a  &  dx <--> dy
      v->Tc = dz;
      v->Tb = v->Tc + dy;
      v->Ta = 1.0 - v->Tc;
      break;
    case 4: // Sector 5 calculations - a,b,c --> c,a,b
      v->Tc = dz;
      v->Ta = v->Tc + dx;
      v->Tb = 1.0 - v->Tc;
      break;
    case 5: // Sector 6 calculations - a,b,c --> a,c,b  &  dx <--> dy
      v->Ta = dz;
      v->Tc = v->Ta + dy;
      v->Tb = 1.0 - v->Ta;
      break;
  }

  // Convert the unsigned GLOBAL_Q format (ranged (0,1)) -> signed GLOBAL_Q format (ranged (-1,1))
  Gain = *v->Ampl;
  if (Gain < 0.0) Gain = 0.0;
  if (Gain > 1.0) Gain = 1.0;

  v->Ta = ((v->Ta * 2.0) - 1.0) * Gain;
  v->Tb = ((v->Tb * 2.0) - 1.0) * Gain;
  v->Tc = ((v->Tc * 2.0) - 1.0) * Gain;
}

