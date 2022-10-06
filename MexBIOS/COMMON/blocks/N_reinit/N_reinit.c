
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->set)
  {
    v->reinited = 1;
    v->val_p = *v->new;
  }
  if (v->reinited)
  {
    v->val = v->val_p;
  } else {
    v->val = v->initial;
  }
}

