
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->timer =  v->timer + v->Td;
  if (v->timer > 1) v->timer = 1;

  switch (v->st) {
    case 0:           // ���������
      if (*v->vec & (1 << 0)) {                //  ��������� ������ ������� ���������
      v->timer = 0;
      v->st = 1;}
      break;
    case 1:           // ����� HALT��
      if (v->timer > v->timeout_RST) {                  // ������ 5��
      v->timer = 0;
      v->st = 2;}
      break;
    case 2:           // ����� ��������
      if  (*v->vec & (1 << 5))  {    // ��2 ������� � ���� � �������
        if (*v->vec & (1 << 1)) {
        v->timer = 0;
        v->st = 3;}}
      break;
    case 3:           // ���� �����������
      if (*v->vec & (1 << 4)) {                // ������� �������� � �������
      v->timer = 0;
      v->st = 4;}
      if (*v->vec & (1 << 3)) {                // ��������� ������������� ����� 800 �
      v->timer = 0;
      v->st = 4;}
      break;
    case 4:           // ������� �� ������
      if (v->timer > v->timeout_KM) {                  // ������ 10��
      v->timer = 0;
      v->st = 5;}
      break;
    case 5:           // ������
      if (*v->vec & (1 << 6)) {    // ���� � ������� � ���������
        if (*v->vec & (1 << 5)) {
        v->timer = 0;
        v->st = 6;}}
      if (*v->vec & (1 << 2)) {               // ������ ������������� ���� 550 �
      v->timer = 0;
      v->st = 0;}
      break;
    case 6:           // ������� � �����������
      if (v->timer > v->timeout_KM) {                  // ������ 10��
      v->timer = 0;
      v->st = 2;}
      break;
   }

   if (*v->rst) v->st = 0;


   v->STAGE = v->st;
}

