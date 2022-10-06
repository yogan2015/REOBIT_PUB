#include "menu2x.h"
#include "strutils.h"
#include "rtc.h"

#define READ_CMD 0x03
#define WRITE_CMD 0x10
#define REQUEST 0x23
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{


if (v->CAN_Enable)
{
  if (*v->GroupPos != v->BrdData_Group_Num) //������ �� ������������ CAN ������� ��� ������ � BrdData ConsoleBoard
  {
    if ( (*v->GroupPos < v->Ind_Group_Num) || (*v->MenuState == 0))
    {
      v->State = 0; //Read only for indicate group
    }
    else
    {
      v->State = 1; //Read or write
    }
  }
  else
  {
    return;
  }
}
else
{
  return;
}

switch (v->State)
{
  case 0: //������������ ������� �� ������ SDO
    v->Time += v->SampleTime;

    //��������� ����������� �������� ��� ������� � ��������� ����������� �����
    v->MBS_CAN_PDO_TX_LOW = (((*v->Modbus_Par_Adr & 0xFF00)>>8) << 16) | ((*v->Modbus_Par_Adr & 0xFF) << 24) | ((REQUEST & 0xFF) << 8) | (READ_CMD & 0xFF);
    v->MBS_CAN_PDO_TX_HIGH = 0;

    //������������� �������� ��������� ���������� � ���������� ���������� Mexbios, ������������ � SDO-List.
    //CAN_SDO_TX_LOW set
    MBS_setData(v->MBS_CAN_PDO_TX_LOW_Adrr, v->MBS_CAN_PDO_TX_LOW, 0);
    //CAN_SDO_TX_HIGH set
    MBS_setData(v->MBS_CAN_PDO_TX_HIGH_Adrr, v->MBS_CAN_PDO_TX_HIGH, 0);

    //�������� Enable �� SDO
    if (v->Time >= v->SDO_Tx_En_Time)
    {
      MBS_setData(v->CAN_SDO_Tx_En, 1, 0);
      v->Time = 0;
    }

    //������ ����� �� Slave-����������
    if (MBS_getData(v->CAN_SDO_Rx_En))
    {
      //�������� ��������. ������������� �������� ���������� ���������� Mexbios, ������������ � SDO-List � ��������� ���������� �����
      v->MBS_CAN_PDO_RX_LOW = MBS_getData(v->MBS_CAN_PDO_RX_LOW_Adrr);
      v->MBS_CAN_PDO_RX_HIGH = MBS_getData(v->MBS_CAN_PDO_RX_HIGH_Adrr);

      //����������� ��������� �����
      v->MBS_CAN_PDO_RX_Value = ( ((((v->MBS_CAN_PDO_RX_HIGH & 0xFF) << 8) | ((v->MBS_CAN_PDO_RX_HIGH & 0xFF00) >> 8)) << 16) |
                        ((((v->MBS_CAN_PDO_RX_HIGH & 0xFF0000) << 8) | ((v->MBS_CAN_PDO_RX_HIGH & 0xFF000000) >> 8)) >> 16) );

     //������������� ���������� �� CAN �������� ���������� � ���������� ���������� Mexbios, ������������ � MENU.
       MBS_setData(*v->Mexbios_Par_Adr, v->MBS_CAN_PDO_RX_Value, 0);
       MBS_setData(v->CAN_SDO_Rx_En, 0, 0);
    }
    v->PrevAdr = 0;
  break;

  case 1: //��������� ������� �� ������ ��� ������ SDO, � ����������� �� ��������� ������ ��������� � ����� � ���, ��� ��� ���������� ���� ���������
    v->Time = 0;

    //���� �� ���� ����� ���������� � ����� ��������� ���� �� ����� ����������� ������ ��������� ����, ��������� ������ �� ������
    if (!*v->EnterParam)
    {
      if (*v->Par_Adr != v->PrevAdr)
      {
        //��������� ����������� �������� ��� ������� � ��������� ����������� �����
        v->MBS_CAN_PDO_TX_LOW = (((*v->Modbus_Par_Adr & 0xFF00)>>8) << 16) | ((*v->Modbus_Par_Adr & 0xFF) << 24) | ((REQUEST & 0xFF) << 8) | (READ_CMD & 0xFF);
        v->MBS_CAN_PDO_TX_HIGH = 0;

        //������������� �������� ��������� ���������� � ���������� ���������� Mexbios, ������������ � SDO-List.
        //CAN_SDO_TX_LOW set
        MBS_setData(v->MBS_CAN_PDO_TX_LOW_Adrr, v->MBS_CAN_PDO_TX_LOW, 0);
        //CAN_SDO_TX_HIGH set
        MBS_setData(v->MBS_CAN_PDO_TX_HIGH_Adrr, v->MBS_CAN_PDO_TX_HIGH, 0);

        //�������� Enable �� SDO
        MBS_setData(v->CAN_SDO_Tx_En, 1, 0);
        v->PrevAdr = *v->Par_Adr;
      }

      //������ ����� �� Slave-����������
      if (MBS_getData(v->CAN_SDO_Rx_En))
      {
      //�������� ��������. ������������� �������� ���������� ���������� Mexbios, ������������ � SDO-List � ��������� ���������� �����
      v->MBS_CAN_PDO_RX_LOW = MBS_getData(v->MBS_CAN_PDO_RX_LOW_Adrr);
      v->MBS_CAN_PDO_RX_HIGH = MBS_getData(v->MBS_CAN_PDO_RX_HIGH_Adrr);

      //����������� ��������� �����
      v->MBS_CAN_PDO_RX_Value = ( ((((v->MBS_CAN_PDO_RX_HIGH & 0xFF) << 8) | ((v->MBS_CAN_PDO_RX_HIGH & 0xFF00) >> 8)) << 16) |
                        ((((v->MBS_CAN_PDO_RX_HIGH & 0xFF0000) << 8) | ((v->MBS_CAN_PDO_RX_HIGH & 0xFF000000) >> 8)) >> 16) );

      //������������� ���������� �� CAN �������� ���������� � ���������� ���������� Mexbios, ������������ � MENU.
      MBS_setData(*v->Mexbios_Par_Adr, v->MBS_CAN_PDO_RX_Value, 0);
      MBS_setData(v->CAN_SDO_Rx_En, 0, 0);

      }
    }
    //���� ��� ����� ���������
    else
    {
      //������ � ���������� �����, �������� ��������� Mexbios, ������� ���� �������� ����� MENU.
      v->MBS_CAN_PDO_TX_Value = MBS_getData(*v->Mexbios_Par_Adr);

      //����� - ������������ ���������� �������.
      v->MBS_CAN_PDO_TX_LOW = (((*v->Modbus_Par_Adr & 0xFF00)>>8) << 16) | ((*v->Modbus_Par_Adr & 0xFF) << 24) | ((REQUEST & 0xFF) << 8) | (WRITE_CMD & 0xFF);
      v->MBS_CAN_PDO_TX_HIGH =  ( ((((v->MBS_CAN_PDO_TX_Value & 0xFF) << 8) | ((v->MBS_CAN_PDO_TX_Value & 0xFF00) >> 8)) << 16) |
                                ((((v->MBS_CAN_PDO_TX_Value & 0xFF0000) << 8) | ((v->MBS_CAN_PDO_TX_Value & 0xFF000000) >> 8)) >> 16) );

      //������������� �������� ��������� ���������� � ���������� ���������� Mexbios, ������������ � SDO-List.
      //CAN_SDO_TX_LOW set
      MBS_setData(v->MBS_CAN_PDO_TX_LOW_Adrr, v->MBS_CAN_PDO_TX_LOW, 0);
      //CAN_SDO_TX_HIGH set
      MBS_setData(v->MBS_CAN_PDO_TX_HIGH_Adrr, v->MBS_CAN_PDO_TX_HIGH, 0);

      //�������� Enable �� SDO
      MBS_setData(v->CAN_SDO_Tx_En, 1, 0);
    }
  break;
}

}



