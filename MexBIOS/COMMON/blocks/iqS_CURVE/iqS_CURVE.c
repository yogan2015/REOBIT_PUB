
void Init(void)
{
}

void Exec(void)
{
  long x, z;

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

      v->MovePos  = (v->TaskPos - v->P) * v->Dir;
      v->CurPosHi = _IQ16int(v->P);
      v->CurPosLo = _IQ16frac(v->P) << 8;

      v->Time      = _IQ15div(v->MovePos, v->Jmax);
      v->Tj        = _IQ16sqrt(v->Time);
      v->Tick      = 0;
      v->InitStage = 2;
    break;
    case 2:
      if (v->Model == 1)
      {
        v->Tj = 0;
        v->Ta = _IQ16div(v->Vmax, v->Amax);
        z     = _IQ16mpy(v->Amax, _IQ16mpy(v->Ta, v->Ta));
        if (z <= v->MovePos) { v->Tv = _IQ16div(v->MovePos - z, v->Vmax); }
        else { v->Ta = _IQ16sqrt(_IQ16div(v->MovePos, v->Amax)); v->Tv = 0; }
        v->InitStage = 4;
      }
      else
      {
        x       = _IQ16div(v->Time, _IQ16mpy(v->Tj, v->Tj));
        v->Tj   = _IQ16div((v->Tj << 1) + x, _IQ16(3.0));
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

      x = _IQ16mpy(v->Jmax, v->Tj);
      z = _IQ16mpy(x, v->Tj);
      if ((x < v->Amax) && (z < v->Vmax)) break;

      x = _IQ16mpy(v->Jmax, _IQ16div(v->Vmax, v->Amax));
      if (x < v->Amax)
      {
        v->Tj = _IQ16sqrt(_IQ16div(v->Vmax, v->Jmax));
        v->Tv = _IQ16div(v->MovePos, v->Vmax) - (v->Tj << 1);
        break;
      }

      v->Tj = _IQ16div(v->Amax, v->Jmax);
      x     = _IQ17mpy(v->Tj, v->Amax);
      v->Ta = _IQ16div(v->Vmax - (x << 1), v->Amax);
      z     = _IQ14mpy(v->Tj, x);
      z    += _IQ15mpy(v->Ta, x);
      z    += _IQ15mpy(v->Amax, _IQ16mpy(v->Ta, v->Tj));
      z    += _IQ16mpy(v->Amax, _IQ16mpy(v->Ta, v->Ta));
      if (z <= v->MovePos) { v->Tv = _IQ16div(v->MovePos - z, v->Vmax); break; }

      x     = _IQ16sqrt(_IQ18mpy(v->Tj, v->Tj) + _IQ16div(v->MovePos, v->Amax));
      v->Ta = x - _IQ16mpy(v->Tj, _IQ16(1.5));
    break;
    case 4:
      switch(v->Model)
      {
        case 1: x = v->Amax << 8; break;
        case 2: x = v->Jmax << 8; break;
        default:
          x = _IQ24sinPU(_IQ24div(v->Time, v->Tj) + _IQ24(0.25));
          x = _IQ16mpy(v->Jmax, _IQ24(1.0) - x);
          break;
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
      else { v->J = x; v->A = v->A + _IQ24mpy(v->J, v->SampleTime); }
      v->V = v->V + _IQ24mpy(v->A, v->SampleTime);

      v->CurPosLo = v->CurPosLo + _IQ24mpy(v->V, v->SampleTime);
      if (v->CurPosLo >= _IQ24( 1.0)) { v->CurPosLo -= _IQ24(1.0); v->CurPosHi++; }
      if (v->CurPosLo <= _IQ24(-1.0)) { v->CurPosLo += _IQ24(1.0); v->CurPosHi--; }

      x    = _IQ1div(v->CurPosLo, 512);
      v->P = (v->CurPosHi << 16) + x;

      v->Tick = v->Tick + v->SampleTime;
      if (v->Tick >= _IQ24(1.0)) { v->Tick -= _IQ24(1.0); v->Time += _IQ16(1.0); }
      v->Time = (v->Time & 0xFFFF0000) | ((v->Tick >> 8) & 0x0000FFFF);

      if (v->Time >= z) { v->WorkStage++; v->Tick = 0; v->Time = 0; }
      if (((v->Dir > 0) && (v->P >= v->TaskPos)) || ((v->Dir < 0) && (v->P <= v->TaskPos)))
      {
        v->P = v->TaskPos;
        v->InitStage = 1;
      }
    break;
  }
}

