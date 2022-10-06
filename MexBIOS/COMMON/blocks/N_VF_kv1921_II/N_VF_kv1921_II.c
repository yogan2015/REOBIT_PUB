
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  float dpi=6.28318;
  float g, gc, e;
  int Cos_IN, Sin_IN, Cos_OUT, Sin_OUT, delt;

//  выходные значения по двухфазной системе расчитываются исходя из текущего значения циклического счетчика
Cos_OUT = _IQ24cos(__IQ(v->ccnt,24));
Sin_OUT = _IQ24sin(__IQ(v->ccnt,24));

Cos_IN = __IQ((*v->Cos_1/ *v->Magn),24);
Sin_IN = __IQ((*v->Sin_1/ *v->Magn),24);
delt = _IQ24mpy(Cos_OUT, Sin_IN) - _IQ24mpy(Sin_OUT, Cos_IN);

//  Разность фаз подается на вход ПИ-регулятора
e = _IQ24toF(delt);


gc = v->g1 + v->K_p * (e - v->e1) + v->K_i * v->Td * e;
if (gc>=v->UI_Max) gc = v->UI_Max;
if (gc<=v->UI_Min) gc = v->UI_Min;

g = gc;
if (*v->RST)  g = 0;


//  циклический счетчик приращается пропорционально f_basic (+ g), где g - выход ПИ-регулятора, поправка опорной частоты
if (*v->RST){
  v->ccnt += ((*v->f_basic * dpi) * v->Td);
} else {
  v->ccnt += ((*v->f_basic * dpi + g) * v->Td);
}
if (v->ccnt > dpi) v->ccnt -= (dpi);
if (v->ccnt < 0) v->ccnt += (dpi);

v->g1 = g;
v->e1 = e;
v->freq = g / dpi + *v->f_basic;

//  выходы
v->Cos = Cos_OUT;
v->Sin = Sin_OUT;
v->Alpha = _IQ24toF(Cos_OUT) * *v->Magn;
v->Beta = _IQ24toF(Sin_OUT) * *v->Magn;
}

