#ifndef __BORLANDC__
#include "../StartUp/flash_log.h"
#include "../StartUp/iwdg.h"
#endif
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
#ifndef __BORLANDC__
long protLog[10] = {0,0,0,0,0,0,0,0,0,0};
if (v->prevNum != *v->Num){
if (( *v->Addr - 10* gLogParam.logProtoDataTotalEntrySize) >= FLASHLOGPAGEADDR)
v->readAddr = ( *v->Addr - 10* gLogParam.logProtoDataTotalEntrySize);
else v->readAddr = FLASHLOGPAGEADDR;

for (v->dataCnt = 0; v->dataCnt <= 9; v->dataCnt++ ){
protLog[v->dataCnt] = FLASHRead(v->readAddr);
v->readAddr += gLogParam.logProtoDataTotalEntrySize;    // инкрементируя адрес с начального до конечного
}

if (*v->Num < 10)  *v->Index = v->StartAddr + *v->Num ;
else *v->Index = v->StartAddr + 9;

v->ProterctionLog1 = protLog[0];
v->ProterctionLog2 = protLog[1];
v->ProterctionLog3 = protLog[2];
v->ProterctionLog4 = protLog[3];
v->ProterctionLog5 = protLog[4];
v->ProterctionLog6 = protLog[5];
v->ProterctionLog7 = protLog[6];
v->ProterctionLog8 = protLog[7];
v->ProterctionLog9 = protLog[8];
v->ProterctionLog10 = protLog[9];
v->prevNum = *v->Num;
}
#endif
}

