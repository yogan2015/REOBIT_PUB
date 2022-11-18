#ifndef rb_general_include

#ifdef RELPATH
    #include "rbutil.h"
#else
    #include "../../../common/qol/inc/rbutil.h"
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <math.h>

void foo1();
void foo2();
void foo3();

#define rb_general_include
#endif