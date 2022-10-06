
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Cos = sqrt(1-(*v->Sin)*(*v->Sin)) * -*v->d1_sign;
}

