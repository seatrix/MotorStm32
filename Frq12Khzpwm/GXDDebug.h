
#ifndef __GXDDebug_H
#define __GXDDebug_H



//调试输出
extern int DebugPrint(  char *sendstring,...);


//调试模式 使能
#define DebugPrintEnable

#ifndef  DebugPrintEnable
#define DebugPrint(str,...)
#endif

#define array_sizeof(a) (sizeof(a) / sizeof(a[0]))
#endif


