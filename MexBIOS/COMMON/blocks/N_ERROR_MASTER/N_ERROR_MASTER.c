
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
if (*v->CTRL_PSP_OFF)
{*v->ERROR &= -65536;}
if (*v->CTRL_GED_OFF)
{*v->ERROR &= 65535;}
v->ERROR_CODE |= (*v->ERROR &= v-> MASK);
if (*v->RST_PSP)
{v->ERROR_CODE &= -65536;}
if (*v->RST_GED)
{v->ERROR_CODE &= 65535;}
if ((v->ERROR_CODE & 65535) != 0)
{v->ERROR_PSP = 1;}
else
{v->ERROR_PSP = 0;}
if ((v->ERROR_CODE & -65536) != 0)
{v->ERROR_GED = 1;}
else
{v->ERROR_GED = 0;}
}

