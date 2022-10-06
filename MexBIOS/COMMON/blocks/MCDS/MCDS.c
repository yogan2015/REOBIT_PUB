#define swap_a  if (InArr_A[v->i]<InArr_A[v->j])  {  InArr_A[v->i] ^= InArr_A[v->j]; InArr_A[v->j] ^= InArr_A[v->i]; InArr_A[v->i] ^= InArr_A[v->j];}
#define swap_b  if (InArr_B[v->i]<InArr_B[v->j])  {  InArr_B[v->i] ^= InArr_B[v->j]; InArr_B[v->j] ^= InArr_B[v->i]; InArr_B[v->i] ^= InArr_B[v->j];}
#define swap  swap_a  swap_b

static void N16    (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B);
static void N8     (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B);
static void N4     (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B);
static void N5     (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B);
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
long *InArr_A  = (long *)(*v->In_A);
long *InArr_B  = (long *)(*v->In_B);

v->i = 0;
v->j = 0;

if (*v->R)
{
v->RMS_A= InArr_A[0];
v->RMS_B= InArr_B[0];
return;
}

if (v->Nmax <= 4)                        N4(v, InArr_A, InArr_B);
else if (v->Nmax == 5)                   N5(v, InArr_A, InArr_B);
else if((v->Nmax >= 8) && (v->Nmax < 16))N8(v, InArr_A, InArr_B);
else                                     N16(v, InArr_A, InArr_B);
}


static void N4     (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B)
{
if ((*v->PWM_A)>(v->COMF))
{
/*  ������� 0  */
v->i = 0; v->j = 1;    swap_b
v->i = 2; v->j = 3;    swap_b
/*  ������� 1  */  v->i = 1; v->j = 3;    swap_b
/*  ������� 2  */  v->i = 0; v->j = 2;    swap_b
/*  ������� 3  */  v->i = 1; v->j = 2;    swap_b

v->RMS_A= InArr_A[0];
v->RMS_B=(InArr_B[1]+InArr_B[2])>>1;

return;
}
if ((*v->PWM_B)>(v->COMF))
{
/*  ������� 0  */
v->i = 0; v->j = 1;    swap_a
v->i = 2; v->j = 3;    swap_a
/*  ������� 1  */  v->i = 1; v->j = 3;    swap_a
/*  ������� 2  */  v->i = 0; v->j = 2;    swap_a
/*  ������� 3  */  v->i = 1; v->j = 2;    swap_a

v->RMS_A=(InArr_A[1]+InArr_A[2])>>1;
v->RMS_B= InArr_B[0];
return;
}
/*  ������� 0  */
v->i = 0; v->j = 1;    swap
v->i = 2; v->j = 3;    swap
/*  ������� 1  */  v->i = 1; v->j = 3;    swap
/*  ������� 2  */  v->i = 0; v->j = 2;    swap
/*  ������� 3  */  v->i = 1; v->j = 2;    swap

v->RMS_A=(InArr_A[1]+InArr_A[2])>>1;
v->RMS_B=(InArr_B[1]+InArr_B[2])>>1;

return;
}


static void N5     (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B)
{

/*  ������� 0  */
v->i = 1; v->j = 2;    swap
v->i = 3; v->j = 4;    swap
/*  ������� 1  */  v->i = 1; v->j = 3;    swap
/*  ������� 2  */  v->i = 0; v->j = 2;    swap
/*  ������� 3  */  v->i = 2; v->j = 4;    swap
/*  ������� 4  */  v->i = 0; v->j = 3;    swap
/*  ������� 5  */  v->i = 0; v->j = 1;    swap
/*  ������� 6  */  v->i = 1; v->j = 2;    swap

v->RMS_A=InArr_A[2];
v->RMS_B=InArr_B[2];

return;
}




static void N8     (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B)
{
if ((*v->PWM_A)>(v->COMF))
{

/*  ������� 0  */  v->i = 0; v->j = 7;    swap_b
/*  ������� 1  */  v->i = 1; v->j = 6;    swap_b
/*  ������� 2  */  v->i = 2; v->j = 5;    swap_b
/*  ������� 3  */  v->i = 3; v->j = 4;    swap_b
/*  ������� 4  */
v->i = 0; v->j = 3;    swap_b
v->i = 4; v->j = 7;    swap_b
/*  ������� 5  */
v->i = 1; v->j = 2;    swap_b
v->i = 5; v->j = 6;    swap_b
/*  ������� 6  */
v->i = 0; v->j = 1;     swap_b
v->i = 2; v->j = 3;     swap_b
v->i = 4; v->j = 5;     swap_b
v->i = 6; v->j = 7;     swap_b
/*  ������� 7  */  v->i = 3; v->j = 5;     swap_b
/*  ������� 8  */  v->i = 2; v->j = 4;     swap_b
/*  ������� 9  */
v->i = 1; v->j = 2;     swap_b
v->i = 3; v->j = 4;    swap_b
v->i = 5; v->j = 6;    swap_b
/*  ������� 10  */
v->i = 2; v->j = 3;     swap_b
v->i = 4; v->j = 5;   swap_b

v->RMS_A= InArr_A[0];
v->RMS_B=(InArr_B[2]+InArr_B[3]+InArr_B[4]+InArr_B[5])>>2;
return;
}
if ((*v->PWM_B)>(v->COMF))
{

/*  ������� 0  */  v->i = 0; v->j = 7;    swap_a
/*  ������� 1  */  v->i = 1; v->j = 6;    swap_a
/*  ������� 2  */  v->i = 2; v->j = 5;    swap_a
/*  ������� 3  */  v->i = 3; v->j = 4;    swap_a
/*  ������� 4  */
v->i = 0; v->j = 3;    swap_a
v->i = 4; v->j = 7;    swap_a
/*  ������� 5  */
v->i = 1; v->j = 2;    swap_a
v->i = 5; v->j = 6;    swap_a
/*  ������� 6  */
v->i = 0; v->j = 1;     swap_a
v->i = 2; v->j = 3;     swap_a
v->i = 4; v->j = 5;     swap_a
v->i = 6; v->j = 7;     swap_a
/*  ������� 7  */  v->i = 3; v->j = 5;     swap_a
/*  ������� 8  */  v->i = 2; v->j = 4;     swap_a
/*  ������� 9  */
v->i = 1; v->j = 2;     swap_a
v->i = 3; v->j = 4;    swap_a
v->i = 5; v->j = 6;    swap_a
/*  ������� 10  */
v->i = 2; v->j = 3;     swap_a
v->i = 4; v->j = 5;   swap_a

v->RMS_A=(InArr_A[2]+InArr_A[3]+InArr_A[4]+InArr_A[5])>>2;
v->RMS_B= InArr_B[0];
return;
}

/*  ������� 0  */  v->i = 0; v->j = 7;    swap
/*  ������� 1  */  v->i = 1; v->j = 6;    swap
/*  ������� 2  */  v->i = 2; v->j = 5;    swap
/*  ������� 3  */  v->i = 3; v->j = 4;    swap
/*  ������� 4  */
v->i = 0; v->j = 3;    swap
v->i = 4; v->j = 7;    swap
/*  ������� 5  */
v->i = 1; v->j = 2;    swap
v->i = 5; v->j = 6;    swap
/*  ������� 6  */
v->i = 0; v->j = 1;     swap
v->i = 2; v->j = 3;     swap
v->i = 4; v->j = 5;     swap
v->i = 6; v->j = 7;     swap
/*  ������� 7  */  v->i = 3; v->j = 5;     swap
/*  ������� 8  */  v->i = 2; v->j = 4;     swap
/*  ������� 9  */
v->i = 1; v->j = 2;     swap
v->i = 3; v->j = 4;    swap
v->i = 5; v->j = 6;    swap
/*  ������� 10  */
v->i = 2; v->j = 3;     swap
v->i = 4; v->j = 5;   swap

v->RMS_A=(InArr_A[2]+InArr_A[3]+InArr_A[4]+InArr_A[5])>>2;
v->RMS_B=(InArr_B[2]+InArr_B[3]+InArr_B[4]+InArr_B[5])>>2;

return;
}
static void N16     (BLOCK_STRUCT *v, long *InArr_A, long *InArr_B)
{
if ((*v->PWM_A)>(v->COMF))
{
/*  ������� 0  */  v->i = 0; v->j = 15;    swap_b
/*  ������� 1  */  v->i = 1; v->j = 14;    swap_b
/*  ������� 2  */  v->i = 2; v->j = 13;    swap_b
/*  ������� 3  */  v->i = 3; v->j = 12;    swap_b
/*  ������� 4  */  v->i = 4; v->j = 11;    swap_b
/*  ������� 5  */  v->i = 5; v->j = 10;    swap_b
/*  ������� 6  */  v->i = 6; v->j = 9;     swap_b
/*  ������� 7  */  v->i = 7; v->j = 8;     swap_b
/*  ������� 8  */  v->i = 0; v->j = 7;     swap_b
                   v->i = 8; v->j = 15;    swap_b
/*  ������� 9  */  v->i = 1; v->j = 6;     swap_b
                   v->i = 9; v->j = 14;    swap_b
/*  ������� 10  */ v->i = 2; v->j = 5;     swap_b
                   v->i = 10; v->j = 13;   swap_b
/*  ������� 11  */ v->i = 3; v->j = 4;     swap_b
                   v->i = 11; v->j = 12;   swap_b
/*  ������� 12  */
  v->i = 0; v->j = 3;    swap_b
  v->i = 4; v->j = 7;    swap_b
  v->i = 8; v->j = 11;    swap_b
  v->i = 12; v->j = 15;    swap_b

/*  ������� 13  */
 v->i = 1; v->j = 2;    swap_b
 v->i = 5; v->j = 6;    swap_b
 v->i = 9; v->j = 10;    swap_b
 v->i = 13; v->j = 14;    swap_b

/*  ������� 14  */
 v->i = 0; v->j = 1;    swap_b
 v->i = 2; v->j = 8;    swap_b
 v->i = 10; v->j = 11;    swap_b
 v->i = 14; v->j = 15;    swap_b
/*  ������� 15  */
v->i = 3; v->j = 9;    swap_b
/*  ������� 16  */
v->i = 4; v->j = 5;    swap_b
v->i = 6; v->j = 12;    swap_b

/*  ������� 17  */
v->i = 7; v->j = 13;    swap_b
/*  ������� 18  */
v->i = 1; v->j = 4;    swap_b
v->i = 5; v->j = 10;    swap_b
v->i = 11; v->j = 14;    swap_b
/*  ������� 19  */
v->i = 2; v->j = 3;    swap_b
v->i = 6; v->j = 9;    swap_b
v->i = 12; v->j = 13;    swap_b

/*  ������� 20  */
v->i = 7; v->j = 8;    swap_b
/*  ������� 21  */
v->i = 1; v->j = 2;    swap_b
v->i = 3; v->j = 4;    swap_b
v->i = 5; v->j = 8;    swap_b
v->i = 11; v->j = 12;    swap_b
v->i = 13; v->j = 14;    swap_b


/*  ������� 22  */
v->i = 6; v->j = 10;    swap_b
/*  ������� 23  */
v->i = 7; v->j = 9;    swap_b
/*  ������� 24  */
v->i = 2; v->j = 3;    swap_b
v->i = 4; v->j = 6;    swap_b
v->i = 9; v->j = 11;    swap_b
v->i = 12; v->j = 13;    swap_b
/*  ������� 25  */
v->i = 5; v->j = 7;    swap_b
v->i = 8; v->j = 10;    swap_b
/*  ������� 26  */
v->i = 4; v->j = 5;    swap_b
v->i = 6; v->j = 7;    swap_b
v->i = 8; v->j = 9;    swap_b
v->i = 10; v->j = 11;    swap_b
/*  ������� 27  */
v->i = 3; v->j = 4;    swap_b
v->i = 5; v->j = 6;    swap_b
v->i = 7; v->j = 8;    swap_b
v->i = 9; v->j = 10;    swap_b
v->i = 11; v->j = 12;    swap_b

v->RMS_A= InArr_A[0];
v->RMS_B=(InArr_B[5]>>3)+(InArr_B[6]>>3)+(InArr_B[7]>>3)+(InArr_B[8]>>3)+(InArr_B[9]>>3)+(InArr_B[10]>>3)+(InArr_B[11]>>3)+(InArr_B[12]>>3);
return;
}
if ((*v->PWM_B)>(v->COMF))
{
/*  ������� 0  */  v->i = 0; v->j = 15;    swap_a
/*  ������� 1  */  v->i = 1; v->j = 14;    swap_a
/*  ������� 2  */  v->i = 2; v->j = 13;    swap_a
/*  ������� 3  */  v->i = 3; v->j = 12;    swap_a
/*  ������� 4  */  v->i = 4; v->j = 11;    swap_a
/*  ������� 5  */  v->i = 5; v->j = 10;    swap_a
/*  ������� 6  */  v->i = 6; v->j = 9;     swap_a
/*  ������� 7  */  v->i = 7; v->j = 8;     swap_a
/*  ������� 8  */  v->i = 0; v->j = 7;     swap_a
                   v->i = 8; v->j = 15;    swap_a
/*  ������� 9  */  v->i = 1; v->j = 6;     swap_a
                   v->i = 9; v->j = 14;    swap_a
/*  ������� 10  */ v->i = 2; v->j = 5;     swap_a
                   v->i = 10; v->j = 13;   swap_a
/*  ������� 11  */ v->i = 3; v->j = 4;     swap_a
                   v->i = 11; v->j = 12;   swap_a
/*  ������� 12  */
  v->i = 0; v->j = 3;    swap_a
  v->i = 4; v->j = 7;    swap_a
  v->i = 8; v->j = 11;    swap_a
  v->i = 12; v->j = 15;    swap_a

/*  ������� 13  */
 v->i = 1; v->j = 2;    swap_a
 v->i = 5; v->j = 6;    swap_a
 v->i = 9; v->j = 10;    swap_a
 v->i = 13; v->j = 14;    swap_a

/*  ������� 14  */
 v->i = 0; v->j = 1;    swap_a
 v->i = 2; v->j = 8;    swap_a
 v->i = 10; v->j = 11;    swap_a
 v->i = 14; v->j = 15;    swap_a
/*  ������� 15  */
v->i = 3; v->j = 9;    swap_a
/*  ������� 16  */
v->i = 4; v->j = 5;    swap_a
v->i = 6; v->j = 12;    swap_a

/*  ������� 17  */
v->i = 7; v->j = 13;    swap_a
/*  ������� 18  */
v->i = 1; v->j = 4;    swap_a
v->i = 5; v->j = 10;    swap_a
v->i = 11; v->j = 14;    swap_a
/*  ������� 19  */
v->i = 2; v->j = 3;    swap_a
v->i = 6; v->j = 9;    swap_a
v->i = 12; v->j = 13;    swap_a

/*  ������� 20  */
v->i = 7; v->j = 8;    swap_a
/*  ������� 21  */
v->i = 1; v->j = 2;    swap_a
v->i = 3; v->j = 4;    swap_a
v->i = 5; v->j = 8;    swap_a
v->i = 11; v->j = 12;    swap_a
v->i = 13; v->j = 14;    swap_a


/*  ������� 22  */
v->i = 6; v->j = 10;    swap_a
/*  ������� 23  */
v->i = 7; v->j = 9;    swap_a
/*  ������� 24  */
v->i = 2; v->j = 3;    swap_a
v->i = 4; v->j = 6;    swap_a
v->i = 9; v->j = 11;    swap_a
v->i = 12; v->j = 13;    swap_a
/*  ������� 25  */
v->i = 5; v->j = 7;    swap_a
v->i = 8; v->j = 10;    swap_a
/*  ������� 26  */
v->i = 4; v->j = 5;    swap_a
v->i = 6; v->j = 7;    swap_a
v->i = 8; v->j = 9;    swap_a
v->i = 10; v->j = 11;    swap_a
/*  ������� 27  */
v->i = 3; v->j = 4;    swap_a
v->i = 5; v->j = 6;    swap_a
v->i = 7; v->j = 8;    swap_a
v->i = 9; v->j = 10;    swap_a
v->i = 11; v->j = 12;    swap_a

v->RMS_A=(InArr_A[5]>>3)+(InArr_A[6]>>3)+(InArr_A[7]>>3)+(InArr_A[8]>>3)+(InArr_A[9]>>3)+(InArr_A[10]>>3)+(InArr_A[11]>>3)+(InArr_A[12]>>3);
v->RMS_B= InArr_B[0];

return;
}
/*  ������� 0  */  v->i = 0; v->j = 15;    swap
/*  ������� 1  */  v->i = 1; v->j = 14;    swap
/*  ������� 2  */  v->i = 2; v->j = 13;    swap
/*  ������� 3  */  v->i = 3; v->j = 12;    swap
/*  ������� 4  */  v->i = 4; v->j = 11;    swap
/*  ������� 5  */  v->i = 5; v->j = 10;    swap
/*  ������� 6  */  v->i = 6; v->j = 9;     swap
/*  ������� 7  */  v->i = 7; v->j = 8;     swap
/*  ������� 8  */  v->i = 0; v->j = 7;     swap
                   v->i = 8; v->j = 15;    swap
/*  ������� 9  */  v->i = 1; v->j = 6;     swap
                   v->i = 9; v->j = 14;    swap
/*  ������� 10  */ v->i = 2; v->j = 5;     swap
                   v->i = 10; v->j = 13;   swap
/*  ������� 11  */ v->i = 3; v->j = 4;     swap
                   v->i = 11; v->j = 12;   swap
/*  ������� 12  */
  v->i = 0; v->j = 3;    swap
  v->i = 4; v->j = 7;    swap
  v->i = 8; v->j = 11;    swap
  v->i = 12; v->j = 15;    swap

/*  ������� 13  */
 v->i = 1; v->j = 2;    swap
 v->i = 5; v->j = 6;    swap
 v->i = 9; v->j = 10;    swap
 v->i = 13; v->j = 14;    swap

/*  ������� 14  */
 v->i = 0; v->j = 1;    swap
 v->i = 2; v->j = 8;    swap
 v->i = 10; v->j = 11;    swap
 v->i = 14; v->j = 15;    swap
/*  ������� 15  */
v->i = 3; v->j = 9;    swap
/*  ������� 16  */
v->i = 4; v->j = 5;    swap
v->i = 6; v->j = 12;    swap

/*  ������� 17  */
v->i = 7; v->j = 13;    swap
/*  ������� 18  */
v->i = 1; v->j = 4;    swap
v->i = 5; v->j = 10;    swap
v->i = 11; v->j = 14;    swap
/*  ������� 19  */
v->i = 2; v->j = 3;    swap
v->i = 6; v->j = 9;    swap
v->i = 12; v->j = 13;    swap

/*  ������� 20  */
v->i = 7; v->j = 8;    swap
/*  ������� 21  */
v->i = 1; v->j = 2;    swap
v->i = 3; v->j = 4;    swap
v->i = 5; v->j = 8;    swap
v->i = 11; v->j = 12;    swap
v->i = 13; v->j = 14;    swap


/*  ������� 22  */
v->i = 6; v->j = 10;    swap
/*  ������� 23  */
v->i = 7; v->j = 9;    swap
/*  ������� 24  */
v->i = 2; v->j = 3;    swap
v->i = 4; v->j = 6;    swap
v->i = 9; v->j = 11;    swap
v->i = 12; v->j = 13;    swap
/*  ������� 25  */
v->i = 5; v->j = 7;    swap
v->i = 8; v->j = 10;    swap
/*  ������� 26  */
v->i = 4; v->j = 5;    swap
v->i = 6; v->j = 7;    swap
v->i = 8; v->j = 9;    swap
v->i = 10; v->j = 11;    swap
/*  ������� 27  */
v->i = 3; v->j = 4;    swap
v->i = 5; v->j = 6;    swap
v->i = 7; v->j = 8;    swap
v->i = 9; v->j = 10;    swap
v->i = 11; v->j = 12;    swap

v->RMS_A=(InArr_A[5]>>3)+(InArr_A[6]>>3)+(InArr_A[7]>>3)+(InArr_A[8]>>3)+(InArr_A[9]>>3)+(InArr_A[10]>>3)+(InArr_A[11]>>3)+(InArr_A[12]>>3);
v->RMS_B=(InArr_B[5]>>3)+(InArr_B[6]>>3)+(InArr_B[7]>>3)+(InArr_B[8]>>3)+(InArr_B[9]>>3)+(InArr_B[10]>>3)+(InArr_B[11]>>3)+(InArr_B[12]>>3);
return;
}


