/**
  ******************************************************************************
  * @file    usb_otg_irq.c
  *
  * @brief   ���� � �������� ����� ��� ������ � ����������� USB OTG.
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

/* Private functions prototypes ----------------------------------------------*/
void USBDev_IntHandler(void);
void USBHost_IntHandler(void);

/* Private functions ---------------------------------------------------------*/
unsigned char devStatePrev = 0;
void USBOTG_IntHandler(void)
{
#ifdef USE_DEVICE_MODE

    USBDev_IntHandler();
//    if((NT_USBOTG->OTG_IRQ_STAT == 1)) //OTG SESS_FAIL int detected
//    {
//            USBDev_Disconnected();
//    }
//    devStatePrev = NT_USBOTG->OTG_IRQ_STAT_bit.B_DEVICE;
#elif defined USE_HOST_MODE
    USBHost_IntHandler();
#elif defined USE_OTG_MODE

    //������������� ���������� �� usb device
    if(USBOTG_GetRole() == USB_Role_Device)
    {
        USBDev_IntHandler();
    }
    //������������� ���������� �� usb host
    else if (USBOTG_GetRole() == USB_Role_Host)
    {
        USBHost_IntHandler();
    }

    //������������� ���������� �� usb otg
    if(NT_USBOTG->OTG_IRQ_EN)
    {
        if((NT_USBOTG->OTG_IRQ_EN & (1<<0)) && (NT_USBOTG->OTG_IRQ_STS & (1<<0))) //OTG VBUS_err int detected
        {
            NT_USBOTG->OTG_IRQ_STS |= (1<<0);
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<1)) && (NT_USBOTG->OTG_IRQ_STS & (1<<1))) //OTG SRP_OK int detected
        {
            //����� ����� ����������
            NT_USBOTG->OTG_IRQ_STS |= (1<<1);
            //������ ������ a-bus request
            NT_USBOTG->OTG_IRQ_STS |= (1<<6); //a-bus request
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<2)) && (NT_USBOTG->OTG_IRQ_STS & (1<<2))) //OTG HANDOFF int detected
        {
            //����� ����� ����������
            NT_USBOTG->OTG_IRQ_STS |= (1<<2);

            if(NT_USBOTG->OTG_IRQ_STS & (1<<13))
            {
                //������ ���� ������ usb
                USBOTG_SetRole(USB_Role_Device);

                USBDev_Init();

                //NT_USBDevice->USB_OPER &= ~(1<<1); //full speed
            }
            else
            {
                USBOTG_SetRole(USB_Role_Host);
            }
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<3)) && (NT_USBOTG->OTG_IRQ_STS & (1<<3))) //OTG SRP_FAIL int detected
        {
            NT_USBOTG->OTG_IRQ_STS |= (1<<3);
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<4)) && (NT_USBOTG->OTG_IRQ_STS & (1<<14))) //OTG SESS_FAIL int detected
        {
            NT_USBOTG->OTG_IRQ_STS |= (1<<14);
            //���������� device disconnected
            if(USBOTG_GetRole() == USB_Role_Device)
                USBDev_Disconnected();
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<5)) && (NT_USBOTG->OTG_IRQ_STS & (1<<16))) //OTG A_DEV_CHNG int detected
        {
            NT_USBOTG->OTG_IRQ_STS |= (1<<16);

            USBOTG_SetRole(USB_Role_Host);

            NT_USBHost->USBCMD_STS_INTR =  (NT_USBHost->USBCMD_STS_INTR & (0x0007807E)) |
                    (1<<1)| //out space available int
                    (1<<2)| //in dataready int
                    //(1<<3)| //frame SOF int
                    //(1<<4)| //uframe SOF int
                    (1<<6); //PORT change int

        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<6)) && (NT_USBOTG->OTG_IRQ_STS & (1<<17))) //OTG B_DEV_CHNG int detected
        {
            NT_USBOTG->OTG_IRQ_STS |= (1<<17);
            //������ ���� ������ usb
            USBOTG_SetRole(USB_Role_Device);
            USBDev_Init();
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<7)) && (NT_USBOTG->OTG_IRQ_STS & (1<<18))) //OTG DEV_SYNC_CHNG int detected
        {
            //���������� ����������
            NT_USBOTG->OTG_IRQ_STS |= (1<<18);
            //������ ���� ������ usb
            USBOTG_SetRole(USB_Role_Device);
            USBDev_Init();
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<8)) && (NT_USBOTG->OTG_IRQ_STS & (1<<19))) //OTG HOST_SYNC_CHNG int detected
        {
            //���������� ����������
            NT_USBOTG->OTG_IRQ_STS |= (1<<19);
            //������ ���� ������ usb
            USBOTG_SetRole(USB_Role_Host);
            //��������� usb host � ��������� IDLE
            //  >>  >      usb_change_host_state(USBHOST_STATE_IDLE);
            //����������� ���������� ��� usb host
            NT_USBHost->USBCMD_STS_INTR =  (NT_USBHost->USBCMD_STS_INTR & (0x0007807E)) |
                    (1<<1)| //out space available int
                    (1<<2)| //in dataready int
                    //(1<<3)| //frame SOF int
                    //(1<<4)| //uframe SOF int
                    (1<<6); //PORT change int
        }
        if((NT_USBOTG->OTG_IRQ_EN & (1<<9)) && (NT_USBOTG->OTG_IRQ_STS & (1<<20))) //OTG DISCONNECT int detected
        {
            NT_USBOTG->OTG_IRQ_STS |= (1<<20);
        }
    }
#endif /* USE_OTG_MODE */
}

void USBDev_IntHandler(void)
{
    //���������� �� �������� �����
    uint32_t ep_irqs = ((uint32_t)(NT_USBDevice->IRQ_STAT_L & NT_USBDevice->IRQ_ENB_L & 0x3e)) >> 1;
    uint32_t ep_idx  = 0;
    //���� ���� ����������
    while(ep_irqs)
    {
        if(ep_irqs & (1<<ep_idx))
        {
            //���������� ��� ���������� � ��������
            NT_USBDevice->IRQ_STAT_L |= (1<<(ep_idx+1));
            //���������� ��� ���������� � ����������
            ep_irqs                  &= ~(1<<ep_idx);
            //������ �� ���������� ���������� �� �������� �����
            USBDev_Ep_Handler(ep_idx);
        }
        //������������� ���������� ���-���������
        ep_idx++;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //���� ���� ���������� �� usb device (���� �� ������� ������������ ������
    //����������� ����� ���������� ����� ������������ ��� ��������� ����������
    if((NT_USBDevice->IRQ_STAT_L & 0x1) && (NT_USBDevice->IRQ_ENB_L & 0x1))
    {
        if(NT_USBDevice->USB_IRQ_STAT & NT_USBDevice->USB_IRQ_ENB & (1<<0)) //USB SOF int detected
        {
            NT_USBDevice->USB_IRQ_STAT |= (1<<0);
            USBDev_SOF_Handler();
        }
        if(NT_USBDevice->USB_IRQ_STAT & NT_USBDevice->USB_IRQ_ENB & (1<<1)) //USB RESET END int detected
        {
            NT_USBDevice->USB_IRQ_STAT |= (1<<1);
            //�������� ���������� �� ��������� ������ �����
            USBDev_ResetDone();
        }
        if(NT_USBDevice->USB_IRQ_STAT & NT_USBDevice->USB_IRQ_ENB & (1<<2)) //USB RESUME int detected
        {
            NT_USBDevice->USB_IRQ_STAT |= (1<<2);
            USBDev_Resume();
        }
        if(NT_USBDevice->USB_IRQ_STAT & NT_USBDevice->USB_IRQ_ENB & (1<<3)) //USB SUSPEND int detected
        {
            NT_USBDevice->USB_IRQ_STAT |= (1<<3);
            USBDev_Suspend();
        }
        if(NT_USBDevice->USB_IRQ_STAT & NT_USBDevice->USB_IRQ_ENB & (1<<4)) //USB HS_settle int detected
        {
            NT_USBDevice->USB_IRQ_STAT |= (1<<4);
        }
        if(NT_USBDevice->USB_IRQ_STAT & NT_USBDevice->USB_IRQ_ENB & (1<<5)) //USB DMA complete int detected
        {
            NT_USBDevice->USB_IRQ_STAT |= (1<<5);
        }
        if(NT_USBDevice->USB_IRQ_STAT & NT_USBDevice->USB_IRQ_ENB & (1<<6)) //USB CLOCK usable int detected
        {
            NT_USBDevice->USB_IRQ_STAT |= (1<<6);
        }
    }
}

void USBHost_IntHandler()
{

}
