
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1cosPU (*v->In << 1) >> 1; break;
    case 1:  v->Out = _IQ1cosPU (*v->In); break;
    case 2:  v->Out = _IQ2cosPU (*v->In); break;
    case 3:  v->Out = _IQ3cosPU (*v->In); break;
    case 4:  v->Out = _IQ4cosPU (*v->In); break;
    case 5:  v->Out = _IQ5cosPU (*v->In); break;
    case 6:  v->Out = _IQ6cosPU (*v->In); break;
    case 7:  v->Out = _IQ7cosPU (*v->In); break;
    case 8:  v->Out = _IQ8cosPU (*v->In); break;
    case 9:  v->Out = _IQ9cosPU (*v->In); break;
    case 10: v->Out = _IQ10cosPU(*v->In); break;
    case 11: v->Out = _IQ11cosPU(*v->In); break;
    case 12: v->Out = _IQ12cosPU(*v->In); break;
    case 13: v->Out = _IQ13cosPU(*v->In); break;
    case 14: v->Out = _IQ14cosPU(*v->In); break;
    case 15: v->Out = _IQ15cosPU(*v->In); break;
    case 16: v->Out = _IQ16cosPU(*v->In); break;
    case 17: v->Out = _IQ17cosPU(*v->In); break;
    case 18: v->Out = _IQ18cosPU(*v->In); break;
    case 19: v->Out = _IQ19cosPU(*v->In); break;
    case 20: v->Out = _IQ20cosPU(*v->In); break;
    case 21: v->Out = _IQ21cosPU(*v->In); break;
    case 22: v->Out = _IQ22cosPU(*v->In); break;
    case 23: v->Out = _IQ23cosPU(*v->In); break;
    case 24: v->Out = _IQ24cosPU(*v->In); break;
    case 25: v->Out = _IQ25cosPU(*v->In); break;
    case 26: v->Out = _IQ26cosPU(*v->In); break;
    case 27: v->Out = _IQ27cosPU(*v->In); break;
    case 28: v->Out = _IQ28cosPU(*v->In); break;
    case 29: v->Out = _IQ29cosPU(*v->In); break;
    case 30: v->Out = _IQ30cosPU(*v->In); break;
  }
}

