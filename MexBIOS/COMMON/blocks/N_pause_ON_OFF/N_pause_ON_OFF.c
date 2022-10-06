
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{


  if(*v->In && !v->mode){    //включаем
    v->cnt_on = v->tick_on;
  }
  if(!*v->In && v->mode){    //вЫключаем
    v->cnt_off = v->tick_off;
  }
  if (v->cnt_on) v->cnt_on--;
  if (v->cnt_off) v->cnt_off--;
  v->mode = *v->In;

  if (v->mode){
    v->Out = *v->In && !v->cnt_on;
  } else {
    v->Out = !(!*v->In && !v->cnt_off);
  }
}
