#include "../inc/main.h"

void main(void)
{
    int i, c, e;
    c = 0; e = 0;
    for (i = 1; i<=100; i++)
    {
        testset1.a = rand();
        testset1.b = rand();
        printf("%d; %d \n", testset1.a, testset1.b);
        test_update(&testset1, &resset1);
        if (resset1.sum == (testset1.a + testset1.b))
        {
            c++;
        } else {
            e++;
        }
        if (resset1.dif == (testset1.a - testset1.b))
        {
            c++;
        } else {
            e++;
        }
    }
    printf("correct: %d/200; error: %d/200 \n", c,e);
}