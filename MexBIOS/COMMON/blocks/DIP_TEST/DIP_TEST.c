
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{

short i;
if (*v->R)
  {
    v->DIP_WORD = 0;
    v->ERROR = 0;
    v->Counter = 0;
  }
else
{
for (i = 0; i < 8; i++)
  {
    if ( *(&v->DIP0)[i] )
    {
      v->Counter++;
      v->j = i;
      v->DIP_WORD |= (1<< i);
      if (v->Counter > 1)
      {
        v->DIP_WORD = ( (v->DIP_WORD^(1<<i))^(1<<v->Prev_j) );
        v->j = 0;
        v->Prev_j = 0;
      }
    }
    v->Prev_j = v->j;

  }


v->Counter = 0;
}
}

