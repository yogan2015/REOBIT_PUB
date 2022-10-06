
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Dif = *v->Ph_A - *v->Ph_B;
  while (v->Dif > 3.1415926535897932384626433832795)
  {
    v->Dif = v->Dif - 6.283185307179586476925286766559;
  }
  while (v->Dif < -3.1415926535897932384626433832795)
  {
    v->Dif = v->Dif + 6.283185307179586476925286766559;
  }
}

