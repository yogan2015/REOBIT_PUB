
void Init(void)
{
}

void Exec(void)
{
  long Result = __IQmpy(*v->In1 - *v->In2, *v->In1 + *v->In2, v->Format);
  if (Result < 0) { v->Out = 0; return; }
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1sqrt(Result << 1) >> 1; break;
    case 1:  v->Out = _IQ1sqrt(Result); break;
    case 2:  v->Out = _IQ2sqrt(Result); break;
    case 3:  v->Out = _IQ3sqrt(Result); break;
    case 4:  v->Out = _IQ4sqrt(Result); break;
    case 5:  v->Out = _IQ5sqrt(Result); break;
    case 6:  v->Out = _IQ6sqrt(Result); break;
    case 7:  v->Out = _IQ7sqrt(Result); break;
    case 8:  v->Out = _IQ8sqrt(Result); break;
    case 9:  v->Out = _IQ9sqrt(Result); break;
    case 10: v->Out = _IQ10sqrt(Result); break;
    case 11: v->Out = _IQ11sqrt(Result); break;
    case 12: v->Out = _IQ12sqrt(Result); break;
    case 13: v->Out = _IQ13sqrt(Result); break;
    case 14: v->Out = _IQ14sqrt(Result); break;
    case 15: v->Out = _IQ15sqrt(Result); break;
    case 16: v->Out = _IQ16sqrt(Result); break;
    case 17: v->Out = _IQ17sqrt(Result); break;
    case 18: v->Out = _IQ18sqrt(Result); break;
    case 19: v->Out = _IQ19sqrt(Result); break;
    case 20: v->Out = _IQ20sqrt(Result); break;
    case 21: v->Out = _IQ21sqrt(Result); break;
    case 22: v->Out = _IQ22sqrt(Result); break;
    case 23: v->Out = _IQ23sqrt(Result); break;
    case 24: v->Out = _IQ24sqrt(Result); break;
    case 25: v->Out = _IQ25sqrt(Result); break;
    case 26: v->Out = _IQ26sqrt(Result); break;
    case 27: v->Out = _IQ27sqrt(Result); break;
    case 28: v->Out = _IQ28sqrt(Result); break;
    case 29: v->Out = _IQ29sqrt(Result); break;
    case 30: v->Out = _IQ30sqrt(Result); break;
  }
}


