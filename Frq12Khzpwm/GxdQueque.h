#ifndef __GxdQueque_H
#define __GxdQueque_H


typedef struct
{
    u16 QuqueMAXSIZE;
    unsigned char * QuqueData;//Ԫ��ָ��
    u16 front,rear;
} Quque; //�����ͷ



//��ʼ��
void initQue(Quque *q, unsigned char * _QuqueData,u16 _QuqueMAXSIZE); //��ʼ��
//��������
unsigned char isFull(Quque *q);
//���п�?
unsigned char  isEmpty(Quque *q);
//��ȡ����
unsigned char  deleteQue(Quque *  q);
//�������
unsigned char  insertQue(Quque  *q,unsigned char elem);
//��ն���
unsigned char  ClearQue(Quque  *q);
#endif


