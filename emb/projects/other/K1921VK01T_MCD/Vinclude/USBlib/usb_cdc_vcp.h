/**
  ******************************************************************************
  * @file    usb_cdc_vcp.h
  *
  * @brief   ������������ ���� ������ CDC USB Device.
  *
  *          Virtual COM-port.
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
#ifndef __USB_CDC_VCP_H
#define __USB_CDC_VCP_H

/* Includes ------------------------------------------------------------------*/
#include <USBlib/usb_dev.h>

/* Exported defines ----------------------------------------------------------*/
#define SEND_ENCAPSULATED_COMMAND               0x00
#define GET_ENCAPSULATED_RESPONSE               0x01
#define SET_COMM_FEATURE                        0x02
#define GET_COMM_FEATURE                        0x03
#define CLEAR_COMM_FEATURE                      0x04
#define SET_LINE_CODING                         0x20
#define GET_LINE_CODING                         0x21
#define SET_CONTROL_LINE_STATE                  0x22
#define SEND_BREAK                              0x23
#define NO_CMD                                  0xFF

/* Exported variables --------------------------------------------------------*/
extern USBDev_ClassCB_TypeDef USBDEV_CDC_VCP_cb;

/* Exported functions prototypes ---------------------------------------------*/
uint32_t VCP_PutChar(uint8_t byte);
uint8_t  VCP_GetChar(void);
uint32_t VCP_IsRxBufEmpty(void);
uint32_t VCP_RxHandlerInit(void (*RxHandler)(void));
uint32_t VCP_TxHandlerInit(void (*TxHandler)(void));

#endif /* __USB_CDC_VCP_H */
