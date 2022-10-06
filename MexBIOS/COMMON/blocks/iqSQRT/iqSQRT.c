
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1sqrt (*v->In << 1) >> 1; break;
    case 1:  v->Out = _IQ1sqrt (*v->In); break;
    case 2:  v->Out = _IQ2sqrt (*v->In); break;
    case 3:  v->Out = _IQ3sqrt (*v->In); break;
    case 4:  v->Out = _IQ4sqrt (*v->In); break;
    case 5:  v->Out = _IQ5sqrt (*v->In); break;
    case 6:  v->Out = _IQ6sqrt (*v->In); break;
    case 7:  v->Out = _IQ7sqrt (*v->In); break;
    case 8:  v->Out = _IQ8sqrt (*v->In); break;
    case 9:  v->Out = _IQ9sqrt (*v->In); break;
    case 10: v->Out = _IQ10sqrt(*v->In); break;
    case 11: v->Out = _IQ11sqrt(*v->In); break;
    case 12: v->Out = _IQ12sqrt(*v->In); break;
    case 13: v->Out = _IQ13sqrt(*v->In); break;
    case 14: v->Out = _IQ14sqrt(*v->In); break;
    case 15: v->Out = _IQ15sqrt(*v->In); break;
    case 16: v->Out = _IQ16sqrt(*v->In); break;
    case 17: v->Out = _IQ17sqrt(*v->In); break;
    case 18: v->Out = _IQ18sqrt(*v->In); break;
    case 19: v->Out = _IQ19sqrt(*v->In); break;
    case 20: v->Out = _IQ20sqrt(*v->In); break;
    case 21: v->Out = _IQ21sqrt(*v->In); break;
    case 22: v->Out = _IQ22sqrt(*v->In); break;
    case 23: v->Out = _IQ23sqrt(*v->In); break;
    case 24: v->Out = _IQ24sqrt(*v->In); break;
    case 25: v->Out = _IQ25sqrt(*v->In); break;
    case 26: v->Out = _IQ26sqrt(*v->In); break;
    case 27: v->Out = _IQ27sqrt(*v->In); break;
    case 28: v->Out = _IQ28sqrt(*v->In); break;
    case 29: v->Out = _IQ29sqrt(*v->In); break;
    case 30: v->Out = _IQ30sqrt(*v->In); break;
  }
}

