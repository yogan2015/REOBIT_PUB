
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->RST)
  {
    v->h_0 = v->i_0;
    v->h_1 = v->i_1;
    v->h_2 = v->i_2;
    v->h_3 = v->i_3;
    v->h_4 = v->i_4;
    v->h_5 = v->i_5;
    v->h_6 = v->i_6;
    v->h_7 = v->i_7;
    v->h_8 = v->i_8;
    v->h_9 = v->i_9;
    v->h_10= v->i_10;
    v->h_11= v->i_11;
    v->h_12= v->i_12;
    v->h_13= v->i_13;
    v->h_14= v->i_14;
    v->h_15= v->i_15;
  } else
  {
    switch (*v->N){
    case 0:  v->h_0   = *v->val; break;
    case 1:  v->h_1   = *v->val; break;
    case 2:  v->h_2   = *v->val; break;
    case 3:  v->h_3   = *v->val; break;
    case 4:  v->h_4   = *v->val; break;
    case 5:  v->h_5   = *v->val; break;
    case 6:  v->h_6   = *v->val; break;
    case 7:  v->h_7   = *v->val; break;
    case 8:  v->h_8   = *v->val; break;
    case 9:  v->h_9   = *v->val; break;
    case 10: v->h_10  = *v->val; break;
    case 11: v->h_11  = *v->val; break;
    case 12: v->h_12  = *v->val; break;
    case 13: v->h_13  = *v->val; break;
    case 14: v->h_14  = *v->val; break;
    case 15: v->h_15  = *v->val; break;}
  }
  v->reg_0  = v->h_0;
  v->reg_1  = v->h_1;
  v->reg_2  = v->h_2;
  v->reg_3  = v->h_3;
  v->reg_4  = v->h_4;
  v->reg_5  = v->h_5;
  v->reg_6  = v->h_6;
  v->reg_7  = v->h_7;
  v->reg_8  = v->h_8;
  v->reg_9  = v->h_9;
  v->reg_10 = v->h_10;
  v->reg_11 = v->h_11;
  v->reg_12 = v->h_12;
  v->reg_13 = v->h_13;
  v->reg_14 = v->h_14;
  v->reg_15 = v->h_15;
}

