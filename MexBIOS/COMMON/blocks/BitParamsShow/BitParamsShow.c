#include "menu2x.h"
#include "strutils.h"
#define BIT_SEARCH 0
#define SHOW_STRING 1

// Do not initialize inputs!
void Init(void)
{
  v->Bit = 0;
  v->Timer = 0;
}

void Exec(void)
{

#ifndef __BORLANDC__

  long Pos = 0;
  switch(*v->CurrentState)
  {
    case 0:
      Pos = *v->CurrentParam;
    break;
    case 2:
      Pos = v->GroupPosition + *v->CurrentParam;
    break;
  }
  const MENU2X_PARAM *Param = &Menu2x_Config->Params[Pos];
  long Data;
  char** strings_buffer = (char**)v->Buffer;

  if(Pos == v->ParamNumber)
  {
	if((*v->CurrentState != 2) || (*v->CurrentGroup == v->GroupNumber))
	{
		Data = MBS_getData(Param->Cfg.Addr);

		if(Data)
		{
		  if(v->Bit == v->NumberOfBits)
		  {
			v->Bit = 0;
		  }
		  else if(v->Bit < 0)
		  {
			v->Bit = 0;
		  }

		  if(!(Data & (1 << v->Bit)))
		  {
			++v->Bit;
		  }

		  switch(v->State)
		  {
			case BIT_SEARCH:

			  copyStr((void *)*v->Str, (char *)"                ", 0, 16);

			  v->Timer += v->SampleTime;
			  if(v->Timer > v->PauseDelay)
			  {
				v->Timer = 0;
				v->State = SHOW_STRING;
				v->ShowBit = v->Bit + 1;
				v->Bit = v->ShowBit;
			  }
			break;
			case SHOW_STRING:
			  copyStr((void *)*v->Str, strings_buffer[v->ShowBit], 0, 16);

			  v->Timer += v->SampleTime;
			  if(v->Timer > v->ShowDelay)
			  {
				v->Timer = 0;
				v->State = BIT_SEARCH;
			  }
			break;
		  }
		}
		else
		{
		  copyStr((void *)*v->Str, strings_buffer[0], 0, 16);
		}
	}
	else
	{
		v->Timer = 0;
		v->Bit = 0;
		v->State = BIT_SEARCH;
	}
  }
  else
  {
	  v->Timer = 0;
	  v->Bit = 0;
	  v->State = BIT_SEARCH;
  }

#endif
}

