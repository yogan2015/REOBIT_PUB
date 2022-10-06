#define enSTATE_AUTO     (v->STATE |= (1<<5))

#define MODE_RESTORE  0x31  //110 001
#define MODE_SYNC     0x2a  //101 010
#define MODE_AUTO     0x1c  //011 100

#define M_RESTORE     0
#define M_SYNC        1
#define M_AUTO        2

void Init(void)
{
  v->MODE = M_RESTORE;
}

void Exec(void)
{

  if (v->MODE == M_RESTORE){
    if (*v->en_sync){
      v->MODE = M_SYNC;
      v->STATE = MODE_SYNC;
      return;
    }
    v->STATE = MODE_RESTORE;
  }

  if (v->MODE == M_SYNC){
    if (!*v->en_sync){
      v->MODE = M_RESTORE;
      v->STATE = MODE_RESTORE;
      return;
    }
    if (*v->en_auto && *v->to_auto){
      v->MODE = M_AUTO;
      v->STATE = MODE_AUTO;
      return;
    }
    v->STATE = MODE_SYNC;
  }

  if (v->MODE == M_AUTO){
    if (!*v->en_auto){
      v->MODE = M_RESTORE;
      v->STATE = MODE_RESTORE;
      return;
    }
    if (*v->en_sync && *v->r_sync){
      v->MODE = M_SYNC;
      v->STATE = MODE_SYNC;
      return;
    }
    v->STATE = MODE_AUTO;
  }
}
