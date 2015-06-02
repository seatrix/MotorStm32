#include "stm32f10x.h"
#include "UserTimer.h"
#include "GXDmodbus.h"
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为8M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void init_TIM3(void)//Tim3初始化
{
    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //①时钟TIM3使能



//定时器TIM3初始化 Tout= ((arr+1)*(psc+1))/Tclk；//采样为20hz
    TIM_TimeBaseStructure.TIM_Period = 400-1;     //设置自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =4000-1;  //设置时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //TIM向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                   //②初始化TIM3
      
    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;               //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;               //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      //IRQ 通道被使能
    NVIC_Init(&NVIC_InitStructure);                                                 //④初始化NVIC寄存器
    TIM_Cmd(TIM3,DISABLE);

    //⑤使能TIM3

}

//0 禁止 1启动
void TIM3_Start(unsigned char EnableTIM)
{
    if(EnableTIM==1)
    {
        TIM_Cmd(TIM3,ENABLE);
			    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );                         //③允许更新中断

    }
    else
    {
        TIM_Cmd(TIM3,DISABLE);

    }
}
unsigned char LED1=0;
//定时器3中断服务程序⑥
void TIM3_IRQHandler(void)      //TIM3中断
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查TIM3更新中断发生与否
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update    ); //清除TIM3更新中断标志
IRQ_xMBRTUTimerT35Expired();


    }
}