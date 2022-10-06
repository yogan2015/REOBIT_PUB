
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = *v->In1 * *v->In2;           break;
    case 1:  v->Out = _IQ1rmpy(*v->In1,  *v->In2); break;
    case 2:  v->Out = _IQ2rmpy(*v->In1,  *v->In2); break;
    case 3:  v->Out = _IQ3rmpy(*v->In1,  *v->In2); break;
    case 4:  v->Out = _IQ4rmpy(*v->In1,  *v->In2); break;
    case 5:  v->Out = _IQ5rmpy(*v->In1,  *v->In2); break;
    case 6:  v->Out = _IQ6rmpy(*v->In1,  *v->In2); break;
    case 7:  v->Out = _IQ7rmpy(*v->In1,  *v->In2); break;
    case 8:  v->Out = _IQ8rmpy(*v->In1,  *v->In2); break;
    case 9:  v->Out = _IQ9rmpy(*v->In1,  *v->In2); break;
    case 10: v->Out = _IQ10rmpy(*v->In1, *v->In2); break;
    case 11: v->Out = _IQ11rmpy(*v->In1, *v->In2); break;
    case 12: v->Out = _IQ12rmpy(*v->In1, *v->In2); break;
    case 13: v->Out = _IQ13rmpy(*v->In1, *v->In2); break;
    case 14: v->Out = _IQ14rmpy(*v->In1, *v->In2); break;
    case 15: v->Out = _IQ15rmpy(*v->In1, *v->In2); break;
    case 16: v->Out = _IQ16rmpy(*v->In1, *v->In2); break;
    case 17: v->Out = _IQ17rmpy(*v->In1, *v->In2); break;
    case 18: v->Out = _IQ18rmpy(*v->In1, *v->In2); break;
    case 19: v->Out = _IQ19rmpy(*v->In1, *v->In2); break;
    case 20: v->Out = _IQ20rmpy(*v->In1, *v->In2); break;
    case 21: v->Out = _IQ21rmpy(*v->In1, *v->In2); break;
    case 22: v->Out = _IQ22rmpy(*v->In1, *v->In2); break;
    case 23: v->Out = _IQ23rmpy(*v->In1, *v->In2); break;
    case 24: v->Out = _IQ24rmpy(*v->In1, *v->In2); break;
    case 25: v->Out = _IQ25rmpy(*v->In1, *v->In2); break;
    case 26: v->Out = _IQ26rmpy(*v->In1, *v->In2); break;
    case 27: v->Out = _IQ27rmpy(*v->In1, *v->In2); break;
    case 28: v->Out = _IQ28rmpy(*v->In1, *v->In2); break;
    case 29: v->Out = _IQ29rmpy(*v->In1, *v->In2); break;
    case 30: v->Out = _IQ30rmpy(*v->In1, *v->In2); break;
  }
}

