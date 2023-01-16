
#ifndef __MBS_KERNEL__
#define __MBS_KERNEL__

#ifndef _FUNC_CALL_
#ifndef __BORLANDC__
#define _FUNC_CALL_
#else
#define _FUNC_CALL_   __stdcall
#endif
#endif

#ifdef __BORLANDC__
#pragma pack(push, 1)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MBS_KERNEL_VERSION        2002

#define MBS_ERR_NONE              0
#define MBS_ERR_HEAP_MEMORY       1
#define MBS_ERR_INVALID_VECTOR    2
#define MBS_ERR_INVALID_OBJ       3
#define MBS_ERR_INVALID_VAR_ADDR  4
#define MBS_ERR_NO_LINKS          5
#define MBS_ERR_BAD_STREAM        6
#define MBS_ERR_MTX_CORRUPTED     7
#define MBS_ERR_NO_ELEMENTS       8
#define MBS_ERR_CFG_MEMORY        9
#define MBS_ERR_UNDEFINED         11

#define MBS_LEX_NONE              0
#define MBS_LEX_BR                1
#define MBS_LEX_VAR               2
#define MBS_LEX_CONST             3
#define MBS_LEX_PLUS              4
#define MBS_LEX_MINUS             5
#define MBS_LEX_UNI_MINUS         6
#define MBS_LEX_MPY               7
#define MBS_LEX_DIV               8
#define MBS_LEX_MOD               9
#define MBS_LEX_EQ                10
#define MBS_LEX_NEQ               11
#define MBS_LEX_GT                12
#define MBS_LEX_GE                13			
#define MBS_LEX_LT                14
#define MBS_LEX_LE                15
#define MBS_LEX_LAND              16
#define MBS_LEX_LOR               17
#define MBS_LEX_LNOT              18
#define MBS_LEX_BAND              19
#define MBS_LEX_BOR               20
#define MBS_LEX_BXOR              21
#define MBS_LEX_BINV              22
#define MBS_LEX_ROL               23
#define MBS_LEX_ROR               24

struct MBS_OBJID {
	short objCrc;
	short nameCrc;
	short dateCrc;
};

struct MBS_OBJECT {
	struct MBS_OBJID id;
	short streamNum;
};

struct MBS_LINK {
	short inObj;
	short outObj;
	short pinMask;
};

typedef short MBS_DFT;

union MBS_MON_TRIGGER {
  unsigned short all;
  struct MBS_MON_TRIGGER_BITS {
    unsigned short mode:2;
	  unsigned short edge:1;
	  unsigned short isFloat:1;
	  unsigned short isSync:1;
	  unsigned short rsvd:11;
  } bit;
};

struct MBS_CONTROL {
	short enable;
	short error;
	struct MBS_OBJECT object;
	short memInfo;
	short cpuLoad;
	short appVersion;
	short krnlVersion;
	short krnlStatus;
	short monMode;
	short monScope;
	short monMaxSize;
	short monChanSize;
	short monChanCount;
	short monChans[6];
	short memCmd;
	short memStatus;
	union MBS_MON_TRIGGER trigger;
	short monTriggerSource;
	long  monTriggerLevel;
	long  monTriggerData;
};

struct MBS_MTX_CFG {
	short crc;
	short glCount;
	long  dataSize;
	long  objSize;
	long  linkSize;
	long  dftSize;
};

struct MBS_BLK_CFG {
	struct MBS_OBJID id;
	short objSize;
	short inCount;
	short outCount;
	short parType[2];
	short parMode[2];
	long  initAddr;
	long  execAddr;
};

struct MBS_KERNEL {
	struct MBS_CONTROL control;
	short    dataCount;
	short    glCount;
	short    objCount;
	short    vecCount;
	long     heapSize;
	long     cfgSize;
	long     memAddr;
	long     monAddr;
	short    memCmd;
	short    elemIndex;
	short    varIndex;
	short    pjtDataSize;
	short    pjtDataAddr;
	short    pjtDataLen;
	void    *pjtData;
	void    *sysData;
  MBS_DFT *dftData;
	void    *cfg;
	void    *blocks;
	void    *menuCfg;
	struct MBS_OBJECT *objects;
	struct MBS_LINK   *links;
	MBS_DFT   	      *dft;
	long	            **glData;
  #ifdef __BORLANDC__
	short _FUNC_CALL_ (*OnGetCommCfg)(void*);
	short _FUNC_CALL_ (*OnGetUserCfg)(void*);
  #else
	short (*OnGetCommCfg)(void*);
	short (*OnGetUserCfg)(void*);
  #endif
  #ifdef __BORLANDC__
  void  _FUNC_CALL_ (*OnExecute)(struct MBS_KERNEL*);
  #endif
};

typedef struct MBS_KERNEL *MBS_Handle;

void  _FUNC_CALL_ MBS_init(MBS_Handle);
void  _FUNC_CALL_ MBS_isr_execute(MBS_Handle, short);
void  _FUNC_CALL_ MBS_mon_execute(MBS_Handle);
short _FUNC_CALL_ MBS_getcrc(short *, long);
long  _FUNC_CALL_ MBS_getGlobalData(MBS_Handle, short addr);
char  _FUNC_CALL_ MBS_setGlobalData(MBS_Handle, short addr, long data, char memFlag);
long  _FUNC_CALL_ MBS_getProjectData(MBS_Handle, short addr, char len);
char  _FUNC_CALL_ MBS_setProjectData(MBS_Handle, short addr, long data, char memFlag, char len);
short _FUNC_CALL_ MBS_getMemStatus(MBS_Handle);

#ifdef __cplusplus
}
#endif // extern "C"

#ifdef __BORLANDC__
#pragma pack(pop)
#endif

#endif /* __MBS_KERNEL__*/





