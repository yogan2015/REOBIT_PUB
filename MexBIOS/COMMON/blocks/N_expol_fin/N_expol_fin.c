
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int delt, deltExt;
  if (!(short)*v->enable)
  {
    v->Out = *v->Pos;
  }
  else
  {
    delt =  *v->Pos - v->pOut;
    // отлов скачков, совпадающих со сменой фазы
    if (delt>= 35000)  delt -=65536;
    if (delt<= -35000) delt +=65536;

    deltExt = abs(delt - *v->Spd);
    if (((deltExt) >= (*v->Spd >> 1)) & !(abs(delt) >= 35000))
    {
      v->Out = v->pOut + *v->Spd;
    } else
    {
      v->Out = *v->Pos;
    }
  }
  if (v->Out >= 65536) v->Out -= 65536;
  if (v->Out < 0 ) v->Out += 65536;
  v->pOut = v->Out;
}
