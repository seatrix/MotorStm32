#ifndef __GxdQueque_H
#define __GxdQueque_H


typedef struct
{
    u16 QuqueMAXSIZE;
    unsigned char * QuqueData;//元素指针
    u16 front,rear;
} Quque; //定义队头



//初始化
void initQue(Quque *q, unsigned char * _QuqueData,u16 _QuqueMAXSIZE); //初始化
//队列满？
unsigned char isFull(Quque *q);
//队列空?
unsigned char  isEmpty(Quque *q);
//读取队列
unsigned char  deleteQue(Quque *  q);
//插入队列
unsigned char  insertQue(Quque  *q,unsigned char elem);
//清空队列
unsigned char  ClearQue(Quque  *q);
#endif


