
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = *v->In;           break;
    case 1:  v->Out = _IQ1int (*v->In); break;
    case 2:  v->Out = _IQ2int (*v->In); break;
    case 3:  v->Out = _IQ3int (*v->In); break;
    case 4:  v->Out = _IQ4int (*v->In); break;
    case 5:  v->Out = _IQ5int (*v->In); break;
    case 6:  v->Out = _IQ6int (*v->In); break;
    case 7:  v->Out = _IQ7int (*v->In); break;
    case 8:  v->Out = _IQ8int (*v->In); break;
    case 9:  v->Out = _IQ9int (*v->In); break;
    case 10: v->Out = _IQ10int(*v->In); break;
    case 11: v->Out = _IQ11int(*v->In); break;
    case 12: v->Out = _IQ12int(*v->In); break;
    case 13: v->Out = _IQ13int(*v->In); break;
    case 14: v->Out = _IQ14int(*v->In); break;
    case 15: v->Out = _IQ15int(*v->In); break;
    case 16: v->Out = _IQ16int(*v->In); break;
    case 17: v->Out = _IQ17int(*v->In); break;
    case 18: v->Out = _IQ18int(*v->In); break;
    case 19: v->Out = _IQ19int(*v->In); break;
    case 20: v->Out = _IQ20int(*v->In); break;
    case 21: v->Out = _IQ21int(*v->In); break;
    case 22: v->Out = _IQ22int(*v->In); break;
    case 23: v->Out = _IQ23int(*v->In); break;
    case 24: v->Out = _IQ24int(*v->In); break;
    case 25: v->Out = _IQ25int(*v->In); break;
    case 26: v->Out = _IQ26int(*v->In); break;
    case 27: v->Out = _IQ27int(*v->In); break;
    case 28: v->Out = _IQ28int(*v->In); break;
    case 29: v->Out = _IQ29int(*v->In); break;
    case 30: v->Out = _IQ30int(*v->In); break;
  }
}

