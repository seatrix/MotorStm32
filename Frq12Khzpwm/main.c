#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "serial.h"
#include "delay.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GXDDebug.h"
#include "UserTimer.h"
#include "TimerDevc.h"
#include "sysbeep.h"

#include "HexString.h"
#include "Weightdo.h"
#include "TM7711.h"
#include "Wmeasure.h"
/*
出水报警



*/


extern int comrev;

void Delay(u32 count)
{
    u32 i=0;
    for(; i<count; i++);
}


#define  ExtOSC 1

void RCC_Configuration(void)
{
    RCC_DeInit();                                    //将外设RCC寄存器重设为缺省值

#ifdef ExtOSC

    RCC_HSEConfig(RCC_HSE_ON);                    //开启外部高速晶振（HSE）

    //等待HSE起振
    if( RCC_WaitForHSEStartUp() == SUCCESS)               //若成功起振，（下面为系统总线时钟设置）
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //使能FLASH预取指缓存

        //FLASH_SetLatency(FLASH_Latency_0);   //设置FLASH存储器延时时钟周期数(根据不同的系统时钟选取不同的值)
        //RCC_HCLKConfig(RCC_SYSCLK_Div1);   //设置AHB时钟=72 MHz
        //RCC_PCLK2Config(RCC_HCLK_Div2);   //设置APB1时钟=36 MHz(APB1时钟最大值)
        //RCC_PCLK1Config(RCC_HCLK_Div1);   //设置APB2时钟=72 MHz
        //4*8=32Mhz
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4); //PLL必须在其激活前完成配置（设置PLL时钟源及倍频系数）
        RCC_PLLCmd(ENABLE);

        // while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        // while(RCC_GetSYSCLKSource() != 0x08);

    }
    //DebugPrint("Use ExtOSC PLL \r\n",);
#else

    /*  使用内部RC晶振 */
    RCC_HSICmd(ENABLE);//使能内部高速晶振 ;
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);//选择内部高速时钟作为系统时钟SYSCLOCK=8MHZ
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//选择HCLK时钟源为系统时钟SYYSCLOCK
    //DebugPrint("Use IntOSC\r\n");
#endif


    SystemCoreClockUpdate(); //更新时钟必须调用
}


void  init_GPIO(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //使能PA,PB端口时钟
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;          //LED0-->PA.1 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //IO 口速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIOA.1


}

unsigned short tempe=0;
int main(void)
{
    RCC_Configuration();
    init_GPIO();
    delay_init();
    NVIC_cfg();//配置中断
    MBRTU_ini(0x01);
    //Tim3初始化
    init_TIM3();
    wd_init();
	  TM7711_init();
    init_serial();//串口初始化
//    TIM3_Start(0);

MeasurePoll_init();

    while(1)
    {
        MBRTUPoll();
			MeasurePoll();
    }
}








