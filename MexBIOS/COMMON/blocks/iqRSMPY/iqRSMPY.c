
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = *v->In1 * *v->In2;            break;
    case 1:  v->Out = _IQ1rsmpy(*v->In1,  *v->In2); break;
    case 2:  v->Out = _IQ2rsmpy(*v->In1,  *v->In2); break;
    case 3:  v->Out = _IQ3rsmpy(*v->In1,  *v->In2); break;
    case 4:  v->Out = _IQ4rsmpy(*v->In1,  *v->In2); break;
    case 5:  v->Out = _IQ5rsmpy(*v->In1,  *v->In2); break;
    case 6:  v->Out = _IQ6rsmpy(*v->In1,  *v->In2); break;
    case 7:  v->Out = _IQ7rsmpy(*v->In1,  *v->In2); break;
    case 8:  v->Out = _IQ8rsmpy(*v->In1,  *v->In2); break;
    case 9:  v->Out = _IQ9rsmpy(*v->In1,  *v->In2); break;
    case 10: v->Out = _IQ10rsmpy(*v->In1, *v->In2); break;
    case 11: v->Out = _IQ11rsmpy(*v->In1, *v->In2); break;
    case 12: v->Out = _IQ12rsmpy(*v->In1, *v->In2); break;
    case 13: v->Out = _IQ13rsmpy(*v->In1, *v->In2); break;
    case 14: v->Out = _IQ14rsmpy(*v->In1, *v->In2); break;
    case 15: v->Out = _IQ15rsmpy(*v->In1, *v->In2); break;
    case 16: v->Out = _IQ16rsmpy(*v->In1, *v->In2); break;
    case 17: v->Out = _IQ17rsmpy(*v->In1, *v->In2); break;
    case 18: v->Out = _IQ18rsmpy(*v->In1, *v->In2); break;
    case 19: v->Out = _IQ19rsmpy(*v->In1, *v->In2); break;
    case 20: v->Out = _IQ20rsmpy(*v->In1, *v->In2); break;
    case 21: v->Out = _IQ21rsmpy(*v->In1, *v->In2); break;
    case 22: v->Out = _IQ22rsmpy(*v->In1, *v->In2); break;
    case 23: v->Out = _IQ23rsmpy(*v->In1, *v->In2); break;
    case 24: v->Out = _IQ24rsmpy(*v->In1, *v->In2); break;
    case 25: v->Out = _IQ25rsmpy(*v->In1, *v->In2); break;
    case 26: v->Out = _IQ26rsmpy(*v->In1, *v->In2); break;
    case 27: v->Out = _IQ27rsmpy(*v->In1, *v->In2); break;
    case 28: v->Out = _IQ28rsmpy(*v->In1, *v->In2); break;
    case 29: v->Out = _IQ29rsmpy(*v->In1, *v->In2); break;
    case 30: v->Out = _IQ30rsmpy(*v->In1, *v->In2); break;
  }
}

