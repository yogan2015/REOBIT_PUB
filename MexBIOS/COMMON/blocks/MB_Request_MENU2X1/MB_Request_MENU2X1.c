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
	if(!v->en_SDO)
	{
		v->Time = 0;
		v->State = 0;
		switch(v->PrevAdr)
		{
			case 0:
				v->Adr_SDO = *v->Mexbios_Par_Adr;
				v->Com_SDO = 3;
				v->en_SDO = 1;
			break;
			
			case 1:
			break;
			
			case 2:
				v->Adr_SDO = *v->Mexbios_Par_Adr;
				v->Com_SDO = 3;
				v->en_SDO = 1;
			break;
			
			case 3:
				if(*v->EnterParam)
				{
					v->Adr_SDO = *v->Mexbios_Par_Adr;
					v->Com_SDO = 16;
					v->en_SDO = 1;
				}
			break;
		}
	}
	else
	{
		switch(v->State)
		{
			case 0:					
				MBS_setData(v->MB_SDO_Adrr, v->Adr_SDO * 2, 0);
				MBS_setData(v->MB_SDO_MexBIOS_Adrr, v->Adr_SDO, 0);
				MBS_setData(v->MB_SDO_Command, v->Com_SDO, 0);
				MBS_setData(v->MB_SDO_Enable, v->en_SDO, 0);
				v->State = 1;
			break;
			
			case 1:
				if(v->Time < v->SDO_Tx_En_Time)
				{	
					v->Time += v->SampleTime;
				}
				else
				{
					v->en_SDO = MBS_getData(v->MB_SDO_Enable);
				}	
			break;
		}
	}
	v->PrevAdr = *v->MenuState;
}
