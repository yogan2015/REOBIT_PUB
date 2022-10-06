
void Init(void)
{
}

void Exec(void)
{
  float x, z;

  if ((short)*v->R) { v->P = ((short)*v->R & 0x2) ? *v->Pref : 0; v->J = 0; v->A = 0; v->V = 0; return;}

  switch (v->InitStage)
  {
    case 0:
      v->P = *v->Pref;
      v->InitStage = 1;
    break;
    case 1:
      v->J = 0; v->A = 0; v->V = 0;
      if (!v->Model) { v->P = *v->Pref; break; }

      v->Dir = 0;
      if (*v->Pref > v->P) { v->Dir =  1; v->TaskPos = ((v->P < 0) && (*v->Pref > 0)) ? 0 : *v->Pref; }
      if (*v->Pref < v->P) { v->Dir = -1; v->TaskPos = ((v->P > 0) && (*v->Pref < 0)) ? 0 : *v->Pref; }
      if (!v->Dir) break;

      v->MovePos   = (v->TaskPos - v->P) * v->Dir;
      v->Time      = v->MovePos / (v->Jmax * 2);
      v->Tj        = sqrt(v->Time);
      v->Tick      = 0;
      v->InitStage = 2;
    break;
    case 2:
      if (v->Model == 1)
      {
        v->Tj = 0;
        v->Ta = v->Vmax / v->Amax;
        z     = v->Amax * v->Ta * v->Ta;
        if (z <= v->MovePos) { v->Tv = (v->MovePos - z) / v->Vmax; }
        else { v->Ta = sqrt(v->MovePos / v->Amax); v->Tv = 0; }
        v->InitStage = 4;
      }
      else
      {
        x       = v->Time / (v->Tj * v->Tj);
        v->Tj   = (v->Tj * 2.0 + x) / 3.0;
        v->Tick = v->Tick + 1;
        if (v->Tick < 20) break;
        v->Ta = 0; v->Tv = 0;
        v->InitStage = 3;
      }
      v->Tick = 0; v->Time = 0;
      v->WorkStage = 0;
    break;
    case 3:
      v->InitStage = 4;

      x = v->Jmax * v->Tj;
      z = x * v->Tj;
      if ((x < v->Amax) && (z < v->Vmax)) break;

      x = v->Jmax * (v->Vmax / v->Amax);
      if (x < v->Amax)
      {
        v->Tj = sqrt(v->Vmax / v->Jmax);
        v->Tv = (v->MovePos / v->Vmax) - (v->Tj * 2.0);
        break;
      }

      v->Tj = v->Amax / v->Jmax;
      x     = v->Tj * v->Amax / 2.0;
      v->Ta = (v->Vmax - x * 2.0) / v->Amax;
      z     = v->Tj * x * 4.0;
      z    += v->Ta * x * 2.0;
      z    += v->Amax * v->Ta * v->Tj * 2.0;
      z    += v->Amax * v->Ta * v->Ta;
      if (z <= v->MovePos) { v->Tv = (v->MovePos - z) / v->Vmax; break; }

      x     = sqrt((v->Tj * v->Tj / 4.0) + (v->MovePos / v->Amax));
      v->Ta = x - v->Tj * 1.5;
    break;
    case 4:
      switch(v->Model)
      {
        case 1:  x = v->Amax; break;
        case 2:  x = v->Jmax; break;
        default: x = v->Jmax * (1.0 - sin(((v->Time / v->Tj) + 0.25) * 2*M_PI));
      }

      z = 0;
      switch(v->WorkStage)
      {
        case 0: x =  x * v->Dir;                         z = v->Tj; if (!z) v->WorkStage++; else break;
        case 1: x = (v->Model == 1) ? (x * v->Dir) : 0;  z = v->Ta; if (!z) v->WorkStage++; else break;
        case 2: x = -x * v->Dir;                         z = v->Tj; if (!z) v->WorkStage++; else break;
        case 3: x =  0;                                  z = v->Tv; if (!z) v->WorkStage++; else break;
        case 4: x = -x * v->Dir;                         z = v->Tj; if (!z) v->WorkStage++; else break;
        case 5: x = (v->Model == 1) ? (-x * v->Dir) : 0; z = v->Ta; if (!z) v->WorkStage++; else break;
        case 6: x =  x * v->Dir;                         z = v->Tj; if (!z) v->WorkStage++; else break;
        case 7: v->P = v->TaskPos; v->InitStage = 1; return;
      }

      if (v->Model == 1) { v->A = x; }
      else { v->J = x; v->A = v->A + v->J * v->SampleTime; }
      v->V = v->V + v->A * v->SampleTime;
      v->P = v->P + v->V * v->SampleTime;

      v->Time = v->Time + v->SampleTime;
      if (v->Time >= z) { v->WorkStage++; v->Time = 0; }
      if (((v->Dir > 0) && (v->P >= v->TaskPos)) || ((v->Dir < 0) && (v->P <= v->TaskPos)))
      {
        v->P = v->TaskPos;
        v->InitStage = 1;
      }
    break;
  }
}

