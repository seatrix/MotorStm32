
#ifndef __GXDDebug_H
#define __GXDDebug_H



//�������
extern int DebugPrint(  char *sendstring,...);


//����ģʽ ʹ��
#define DebugPrintEnable

#ifndef  DebugPrintEnable
#define DebugPrint(str,...)
#endif

#define array_sizeof(a) (sizeof(a) / sizeof(a[0]))
#endif


