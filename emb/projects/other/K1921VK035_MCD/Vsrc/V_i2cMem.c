/*!
    Copyright 2019  �� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      v_i2cMem.c
 \brief     ������� ��� ������ � ����������� ���� ������ 24LC256 ��
 ���������� I2C
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 10/08/2019

 \addtogroup v_i2cMem
@{
*/

#include "main.h"
#include "V_i2cmem.h"
#define I2C_MEM_ERROR_OK                0
#define I2C_MEM_ERROR_WRITE_HW_ERR      1
#define I2C_MEM_ERROR_READ_HW_ERR       2
#define I2C_MEM_ERROR_TIMEOUT           3

TI2cMem i2cMem = I2CMEM_DEFAULTS;

// �������� ������� ���� I2C � ����������
#define I2CMEM_FREQUENCY_KHZ    400

// ������� �������� ���������� ������� ������� I2C
// ������ ���, ���� ������ ������ �� ��������� "IDLE"
Uint16 i2c_waitIdle() {
    Uint32 idle = 0;

    while ((I2C->ST & I2C_ST_MODE_Msk) == I2C_ST_MODE_IDLE){
        idle++;
        // ���� �������� ������� ������ - ������ ������
        if (idle > 10000000)
            return 1;
    };

    return 0;
}


// ������� ���, ���� ���������� ���������� ���� ������ � ���������� ������.
// ���� ���� ���, ���������� �� ��������� ������������ �� ���� � ����������� ������� � �������� "Write"
// ���� ���������, ���� ���������� �����������, �� �� ������ �� ������� ��� ����� � ���������
// �������� ����� ����������� ������ (�� ���� � ������ ����� � ����� ���������� � ����� "Write")
Uint16 i2c_waitMemBusyAndSendAddWr () {
    volatile Uint32 waitCycles = 0;
    // �������� ����� � ���, ���� �� ���������
    I2C->CTL0 = I2C_CTL0_START_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_STDONE)
        return I2C_MEM_ERROR_TIMEOUT;


    do {
        // ������� ����� ���������� + Write, ���������, ���� ����������
        I2C->SDA = 0b10100000;
        I2C->CTL0 = I2C_CTL0_CLRST_Msk;
        if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

        // �������, ��� �������� ����������. ���� �������� "4" - ������ ���������� ���� ������
        // ������� � ����� ����� ������. ���������� 0
        if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTADPA){
            // ����� �������, ������� ��� ��� �������� ��������� ������. ���� ������� ����� - ������ ������
            waitCycles++;
            if (waitCycles > 10000000) {
                I2C->CTL0 = I2C_CTL0_STOP_Msk | I2C_CTL0_CLRST_Msk;
                return I2C_MEM_ERROR_TIMEOUT;
            }

            // ���� �� ������� ����� - �������� ��������� �����
            I2C->CTL0 = I2C_CTL0_START_Msk;
            I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
            if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

            if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_RSDONE)
                return I2C_MEM_ERROR_TIMEOUT;
        }
    } while ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTADPA);

    // ����� �� ���� - �� ������
    return I2C_MEM_ERROR_OK;
}

// ��������������� ������� ��� ������� ������ ������ � ������.
// ������������ ����/�������� ������ �������, ������� ���� ��������
// ��� ���������� ������� �������� (64 �����) ������ ������.
Uint16 i2c_initWriteArray (Uint16 address) {
    Uint16 retVal;
    // ���, ���� ������ ������ �������� ���������� ����������
    retVal = i2c_waitMemBusyAndSendAddWr();
    if (retVal != I2C_MEM_ERROR_OK)
        return retVal;

    // ������� ���� ������ 0x0000____
    I2C->SDA = (address >> 8) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // ���� �� ���������� - ������
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_WRITE_HW_ERR;

    // ������� ���� ������ 0x____0000
    I2C->SDA = (address >> 0) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // ���� �� ���������� - ������
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_WRITE_HW_ERR;

    // �� ������
    return I2C_MEM_ERROR_OK;
}

// ������ ������� ���� � ������.
Uint16 i2c_writeArray(Uint16 address, Uint16 *dataPtr_u16, Uint16 length_u8) {
    // ��� ������ ����� �������� � �������
    Uint8* dataPtr_u8 = (Uint8*)dataPtr_u16;

    // ���������� �����, � ������� ����� ������
    i2c_initWriteArray(address);

    // ���������� ������
    while (length_u8 > 0) {
        I2C->SDA = *dataPtr_u8;
        I2C->CTL0 = I2C_CTL0_CLRST_Msk;
        if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

        // ���� �� ���������� - ������
        if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
            return I2C_MEM_ERROR_WRITE_HW_ERR;

        length_u8--;
        dataPtr_u8++;
        address++;

        // �������, �� ����� �� �� ����� �������� ������ ������/
        // ���� ����� - ���� ��������� ���� � ���������, ���� ������ ����������
        if ((address & 0x3F) == 0) {
            // ��������� ���� � ������������� ����������� �� ����� �����
            I2C->CTL0 = I2C_CTL0_STOP_Msk;
            I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
            i2c_initWriteArray(address);
        }
    }

    // ��������� - ��������� ����
    I2C->CTL0 = I2C_CTL0_STOP_Msk;
    I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
    return I2C_MEM_ERROR_OK;
}

// ������ ������� 16-��������� ����
Uint16 i2c_readArray(Uint16 address, Uint16* readDataPtr_u16, Uint16 length_u8){
    // ��� ������ ����� �������� � �������
    Uint8* readDataPtr_u8 = (Uint8*)readDataPtr_u16;

    Uint16 retVal;

    // ���, ���� ������ ������ �������� ���������� ����������
    retVal = i2c_waitMemBusyAndSendAddWr();
    if (retVal != I2C_MEM_ERROR_OK)
        return retVal;

    // ������� ���� ������ 0x0000____
    I2C->SDA = (address >> 8) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // ���� �� ���������� - ������
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // ������� ���� ������ 0x____0000
    I2C->SDA = (address >> 0) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // ���� �� ���������� - ������
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // ��������� �����, ����� ������� � ����� �������-��������
    I2C->CTL0 = I2C_CTL0_START_Msk;
    I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // ���� ����� ������������ - ������
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_RSDONE)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // ����� ���������� + Read
    I2C->SDA = 0b10100001;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // ���� �������� ������ ���������� �� ����������� - ������
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MRADPA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // �� ���������� ����� ��������� � ���������
    while (length_u8 > 1) {
        I2C->CTL0 = I2C_CTL0_CLRST_Msk;
        if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

        // ���� ����� �� ���� ���������� - ������
        if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MRDAPA)
            return I2C_MEM_ERROR_READ_HW_ERR;

        *readDataPtr_u8 = I2C->SDA;
        readDataPtr_u8++;
        length_u8--;
    }

    // ��������� ���� ���������, �� �� ���������
    I2C->CTL0 = I2C_CTL0_ACK_Msk;  // Reset + NACK
    I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // ���� ����� �� ���� ���������� - ������
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MRDANA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    *readDataPtr_u8 = I2C->SDA;

    // ��������� ����
    I2C->CTL0 = I2C_CTL0_STOP_Msk | I2C_CTL0_CLRST_Msk;
    return I2C_MEM_ERROR_OK;
}



// ���� ������ I2C � GPIO, � ������� ���������� ������
void I2CMEM_Init(TI2cMem*p){
    // ��������� ������ 0 � 1 ����� ����� � � ��������� �� � ������������ �����
    GPIOA->ALTFUNCSET = 0x3;

    // ��������� ������ I2C ������ � ������ ��� ��������
    // Fi2c = Fcpu / (4 * SCLFRQ), � Fcpu ��� 035 = 100 ���
    I2C->CTL1 |= I2C_CTL1_ENABLE_Msk;
    I2C->CTL1 |= (25000 / I2CMEM_FREQUENCY_KHZ) << I2C_CTL1_SCLFRQ_Pos;
}

// ������ ������� ������
void I2CMEM_Write(TI2cMem*p){
    p->LastErr = i2c_writeArray(p->MEMstartaddr, p->DSPstartaddr, p->data_length);
}

// ������ ������� ������
void I2CMEM_Read(TI2cMem*p){
    p->LastErr = i2c_readArray(p->MEMstartaddr, p->DSPstartaddr, p->data_length);
}

// ������ ������� ������
void I2CMEM_Clear(TI2cMem*p){
    Uint32 i = 0;
    Uint16 ffArr[32];
    for (i = 0; i < 32; i++) {
        ffArr[i] = 0xFFFF;
    }

    // �������� ������ �������� 0xFF
    for (i = 0; i < EEPROM_MEM_LENGTH; i += 0x40){
        p->MEMstartaddr = i;
        p->DSPstartaddr = ffArr;
        p->data_length = 0x40;

        p->LastErr = i2c_writeArray(p->MEMstartaddr, p->DSPstartaddr, p->data_length);
        if (p->LastErr != I2C_MEM_ERROR_OK)
            return;
    }
}
/*@}*/
