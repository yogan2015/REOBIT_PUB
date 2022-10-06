
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
if (*v->ARR_Func)
{
   if (!*v->ARR_D_IN)
     {
       v->VKZ_DO = 0;
        v->VKZ_To_SW = ((*v->SW) ^ (*v->VKZ<<7));
     }
   else
     {
       v->VKZ_DO = *v->VKZ;
       v->VKZ_To_SW = ((*v->SW) ^ (*v->VKZ<<7)) | (*v->VKZ<<7);
     }

}
else
{
  v->VKZ_DO = *v->VKZ;
  v->VKZ_To_SW = ((*v->SW) ^ (*v->VKZ<<7)) | (*v->VKZ<<7);
}

v->VKZ_Light = (v->VKZ_To_SW & 0x80) >> 7;

}

