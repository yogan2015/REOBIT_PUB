
#ifdef NUCLIO_G4
	#include "stm32g4xx.h"
#endif

#ifdef NUCLEO_H755ZI_Q
	#include "stm32h7xx.h"
#endif

#include "chip.h"
#include "m95x.h"

#define OPCODE_WREN		0b00000110	// Write Enable
#define OPCODE_WRDI		0b00000100	// Write Disable
#define OPCODE_RDSR		0b00000101	// Read Status Register
#define OPCODE_WRSR		0b00000001	// Write Status Register
#define OPCODE_READ		0b00000011	// Read from Memory Array
#define OPCODE_WRITE	0b00000010	// Write to Memory Array
#define OPCODE_RDID		0b10000011	// Read Identification Page
#define OPCODE_WRID		0b10000010	// Write Identification Page
#define OPCODE_RDLS		0b10000011	// Reads the Identification Page lock status.
#define OPCODE_LID		0b10000010	// Locks the Identification page in read-only mode.

#define LCONV(A)  		*((uint32_t *)(A))

static uint8_t ReadStatus(M95X *);
static void    WriteStatus(M95X *, uint8_t Status);
static void    WriteEnable(M95X *);
static uint8_t ReadByte(M95X *, uint32_t Addr);
static void    WriteByte(M95X *, uint32_t Addr, uint8_t Data);


void M95X_Init(M95X *p)
{
	SPI_init(p->SpiId, 1, 0, p->SpiBaud, 8);
	
	if 		(p->Type == M95512_TYPE) { p->Size = 0x10000; }
	else if (p->Type == M95M02_TYPE) { p->Size = 0x40000; }
	else if (p->Type == M95256_TYPE) { p->Size = 0x8000;  }
	p->Func = 0;
	p->State = 0;
	p->Status = M95X_SUCCESS;
	if (ReadStatus(p) == 0xFF) p->Status = M95X_EDISCON;
}

void M95X_Update(M95X *p)
{
	uint8_t Offs;
	uint32_t dAddr;

	if (!p->Func) {p->State = 0; return;}

	SPI_init(p->SpiId, 1, 0, p->SpiBaud, 8);

	switch(++p->State)
	{
		case 1:
			if (p->Func & M95X_STATUS)       p->State = 1;
			else if (p->Func & M95X_READ)    p->State = 2;
			else if (p->Func & M95X_WRITE)   p->State = 3;
			else if (p->Func & M95X_PROTECT) p->State = 4;
			else {p->Status = M95X_SUCCESS; p->Func = 0; p->State = 0;}
			break;
		case 2:
			p->RdData = ReadStatus(p);
			if (!(p->Func & M95X_WRITE)) {p->Status = M95X_SUCCESS; p->Func = 0;}
			else if (!(p->RdData & 0x01)) p->Func &= ~M95X_STATUS;
			else if (++p->BusyTimer < p->BusyTime) {p->State = 1; break;}
			else {p->Status = M95X_EDISCON; p->Func = 0;}
			p->State = 0;
			break;
		case 3:
			p->RdData = ReadByte(p, p->Addr);
			if (!(p->Func & M95X_WRITE))
			{
				if (!p->Buffer) p->Count = 0;
				else if (!p->Mode) *p->Buffer = p->RdData;
				else
				{
					dAddr = LCONV(p->Buffer);
					if (dAddr) {Offs = p->Counter << 3; LCONV(dAddr) = (LCONV(dAddr) & (~((uint32_t)0xFF << Offs))) | ((uint32_t)p->RdData << Offs);}
				}
			}
			else if (p->RdData != p->WrData)
			{
				p->Status = M95X_EWRITE_ERR;
				p->Func = 0;
				p->State = 0;
				break;
			}
			else {p->Func &= ~M95X_READ;}
			if (p->Count <= 1)
			{
				p->Status = M95X_SUCCESS;
				p->Count = 0;
				p->Func = 0;
			}
			else
			{
				if (p->Buffer)
				{
					if (!p->Mode) p->Buffer++;
					else if (++p->Counter == 4) {p->Buffer = (uint8_t *)((uint32_t *)p->Buffer + 1); p->Counter = 0;}
				}
				p->Addr++;
				p->Count--;
			}
			p->State = 0;
			break;
		case 4:
			if (!p->Buffer) p->WrData = 0xFF;
			else if (!p->Mode) p->WrData = *p->Buffer;
			else
			{
				dAddr = LCONV(p->Buffer);
				if (!dAddr) p->WrData = 0;
				else {Offs = p->Counter << 3; p->WrData = (LCONV(dAddr) >> Offs) & 0xFF;}
			}
			WriteEnable(p);
			WriteByte(p, p->Addr, p->WrData);
			p->Func |= (M95X_STATUS|M95X_READ);
			p->BusyTimer = 0;
			p->State = 0;
			break;
		case 5:
			WriteStatus(p, (p->WrData & 0x03) << 2);
			p->Func &= ~M95X_PROTECT;
			p->State = 0;
			break;
	}
}

void M95X_Func(M95X *p, uint8_t Func, uint8_t Mode,
	uint32_t Addr, uint8_t *Data, uint16_t Count)
{
	if ((p->Status < 0) || !Count) return;
	p->Addr    = Addr;
	p->Buffer  = Data;
	p->Count   = Count;
	p->Mode    = Mode;
	p->Func    = Func;
	p->Counter = 0;
	p->State   = 0;
	p->Status  = M95X_BUSY;
}

static uint8_t ReadStatus(M95X *p)
{
	uint8_t Status;
	p->CsFunc(0);
	SPI_send(p->SpiId, OPCODE_RDSR);
	Status = SPI_send(p->SpiId, 0);
	p->CsFunc(1);
	return Status;
}

static void WriteStatus(M95X *p, uint8_t Status)
{
	p->CsFunc(0);
	SPI_send(p->SpiId, OPCODE_WRSR);
	SPI_send(p->SpiId, Status);
	p->CsFunc(1);
}

static void WriteEnable(M95X *p)
{
	p->CsFunc(0);
	SPI_send(p->SpiId, OPCODE_WREN);
	p->CsFunc(1);
}

static uint8_t ReadByte(M95X *p, uint32_t Addr)
{
	uint8_t Data;
	p->CsFunc(0);
	SPI_send(p->SpiId, OPCODE_READ);
	if (p->Type == M95M02_TYPE) SPI_send(p->SpiId, (Addr >> 16) & 0xFF);
	SPI_send(p->SpiId, (Addr >> 8) & 0xFF);
	SPI_send(p->SpiId, Addr & 0xFF);
	Data = SPI_send(p->SpiId, 0);
	p->CsFunc(1);
	return Data;
}

static void WriteByte(M95X *p, uint32_t Addr, uint8_t Data)
{
	p->CsFunc(0);
	SPI_send(p->SpiId, OPCODE_WRITE);
	if (p->Type == M95M02_TYPE) SPI_send(p->SpiId, (Addr >> 16) & 0xFF);
	SPI_send(p->SpiId, (Addr >> 8) & 0xFF);
	SPI_send(p->SpiId, Addr & 0xFF);
	SPI_send(p->SpiId, Data);
	p->CsFunc(1);
}

