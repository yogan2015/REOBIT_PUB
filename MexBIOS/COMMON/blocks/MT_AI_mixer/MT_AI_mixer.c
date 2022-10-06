
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->val0 = MBS_getData(*v->adr0);
  v->val1 = MBS_getData(*v->adr1);
  v->val2 = MBS_getData(*v->adr2);
  v->val3 = MBS_getData(*v->adr3);
  v->val4 = MBS_getData(*v->adr4);
  v->val5 = MBS_getData(*v->adr5);
}

