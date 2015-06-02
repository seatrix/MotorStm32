
#ifndef __serial_H
#define __serial_H
#include "GxdQueque.h"

#define  revbufflen2 512   //缓冲区长度，保持与c文件中的一致
extern volatile unsigned char revbuff2[revbufflen2];// 接收数据缓冲

#define  revbufflen1 1024   //缓冲区长度，保持与c文件中的一致
extern volatile unsigned char revbuff1[revbufflen1];// 接收数据缓冲

//serial1队列
extern Quque QuqueSerial1;

//serial2队列
extern Quque QuqueSerial2;

void init_serial(void);//串口初始化

extern volatile unsigned char comstate1;//串口1状态
extern volatile unsigned char comstate2;//串口2状态

#define Com_NoData       0   //无数据
#define Com_RevData      2 	//接收正确


//发送二进制,设备 1 2
void ComSndBytes(  char *str,int len,unsigned char Dev);
//发送字符串,设备 1 2
void ComPrintString(  char *str,unsigned char Dev);

//发送字符
void sndcharDev(unsigned char singlechar,unsigned char Dev);
//关闭串口
void Close_serial(u8 dev);



#endif


