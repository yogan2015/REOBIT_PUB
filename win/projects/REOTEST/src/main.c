#include "main.h"

void main(void)
{
    testset1.a = 95;
    testset1.b = 44;

    test_update(&testset1, &resset1);
    printf("sum:%d dif:%d\n", resset1.sum, resset1.dif);
}