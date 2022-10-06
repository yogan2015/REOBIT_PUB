
// Do not initialize inputs!
#ifndef N_CBUF
#define N_CBUF
  volatile int bufbase[1024];
#endif

void Init(void)
{

}

void Exec(void)
{
   int* buf;
   switch (v->bufN){
     case 0:  buf = bufbase;         break;
     case 1:  buf = bufbase + 256;   break;
     case 2:  buf = bufbase + 512;   break;
     case 3:  buf = bufbase + 768;   break;
   }
   if ((short)*v->en)
   {
     v->index += 1;
     if (v->index >= 256) v->index = 0;
     buf[v->index] = *v->value;
   }
   v->index_now = v->index;
   v->value_read = buf[*v->index_get];

}

