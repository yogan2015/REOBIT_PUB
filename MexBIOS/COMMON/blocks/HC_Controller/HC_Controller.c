
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{

v->Out = v->PrevOut + (v->SampleTime * v->Ki * v->PrevErr) - (v->SampleTime * v->PrevV) + v->AntiWindup;
v->V = v->PrevV + (v->SampleTime * v->AngularFreq * v->AngularFreq * v->Out);
v->PrevErr = *v->Err;
v->PrevOut = v->Out;
v->PrevV = v->V;
if (v->Out > v->MaxMin) {v->AntiWindup = v->MaxMin - v->Out;}
if (v->Out < -v->MaxMin) {v->AntiWindup = -v->MaxMin - v->Out;}

}

