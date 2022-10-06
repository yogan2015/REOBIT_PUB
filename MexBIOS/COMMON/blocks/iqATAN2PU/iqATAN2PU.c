
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1atan2PU(*v->In1 << 1, *v->In2 << 1) >> 1; break;
    case 1:  v->Out = _IQ1atan2PU(*v->In1,  *v->In2); break;
    case 2:  v->Out = _IQ2atan2PU(*v->In1,  *v->In2); break;
    case 3:  v->Out = _IQ3atan2PU(*v->In1,  *v->In2); break;
    case 4:  v->Out = _IQ4atan2PU(*v->In1,  *v->In2); break;
    case 5:  v->Out = _IQ5atan2PU(*v->In1,  *v->In2); break;
    case 6:  v->Out = _IQ6atan2PU(*v->In1,  *v->In2); break;
    case 7:  v->Out = _IQ7atan2PU(*v->In1,  *v->In2); break;
    case 8:  v->Out = _IQ8atan2PU(*v->In1,  *v->In2); break;
    case 9:  v->Out = _IQ9atan2PU(*v->In1,  *v->In2); break;
    case 10: v->Out = _IQ10atan2PU(*v->In1, *v->In2); break;
    case 11: v->Out = _IQ11atan2PU(*v->In1, *v->In2); break;
    case 12: v->Out = _IQ12atan2PU(*v->In1, *v->In2); break;
    case 13: v->Out = _IQ13atan2PU(*v->In1, *v->In2); break;
    case 14: v->Out = _IQ14atan2PU(*v->In1, *v->In2); break;
    case 15: v->Out = _IQ15atan2PU(*v->In1, *v->In2); break;
    case 16: v->Out = _IQ16atan2PU(*v->In1, *v->In2); break;
    case 17: v->Out = _IQ17atan2PU(*v->In1, *v->In2); break;
    case 18: v->Out = _IQ18atan2PU(*v->In1, *v->In2); break;
    case 19: v->Out = _IQ19atan2PU(*v->In1, *v->In2); break;
    case 20: v->Out = _IQ20atan2PU(*v->In1, *v->In2); break;
    case 21: v->Out = _IQ21atan2PU(*v->In1, *v->In2); break;
    case 22: v->Out = _IQ22atan2PU(*v->In1, *v->In2); break;
    case 23: v->Out = _IQ23atan2PU(*v->In1, *v->In2); break;
    case 24: v->Out = _IQ24atan2PU(*v->In1, *v->In2); break;
    case 25: v->Out = _IQ25atan2PU(*v->In1, *v->In2); break;
    case 26: v->Out = _IQ26atan2PU(*v->In1, *v->In2); break;
    case 27: v->Out = _IQ27atan2PU(*v->In1, *v->In2); break;
    case 28: v->Out = _IQ28atan2PU(*v->In1, *v->In2); break;
    case 29: v->Out = _IQ29atan2PU(*v->In1, *v->In2); break;
    case 30: v->Out = _IQ30atan2PU(*v->In1, *v->In2); break;
  }
}

