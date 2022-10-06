
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1cos (*v->In << 1) >> 1; break;
    case 1:  v->Out = _IQ1cos (*v->In); break;
    case 2:  v->Out = _IQ2cos (*v->In); break;
    case 3:  v->Out = _IQ3cos (*v->In); break;
    case 4:  v->Out = _IQ4cos (*v->In); break;
    case 5:  v->Out = _IQ5cos (*v->In); break;
    case 6:  v->Out = _IQ6cos (*v->In); break;
    case 7:  v->Out = _IQ7cos (*v->In); break;
    case 8:  v->Out = _IQ8cos (*v->In); break;
    case 9:  v->Out = _IQ9cos (*v->In); break;
    case 10: v->Out = _IQ10cos(*v->In); break;
    case 11: v->Out = _IQ11cos(*v->In); break;
    case 12: v->Out = _IQ12cos(*v->In); break;
    case 13: v->Out = _IQ13cos(*v->In); break;
    case 14: v->Out = _IQ14cos(*v->In); break;
    case 15: v->Out = _IQ15cos(*v->In); break;
    case 16: v->Out = _IQ16cos(*v->In); break;
    case 17: v->Out = _IQ17cos(*v->In); break;
    case 18: v->Out = _IQ18cos(*v->In); break;
    case 19: v->Out = _IQ19cos(*v->In); break;
    case 20: v->Out = _IQ20cos(*v->In); break;
    case 21: v->Out = _IQ21cos(*v->In); break;
    case 22: v->Out = _IQ22cos(*v->In); break;
    case 23: v->Out = _IQ23cos(*v->In); break;
    case 24: v->Out = _IQ24cos(*v->In); break;
    case 25: v->Out = _IQ25cos(*v->In); break;
    case 26: v->Out = _IQ26cos(*v->In); break;
    case 27: v->Out = _IQ27cos(*v->In); break;
    case 28: v->Out = _IQ28cos(*v->In); break;
    case 29: v->Out = _IQ29cos(*v->In); break;
    case 30: v->Out = _IQ30cos(*v->In); break;
  }
}

