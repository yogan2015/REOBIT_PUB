void Init(void)
{
}

void Exec(void)
{
#ifndef __BORLANDC__
v->sin_out=SinCorr(*v->sin);
#endif
}



