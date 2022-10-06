
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1isqrt (*v->In << 1) >> 1; break;
    case 1:  v->Out = _IQ1isqrt (*v->In); break;
    case 2:  v->Out = _IQ2isqrt (*v->In); break;
    case 3:  v->Out = _IQ3isqrt (*v->In); break;
    case 4:  v->Out = _IQ4isqrt (*v->In); break;
    case 5:  v->Out = _IQ5isqrt (*v->In); break;
    case 6:  v->Out = _IQ6isqrt (*v->In); break;
    case 7:  v->Out = _IQ7isqrt (*v->In); break;
    case 8:  v->Out = _IQ8isqrt (*v->In); break;
    case 9:  v->Out = _IQ9isqrt (*v->In); break;
    case 10: v->Out = _IQ10isqrt(*v->In); break;
    case 11: v->Out = _IQ11isqrt(*v->In); break;
    case 12: v->Out = _IQ12isqrt(*v->In); break;
    case 13: v->Out = _IQ13isqrt(*v->In); break;
    case 14: v->Out = _IQ14isqrt(*v->In); break;
    case 15: v->Out = _IQ15isqrt(*v->In); break;
    case 16: v->Out = _IQ16isqrt(*v->In); break;
    case 17: v->Out = _IQ17isqrt(*v->In); break;
    case 18: v->Out = _IQ18isqrt(*v->In); break;
    case 19: v->Out = _IQ19isqrt(*v->In); break;
    case 20: v->Out = _IQ20isqrt(*v->In); break;
    case 21: v->Out = _IQ21isqrt(*v->In); break;
    case 22: v->Out = _IQ22isqrt(*v->In); break;
    case 23: v->Out = _IQ23isqrt(*v->In); break;
    case 24: v->Out = _IQ24isqrt(*v->In); break;
    case 25: v->Out = _IQ25isqrt(*v->In); break;
    case 26: v->Out = _IQ26isqrt(*v->In); break;
    case 27: v->Out = _IQ27isqrt(*v->In); break;
    case 28: v->Out = _IQ28isqrt(*v->In); break;
    case 29: v->Out = _IQ29isqrt(*v->In); break;
    case 30: v->Out = _IQ30isqrt(*v->In); break;
  }
}

