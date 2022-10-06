
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if ((*v->OFF)||(*v->STAGE != v->Own))  {
    v->OUT = v->Rst;
    v->En = 0;
  } else {
    if (*v->ON) {
      v->OUT = v->Next;
      v->En = 0;
    } else {
      v->OUT = v->Own;
      v->En = 1;
    }
  }
}

