#define VKO ((MBS_getData(0) & 0x40)>>6)
#define VKZ ((MBS_getData(0) & 0x80)>>7)
#define INIT ((MBS_getData(0) & 0x4)>>2)
#define Pos MBS_getData(1)
#define FL MBS_getData(14)
#define Len MBS_getData(2)
#define DO MBS_getData(20)
//RVCT ON
//#define COMMANDS_BLOCK_ARVM 0
#define COMMANDS_EN_ARVM 0
#define OPENING 1
//RVCT OFF
#define COMMANDS_EN 0
#define RVM_STOP 1
#define RVM_OPENING 2
#define STOP_AFTER_RVM_OPENING 3 //when FB ON
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->FBRVM_Out = 0;
  switch(v->nAutoReversState)
  {

    case COMMANDS_EN:
      switch (v->SubState)
      {
        case 0:
        //v->Time = 0;
        if ((v->OP_Out) && (!(*v->SB_OP||*v->OP))) //Open command edge cap falling
        {
          v->SubState = 1; //start delay. Slow Close after OP
          return;
        }
        v->SpdDiv = 0;
        v->SB_CL_Out = (*v->SB_CL);
        v->SB_OP_Out = (*v->SB_OP);
        v->CL_Out = (*v->CL);
        v->OP_Out = (*v->OP);
        v->AR_Out = (*v->AR);
        if (*v->AlarmClose)
        {
          v->Time+= v->SampleTime;
          if (v->Time >= v->CMD_Time_Change)
          {
            v->Time = 0;
            v->SubState = 2; // Slow close
          }
        }
        break;

        case 1:
        v->SB_CL_Out = 0;
        v->SB_OP_Out = 0;
        v->CL_Out = 0;
        v->OP_Out = 0;
        v->AR_Out = 0;
        v->Time += v->SampleTime;
        if (v->Time >= v->CMD_Time_Change)
        {
          v->Time = 0;
          v->SubState = 0;
        }
        break;

        case 2:
        if (*v->AlarmClose)
        {
          v->SpdDiv = 1;
          v->SB_CL_Out = (*v->AlarmClose);
          v->CL_Out = (*v->AlarmClose);
          v->OP_Out = 0;
          v->SB_OP_Out = 0;
          v->AR_Out = 0;
        }
        else
        {
          v->Time += v->SampleTime;
          if (v->Time >= v->CMD_Time_Change)
          {
            v->SubState = 0;
            v->Time = 0;
          }
        }
        break;
      }
    if (*v->RVM && !v->PrevRVM) //edge cap rising
    {
      v->nAutoReversState = RVM_STOP;
      v->Pos_RVM = (*v->Pos_mm);
      v->Time = 0;
    }
    v->PrevRVM = *v->RVM;
    break;

    case RVM_STOP:
    v->SpdDiv = 0;
    v->SB_CL_Out = 0;
    v->SB_OP_Out = 0;
    v->CL_Out = 0;
    v->OP_Out = 0;
    v->AR_Out = 0;
    v->Time += v->SampleTime;
    if (v->Time >= v->CMD_Time_Reset_RVM)
    {
     v->nAutoReversState = RVM_OPENING;
     v->Time = 0;
    }
   break;

   case RVM_OPENING:
   v->Time += v->SampleTime;
   v->AR_Out = 0;
   v->SB_CL_Out = 0;
   v->CL_Out = 0;
   v->OP_Out = 1;
   v->SB_OP_Out = 1;
   if (!*v->AutoRVM_Func)
   {
     if ( (v->Time >= v->CMD_Time_Reset_RVM) || (*v->Pos_mm >= (v->Pos_RVM + v->deltaPos))  )
     {
        v->OP_Out = 0;
        v->SB_OP_Out = 0;
        v->nAutoReversState = STOP_AFTER_RVM_OPENING;
        v->Pos_RVM = 0;
        v->Time = 0;
     }
   }
   else
   {
     if (VKO || VKZ)
     {
       v->nAutoReversState = STOP_AFTER_RVM_OPENING;
     }
   }
   break;

   case STOP_AFTER_RVM_OPENING:
   v->Time += v->SampleTime;
   v->SB_CL_Out = 0;
   v->SB_OP_Out = 0;
   v->CL_Out = 0;
   v->OP_Out = 0;
   v->AR_Out = 0;
   v->FBRVM_Out = 0;
   if( v->Time >= v->CMD_Time_Reset_After_RVM)
   {
     v->nAutoReversState = COMMANDS_EN;
     v->Time = 0;
   }
   break;
  }
}

