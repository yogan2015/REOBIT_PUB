
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  switch (*v->STAGE) {
  case 0 :
    v->vec = v->vec0;
    break;
  case 1 :
    v->vec = v->vec1;
    break;
  case 2 :
    v->vec = v->vec2;
    break;
  case 3 :
    v->vec = v->vec3;
    break;
  case 4 :
    v->vec = v->vec4;
    break;
  case 5 :
    v->vec = v->vec5;
    break;
  case 6 :
    v->vec = v->vec6;
    break;}
}

