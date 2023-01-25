/**
  ******************************************************************************
  * @file    usb_otg.h
  *
  * @brief   ������������ ���� USB OTG.
  *
  *          ����������: GCC ARM 4.9.3
  *          �����: Qt Creator 3.4.2
  *
  * @author  �����
  *             - ������� �������, lonie@niiet.ru
  *             - ������ ������, kolbov@niiet.ru
  * @date    21.09.2013
  *
  ******************************************************************************
  * @attention
  *
  * ������ ����������� ����������� ��������������� ���� ���ܻ, ��� �����-����
  * ��������, ���� ���������� ��� ���������������, ������� �������� ��������
  * �����������, ������������ �� ��� ����������� ���������� � ����������
  * ���������, �� �� ������������� ���. ������ ����������� �����������
  * ������������� ��� ��������������� ����� � ���������� ������ ��
  * �������������� �������������� ���������� � ��������, � ����� ��������� �����
  * �����������. �� � ����� ������ ������ ��� ��������������� �� �����
  * ��������������� �� �����-���� �����, �� ������ ��� ��������� �����, ���
  * �� ���� �����������, ��������� ��-�� ������������� ������������ �����������
  * ��� ���� �������� � ����������� ������������.
  *
  * <h2><center>&copy; 2016 ��� "�����"</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_OTG_H
#define __USB_OTG_H

/* Includes ------------------------------------------------------------------*/
#include <USBlib/usb_conf.h>
#include <USBlib/usb_dev.h>
#include <USBlib/usb_otg_irq.h>
//#include "usb_host.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    USB_Role_Unknown = 0,
    USB_Role_Device,
    USB_Role_Host
}USB_Role_TypeDef;

/* Exported functions prototypes ---------------------------------------------*/
void USBOTG_Init(USBDev_ClassCB_TypeDef *cb);
void USBOTG_DeInit(void);

bool otg_is_host(void);
bool otg_is_device(void);
void otg_idle(void);
void set_port_change_status (bool status);
void USBOTG_SetRole(USB_Role_TypeDef Role);
USB_Role_TypeDef USBOTG_GetRole(void);

#endif //__USB_OTG_H
