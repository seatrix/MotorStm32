void vMBPortTimersDisable();
void vMBPortTimersEnable();
void MBCallback();
void MBRTUSendChar(unsigned char snd);
//����,�Ĵ������Ĵ�������
void Buf2Regster(unsigned char *buf,unsigned char StartRegaddr,unsigned char Reglength);
//����,�Ĵ������Ĵ�������
void  Regster2buf(unsigned char *buf,unsigned char StartRegaddr,unsigned char Reglength);

//�����ⲿ����
unsigned short Callback_HoldRegRead(unsigned char Regaddr);
void Callback_HoldRegWrite(unsigned char Regaddr,unsigned short RegVal);
//�Ĵ����޸�
extern char RegsterModfied;