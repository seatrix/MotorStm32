/*
名称:用户定时器
By: gongxd@126.com
Date:2008.12.5	20:35
*/
#ifndef __UserTimer_H
#define __UserTimer_H
#include "sys.h"
//#include "UserTimer.h"
//定时器个数
#define	 UserTimer_MAX_Timer  8
//======================================================//

//按键扫描时钟
#define  UserTimer_key 0
//蜂鸣器
#define  UserTimer_beepIntver 1
#define  UserTimer_beepLength 2

//定位定时器
#define  UserTimer_Location 3

//水深定时器
#define  UserTimer_WaterDeep 4

//秒定时器
#define  UserTimer_Second 5

//分钟定时器
#define  UserTimer_munite 6
//=====================================================//

//定时器中断间隔单位ms
#define	 UserTimer_Tick 50

typedef struct  My_Timer
{
    u32 Interval;
    u32 Interval_Org;
    u8 Enabled;
    u8 EventON;//事件用
    u8 TimeOut;//查询用
//unsigned char TimerEvent;
} Timer1;

#ifdef   _UserTimer_h_slef
volatile Timer1 Timer[UserTimer_MAX_Timer];
#else
extern volatile Timer1 Timer[UserTimer_MAX_Timer];
#endif

/*====================================使用说明=======================================*/
//定时器初始化
void init_Timer(void );
//定时器刷新函数放置于定时器中断内，一定要设置定时器中断间隔
void Timer_Refresh(void );
//时钟运行 放置于Main大循环中
void Timer_RUN(void );
//秒定时 ID 时间  秒
void SetTimerSecond( u8 nIDEvent, u32 nElapse);
//设置定时器 ID 时间 毫秒
void SetTimer( u8 nIDEvent, u32 nElapse);
//销毁定时器
void KillTimer(u8 nIDEvent);
//外部实现 时钟事件
extern void OnTimer(u8 nIDEvent);
//查询方式定时器到时间
u8 Timer_TimeOut(u8 nIDEvent);

//时钟事件
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

