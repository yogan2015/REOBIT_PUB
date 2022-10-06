// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
   v->Out_r1_TOP =  16777216 + (__IQmpy(*v->k, *v->In_r1 - 16777216, 24)>>1);
   v->Out_r1_BOT = -16777216 + (__IQmpy(*v->k, *v->In_r1 + 16777216, 24)>>1);

   v->Out_r2_TOP =  16777216 + (__IQmpy(*v->k, *v->In_r2 - 16777216, 24)>>1);
   v->Out_r2_BOT = -16777216 + (__IQmpy(*v->k, *v->In_r2 + 16777216, 24)>>1);

   v->Out_r3_TOP =  16777216 + (__IQmpy(*v->k, *v->In_r3 - 16777216, 24)>>1);
   v->Out_r3_BOT = -16777216 + (__IQmpy(*v->k, *v->In_r3 + 16777216, 24)>>1);
}

