
void Init(void)
{
}

void Exec(void)
{
  switch(v->Format)
  {
    case 0:  v->Out = _IQ1sqrt((*v->In1 * *v->In1 + *v->In2 * *v->In2) << 1) >> 1; break;
    case 1:  v->Out = _IQ1mag(*v->In1,  *v->In2); break;
    case 2:  v->Out = _IQ2mag(*v->In1,  *v->In2); break;
    case 3:  v->Out = _IQ3mag(*v->In1,  *v->In2); break;
    case 4:  v->Out = _IQ4mag(*v->In1,  *v->In2); break;
    case 5:  v->Out = _IQ5mag(*v->In1,  *v->In2); break;
    case 6:  v->Out = _IQ6mag(*v->In1,  *v->In2); break;
    case 7:  v->Out = _IQ7mag(*v->In1,  *v->In2); break;
    case 8:  v->Out = _IQ8mag(*v->In1,  *v->In2); break;
    case 9:  v->Out = _IQ9mag(*v->In1,  *v->In2); break;
    case 10: v->Out = _IQ10mag(*v->In1, *v->In2); break;
    case 11: v->Out = _IQ11mag(*v->In1, *v->In2); break;
    case 12: v->Out = _IQ12mag(*v->In1, *v->In2); break;
    case 13: v->Out = _IQ13mag(*v->In1, *v->In2); break;
    case 14: v->Out = _IQ14mag(*v->In1, *v->In2); break;
    case 15: v->Out = _IQ15mag(*v->In1, *v->In2); break;
    case 16: v->Out = _IQ16mag(*v->In1, *v->In2); break;
    case 17: v->Out = _IQ17mag(*v->In1, *v->In2); break;
    case 18: v->Out = _IQ18mag(*v->In1, *v->In2); break;
    case 19: v->Out = _IQ19mag(*v->In1, *v->In2); break;
    case 20: v->Out = _IQ20mag(*v->In1, *v->In2); break;
    case 21: v->Out = _IQ21mag(*v->In1, *v->In2); break;
    case 22: v->Out = _IQ22mag(*v->In1, *v->In2); break;
    case 23: v->Out = _IQ23mag(*v->In1, *v->In2); break;
    case 24: v->Out = _IQ24mag(*v->In1, *v->In2); break;
    case 25: v->Out = _IQ25mag(*v->In1, *v->In2); break;
    case 26: v->Out = _IQ26mag(*v->In1, *v->In2); break;
    case 27: v->Out = _IQ27mag(*v->In1, *v->In2); break;
    case 28: v->Out = _IQ28mag(*v->In1, *v->In2); break;
    case 29: v->Out = _IQ29mag(*v->In1, *v->In2); break;
    case 30: v->Out = _IQ30mag(*v->In1, *v->In2); break;
  }
}

