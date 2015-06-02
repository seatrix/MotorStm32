void vMBPortTimersDisable();
void vMBPortTimersEnable();
void MBCallback();
void MBRTUSendChar(unsigned char snd);
//数组,寄存器，寄存器长度
void Buf2Regster(unsigned char *buf,unsigned char StartRegaddr,unsigned char Reglength);
//数组,寄存器，寄存器长度
void  Regster2buf(unsigned char *buf,unsigned char StartRegaddr,unsigned char Reglength);

//调用外部函数
unsigned short Callback_HoldRegRead(unsigned char Regaddr);
void Callback_HoldRegWrite(unsigned char Regaddr,unsigned short RegVal);
//寄存器修改
extern char RegsterModfied;