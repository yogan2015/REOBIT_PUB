
#ifndef STRUTILS_
#define STRUTILS_

#ifndef _FUNC_CALL_
#ifndef __BORLANDC__
#define _FUNC_CALL_
#else
#define _FUNC_CALL_ __stdcall
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

void _FUNC_CALL_ charToStr(void *str, char c, short pos);
char _FUNC_CALL_ strToChar(void *str, short pos);
void _FUNC_CALL_ copyStr(void *str, char *src, short pos, short len);
void _FUNC_CALL_ decToStr(void *str, long value, short offset, short prec, short digits, char flag);
void _FUNC_CALL_ hexToStr(void *str, long value, short offset, short digits);
void _FUNC_CALL_ binToStr(void *str, long value, short offset, short digits);
void _FUNC_CALL_ timeToStr(void *str, short value, short offset);
void _FUNC_CALL_ dateToStr(void *str, short value, short offset);
void _FUNC_CALL_ decToStr4(void *str, short value);
void _FUNC_CALL_ hexToStr4(void *str, short value);
void _FUNC_CALL_ binToStr4(void *str, short value, char bit);
void _FUNC_CALL_ timeToStr4(void *str, short value);
void _FUNC_CALL_ dateToStr4(void *str, short value, char flag);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* STRUTILS_ */ 

