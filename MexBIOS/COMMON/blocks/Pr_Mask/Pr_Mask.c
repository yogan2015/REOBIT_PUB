// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
if (*v->State != 0)
{
  if ((*v->State < 1) || (*v->State > v->StateCount)) return;
}
// Отсеиваем активные защиты в зависимсоти от текущего стейта от общего количества защит
v->Active_Pr = (*v->In_Pr_Word & v->ActivePr_Mask[*v->State]);
v->Active_Pr_Trigg |= (*v->In_Pr_Word & v->ActivePr_Mask[*v->State]);
//Выходы
v->gProtect = v->Active_Pr; //не фиксируемое слово защит 1 уровень
v->gProtect_Trigg = v->Active_Pr_Trigg; //зафиксированное слово защит 1 уровень
v->Common_Pr |= (v->Active_Pr & v->Common_Pr_Mask[*v->State]); //триггер сработавших промаскированных защит штатного останова 2 уровень
v->Alarm_Pr |= (v->Active_Pr & v->Alarm_Pr_Mask[*v->State]); //триггер сработавших промаскированных защит аварийного останова 2 уровень

//Фиксация внутреннего слова защит штатного останова по изменению входного слова защит
//if (v->Active_Pr != v->Curr_Common_Pr)
 if(  !v->Lock )
{
  v->Prev_Common_Pr = v->Curr_Common_Pr;
  v->Curr_Common_Pr |= ( v->Active_Pr_Trigg & v->Common_Pr_Mask[*v->State]);
  v->Curr_Common_Pr &= (~v->gCommonStopOffMask);
}
//Фиксация внутреннего слова защит аварийного останова по изменению входного слова защит
if (!v->Lock)
{
  v->Prev_Alarm_Pr = v->Curr_Alarm_Pr;
  v->Curr_Alarm_Pr |= ( v->Active_Pr_Trigg & v->Alarm_Pr_Mask[*v->State]);
  v->Curr_Alarm_Pr &= (~v->gAlarmStopOffMask);
}
//Если есть защиты аварийного останова
if (v->Curr_Alarm_Pr)
{
  v->Lock = 1;
  v->Curr_Alarm_Pr &= (~v->Alarm_Pr_Off_Mask[*v->State]); //Обнуляем биты внутренного слова защит аварийного останова
  //в зависимости от маски сброса флага аварийного останова
  v->Alarm_Stop = (v->Curr_Alarm_Pr & (~v->Alarm_Pr_Off_Mask[*v->State])) ? 1 : 0; //Запрет выставления аварийного останова при повторном появлении бита защиты,
  //равном биту маски сброса флага аварийного останова
}

 //Если есть защиты штатного останова
  if (v->Curr_Common_Pr)
  {
    v->Lock = 1;
    v->Curr_Common_Pr &= (~v->Common_Pr_Off_Mask[*v->State]); //Обнуляем биты внутренного слова защит штатного останова
  //в зависимости от маски сброса флага штатного останова
    v->Common_Stop = (v->Curr_Common_Pr & (~v->Common_Pr_Off_Mask[*v->State])) ? 1 : 0; //Запрет выставления штатного останова при повторном появлении бита защиты,
  //равном биту маски сброса флага штатного останова
    v->gCommonStopOffMask |= v->Common_Pr_Off_Mask[*v->State];
  }

//Сброс флага аварийного останова
if (v->Curr_Alarm_Pr == 0)
{
  v->Lock = 0;
  v->Alarm_Stop = 0;
}
//Сброс флага штатного останова
if (v->Curr_Common_Pr == 0)
{
  v->Lock = 0;
  v->Common_Stop = 0;
}
//Выставления запрета запуска
v->Launch_Ban = ((v->Common_Pr | v->Alarm_Pr) & v->Launch_Ban_Pr_Mask[*v->State]) ? 1 : 0;

if (*v->Reset)
{
  v->Launch_Ban = 0;
  v->Common_Stop = 0;
  v->Alarm_Stop = 0;
  v->gProtect = 0;
  v->gProtect_Trigg = 0;
  v->Prev_Common_Pr = 0;
  v->Prev_Alarm_Pr = 0;
  v->Active_Pr_Trigg = 0;
  v->Common_Pr = 0;
  v->Alarm_Pr = 0;
  v->Active_Pr = 0;
  v->Lock = 0;
  v->gCommonStopOffMask = 0;
  v->gAlarmStopOffMask = 0;
}
}

