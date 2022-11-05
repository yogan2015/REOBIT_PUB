#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

union rb24math
{
    struct rbsint
    {    
        int  val   : 31;  
        int  sign  : 1; 
    } num;
    int i;
    float f;
};

void rb24math_printf(float f);
void rb24math_printi(int i);

int     _f_to_IQ(float f);
float   _IQ_to_f(int i);