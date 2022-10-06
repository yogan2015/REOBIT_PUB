
void Init(void)
{
}


void Exec(void)
{


  v->Data= MBS_getData(*v->In);
  if (((short)*v->En == 0) && (v->Prev == 1) )
    MBS_setData(*v->In, v->Data, 1);

  v->Prev = *v->En;
  v->Out = v->Data;

}


