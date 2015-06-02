typedef char    BOOL;

typedef unsigned char UCHAR;
typedef char    CHAR;

typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;


//接收状态机,串口中断中调用
void IRQ_xMBRTUReceiveFSM(char ucByte );
void IRQ_xMBRTUTimerT35Expired();
void MBRTUSend(unsigned char *pucFrame, unsigned char usLength );
void MBRTUPoll();
 
void MBRTU_ini(unsigned char addr);
unsigned short usMBCRC16( unsigned char * pucFrame,unsigned char usLen );


extern   unsigned char    MBSlaveAddr;
extern volatile unsigned char  ucRTUTxBuf[];
extern volatile unsigned char  ucRTUBuf[];
extern  volatile unsigned char usRcvBufferPos;