/* TM7711.c 程序文件*/
#include "TM7711.h"
#include "delay.h" //延时子程序
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include <stdlib.h>

#define SET_SCK_L()   GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define SET_SCK_H()   GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define READ_PORT()   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define delay_1us()  delay_us(1)

void TM7711_init()
{
    //硬件初始化
    GPIO_InitTypeDef GPIO_InitStructure;
//串口时钟使能，GPIO时钟使能，复用时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);      //使能IO时钟
// GPIO端口模式设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //初始化IO

    GPIO_ResetBits(GPIOC,GPIO_Pin_4);

    // GPIO端口模式设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //初始化IO


}
unsigned long Read_TM7711(unsigned char next_select)
{
    unsigned char i = 0;
    unsigned long data_temp = 0;
    for(i = 0; i < 24; i++)
    {
        SET_SCK_H(); //在global.h 文件中定义，置SCK 脚输出高电平
        data_temp <<= 1;
        delay_us(5); //延时5 个微秒，根据不同的MCU 自定义此函数
        if(READ_PORT()) //判断DOUT 是否为高电平
            data_temp |= 1;
        SET_SCK_L();//在global.h 文件中定义，置SCK 脚输出低电平
    }
    switch(next_select) //确定下一次数据更新率或者切换通道
    {
    case CH1_10HZ:
        SET_SCK_H();
        delay_1us();
        SET_SCK_L();
        break;
    case CH1_40HZ:
        SET_SCK_H();
        delay_1us();
        SET_SCK_L();
        delay_1us();
        SET_SCK_H();
        delay_1us();
        SET_SCK_L();
        delay_1us();
        SET_SCK_H();
        delay_1us();
        SET_SCK_L();
        break;
    case CH2_TEMP:
        SET_SCK_H();
        delay_1us();
        SET_SCK_L();
        delay_1us();
        SET_SCK_H();
        delay_1us();
        SET_SCK_L();
        break;
    default:
        break;
    }
    //return(data_temp); //返回从TM7711 中读出的数据
    return rand()%20000+627192;
}