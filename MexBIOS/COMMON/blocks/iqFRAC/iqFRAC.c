
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = 0;                 break;
    case 1:  v->Out = _IQ1frac (*v->In); break;
    case 2:  v->Out = _IQ2frac (*v->In); break;
    case 3:  v->Out = _IQ3frac (*v->In); break;
    case 4:  v->Out = _IQ4frac (*v->In); break;
    case 5:  v->Out = _IQ5frac (*v->In); break;
    case 6:  v->Out = _IQ6frac (*v->In); break;
    case 7:  v->Out = _IQ7frac (*v->In); break;
    case 8:  v->Out = _IQ8frac (*v->In); break;
    case 9:  v->Out = _IQ9frac (*v->In); break;
    case 10: v->Out = _IQ10frac(*v->In); break;
    case 11: v->Out = _IQ11frac(*v->In); break;
    case 12: v->Out = _IQ12frac(*v->In); break;
    case 13: v->Out = _IQ13frac(*v->In); break;
    case 14: v->Out = _IQ14frac(*v->In); break;
    case 15: v->Out = _IQ15frac(*v->In); break;
    case 16: v->Out = _IQ16frac(*v->In); break;
    case 17: v->Out = _IQ17frac(*v->In); break;
    case 18: v->Out = _IQ18frac(*v->In); break;
    case 19: v->Out = _IQ19frac(*v->In); break;
    case 20: v->Out = _IQ20frac(*v->In); break;
    case 21: v->Out = _IQ21frac(*v->In); break;
    case 22: v->Out = _IQ22frac(*v->In); break;
    case 23: v->Out = _IQ23frac(*v->In); break;
    case 24: v->Out = _IQ24frac(*v->In); break;
    case 25: v->Out = _IQ25frac(*v->In); break;
    case 26: v->Out = _IQ26frac(*v->In); break;
    case 27: v->Out = _IQ27frac(*v->In); break;
    case 28: v->Out = _IQ28frac(*v->In); break;
    case 29: v->Out = _IQ29frac(*v->In); break;
    case 30: v->Out = _IQ30frac(*v->In); break;
  }
}



