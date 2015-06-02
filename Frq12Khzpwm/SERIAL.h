
#ifndef __serial_H
#define __serial_H
#include "GxdQueque.h"

#define  revbufflen2 512   //���������ȣ�������c�ļ��е�һ��
extern volatile unsigned char revbuff2[revbufflen2];// �������ݻ���

#define  revbufflen1 1024   //���������ȣ�������c�ļ��е�һ��
extern volatile unsigned char revbuff1[revbufflen1];// �������ݻ���

//serial1����
extern Quque QuqueSerial1;

//serial2����
extern Quque QuqueSerial2;

void init_serial(void);//���ڳ�ʼ��

extern volatile unsigned char comstate1;//����1״̬
extern volatile unsigned char comstate2;//����2״̬

#define Com_NoData       0   //������
#define Com_RevData      2 	//������ȷ


//���Ͷ�����,�豸 1 2
void ComSndBytes(  char *str,int len,unsigned char Dev);
//�����ַ���,�豸 1 2
void ComPrintString(  char *str,unsigned char Dev);

//�����ַ�
void sndcharDev(unsigned char singlechar,unsigned char Dev);
//�رմ���
void Close_serial(u8 dev);



#endif


