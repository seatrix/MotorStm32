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
��ˮ����



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
    RCC_DeInit();                                    //������RCC�Ĵ�������Ϊȱʡֵ

#ifdef ExtOSC

    RCC_HSEConfig(RCC_HSE_ON);                    //�����ⲿ���پ���HSE��

    //�ȴ�HSE����
    if( RCC_WaitForHSEStartUp() == SUCCESS)               //���ɹ����񣬣�����Ϊϵͳ����ʱ�����ã�
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //ʹ��FLASHԤȡָ����

        //FLASH_SetLatency(FLASH_Latency_0);   //����FLASH�洢����ʱʱ��������(���ݲ�ͬ��ϵͳʱ��ѡȡ��ͬ��ֵ)
        //RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����AHBʱ��=72 MHz
        //RCC_PCLK2Config(RCC_HCLK_Div2);   //����APB1ʱ��=36 MHz(APB1ʱ�����ֵ)
        //RCC_PCLK1Config(RCC_HCLK_Div1);   //����APB2ʱ��=72 MHz
        //4*8=32Mhz
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4); //PLL�������伤��ǰ������ã�����PLLʱ��Դ����Ƶϵ����
        RCC_PLLCmd(ENABLE);

        // while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        // while(RCC_GetSYSCLKSource() != 0x08);

    }
    //DebugPrint("Use ExtOSC PLL \r\n",);
#else

    /*  ʹ���ڲ�RC���� */
    RCC_HSICmd(ENABLE);//ʹ���ڲ����پ��� ;
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);//ѡ���ڲ�����ʱ����Ϊϵͳʱ��SYSCLOCK=8MHZ
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//ѡ��HCLKʱ��ԴΪϵͳʱ��SYYSCLOCK
    //DebugPrint("Use IntOSC\r\n");
#endif


    SystemCoreClockUpdate(); //����ʱ�ӱ������
}


void  init_GPIO(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //ʹ��PA,PB�˿�ʱ��
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;          //LED0-->PA.1 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //IO ���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIOA.1


}

unsigned short tempe=0;
int main(void)
{
    RCC_Configuration();
    init_GPIO();
    delay_init();
    NVIC_cfg();//�����ж�
    MBRTU_ini(0x01);
    //Tim3��ʼ��
    init_TIM3();
    wd_init();
	  TM7711_init();
    init_serial();//���ڳ�ʼ��
//    TIM3_Start(0);

MeasurePoll_init();

    while(1)
    {
        MBRTUPoll();
			MeasurePoll();
    }
}








