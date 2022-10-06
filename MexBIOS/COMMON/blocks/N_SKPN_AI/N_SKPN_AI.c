#define CTRL_BUCK        (*v->CTRL & (1<<0))
#define CTRL_BOOST       (*v->CTRL & (1<<1))
#define CTRL_REV         (*v->CTRL & (1<<2))
#define CTRL_AUTO_EN     (*v->CTRL & (1<<3))
#define CTRL_SYNC_EN     (*v->CTRL & (1<<4))
#define EXT_AUTO         (*v->CTRL & (1<<5))
#define EXT_SYNCREADY    (*v->CTRL & (1<<6))

#define enSTATE_BUCK     (v->STATE |= (1<<0))
#define enSTATE_BOOST    (v->STATE |= (1<<1))
#define enSTATE_REV      (v->STATE |= (1<<2))
#define enSTATE_RESTORE  (v->STATE |= (1<<3))
#define enSTATE_SYNC     (v->STATE |= (1<<4))
#define enSTATE_AUTO     (v->STATE |= (1<<5))

#define COND_BUCK  (*v->DIR < *v->DIR_MIN)
#define COND_BOOST (*v->DIR > *v->DIR_MAX)
#define COND_REV   (REV_ABS > *v->REV_MAX)
#define COND_AUTO  ((*v->DIR < *v->COMP_MIN) | (*v->DIR > *v->COMP_MAX))

void Init(void)
{

}

void Exec(void)
{
  int REV_ABS;
  REV_ABS = _IQ24sqrt(_IQ24mpy(*v->REV_D, *v->REV_D)+_IQ24mpy(*v->REV_Q, *v->REV_Q));

if ((!CTRL_SYNC_EN)&&(!CTRL_AUTO_EN))  // Начальный режим восстановления
{
  v->AUTO     = 0;
  v->SYNC     = 0;
  v->RESTORE  = 1;
  goto a;
}

if ((CTRL_SYNC_EN) && (v->RESTORE))  //  Из восстановления в синх.
{
  v->AUTO     = 0;
  v->SYNC     = 1;
  v->RESTORE  = 0;
  goto a;
}

if (v->SYNC && ((CTRL_AUTO_EN && COND_AUTO) || EXT_AUTO))  // Переход а авто
{
  v->AUTO     = 1;
  v->SYNC     = 0;
  v->RESTORE  = 0;
  goto a;
}

if ((v->AUTO) && CTRL_SYNC_EN && EXT_SYNCREADY)  //  Обратная синхронизация из режима разряда
{
  v->AUTO     = 0;
  v->SYNC     = 1;
  v->RESTORE  = 0;
  goto a;
}

if ((v->AUTO) && !CTRL_SYNC_EN && EXT_SYNCREADY)  //  Возврат в режим восстановления
{
  v->AUTO     = 0;
  v->SYNC     = 0;
  v->RESTORE  = 1;
  goto a;
}
a:  v->STATE = 0;

if (v->AUTO) enSTATE_AUTO;
if (v->SYNC) enSTATE_SYNC;
if (v->RESTORE) enSTATE_RESTORE;

v->U_DIR = 0;
v->U_REV_D = 0;
v->U_REV_Q = 0;

// КОМПЕНСАЦИИ
if (v->SYNC)
  {
    if ((COND_BUCK)&&(CTRL_BUCK))
    {      enSTATE_BUCK;
      v->U_DIR = *v->DIR_MIN - *v->DIR;
    }

    if ((COND_BOOST)&&(CTRL_BOOST))
    {
      enSTATE_BOOST;
      v->U_DIR = *v->DIR - *v->DIR_MAX;
    }

    if ((COND_REV)&&(CTRL_REV))
    {
      enSTATE_REV;
      v->U_REV_Q = _IQ24mpy((*v->REV_MAX - REV_ABS), *v->REV_Q);
      v->U_REV_D = _IQ24mpy((*v->REV_MAX - REV_ABS), *v->REV_D);
    }
  }
}

