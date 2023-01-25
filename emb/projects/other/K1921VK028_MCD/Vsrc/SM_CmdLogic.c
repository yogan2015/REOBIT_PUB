/*!
    Copyright 2017 	ÀÎ "ÍÈÈİÒ" è ÎÎÎ "ÍÏÔ ÂÅÊÒÎĞ"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 
 \file      SMCmdLogic.c
 \brief     Îáğàáîòêà êîìàíä è çàäàíèé, ïîñòóïàşùèõ èç ğàçëè÷íûõ èñòî÷íèêîâ. (ñì. TSM_CmdLogic)
 \author    ÎÎÎ "ÍÏÔ Âåêòîğ". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup SMCmdLogic
 @{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "main.h"

//!Èíèöèàëèçàöèÿ

//!Âñÿêèå îáíóëåíèÿ...
//! \memberof TSM_CmdLogic
void SM_CmdLogicInit(TSM_CmdLogic *p) {
	p->state = 0;
	p->state_prev = 0xFF;
	cmd.all = 0;
}

//!Ìåäëåííûé ğàñ÷åò

//! \memberof TSM_CmdLogic
void SM_CmdLogicSlow_Calc(TSM_CmdLogic *p) {

}

//!1êÃö ğàñ÷åò

//!Îáğàáîòêà ğàçëè÷íûõ èñòî÷íèêîâ êîìàíä è ğàñ÷åò ÄÀ,
//!êîòîğûé ïåğåêëş÷àåò ãëîáàëüíî ğåæèìû ĞÀÁÎÒÀ è ÎÑÒÀÍÎÂ.
//! \memberof TSM_CmdLogic
void SM_CmdLogicms_Calc(TSM_CmdLogic *p) {
	p->StartButton = STARTBUTTON;   //îáğàáîòêà íîæêè ñòàğòà
	p->StopButton = STOPBUTTON;     //îáğàáîòêà íîæêè ñòîïà
	p->ResetButton = RESETBUTTON;

	//Ñòàíäàğòíàÿ îáğàáîòêà äèñêğåòíîãî àâòîìàòà
	if (p->state_prev != p->state)
		p->E = 1;
	else
		p->E = 0;
	p->state_prev = p->state;

#if defined (HW_MCB3)
	if ((p->StartButton==1) && (p->StartButtonPrev==0)){
		cmd.bit.start=1;//êîìàíäà íà çàïóñê. Îíà æå ñòàâèòñÿ ÷åğåç CAN
	}
	if ((p->StopButton==1) && (p->StopButtonPrev==0)){
		cmd.bit.stop=1;
	}
	p->StartButtonPrev=p->StartButton;
	p->StopButtonPrev=p->StopButton;
	p->ResetButtonPrev = p->ResetButton;
#endif

	//îïğåäåëÿåì ğåæèì ğàáîòû
	switch (p->state) {
	case CMD_LOGIC_TURNED_OFF: {	//ñîñòîÿíèå 0- ÎÒÊËŞ×ÅÍ
		if (p->E == 1) {
			/*ENTRY*/
			sm_ctrl.state = CTRL_STOP;
			drv_status.bit.ready = 1;
			drv_status.bit.running = 0;
		}

		if (sm_prot.state == PROT_ON_OK) {//åñëè ÄÀ çàùèò âêëş÷èëñÿ, îáğàáàòûâàåì êîìàíäû âêëş÷åíèÿ
			if ((cmd.bit.start == 1) && (sm_sys.state == SYS_READY)) {//åñòü áèòîâàÿ êîìàíäà ñòàğòà
				if (udControl.Enabled == 0) {	//Åñëè öåïü ïëàâíîãî çàğÿäà ÇÏÒ îòêëş÷åíà, òî ïåğåõîäèì ê ïóñêó
					p->state = CMD_LOGIC_TURNED_ON;	//ïîåõàëè
				}
				else {
				    if (udControl.StateOn == 1) { //Åñëè öåïü ïëàâíîãî çàğÿäà ÇÏÒ âêëş÷åíà, æäåì ñğàáàòûâàíèÿ ğåëå, à ïîòîì çàïóñêàåì
				        p->state = CMD_LOGIC_TURNED_ON;	//ïîåõàëè
				    }
				    else {
				        udControl.fault_start = 1;  //åñëè ïûòàåìñÿ ïóñòèòñÿ ïğè íåçàøóíòèğîâàííîì ğåëå, ïîïàäàåì â àâàğèş
				    }
				}
			}
		}

		//äèñêğåòíûé àâòîìàò ñî ñòğóêòóğàìè óïğàâëåíèÿ â ÑÒÎÏå âñåãäà òîæå ïğèíóäèòåëüíî ïåğåâîäèì â ñòîï
		sm_ctrl.state = CTRL_STOP;
		//âñåãäà ñáğàñûâàåì áèòîâûå êîìàíäû óïğàâëåíèÿ
		cmd.bit.stop = 0;
		cmd.bit.start = 0;
		break;
	}

	case CMD_LOGIC_TURNED_ON: {	//ñîñòîÿíèå - ĞÀÁÎÒÀ
		if (p->E == 1) {
			/*ENTRY*/
			drv_status.bit.ready = 1;
			drv_status.bit.running = 1;
			sm_ctrl.state = CTRL_RUN;//ïîåõàëè
		}
		//åñëè ÀÂÀĞÈÿ èëè ÊÎÌÀÍÄÀ ÑÒÎÏ òî ñîñòîÿíèå ñòîï
		if ((sm_prot.state == PROT_FAIL) || (cmd.bit.stop == 1)
				|| (sm_ctrl.state == CTRL_STOP)){
			p->state = CMD_LOGIC_TURNED_OFF;
		}

		//âñåãäà ñáğàñûâàåì êîìàíäó óïğàâëåíèÿ
		cmd.bit.stop = 0;
		cmd.bit.start = 0;
		break;
	}

    default: {      //íà âñÿêèé ñëó÷àé äåëàåì ğåæèì ïî-óìîë÷àíèş "âûêëş÷åí"
        p->state = CMD_LOGIC_TURNED_OFF;
        break;
    }

	} // êîíåö switch(p->state)
}

/*@}*/
