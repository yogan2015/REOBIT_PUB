
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->A = __IQmpy ((-5592405) , ((*v->AB << 1) + *v->BC)  , 24);
  v->B = __IQmpy (5592405  , (*v->AB - *v->BC)       , 24);
  v->C = __IQmpy (5592405  , (*v->AB + *v->BC << 1)  , 24);
}

