#include "..\inc\rb24math.h"

void rb24math_printf(float f)
{
    union rb24math u;
    u.f = f;
    printf("(%x)(%x) : %d : %f\n",(u.num.sign & 0x80000000)>>31, u.num.val & 0x7FFFFFFF, u.i, u.f);
}

void rb24math_printi(int i)
{
    union rb24math u;
    u.i = i;
    printf("(%x)(%x) : %d : %f\n",(u.num.sign & 0x80000000)>>31, u.num.val & 0x7FFFFFFF, u.i, u.f);
}

int _f_to_IQ(float f)
{
    return ((f>0) ? ((int)(f * (1<<24))) : ((int)(256 + f * (1<<24)) | 0x80000000));
}

float _IQ_to_f(int i)
{
    
}