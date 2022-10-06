#define _PDO_En(__index__)       (1+(__index__-1)*5)
#define _PDO_InNum(__index__)    (2+(__index__-1)*5)
#define _PDO_AddrNum(__index__)  (3+(__index__-1)*5)
#define _PDO_Count(__index__)    (4+(__index__-1)*5)
#define _PDO_Command(__index__)  (5+(__index__-1)*5)

#define _errorCounter(__index__) (1+(__index__-1)*2)
#define _errorIndex(__index__)   (2+(__index__-1)*2)

#define NO_CONNECTION 0x09
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
 short i;
 if ((short)(*v->R))
 {
    return;
 }

if (v->EnCount > v->pEnCount ) {v->No_Connection_Time=0;}
if (v->EnCount) {v->No_Connection_Time++;}


v->pEnCount = v->EnCount;

switch (v->State)
{
  case 0:

       if (
           (v->PDO_Errs[_errorIndex(v->ActivNumber+1)] ==  NO_CONNECTION)
           &&
           (v->PDO_Errs[_errorCounter(v->ActivNumber+1)] >= v->Err_TimeOut)
          )
        {
          v->State = 1;
        }
        else if (*v->Connect)   {   v->EnCount=0;   v->Error_Connect=0;  }
        break;
  case 1:
       for (i= 1; i <= (v->Devices_Number); i++)
       {
        if ( (v->PDO_Errs[_errorIndex(i)] ==  NO_CONNECTION) && (v->PDO_Errs[_errorCounter(i)] >= v->Err_TimeOut))
        {
          v->PDO_Errs[_errorCounter(i)] = 0;
          v->PDO_Errs[_errorIndex(i)] = 0;
          v->List_PDO[_PDO_En(i)] = 0;
          if (i == v->Devices_Number) //switch to first device
          {
            v->List_PDO[_PDO_En(1)] = 1;
            v->PDO_Errs[_errorCounter(i)] = 0;
            v->PDO_Errs[_errorIndex(i)] = 0;
            v->List_PDO[_PDO_En(i)] = 0;
            v->ActivNumber = 0;
            break;
          }
          v->List_PDO[_PDO_En(i+1)] = 1; //switch to the next device
          v->ActivNumber ++;
          break;
        }
        if (i > (v->Devices_Number)){i = 0;}
       }
       v->State=2;
       break;
  case 2:
      v->EnCount=1;
      v->Error_Connect=1;
      v->State=0;
      break;
}

}

