/*
����:�û���ʱ��
By: gongxd@126.com
Date:2008.12.5	20:35
*/
#ifndef __UserTimer_H
#define __UserTimer_H
#include "sys.h"
//#include "UserTimer.h"
//��ʱ������
#define	 UserTimer_MAX_Timer  8
//======================================================//

//����ɨ��ʱ��
#define  UserTimer_key 0
//������
#define  UserTimer_beepIntver 1
#define  UserTimer_beepLength 2

//��λ��ʱ��
#define  UserTimer_Location 3

//ˮ�ʱ��
#define  UserTimer_WaterDeep 4

//�붨ʱ��
#define  UserTimer_Second 5

//���Ӷ�ʱ��
#define  UserTimer_munite 6
//=====================================================//

//��ʱ���жϼ����λms
#define	 UserTimer_Tick 50

typedef struct  My_Timer
{
    u32 Interval;
    u32 Interval_Org;
    u8 Enabled;
    u8 EventON;//�¼���
    u8 TimeOut;//��ѯ��
//unsigned char TimerEvent;
} Timer1;

#ifdef   _UserTimer_h_slef
volatile Timer1 Timer[UserTimer_MAX_Timer];
#else
extern volatile Timer1 Timer[UserTimer_MAX_Timer];
#endif

/*====================================ʹ��˵��=======================================*/
//��ʱ����ʼ��
void init_Timer(void );
//��ʱ��ˢ�º��������ڶ�ʱ���ж��ڣ�һ��Ҫ���ö�ʱ���жϼ��
void Timer_Refresh(void );
//ʱ������ ������Main��ѭ����
void Timer_RUN(void );
//�붨ʱ ID ʱ��  ��
void SetTimerSecond( u8 nIDEvent, u32 nElapse);
//���ö�ʱ�� ID ʱ�� ����
void SetTimer( u8 nIDEvent, u32 nElapse);
//���ٶ�ʱ��
void KillTimer(u8 nIDEvent);
//�ⲿʵ�� ʱ���¼�
extern void OnTimer(u8 nIDEvent);
//��ѯ��ʽ��ʱ����ʱ��
u8 Timer_TimeOut(u8 nIDEvent);

//ʱ���¼�
/*
void OnTimer(unsigned char nIDEvent)
{

switch(nIDEvent)
{

case 0:

   Timer1Proc();

   break;

case 1:

   Timer2Proc();

   break;

}

}
*/

#endif

