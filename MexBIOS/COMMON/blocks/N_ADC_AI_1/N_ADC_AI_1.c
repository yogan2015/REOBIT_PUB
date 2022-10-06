#ifndef ADC_MACROSS
#define ADC_MACROSS

#define IPM0_Iu      0
#define IPM0_Iv      4
#define IPM0_Iw      8
#define IPM0_UDC     32
#define IPM0_T       36

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
  v->AI_0    = _IQ24mpy(((((*((int *)(*v->offset + AI0)))) << 12) - v->off_0) << 5, v->g_0);
  v->AI_1    = _IQ24mpy(((((*((int *)(*v->offset + AI1)))) << 12) - v->off_1) << 5, v->g_1);
  v->AI_2    = _IQ24mpy(((((*((int *)(*v->offset + AI2)))) << 12) - v->off_2) << 5, v->g_2);
  v->AI_3    = _IQ24mpy(((((*((int *)(*v->offset + AI3)))) << 12) - v->off_3) << 5, v->g_3);
  v->AI_4    = _IQ24mpy(((((*((int *)(*v->offset + AI4)))) << 12) - v->off_4) << 5, v->g_4);
  v->AI_5    = _IQ24mpy(((((*((int *)(*v->offset + AI5)))) << 12) - v->off_5) << 5, v->g_5);
}

