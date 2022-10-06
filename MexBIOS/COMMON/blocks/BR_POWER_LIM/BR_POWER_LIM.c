#define INIT 0
#define BRAKE_ON 1 //��������� Brake.
#define STOP_COUNT 2 //������������� ������� �� ����� ������������ ��������� ����� (������������ �� ���������� �������������� ����������� ��������
//� ������������ �� ����������� ��������. ��������� ������� � �������������� ����������� ���������� ��������� � ���� �� �������� �������������� �
//�� ���� �������������� �������������� ����������� ��������.
#define BRAKE_OFF 3 //���������� Brake. �������������� ��������.
#define SECTOR_SEARCHING_BR_ONOFF 4 //����� ������� �� ������ ��������������, � ������� ��������� ��������, ��������������� � ������ ���������� Brake.
#define VALUE_SEARCHING_BR_ONOFF 5 //����� ������� ������� (�����, t), �������������� ��������, ��������������� � ������ ���������� Brake ��
//������� ����������� ��������. ������ ��������� �� ��������� ������, ��������� ����� ��� �����, ��� ������ ����� ��� ��������� � �������� ��������
//���������� �������.
#define SECTOR_SEARCHING_BR_OFFON 6 //����� ������� �� ������ �����������, � ������� ��������� ��������, ��������������� � ������ ��������� Brake.
#define VALUE_SEARCHING_BR_OFFON 7 //����� ������� ������� (�����, t), �������������� ��������, ��������������� � ������ ��������� Brake ��
//������� �������������� ��������. ������ ��������� �� ��������� ������, ��������� ����� ��� �����, ��� ������ ����� ��� ��������� � �������� ��������
//���������� �������.
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
float *t1_Buffer = (float *)*v->t1_Buff;
float *P1_Buffer = (float *)*v->P1_Buff;
float *t2_Buffer = (float *)*v->t2_Buff;
float *P2_Buffer = (float *)*v->P2_Buff;

if (*v->Reset_Counter)
  {
    v->Counter_Limit = 0;
    v->Pt_Ref_Sat = P1_Buffer[0];
    v->Integral_A = 0;
    v->Integral_B = 0;
    v->Alarm = 0;
    v->State = INIT;
    return;
  }

  switch (v->State)
  {
  case INIT:
    v->Pt_Ref_Sat = P1_Buffer[0];;
    v->Alarm = 0;
    v->Prev_Pt_Restore = 0;
    v->Prev_Pt_Lim = 0;
    if (*v->Brake_On)
    {
      v->State = BRAKE_ON;
    }
    break;

  case BRAKE_ON: //��������� Brake
    v->Prev_Pt_Lim = 0;
    if (*v->Brake_On < v->pBrake_On) //������� ���������� Brake, ��������� �����
    {
      v->State = SECTOR_SEARCHING_BR_ONOFF; //����� ������� �� ������ ��������������
      v->i = 0;
      v->Prev_Pt_Lim = *v->Pt_max_Limit; //���������� ������� �������� ��������
      v->Integral_A = 0;
      v->Integral_B = 0;
    }
    v->Counter_Limit += v->SampleTime;

   //������� ����������� ������
    v->Pt_Ref_Sat = *v->Pt_max_Limit;
    /*if (v->Pt_Ref_Sat >= *v->Pt_max_Limit)
    {
      v->Pt_Ref_Sat =*v->Pt_Ref;
    }
    if (v->Pt_Ref_Sat <= 0)
    {
      v->Pt_Ref_Sat = 0;
    }*/
    //������� ���������� �� �������� �� �������, ������
    if (*v->Pt_Ref > P1_Buffer[v->NumPoints]) //���� �������� �������� ������ �����������, ������ ���������
    {
    v->Integral_A = v->Integral_A + *v->Pt_max_Limit * v->SampleTime;  //������, ������������ �� ��������� ����������� ��������
    v->Integral_B = v->Integral_B + *v->Pt_Ref * v->SampleTime;  //������, ������������ �� ������� ��������
    }

    if (v->Counter_Limit >= t1_Buffer[v->NumPoints])
    {
        v->Counter_Limit = t1_Buffer[v->NumPoints];
    }

    if (*v->Pt_max_Limit <= *v->Pt_Ref) //���������� ����������� �������� �������� � ����������� ����������� ��������
    {
      v->State = STOP_COUNT;
    }

    if (v->Pt_Ref_Sat <= v->Alarm_Level)
    {
      v->Alarm = 1;
    }
    else
    {
      v->Alarm = 0;
    }
    break;

  case STOP_COUNT:
    v->Integral_B = v->Integral_B + v->Pt_Ref_Sat * v->SampleTime; //������, ������������ �� ������� ��������
    if (v->Integral_B >= v->Integral_A) //���� ���� ������, ������������ �� ������� �������� ������ ������ ������, ������������ �� ��������� ����������� ��������
    {
      v->Counter_Limit += v->SampleTime;

      v->Pt_Ref_Sat = *v->Pt_max_Limit; //����������� �������� �� �������� ���������� ����������� ��������
    }
    if (v->Counter_Limit >= t1_Buffer[v->NumPoints])
    {
        v->Counter_Limit = t1_Buffer[v->NumPoints];
    }

    if (*v->Brake_On < v->pBrake_On) //������� ���������� Brake, ��������� �����
    {
      v->State = SECTOR_SEARCHING_BR_ONOFF; //����� ������� �� ������ ��������������
      v->i = 0;
      v->Prev_Pt_Lim = *v->Pt_max_Limit; //���������� ������� �������� ��������
      v->Integral_A = 0;
      v->Integral_B = 0;
    }

    if (v->Pt_Ref_Sat <= v->Alarm_Level)
    {
      v->Alarm = 1;
    }
    else
    {
      v->Alarm = 0;
    }
    break;

  case BRAKE_OFF:
    v->Prev_Pt_Restore = 0;
    v->Counter_Limit -= v->SampleTime;
    //������� ����������� ������
    v->Pt_Ref_Sat = *v->Pt_Restore;
    /*if (v->Pt_Ref_Sat >= *v->Pt_Ref)
    {
      v->Pt_Ref_Sat = *v->Pt_Ref;
    }*/
    if (v->Counter_Limit <= 0)
    {
      v->State = INIT;
      v->Counter_Limit = 0;
    }
    //���� �������� Brake
    if (*v->Brake_On)
    {
      v->State = SECTOR_SEARCHING_BR_OFFON;
      v->i = 0;
      v->Integral_A = 0;
      v->Integral_B = 0;
      v->Prev_Pt_Restore = *v->Pt_Restore;
    }

    if (v->Pt_Ref_Sat <= v->Alarm_Level)
    {
      v->Alarm = 1;
    }
    else
    {
      v->Alarm = 0;
    }
    break;

    case SECTOR_SEARCHING_BR_ONOFF:
      if (v->Prev_Pt_Lim <= P2_Buffer[v->i])
      {
        v->i++;
      }
      else
      {
        v->State = VALUE_SEARCHING_BR_ONOFF;
        v->j = v->i - 1;
      }

     break;

    case VALUE_SEARCHING_BR_ONOFF:
      v->Counter_Limit = (t2_Buffer[v->j] - t2_Buffer[v->i])*(v->Prev_Pt_Lim - P2_Buffer[v->i])/(P2_Buffer[v->j] - P2_Buffer[v->i]) + t2_Buffer[v->i];
      v->State = BRAKE_OFF;
     break;

   case SECTOR_SEARCHING_BR_OFFON:
      if (v->Prev_Pt_Restore <= P1_Buffer[v->i])
      {
        v->i++;
      }
      else
      {
        v->State = VALUE_SEARCHING_BR_OFFON;
        v->j = v->i - 1;
      }
     break;

   case VALUE_SEARCHING_BR_OFFON:
      v->Counter_Limit = (t1_Buffer[v->i] - t1_Buffer[v->j])*(v->Prev_Pt_Restore - P1_Buffer[v->j])/(P1_Buffer[v->i] - P1_Buffer[v->j]) + t1_Buffer[v->j];
      v->State = BRAKE_ON;
   break;

  }
  v->pBrake_On = *v->Brake_On;
  v->A_fixed = v->Integral_A;
  v->A_fdb = v->Integral_B;
}

