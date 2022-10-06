#ifndef ADC_MACROSS
#define ADC_MACROSS

#define IPM0_Iu      0
#define IPM0_Iv      4
#define IPM0_Iw      8
#define IPM0_UDC     36
#define IPM0_T       32

#define IPM3_Iu      12
#define IPM3_Iv      16
#define IPM3_Iw      20
#define IPM3_UDC     24
#define IPM3_T       28

#define AI0          44
#define AI1          40
#define AI2          52
#define AI3          48
#define AI4          60
#define AI5          56

#endif

// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->U1_Iu  = *((int *)(*v->offset + IPM0_Iu));
  v->U1_Iv  = *((int *)(*v->offset + IPM0_Iv));
  v->U1_Iw  = *((int *)(*v->offset + IPM0_Iw));
  v->U1_UDC = *((int *)(*v->offset + IPM0_UDC));
  v->U1_T   = *((int *)(*v->offset + IPM0_T));

  v->U2_Iu  = *((int *)(*v->offset + IPM3_Iu));
  v->U2_Iv  = *((int *)(*v->offset + IPM3_Iv));
  v->U2_Iw  = *((int *)(*v->offset + IPM3_Iw));
  v->U2_UDC = *((int *)(*v->offset + IPM3_UDC));
  v->U2_T   = *((int *)(*v->offset + IPM3_T));

  v->AI_0   = *((int *)(*v->offset + AI0));
  v->AI_1   = *((int *)(*v->offset + AI1));
  v->AI_2   = *((int *)(*v->offset + AI2));
  v->AI_3   = *((int *)(*v->offset + AI3));
  v->AI_4   = *((int *)(*v->offset + AI4));
  v->AI_5   = *((int *)(*v->offset + AI5));
}

