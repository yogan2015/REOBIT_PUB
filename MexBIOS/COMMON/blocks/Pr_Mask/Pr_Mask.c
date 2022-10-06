// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
if (*v->State != 0)
{
  if ((*v->State < 1) || (*v->State > v->StateCount)) return;
}
// ��������� �������� ������ � ����������� �� �������� ������ �� ������ ���������� �����
v->Active_Pr = (*v->In_Pr_Word & v->ActivePr_Mask[*v->State]);
v->Active_Pr_Trigg |= (*v->In_Pr_Word & v->ActivePr_Mask[*v->State]);
//������
v->gProtect = v->Active_Pr; //�� ����������� ����� ����� 1 �������
v->gProtect_Trigg = v->Active_Pr_Trigg; //��������������� ����� ����� 1 �������
v->Common_Pr |= (v->Active_Pr & v->Common_Pr_Mask[*v->State]); //������� ����������� ���������������� ����� �������� �������� 2 �������
v->Alarm_Pr |= (v->Active_Pr & v->Alarm_Pr_Mask[*v->State]); //������� ����������� ���������������� ����� ���������� �������� 2 �������

//�������� ����������� ����� ����� �������� �������� �� ��������� �������� ����� �����
//if (v->Active_Pr != v->Curr_Common_Pr)
 if(  !v->Lock )
{
  v->Prev_Common_Pr = v->Curr_Common_Pr;
  v->Curr_Common_Pr |= ( v->Active_Pr_Trigg & v->Common_Pr_Mask[*v->State]);
  v->Curr_Common_Pr &= (~v->gCommonStopOffMask);
}
//�������� ����������� ����� ����� ���������� �������� �� ��������� �������� ����� �����
if (!v->Lock)
{
  v->Prev_Alarm_Pr = v->Curr_Alarm_Pr;
  v->Curr_Alarm_Pr |= ( v->Active_Pr_Trigg & v->Alarm_Pr_Mask[*v->State]);
  v->Curr_Alarm_Pr &= (~v->gAlarmStopOffMask);
}
//���� ���� ������ ���������� ��������
if (v->Curr_Alarm_Pr)
{
  v->Lock = 1;
  v->Curr_Alarm_Pr &= (~v->Alarm_Pr_Off_Mask[*v->State]); //�������� ���� ����������� ����� ����� ���������� ��������
  //� ����������� �� ����� ������ ����� ���������� ��������
  v->Alarm_Stop = (v->Curr_Alarm_Pr & (~v->Alarm_Pr_Off_Mask[*v->State])) ? 1 : 0; //������ ����������� ���������� �������� ��� ��������� ��������� ���� ������,
  //������ ���� ����� ������ ����� ���������� ��������
}

 //���� ���� ������ �������� ��������
  if (v->Curr_Common_Pr)
  {
    v->Lock = 1;
    v->Curr_Common_Pr &= (~v->Common_Pr_Off_Mask[*v->State]); //�������� ���� ����������� ����� ����� �������� ��������
  //� ����������� �� ����� ������ ����� �������� ��������
    v->Common_Stop = (v->Curr_Common_Pr & (~v->Common_Pr_Off_Mask[*v->State])) ? 1 : 0; //������ ����������� �������� �������� ��� ��������� ��������� ���� ������,
  //������ ���� ����� ������ ����� �������� ��������
    v->gCommonStopOffMask |= v->Common_Pr_Off_Mask[*v->State];
  }

//����� ����� ���������� ��������
if (v->Curr_Alarm_Pr == 0)
{
  v->Lock = 0;
  v->Alarm_Stop = 0;
}
//����� ����� �������� ��������
if (v->Curr_Common_Pr == 0)
{
  v->Lock = 0;
  v->Common_Stop = 0;
}
//����������� ������� �������
v->Launch_Ban = ((v->Common_Pr | v->Alarm_Pr) & v->Launch_Ban_Pr_Mask[*v->State]) ? 1 : 0;

if (*v->Reset)
{
  v->Launch_Ban = 0;
  v->Common_Stop = 0;
  v->Alarm_Stop = 0;
  v->gProtect = 0;
  v->gProtect_Trigg = 0;
  v->Prev_Common_Pr = 0;
  v->Prev_Alarm_Pr = 0;
  v->Active_Pr_Trigg = 0;
  v->Common_Pr = 0;
  v->Alarm_Pr = 0;
  v->Active_Pr = 0;
  v->Lock = 0;
  v->gCommonStopOffMask = 0;
  v->gAlarmStopOffMask = 0;
}
}

