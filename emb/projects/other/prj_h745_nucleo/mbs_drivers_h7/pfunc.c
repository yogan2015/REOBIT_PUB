
#include <string.h>


void pgm_blkRead(void *pAddr, void *dAddr, unsigned short Cnt)
{
  memcpy(dAddr, pAddr, Cnt);
}

void pgm_blkWrite(void *pAddr, void *dAddr, unsigned short Cnt)
{
  memcpy(pAddr, dAddr, Cnt);
}

void pgm_strRead(char *pAddr, char *dAddr)
{
  strcpy(dAddr, pAddr);
}

void pgm_strWrite(char *pAddr, char *dAddr)
{
  strcpy(pAddr, dAddr);
}


