/*!
    Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_usblib.c
 \brief     ����� ������� ��� ������������� �������� USB. ������� �� �������
 			USB VCP" �� �����:
 			https://bitbucket.org/niietcm4/
 			---> / chip / K1921VK01T / GCC / USB / CDC_VCP /

 \author    ��� "��� ������" http://motorcontrol.ru, ����� http://niiet.ru
 \version   v 1.0 08/08/2017

 \addtogroup usb_cdc_vcp
@{
*/

/* Includes ------------------------------------------------------------------*/
#include"DSP.h"
#include "USBlib/usb_cdc_vcp.h"
#include "V_fifo.h"
#include "V_usblib.h"
Uint8 usbActiveFlag = 0;
/* Private defines -----------------------------------------------------------*/
#define EP_DATA_IN      (EP_IN | 0x1)
#define EP_DATA_OUT     (EP_OUT| 0x2)
#define EP_STATUS_IN    (EP_IN | 0x3)

// buffer settings for VCP
#define BUF_SIZE 128
#define BUF_MASK (BUF_SIZE - 1)

/* Private functions prototypes ----------------------------------------------*/
uint32_t USBDev_CDC_Init(uint8_t config_num);
uint32_t USBDev_CDC_DeInit(uint8_t config_num);
uint32_t USBDev_CDC_DataOut(USBDev_EP_TypeDef *ep);
uint32_t USBDev_CDC_DataIn(USBDev_EP_TypeDef *ep);
uint32_t USBDev_CDC_Setup(USBDev_Setup_TypeDef *pUSB_SETUP_PACKET);
uint32_t USBDev_CDC_SOF(void);
uint32_t USBDev_CDC_EP0_RxReady(void);
uint32_t USBDev_CDC_EP0_TxSent(void);
uint8_t *USBDev_CDC_GetConfigDscr(USBDev_Speed_TypeDef dev_speed, uint32_t *len);

uint32_t Handle_TX(uint8_t epnum);
uint32_t Handle_RX(uint8_t epnum);

Tfifo usbRxBuf = FIFO_DEFAULTS;
Tfifo usbTxBuf = FIFO_DEFAULTS;
uint8_t tempUsbRxData[64];
uint8_t tempUsbTxData[64];
/* Private variables ---------------------------------------------------------*/
__ALIGN_BEGIN static uint8_t cfg_dscr [0x43] __ALIGN_END =
{
    sizeof(CONFIGURATION_DSCR_TYPE),
    USB_DESC_TYPE_CONFIGURATION,
    LOBYTE(sizeof(cfg_dscr)),
    HIBYTE(sizeof(cfg_dscr)),
    0x02, //bNumInterfaces
    0x01, //bConfigurationValue,
    0x00, //iConfiguration
    0xc0, // ???
    0x32, //max 100 mA

    sizeof(INTERFACE_DSCR_TYPE),
    USB_DESC_TYPE_INTERFACE,
    0x00, //bInterfaceNumber
    0x00, //bAlternateSetting
    0x01, //bNumEndpoints
    0x02, //bInterfaceClass
    0x02, //bInterfaceSubClass
    0x01, //bInterfaceProtocol
    0x00, //iInterface
    //header func descr
    0x05, // bLength (EP Descr size)
    0x24, // bDescriptorType (CS_INTERFACE)
    0x00, // bDescriptorSubType (Header func Descr)
    0x10, 0x01, //bcd CDC
    // Call Management Function
    0x05, // bFunctionLength
    0x24, // bDescrType
    0x01, // bDescrSubType
    0x00, // bmCapabilities
    0x01, // bDataInterface
    // ACM functional Descr
    0x04, // bFunctionLength
    0x24, // bDescrType (CS_INTERFACE)
    0x02, // bDescrSubType (ACM)
    0x00,//0x06, // bmCapabilities
    // Union Func Descr
    0x05, // bFunctionLength
    0x24, // bDescriptorType (CS_INTERFACE)
    0x06, // bDescriptorSubtype (Union func desc)
    0x00, // bMasterInterface (Communication class interface)
    0x01, // bSlaveInterface0 (Data Class Interface)
    // EP 3 Descr
    0x07, // bLength (Endpoint Descriptor size)
    0x05, // bDescriptorType (Endpoint)
    EP_STATUS_IN, // bEndpointAddress (IN | 3)
    EP_INTERRUPT, // bmAttributes (Interrupt)
    64,
    0x00, //  wMaxPacketSize
    0x02, // bInterval
    // Data class interface Descriptor
    0x09, // bLength
    0x04, // bDescriptorType (Interface)
    0x01, // bInterfaceNumber
    0x00, // bAlternateSetting
    0x02, // bNumEndpoints (Two endpoints used)
    0x0a, // bInterfaceClass (CDC)
    0x00, // bInterfaceSubClass
    0x00, // bInterfaceProtocol
    0x00, // iInterface
    // EP 1 Descr
    0x07, // bLength (Endpoint Descriptor size)
    0x05, // bDescriptorType (Endpoint)
    EP_DATA_IN, // bEndpointAddress (IN | 1)
    EP_BULK, // bmAttributes (Bulk)
    64,
    0x00, //  wMaxPacketSize
    0, // bInterval
    // EP 2 Descr
    0x07, // bLength (Endpoint Descriptor size)
    0x05, // bDescriptorType (Endpoint)
    EP_DATA_OUT, // bEndpointAddress (OUT | 2)
    EP_BULK, // bmAttributes (Bulk)
    64,
    0x00, //  wMaxPacketSize
    0 // bInterval
};

USBDev_ClassCB_TypeDef USBDEV_CDC_VCP_cb =
{
    USBDev_CDC_Init,
    USBDev_CDC_DeInit,
    USBDev_CDC_DataOut,
    USBDev_CDC_DataIn,
    USBDev_CDC_Setup,
    USBDev_CDC_SOF,
    USBDev_CDC_EP0_RxReady,
    USBDev_CDC_EP0_TxSent,
    USBDev_CDC_GetConfigDscr
};

uint8_t buf_rx[BUF_SIZE];
uint8_t buf_tx[BUF_SIZE];

uint32_t wrptr_rxbuf = 0;
uint32_t rdptr_rxbuf = 0;
uint32_t fill_rxbuf = 0;

uint32_t wrptr_txbuf = 0;
uint32_t rdptr_txbuf = 0;
uint32_t fill_txbuf = 0;

uint8_t cdc_tx_now = 0;
uint8_t line_coding_struct[7]; //��������

void (*VCP_CDC_DataTransmitted)(void) = NULL;
void (*VCP_CDC_DataReceived)(void) = NULL;

/* Private functions ---------------------------------------------------------*/
uint32_t USBDev_CDC_Init(uint8_t config_num)
{
    if (config_num == 1)
    {
        //in DATA EP1
        USBDev_EP_Open(EP_DATA_IN, 64, 2); //IN,maxpack=64,Bulk
        //out DATA EP2
        USBDev_EP_Open(EP_DATA_OUT, 64, 2); //OUT,maxpack=64,Bulk
        //command IN EP
        USBDev_EP_Open(EP_STATUS_IN, 64, 3); //IN,maxpack=64,Int

        //enable receiving data
        USBDev_EPSetResponse(EP_CLRNAK, EP_DATA_OUT);

    }
    usbTxBuf.clear(&usbTxBuf);
    usbRxBuf.clear(&usbRxBuf);
    usbActiveFlag ^= 1;
    return 0;
}

uint32_t USBDev_CDC_DeInit(uint8_t config_num)
{
    if (config_num == 1)
    {
        //in DATA EP1
        USBDev_EP_Close(EP_DATA_IN);
        //out DATA EP2
        USBDev_EP_Close(EP_DATA_OUT);
        //command IN EP
        USBDev_EP_Close(EP_STATUS_IN);
    }
    usbActiveFlag = 0;
    return 0;
}

uint32_t USBDev_CDC_DataOut(USBDev_EP_TypeDef *ep)
{
    if(ep->epnum & EP_DATA_OUT & 0x7F)
        return Handle_RX(EP_DATA_OUT & 0x7F);

    return 0;
}

uint32_t USBDev_CDC_DataIn(USBDev_EP_TypeDef *ep)
{
    if(ep->epnum & EP_DATA_IN & 0x7F)
        Handle_TX(EP_DATA_IN & 0x7F);

    return 0;
}

uint32_t USBDev_CDC_Setup(USBDev_Setup_TypeDef *pUSB_SETUP_PACKET)
{
    switch(pUSB_SETUP_PACKET->bmRequestType & 0x60)
    {
    //��������� ������������� ��� ����� ��������
    case 0x20: //CLASS_SPECIFIC_REQ
        switch (pUSB_SETUP_PACKET->bRequest)
        {
        case SET_LINE_CODING:
            if(pUSB_SETUP_PACKET->wLength == 7)
            {
                // ������� �����, ���� ���������� ������
                USBDev_EPPrepareRx(&line_coding_struct[0], 7, 0);

                /*pUSB_SETUP_PACKET->xfer_buff = (uint8_t*)&line_coding_struct[0];
        pUSB_SETUP_PACKET->xfer_count = 0;
        pUSB_SETUP_PACKET->xfer_len = pUSB_SETUP_PACKET->wLength;
        
        USBDev_ReadPacket((uint8_t*)&line_coding_struct[0],
                          7,
                          0);*/
                //USBDev_CEPSendResponse(CEP_ZEROLEN);
            }
            else
            {
                USBDev_CEPSendResponse(CEP_STALL);
            }
            break;
        case GET_LINE_CODING:
            if(pUSB_SETUP_PACKET->wLength == 7)
            {
                /*USBDev_CEPSendData((uint8_t*)&line_coding_struct[0],
                           7);*/

                USBDev_CEPSendResponse(CEP_STALL);


            }
            else
            {
                USBDev_CEPSendResponse(CEP_STALL);
            }
            break;

        case SET_CONTROL_LINE_STATE:
            // ���� ������ �� ������� ������
            // ���� ������ ����� � wValue
            USBDev_CEPSendResponse(CEP_ZEROLEN);
            break;

        default:
            USBDev_CEPSendResponse(CEP_STALL);
            break;
        }
        break;

    default:
        break;

    }

    if(pUSB_SETUP_PACKET->wLength == 0)
    {
        if(pUSB_SETUP_PACKET->bmRequestType & 0x80) //device to host
        {

        }
        else //host to device
        {
            USBDev_CEPSendResponse(CEP_ZEROLEN);
        }
    }

    return 0;
}

uint32_t USBDev_CDC_SOF(void)
{
    if((cdc_tx_now == 0) && (USBDev_ReadState() == USBDev_Configured))
        Handle_TX(EP_DATA_IN & 0x7F);

    //if rx buffer have some data
    if(VCP_IsRxBufEmpty() == 0)
        if (VCP_CDC_DataReceived != NULL)
            VCP_CDC_DataReceived();
    
    return 0;
}

uint32_t USBDev_CDC_EP0_RxReady(void)
{
    return 0;
}

uint32_t USBDev_CDC_EP0_TxSent(void)
{
    return 0;
}

uint8_t *USBDev_CDC_GetConfigDscr(USBDev_Speed_TypeDef dev_speed, uint32_t *len)
{
    uint8_t *pcfgdscr;
    if(dev_speed == USBDev_Speed_Full)
    {
        *len = sizeof(cfg_dscr);
        pcfgdscr = &cfg_dscr[0];
    }
    else //HIGH
    {
        *len = sizeof(cfg_dscr);
        pcfgdscr = &cfg_dscr[0];
    }
    return pcfgdscr;
}

uint32_t Handle_RX(uint8_t epnum)
{
    uint32_t diff;
    // ������� ���������� ����, ������� ������ � �����
    uint32_t rx_bytes_cnt = USBDev_EP_AvailCnt(epnum);
    //������� ������ �� � ����� ���������� ��������� ������
    //���� ���� ����� � ���� �� �����

    if((usbRxBuf.availSpace(&usbRxBuf) >= rx_bytes_cnt) && (usbRxBuf.busy == 0))
    {
    	// ������� ��������� � ������������� usbRxBuf,
    	// � ����� ����� ��� � ��� ����
        USBDev_ReadPacket(tempUsbRxData, rx_bytes_cnt, epnum);
        usbRxBuf.put(&usbRxBuf, rx_bytes_cnt, tempUsbRxData);
        return 0;
    }
    else // ���� ����� ������������, �� ��������� ������������ ���������� ���� �� �����
    {
        return 1;
    }
}

uint8_t need_zlp = 0;
uint32_t Handle_TX(uint8_t epnum)
{
    int32_t data_len;

    if (usbTxBuf.busy == 1) return 0;
    data_len = usbTxBuf.filledSpace(&usbTxBuf);
    //���� ���� ������ � ������
    if(data_len > 0)
    {
        // ������ ���� ��������, ������ �� ���� � ������������� �����, � ���������� ���
        cdc_tx_now = 1;
        usbTxBuf.get(&usbTxBuf, data_len, tempUsbTxData);
        USBDev_WritePacket(tempUsbTxData, data_len, epnum);
     }
    //���� ��� ������ ��������, �� ������ ���� ���������� ��������
    else
    {
        if(cdc_tx_now)
        {
            cdc_tx_now = 0;
        }
        else
        {
            //CALL DATA_SEND_COMPLETE_FUNC
            if (VCP_CDC_DataTransmitted != NULL)
                VCP_CDC_DataTransmitted();
        }
    }

    return 0;
}

uint32_t VCP_PutChar(uint8_t byte)
{
    if(fill_txbuf == BUF_SIZE)
        return 1;

    buf_tx[wrptr_txbuf] = byte;
    wrptr_txbuf = (wrptr_txbuf + 1) & BUF_MASK;
    fill_txbuf++;

    return 0;
}


uint8_t VCP_GetChar(void)
{  
    uint8_t byte;

    byte = buf_rx[rdptr_rxbuf];
    rdptr_rxbuf = (rdptr_rxbuf + 1) & BUF_MASK;
    fill_rxbuf--;

    return byte;
}

uint32_t VCP_IsRxBufEmpty(void)
{
    if(fill_rxbuf == 0) return 1;
    else                return 0;
}

uint32_t VCP_RxHandlerInit(void (*RxHandler)(void))
{
    VCP_CDC_DataReceived = RxHandler;

    return 0;
}

uint32_t VCP_TxHandlerInit(void (*TxHandler)(void))
{
    VCP_CDC_DataTransmitted = TxHandler;

    return 0;
}


