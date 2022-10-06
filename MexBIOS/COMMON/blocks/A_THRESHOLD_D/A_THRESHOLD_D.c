
void Init(void)
{
}

void Exec(void)
{
    if ( v->Delta <= 0 )
      {
      if ( *v->In >= v->Level_ON ) v->Out = 1;
      if ( *v->In <= ( v->Level_ON+v->Delta )) v->Out = 0;
      }

    if ( v->Delta > 0 )
      {
      if ( ( *v->In >= v->Level_ON ) && ( *v->In <= ( v->Level_ON+v->Delta )) )
           v->Out = 1;
      else v->Out = 0;
      }
}

