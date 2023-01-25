
#ifndef _MENU2X_
#define _MENU2X_

#define MENU2X_STATE_START      0		// Start display
#define MENU2X_STATE_SEL_GR     1		// Select group
#define MENU2X_STATE_SEL_PAR		2		// Select parameter
#define MENU2X_STATE_EDIT_PAR	3		// Edit parameter

#define MENU2X_TYPE_DEC			1		// Decimal value
#define MENU2X_TYPE_STR			2		// String list value
#define MENU2X_TYPE_UNION			3		// Union list value
#define MENU2X_TYPE_TIME			4		// Time value
#define MENU2X_TYPE_DATE			5		// Date value
#define MENU2X_TYPE_BIN			6		// Binary value
#define MENU2X_TYPE_HEX			7		// Hexadecimal value

#define MENU2X_KEY_UP         	4		// Up
#define MENU2X_KEY_LEFT       	5		// Left
#define MENU2X_KEY_RIGHT      	6		// Right
#define MENU2X_KEY_DOWN       	7		// Down
#define MENU2X_KEY_ESCAPE     	8		// Escape
#define MENU2X_KEY_ENTER      	9		// Enter

#define MENU2X_READ_ONLY			0x0010
#define MENU2X_MEMORY				0x0020
#define MENU2X_PREC(A)				((unsigned int)((A) & 0x07) << 6)
#define MENU2X_FORMAT(A)			((unsigned int)((A) & 0x1F) << 9)
#define MENU2X_FIXED				0x4000
#define MENU2X_LEN					0x8000
 
typedef union {
	unsigned int all;
	struct {
		unsigned int Type:4;				// 0:3   Type of parameter
		unsigned int ReadOnly:1;		// 4     Read only property
		unsigned int Memory:1;			// 5     Store in NVM
		unsigned int Precision:3;		// 6     Precision of parameter
		unsigned int Format:5;			// 9:13  Value format
		unsigned int Fixed:1;			// 14		Fixed project parameter
		unsigned int Len:1;				// 15		Length of data (0 - short, 1 - long)
	} bit;
} MENU2X_PARAM_PROP;
 
typedef struct {
	MENU2X_PARAM_PROP   Cfg;				// Configuration properties
	unsigned int   		Addr;				// Global address
	long           		Min;				// Minimum value
	long           		Max;				// Maximum value
} MENU2X_PARAM_CFG;

typedef struct {
	char						HiString[16];	// First string
	char						LoString[16];	// Second string
	unsigned int			Index;			// First parameter index
	unsigned int			Count;			// Number of parameters
} MENU2X_GROUP;

typedef struct {
	char						Name[16];		// Name of parameter
	char						Unit[4];			// Measure unit
	MENU2X_PARAM_CFG		Cfg;				// Configuration
} MENU2X_PARAM;

typedef struct {
	char                Name[16];			// Name of parameter
	MENU2X_PARAM_PROP   Cfg;				// Configuration properties
	unsigned int   		Addr;				// Global address
} MENU2X_SIMPLE_PARAM;

typedef struct {
	long 						Data;				// Data
	char						Text[16];		// Text
} MENU2X_STRING;

typedef struct {
  const MENU2X_GROUP	*Groups;
  const MENU2X_PARAM	*Params;
  const MENU2X_STRING	*Strings;
  unsigned int			GroupCount;
} MENU2X_CFG;

#define Menu2x_Config        ((const MENU2X_CFG *)(Kernel.menuCfg))
#define Menu_Simple_Config   ((const MENU2X_SIMPLE_PARAM *)(Kernel.menuCfg))

#endif




