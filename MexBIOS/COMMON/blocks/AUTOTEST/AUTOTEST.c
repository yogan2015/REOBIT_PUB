
 #define inSB1  0x1
 #define inSB2  0x2
 #define inCcmd 0x4
 #define inOcmd 0x8
 #define inARR  0x10
 #define VKO  (*v->SIGNAL & 0x20)>>5
 #define VKZ  (*v->SIGNAL & 0x40)>>6
 #define RVM  (*v->SIGNAL & 0x80)>>7

// Do not initialize inputs!
void Init(void)
{
  v->CMD = 0;
}

void Exec(void)
{

  if (*v->En == 0)
  {
 v->CMD = *v->SIGNAL;

  }
  else
  {

  if ((*v->SIGNAL & 0x1) && (*v->SIGNAL & 0x2) )
  {
    v->Time = 0;
    v->CMD = 0;
  }
    if (v->N)
    {

      if (((v->CMD & inOcmd) == 0)&& ( v->Time == 0))v->CMD |= inCcmd;
      if (RVM) { v->CMD &= 0xFFFFFFFA; v->CMD |= inOcmd;}

      if (VKO && (v->CMD & inOcmd) && (v->Time == 0) )
      {
      v->CMD &= 0xFFFFFFF5;
      v->N--;
      }
      if (VKO && (v->Time < v->Delay))      v->Time+=v->SampleTime;
      if (VKO && (v->Time >= v->Delay ) )  { v->CMD |= inCcmd;}

      if (VKZ && (v->CMD & inCcmd) && (v->Time == 0) )
      {
      v->CMD &= 0xFFFFFFFA;
      v->N--;
      }
      if (VKZ && (v->Time < v->Delay))      v->Time+=v->SampleTime;
      if (VKZ && (v->Time >= v->Delay ) )  { v->CMD |= inOcmd;}



      if ( (VKO == 0) && (VKZ == 0)) v->Time = 0;

    }
    else
    {
    if ( (*v->SIGNAL & 0x4 ) != (v->CMD & 0x4) ) v->CMD ^= 0x4; //send command to output
    if ( (*v->SIGNAL & 0x8 ) != (v->CMD & 0x8) ) v->CMD ^= 0x8; //send command to output
    }
   if ((*v->SIGNAL & 0x1)  != (v->CMD & 0x1)  ) v->CMD ^= 0x1; //send command to output
   if ((*v->SIGNAL & 0x2 ) != (v->CMD & 0x2)  ) v->CMD ^= 0x2; //send command to output
   if ((*v->SIGNAL & 0x10 ) != (v->CMD & 0x10)  ) v->CMD ^= 0x10; //send command to output*/

  if (RVM) v->Time = 0;
  }

}



