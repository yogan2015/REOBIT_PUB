
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if(*v->In){
    if (v->cnt){
      v->cnt--;
      v->Out = 0;
    } else {
      v->Out = 1;
    }
  } else {
    v->Out = 0;
    v->cnt = v->tick;
  }
}

