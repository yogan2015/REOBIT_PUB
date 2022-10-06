

void Init(void)
{

}

void Exec(void)
{
  if (*v->En)
  {
    switch(*v->In)
      {
      //Reset Mask
      case 0:
        MBS_setData(v->Global_variable, (MBS_getData(v->Global_variable) & ~(v->Mask)), 0);
        break;
      //Set Mask
      case 1:
        MBS_setData(v->Global_variable, (MBS_getData(v->Global_variable) | v->Mask), 0);
        break;
      }
  }

}

