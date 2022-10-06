
void Init(void)
{
}

void Exec(void)
{
     if ((short)*v->En)
     {
       v->Time += v->SampleTime;
       if (*v->In <= v->Min) v->Out = 0;
       else if (*v->In >= v->Max) v->Out = 1;
       else if ( v->Time < ((*v->In - v->Min) / (v->Max - v->Min) * v->T) ) v->Out = 1;
       else v->Out = 0;
       if ( v->Time > v->T ) v->Time = 0;
       }
     else
       { v->Time = 0; v->Out = 0; }
}

