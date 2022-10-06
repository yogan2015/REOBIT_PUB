
 #define GPUn   2
 #define GPUk   3
 #define LPUlb  4
 #define LPUpb  5

// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
v->Chanel = ( *v->CanL & 1);

switch (*v->ID)
{
  case GPUn:
    v->Pusk = (*v->CanL & 2)>>1;
    v->Stop = (*v->CanL & 4)>>2;
    v->SpdReff = _IQtoIQ((((*v->CanL >> 5) & 0x7FF) << 21),21,0);
    break;
  case GPUk:
    v->Pusk    = (*v->CanL & 8)>>3;
    v->Stop    = (*v->CanL & 16)>>4;
    v->SpdReff = _IQtoIQ((((*v->CanL >> 21) & 0x7FF) << 21),21,0);
    break;
  case LPUlb:
    v->Pusk    = (*v->CanL & (1<<17))>>17;
    v->Stop    = (*v->CanL & (1<<18))>>18;
    v->SpdReff = _IQtoIQ((((*v->CanH >> 5) & 0x7FF) << 21),21,0);
    break;
  case LPUpb:
    v->Pusk    = (*v->CanL & (1<<19))>>19;
    v->Stop    = (*v->CanL & (1<<20))>>20;
    v->SpdReff = _IQtoIQ((((*v->CanH >> 21) & 0x7FF) << 21),21,0);
    break;
  }
}

