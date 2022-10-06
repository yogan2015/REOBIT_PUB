
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->RST)
  {
    v->val = v->val_rst;
  } else {
    v->val = v->val + (*v->fb * v->Td);
    if (v->val > v->Max) v->val = v->val - (v->Max - v->Min);
    if (v->val < v->Min) v->val = v->val + (v->Max + v->Min);
  }
   v->Cos = _IQ24cos(__IQ(v->val,24));
   v->Sin = _IQ24sin(__IQ(v->val,24));
}

