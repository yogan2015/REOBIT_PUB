
#include "menu2x.h"
#include "strutils.h"
#include "rtc.h"

static void StartState(BLOCK_STRUCT *v, char KeyCode);
static void SelectGroup(BLOCK_STRUCT *v, char KeyCode);
static void SelectParam(BLOCK_STRUCT *v, char KeyCode);
static void EditParam(BLOCK_STRUCT *v, char KeyCode);
static void ShowParamValue(BLOCK_STRUCT *v, short Pos, char Flag);
static void OnChangeGroup(BLOCK_STRUCT *v);
static void OnEnterParam(BLOCK_STRUCT *v);
static void OnChangeParam(BLOCK_STRUCT *v);
static void clearStr(long *str);


void Init(void)
{
}

void Exec(void)
{
  char KeyCode;

  if (!*v->HiStr || !*v->LoStr || !Menu2x_Config) return;

  if ((char)*v->Key && !v->LastKey) KeyCode = (char)*v->Key;
  else KeyCode = 0;
  v->LastKey = (char)*v->Key;

  if (v->BlinkTimer > 0) v->BlinkTimer--;
  else { v->Blink = !v->Blink; v->BlinkTimer = v->BlinkTimeout; }

  if (((short)*v->Mode & 0x1) && (v->State != MENU2X_STATE_START))
    v->State = MENU2X_STATE_START;

  switch(v->State)
  {
    case MENU2X_STATE_START:    StartState(v, KeyCode);  break;
    case MENU2X_STATE_SEL_GR:   SelectGroup(v, KeyCode); break;
    case MENU2X_STATE_SEL_PAR:  SelectParam(v, KeyCode); break;
    case MENU2X_STATE_EDIT_PAR: EditParam(v, KeyCode);   break;
 }

  v->Out = v->State;
}

static void StartState(BLOCK_STRUCT *v, char KeyCode)
{
  const char *str;
  short i, Pos;

  if (KeyCode == MENU2X_KEY_ENTER)
  {
    v->GroupPos = 0;
    if (Menu2x_Config->GroupCount < 2) OnEnterParam(v);
    else { v->State = MENU2X_STATE_SEL_GR; OnChangeGroup(v); }
    return;
  }

  Pos = ((short)*v->Mode & 0x1) ? v->FaultPos : *v->Ind;
  str = Menu2x_Config->Params[Pos].Name;
  for (i = 0; i < 16; i++) { if (str[i] == '.') { i++; break; } }
  if (i >= 16) i = 0;

  clearStr((long *)*v->HiStr);
  copyStr((void *)*v->HiStr, (char *)(str + i), 0, 16 - i);
  ShowParamValue(v, Pos, 1);
}

static void SelectGroup(BLOCK_STRUCT *v, char KeyCode)
{
  switch (KeyCode)
  {
    case MENU2X_KEY_UP:
      v->GroupPos = v->GroupPos + 1;
      if (v->GroupPos >= (short)Menu2x_Config->GroupCount) v->GroupPos = 0;
      OnChangeGroup(v);
      break;
    case MENU2X_KEY_DOWN:
      v->GroupPos = v->GroupPos - 1;
      if (v->GroupPos < 0) v->GroupPos = (short)Menu2x_Config->GroupCount-1;
      OnChangeGroup(v);
      break;
    case MENU2X_KEY_ESCAPE:
      v->State = MENU2X_STATE_START;
      break;
    case MENU2X_KEY_ENTER:
      OnEnterParam(v);
      break;
  }
}

static void SelectParam(BLOCK_STRUCT *v, char KeyCode)
{
  const MENU2X_PARAM *Param;
  char Type;

  switch (KeyCode)
  {
    case MENU2X_KEY_UP:
      v->ParamPos = v->ParamPos + 1;
      if (v->ParamPos >= v->ParamCount) v->ParamPos = 0;
      OnChangeParam(v);
      break;
    case MENU2X_KEY_DOWN:
      v->ParamPos = v->ParamPos - 1;
      if (v->ParamPos < 0) v->ParamPos = v->ParamCount-1;
      OnChangeParam(v);
      break;
    case MENU2X_KEY_ESCAPE:
      if (Menu2x_Config->GroupCount < 2) v->State = MENU2X_STATE_START;
      else { v->State = MENU2X_STATE_SEL_GR; OnChangeGroup(v); }
      return;
    case MENU2X_KEY_ENTER:
      Param = &Menu2x_Config->Params[v->ParamPos + v->ParamIndex];
      if (Param->Cfg.Cfg.bit.ReadOnly || ((short)*v->Mode & 0x2)) return;
      Type = Param->Cfg.Cfg.bit.Type;
      if ((Type == MENU2X_TYPE_DEC) || (Type == MENU2X_TYPE_BIN) || (Type == MENU2X_TYPE_HEX)) v->Rate = 0;
      v->State = MENU2X_STATE_EDIT_PAR;
      v->BlinkTimer = 0;
      v->Blink = 0;
      return;
  }

  ShowParamValue(v, v->ParamPos + v->ParamIndex, 1);
}

static void EditParam(BLOCK_STRUCT *v, char KeyCode)
{
  const MENU2X_PARAM *Param;
  union TTimeVar TV;
  union TDateVar DV;
  long Temp, Data;
  float fData;
  short i;

  Param = &Menu2x_Config->Params[v->ParamPos + v->ParamIndex];
  switch (KeyCode)
  {
    case MENU2X_KEY_UP:
      switch (Param->Cfg.Cfg.bit.Type)
      {
        case MENU2X_TYPE_DEC:
          Temp = 1; for (i = 0; i < v->Rate; i++) Temp *= 10;
          v->Value = v->Value + Temp;
          if (v->Value > Param->Cfg.Max) v->Value = Param->Cfg.Max;
          break;
        case MENU2X_TYPE_STR:
          v->Rate = v->Rate + 1;
          if (v->Rate > v->RateMax) v->Rate = 0;
          v->Value = Menu2x_Config->Strings[v->Rate + Param->Cfg.Min].Data;
          break;
        case MENU2X_TYPE_TIME:
          TV.all = v->Value;
          switch (v->Rate)
          {
            case 0: if (TV.bit.Min  < 59) TV.bit.Min++;  else TV.bit.Min  = 0; break;
            case 1: if (TV.bit.Hour < 23) TV.bit.Hour++; else TV.bit.Hour = 0; break;
          }
          v->Value = TV.all;
          break;
        case MENU2X_TYPE_DATE:
          DV.all = v->Value;
          switch (v->Rate)
          {
            case 0: if (DV.bit.Year  < 99) DV.bit.Year++;  else DV.bit.Year  = 0; break;
            case 1: if (DV.bit.Month < 12) DV.bit.Month++; else DV.bit.Month = 1; break;
            case 2:
              if (DV.bit.Day < RTC_DefMaxDay(DV.bit.Year, DV.bit.Month)) DV.bit.Day++;
              else DV.bit.Day = 1;
            break;
          }
          v->Value = DV.all;
          break;
        case MENU2X_TYPE_BIN:
          Temp = 1L << v->Rate;
          if (v->Value & Temp) v->Value &= ~Temp; else v->Value |= Temp;
          if (v->Value > Param->Cfg.Max) v->Value = Param->Cfg.Max;
          break;
        case MENU2X_TYPE_HEX:
          Temp = 1; for (i = 0; i < v->Rate; i++) Temp <<= 4;
          v->Value = v->Value + Temp;
          if (v->Value > Param->Cfg.Max) v->Value = Param->Cfg.Max;
          break;
      }
      break;
    case MENU2X_KEY_DOWN:
      switch (Param->Cfg.Cfg.bit.Type)
      {
        case MENU2X_TYPE_DEC:
          Temp = 1; for (i = 0; i < v->Rate; i++) Temp *= 10;
          v->Value = v->Value - Temp;
          if (v->Value < Param->Cfg.Min) v->Value = Param->Cfg.Min;
          break;
        case MENU2X_TYPE_STR:
          v->Rate = v->Rate - 1;
          if (v->Rate < 0) v->Rate = v->RateMax;
          v->Value = Menu2x_Config->Strings[v->Rate + Param->Cfg.Min].Data;
          break;
        case MENU2X_TYPE_TIME:
          TV.all = v->Value;
          switch (v->Rate)
          {
            case 0: if (TV.bit.Min  > 0) TV.bit.Min--;  else TV.bit.Min  = 59; break;
            case 1: if (TV.bit.Hour > 0) TV.bit.Hour--; else TV.bit.Hour = 23; break;
          }
          v->Value = TV.all;
          break;
        case MENU2X_TYPE_DATE:
          DV.all = v->Value;
          switch (v->Rate)
          {
            case 0: if (DV.bit.Year  > 0) DV.bit.Year--;  else DV.bit.Year  = 99; break;
            case 1: if (DV.bit.Month > 1) DV.bit.Month--; else DV.bit.Month = 12; break;
            case 2:
              if (DV.bit.Day > 1) DV.bit.Day--;
              else DV.bit.Day = RTC_DefMaxDay(DV.bit.Year, DV.bit.Month);
              break;
          }
          v->Value = DV.all;
          break;
        case MENU2X_TYPE_BIN:
          Temp = 1L << v->Rate;
          if (v->Value & Temp) v->Value &= ~Temp; else v->Value |= Temp;
          if (v->Value < Param->Cfg.Min) v->Value = Param->Cfg.Min;
          break;
        case MENU2X_TYPE_HEX:
          Temp = 1; for (i = 0; i < v->Rate; i++) Temp <<= 4;
          v->Value = v->Value - Temp;
          if (v->Value < Param->Cfg.Min) v->Value = Param->Cfg.Min;
          break;
      }
      break;
    case MENU2X_KEY_LEFT:
      v->Rate = v->Rate + 1;
      if (v->Rate > v->RateMax) v->Rate = 0;
      if (Param->Cfg.Cfg.bit.Type == MENU2X_TYPE_STR)
        v->Value = Menu2x_Config->Strings[v->Rate + Param->Cfg.Min].Data;
      break;
    case MENU2X_KEY_RIGHT:
      v->Rate = v->Rate - 1;
      if (v->Rate < 0) v->Rate = v->RateMax;
      if (Param->Cfg.Cfg.bit.Type == MENU2X_TYPE_STR)
        v->Value = Menu2x_Config->Strings[v->Rate + Param->Cfg.Min].Data;
      break;
    case MENU2X_KEY_ESCAPE:
      v->State = MENU2X_STATE_SEL_PAR;
      return;
    case MENU2X_KEY_ENTER:
      Temp = 1; for (i = 0; i < (short)Param->Cfg.Cfg.bit.Precision; i++) Temp *= 10;
      i = Param->Cfg.Cfg.bit.Format;
      if (i == 31) { fData = (float)v->Value / Temp; Data = *(long *)&fData; }
      else Data = __IQdiv(v->Value, Temp, i);
      if(Param->Cfg.Cfg.bit.Fixed)
        { if(!MBS_setPjtData(Param->Cfg.Addr, Data, Param->Cfg.Cfg.bit.Memory, Param->Cfg.Cfg.bit.Len)) break; }
      else
        { if(!MBS_setData(Param->Cfg.Addr, Data, Param->Cfg.Cfg.bit.Memory)) break; }
      v->State = MENU2X_STATE_SEL_PAR;
      return;
  }

  ShowParamValue(v, v->ParamPos + v->ParamIndex, 0);
}

static void ShowParamValue(BLOCK_STRUCT *v, short Pos, char Flag)
{
  const MENU2X_PARAM *Param = &Menu2x_Config->Params[Pos];
  short i, Prec;
  long Data, Temp;

  Prec = (short)Param->Cfg.Cfg.bit.Precision;
  if (Flag)
  {
    Temp = 1; for (i = 0; i < Prec; i++) Temp *= 10;
    i = Param->Cfg.Cfg.bit.Format;
    if(Param->Cfg.Cfg.bit.Fixed)
      Data = MBS_getPjtData(Param->Cfg.Addr, Param->Cfg.Cfg.bit.Len);
    else
      Data = MBS_getData(Param->Cfg.Addr);
    if (i == 31) v->Value = __IQ(*((float *)&Data) * Temp, 0);
    else v->Value = __IQmpy(Data, Temp, i);
  }

  clearStr((long *)*v->LoStr);

  switch(Param->Cfg.Cfg.bit.Type)
  {
    case MENU2X_TYPE_DEC:
      decToStr((void *)*v->LoStr, v->Value, 0, Prec, 11, Flag);
      if (!Flag && v->Blink)
      {
        i = 10 - v->Rate;
        if (Prec && (v->Rate >= Prec)) i--;
        charToStr((void *)*v->LoStr, ' ', i);
      }
      copyStr((void *)*v->LoStr, (char *)Param->Unit, 12, 4);
      break;
    case MENU2X_TYPE_STR:
      if ((v->Rate == -1) || Flag)
      {
        for (i = 0; i <= v->RateMax; i++)
          if (v->Value == Menu2x_Config->Strings[i + Param->Cfg.Min].Data) { v->Rate = i; break; }
      }
      if(!Flag && v->Blink) break;
      if (v->Rate == -1) decToStr((void *)*v->LoStr, v->Value, 0, Prec, 11, 1);
      else copyStr((void *)*v->LoStr, (char *)Menu2x_Config->Strings[v->Rate + Param->Cfg.Min].Text, 0, 16);
      break;
    case MENU2X_TYPE_TIME:
      timeToStr((void *)*v->LoStr, v->Value, 5);
      if (!Flag && v->Blink)
      {
        i = v->Rate ? 5 : 8;
        charToStr((void *)*v->LoStr, ' ', i);
        charToStr((void *)*v->LoStr, ' ', i+1);
      }
      break;
    case MENU2X_TYPE_DATE:
      dateToStr((void *)*v->LoStr, v->Value, 4);
      if (!Flag && v->Blink)
      {
        i = 10 - v->Rate * 3;
        charToStr((void *)*v->LoStr, ' ', i);
        charToStr((void *)*v->LoStr, ' ', i+1);
      }
      break;
    case MENU2X_TYPE_BIN:
      binToStr((void *)*v->LoStr, v->Value, 0, 16);
      if (!Flag && v->Blink) charToStr((void *)*v->LoStr, ' ', 15 - v->Rate);
      break;
    case MENU2X_TYPE_HEX:
      hexToStr((void *)*v->LoStr, v->Value, 4, 8);
      if (!Flag && v->Blink) charToStr((void *)*v->LoStr, ' ', 11 - v->Rate);
      break;
    case MENU2X_TYPE_UNION:
      if (v->Blink)
      {
        if (!v->Value) v->Rate = -1;
        else do { v->Rate = v->Rate + 1; if (v->Rate > 31) v->Rate = 0; }
        while (!(v->Value & (1L << v->Rate)));
        v->Blink = 0;
      }
      if (v->Rate == -1) decToStr((void *)*v->LoStr, 0, 0, 0, 11, 1);
      else copyStr((void *)*v->LoStr, (char *)Menu2x_Config->Strings[v->Rate + Param->Cfg.Min].Text, 0, 16);
      break;
  }
}

static void OnChangeGroup(BLOCK_STRUCT *v)
{
  copyStr((void *)*v->HiStr, (char *)Menu2x_Config->Groups[v->GroupPos].HiString, 0, 16);
  copyStr((void *)*v->LoStr, (char *)Menu2x_Config->Groups[v->GroupPos].LoString, 0, 16);
}

static void OnEnterParam(BLOCK_STRUCT *v)
{
  v->State      = MENU2X_STATE_SEL_PAR;
  v->ParamPos   = 0;
  v->ParamCount = Menu2x_Config->Groups[v->GroupPos].Count;
  v->ParamIndex = Menu2x_Config->Groups[v->GroupPos].Index;

  OnChangeParam(v);
}

static void OnChangeParam(BLOCK_STRUCT *v)
{
  const MENU2X_PARAM *Param;

  Param = &Menu2x_Config->Params[v->ParamPos + v->ParamIndex];

  v->Rate = 0;
  switch(Param->Cfg.Cfg.bit.Type)
  {
    case MENU2X_TYPE_DEC:   v->RateMax = Param->Cfg.Cfg.bit.Precision ? 8 : 9; break;
    case MENU2X_TYPE_STR:   v->RateMax = Param->Cfg.Max - 1; v->Rate = -1; break;
    case MENU2X_TYPE_UNION: v->RateMax = Param->Cfg.Max - 1; v->Rate = -1; break;
    case MENU2X_TYPE_TIME:  v->RateMax = 1;  break;
    case MENU2X_TYPE_DATE:  v->RateMax = 2;  break;
    case MENU2X_TYPE_BIN:   v->RateMax = 15; break;
    case MENU2X_TYPE_HEX:   v->RateMax = 7;  break;
    default: return;
  }

  copyStr((void *)*v->HiStr, (char *)Param->Name, 0, 16);
}

static void clearStr(long *str)
{
  str[0] = 0x20202020;
  str[1] = 0x20202020;
  str[2] = 0x20202020;
  str[3] = 0x20202020;
}


