#include "header.h"
#include "mbs_flash.h"

#ifdef NUCLEO_H755ZI_Q
	#define MBS_FLASH_ADDR			0x080E0000
	#define MBS_FLASH_SIZE			0x20000
	#define MBS_FLASH_SECTOR		7
	#define MBS_FLASH_NB_SECTOR		1
	#define MBS_FLASH_BANK			FLASH_BANK_1
	#define MBS_FLASH_TIMOUT		10000*5
#endif

#ifdef HYDROPRESS_H7
	#define MBS_FLASH_ADDR			0x080E0000
	#define MBS_FLASH_SIZE			0x20000
	#define MBS_FLASH_SECTOR		7
	#define MBS_FLASH_NB_SECTOR		1
	#define MBS_FLASH_BANK			FLASH_BANK_1
	#define MBS_FLASH_TIMOUT		10000*5
#endif

#ifdef H745_NUCLEO
	#define MBS_FLASH_ADDR			0x081E0000
	#define MBS_FLASH_SIZE			0x20000
	#define MBS_FLASH_SECTOR		7
	#define MBS_FLASH_NB_SECTOR		1
	#define MBS_FLASH_BANK			FLASH_BANK_1
	#define MBS_FLASH_TIMOUT		10000*5
#endif

#ifdef H745_REO
	#define MBS_FLASH_ADDR			0x081E0000
	#define MBS_FLASH_SIZE			0x20000
	#define MBS_FLASH_SECTOR		7
	#define MBS_FLASH_NB_SECTOR		1
	#define MBS_FLASH_BANK			FLASH_BANK_1
	#define MBS_FLASH_TIMOUT		10000*5
#endif


int16_t FlashErase(void)
{
	FLASH_EraseInitTypeDef pEraseInit;
	uint32_t SectorError =0;
	int16_t Status = 0;

	pEraseInit.Banks	 = MBS_FLASH_BANK;
	pEraseInit.NbSectors	 = MBS_FLASH_NB_SECTOR;
	pEraseInit.Sector		 = MBS_FLASH_SECTOR;
	pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_2;

	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGSERR);

	HAL_FLASHEx_Erase(&pEraseInit,&SectorError);


	if (FLASH_WaitForLastOperation(MBS_FLASH_TIMOUT, MBS_FLASH_BANK) != HAL_OK) Status = -2;
	HAL_FLASH_Lock();
	return Status;
}

// Size для 16bit

int16_t FlashRead(uint8_t Mode, uint32_t Addr, void *pData, uint16_t Size)
{
	uint16_t i;
	int16_t Status = 0;
	if((Addr + Size) > (MBS_FLASH_SIZE / 2))
	{
		Status = -3;
	}
	else
	{
		Addr += MBS_FLASH_ADDR;
		Size *= 2;
		if(Size % 4)
		{
			Size += 4 - Size % 4;
		}
		Size /= 4;
		for(i = 0; i < Size; i++)
		{
			if(Mode)
			{
				break;
			}
			else
			{
				*(uint32_t *)pData = *((uint32_t *)Addr);
				pData = (uint32_t *)pData + 1;
			}
			Addr = Addr + 4;
		}
	}

	return Status;
}

// Size для 16bit

int16_t FlashWrite(uint8_t Mode, uint32_t Addr, void *pData, uint16_t Size)
{
	uint32_t i;
	int16_t Status = 0;
	if((Addr + Size) > (MBS_FLASH_SIZE / 2))
	{
		Status = -3;
	}
	else
	{
		Addr += MBS_FLASH_ADDR;
		Size *= 2;
		if(Size % 4)
		{
			Size += 4 - Size % 4;
		}
		Size /= 4;
		if(Size % 8)
		{
			Size += 8 - Size % 8;
		}
		Size /= 8;
		HAL_FLASH_Unlock();
		for(i = 0; i < Size; i++)
		{
			if(Mode)
			{
				break;
			}
			if((HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, Addr, (uint32_t)pData) != HAL_OK) || ((*((uint32_t *)Addr)) != (*((uint32_t *)pData))))
			{
				Status = -2;
				break;
			}
			pData = (uint32_t *)pData + 8;
			Addr = Addr + (4 * 8);
		}
		HAL_FLASH_Lock();
	}
	return Status;
}
