
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
int word;
int MSBPower;
word = *v->In;
MSBPower = 0;
while (word > 0)
{
word >>= 1;
MSBPower++;
}
v->Out = MSBPower;
}

