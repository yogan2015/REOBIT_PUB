
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->timer =  v->timer + v->Td;
  if (v->timer > 1) v->timer = 1;

  switch (v->st) {
    case 0:           // предзаряд
      if (*v->vec & (1 << 0)) {                //  разрешена работа системы переходов
      v->timer = 0;
      v->st = 1;}
      break;
    case 1:           // сброс HALTов
      if (v->timer > v->timeout_RST) {                  // таймер 5мс
      v->timer = 0;
      v->st = 2;}
      break;
    case 2:           // режим дозаряда
      if  (*v->vec & (1 << 5))  {    // КМ2 замкнут и сеть в порядке
        if (*v->vec & (1 << 1)) {
        v->timer = 0;
        v->st = 3;}}
      break;
    case 3:           // авто компенсация
      if (*v->vec & (1 << 4)) {                // признак перехода к разряду
      v->timer = 0;
      v->st = 4;}
      if (*v->vec & (1 << 3)) {                // перезаряд конденсаторов свыше 800 В
      v->timer = 0;
      v->st = 4;}
      break;
    case 4:           // переход на разряд
      if (v->timer > v->timeout_KM) {                  // таймер 10мс
      v->timer = 0;
      v->st = 5;}
      break;
    case 5:           // разряд
      if (*v->vec & (1 << 6)) {    // сеть в порядке и синхронна
        if (*v->vec & (1 << 5)) {
        v->timer = 0;
        v->st = 6;}}
      if (*v->vec & (1 << 2)) {               // разряд конденсаторов ниже 550 В
      v->timer = 0;
      v->st = 0;}
      break;
    case 6:           // переход к компенсации
      if (v->timer > v->timeout_KM) {                  // таймер 10мс
      v->timer = 0;
      v->st = 2;}
      break;
   }

   if (*v->rst) v->st = 0;


   v->STAGE = v->st;
}

