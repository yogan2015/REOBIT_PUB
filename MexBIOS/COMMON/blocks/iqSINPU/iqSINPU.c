
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1sinPU (*v->In << 1) >> 1; break;
    case 1:  v->Out = _IQ1sinPU (*v->In); break;
    case 2:  v->Out = _IQ2sinPU (*v->In); break;
    case 3:  v->Out = _IQ3sinPU (*v->In); break;
    case 4:  v->Out = _IQ4sinPU (*v->In); break;
    case 5:  v->Out = _IQ5sinPU (*v->In); break;
    case 6:  v->Out = _IQ6sinPU (*v->In); break;
    case 7:  v->Out = _IQ7sinPU (*v->In); break;
    case 8:  v->Out = _IQ8sinPU (*v->In); break;
    case 9:  v->Out = _IQ9sinPU (*v->In); break;
    case 10: v->Out = _IQ10sinPU(*v->In); break;
    case 11: v->Out = _IQ11sinPU(*v->In); break;
    case 12: v->Out = _IQ12sinPU(*v->In); break;
    case 13: v->Out = _IQ13sinPU(*v->In); break;
    case 14: v->Out = _IQ14sinPU(*v->In); break;
    case 15: v->Out = _IQ15sinPU(*v->In); break;
    case 16: v->Out = _IQ16sinPU(*v->In); break;
    case 17: v->Out = _IQ17sinPU(*v->In); break;
    case 18: v->Out = _IQ18sinPU(*v->In); break;
    case 19: v->Out = _IQ19sinPU(*v->In); break;
    case 20: v->Out = _IQ20sinPU(*v->In); break;
    case 21: v->Out = _IQ21sinPU(*v->In); break;
    case 22: v->Out = _IQ22sinPU(*v->In); break;
    case 23: v->Out = _IQ23sinPU(*v->In); break;
    case 24: v->Out = _IQ24sinPU(*v->In); break;
    case 25: v->Out = _IQ25sinPU(*v->In); break;
    case 26: v->Out = _IQ26sinPU(*v->In); break;
    case 27: v->Out = _IQ27sinPU(*v->In); break;
    case 28: v->Out = _IQ28sinPU(*v->In); break;
    case 29: v->Out = _IQ29sinPU(*v->In); break;
    case 30: v->Out = _IQ30sinPU(*v->In); break;
  }
}

