_estack = 0x20005000;

MEMORY
{
	RAM (xrw)	:	ORIGIN = 0x20000000,	LENGTH = 20K
	FLASH1 (rx)	:	ORIGIN = 0x08000000,	LENGTH = 20K
	FLASH2 (rx)	:	ORIGIN = 0x08005000,	LENGTH = 20K
	FLASH3 (rx) :	ORIGIN = 0x0800A000,	LENGTH = 20K
	FLASH4 (rx)  :	ORIGIN = 0x0800F000,	LENGTH = 4K
}

SECTIONS
{
	.text	:
	{
		. = ALIGN(4);			/*	*/
		*(.vectors)				/*	*/
		KEEP(*(.vectors))		/*	*/
		*(.text)				/*	*/
	} >FLASH1
	
	.jopa	:
	{
		. = ALIGN(4);
		*(.jopa)
	} >FLASH1

	.rodata	:
	{
		. = ALIGN(4);
		*(.rodata)
	} >FLASH1


	.data :
	{
		. = ALIGN(4);
		*(.data)
	} >RAM AT> FLASH1
	
	.BRADIS	:
	{
		. = ALIGN(4);
		*(.bt_sin)
		KEEP(*(.bt_sin))
		*(.bt_cos)
		KEEP(*(.bt_cos))
		*(.bt_tg)
		KEEP(*(.bt_tg))
		*(.bt_ctg)
		KEEP(*(.bt_ctg))
		*(.BRADIS)
	} >FLASH3

	. = ALIGN(4);
	.bss :
	{
		*(.bss)
		*(COMMON)
		
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
	} >RAM

}