#ifndef __BORLANDC__
#include "stm32f4xx.h"
#include "boards.h"
#endif
// Do not initialize inputs!
void Init(void)
{
#ifndef __BORLANDC__

#endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  //BrdData.Status.bit.WriteProjectData = 0;
  v->Data = MBS_getData(v->Index);
    if ( BrdData.DevNumber != v->Data )
    {
      BrdData.DevNumber = v->Data;
      BrdData.Status.bit.WriteProjectData = 1;
      MBS_setData(v->Index, v->Data, 1);
    return;
    }
#endif
}


