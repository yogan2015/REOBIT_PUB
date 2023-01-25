/**
  ******************************************************************************
  * @file    usb_otg.c
  *
  * @brief   ���� � �������� ����� ��� ������ � USB OTG.
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

/* Includes ------------------------------------------------------------------*/
#include "USBlib/usb_otg.h"

/* Private defines -----------------------------------------------------------*/

/* Private functions prototypes ----------------------------------------------*/
void set_abus_req(void);
void clr_abus_req(void);
void set_bbus_req(void);
void clr_bbus_req(void);

/* Private variables ---------------------------------------------------------*/
volatile USB_Role_TypeDef USB_Role_Now  = USB_Role_Unknown;
volatile uint8_t port_changed = 0;
bool direct_connect_present   = false;

/* Private functions ---------------------------------------------------------*/
/*
 * ������� �������������� ����������� ��������� � ������ ��� ������ usb otg
 *
 */
void USBOTG_Init(USBDev_ClassCB_TypeDef *cb)
{
    //HW INIT
    //init VBUS pin
    NT_GPIOE->ALTFUNCSET |= (1<<7);
    NT_COMMON_REG->GPIODEN2 |= (1<<7);

    NT_USBOTG->OTG_IRQ_EN = 0xfff;

    //SW INIT
    USBDev_ClassCbInit(cb);
}

/*
 * ������� ���������������� ����������� ��������� � ������ usb otg
 *
 */

void USBOTG_DeInit()
{

}

/*
 * ���������� ���� ������ usb otg
 *
 */
extern bool in_enumeration;

void otg_idle(void)
{
    switch(USBOTG_GetRole())
    {
    case USB_Role_Host:
        break;
    case USB_Role_Device:
        break;
    case USB_Role_Unknown:
        break;
    }
}

/*
 * ������� ���������� �������� ��������, ���� �������� � ������ �����
 *
 */

bool otg_is_host(void)
{
    if(NT_USBOTG->OTG_IRQ_STAT & (1<<5))
        return true;
    else
        return false;
}

/*
 * ������� ���������� �������� ��������, ���� �������� � ������ ����������
 *
 */

bool otg_is_device(void)
{
    if(NT_USBOTG->OTG_IRQ_STAT & (1<<4))
        return true;
    else
        return false;
}

/*
 * ������� ���������� �������� ���� ������ ����������
 *
 */

USB_Role_TypeDef USBOTG_GetRole(void)
{    
    return USB_Role_Now;
}

/*
 * ������� ������������� ������ ��������� ����� (� ������ �����)
 *
 */

void set_port_change_status (bool status)
{
    port_changed = status;
}

/*bool is_port_connected(void)
{
  if(USBHost->PORT_STS & 1) return true;
  else                      return false;
}*/

void set_abus_req(void)
{
    NT_USBOTG->OTG_IRQ_STAT |=  (1<<6);  // on  a-bus request
}

void clr_abus_req(void)
{
    NT_USBOTG->OTG_IRQ_STAT &= ~(1<<6); // off a-bus request
}

void set_bbus_req(void)
{
    NT_USBOTG->OTG_IRQ_STAT |= (1<<10); // on  b-bus request
}

void clr_bbus_req(void)
{
    NT_USBOTG->OTG_IRQ_STAT &= ~(1<<10); // off b-bus request
}

/*
 * ������� ������������� ���� ������ ����������
 *
 */

void USBOTG_SetRole(USB_Role_TypeDef Role)
{
    switch(Role)
    {
    case USB_Role_Device:
        clr_abus_req();
        set_bbus_req();
        break;
    case USB_Role_Host:
        clr_bbus_req();
        set_abus_req();
        break;
    case USB_Role_Unknown:
    default:
        clr_abus_req();
        clr_bbus_req();
        break;
    }

    USB_Role_Now = Role;
}
