/* TM7711.c �����ļ�*/
#include "TM7711.h"
#include "delay.h" //��ʱ�ӳ���
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include <stdlib.h>

#define SET_SCK_L()   GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define SET_SCK_H()   GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define READ_PORT()   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define delay_1us()  delay_us(1)

void TM7711_init()
{
    //Ӳ����ʼ��
    GPIO_InitTypeDef GPIO_InitStructure;
//����ʱ��ʹ�ܣ�GPIOʱ��ʹ�ܣ�����ʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);      //ʹ��IOʱ��
// GPIO�˿�ģʽ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��IO

    GPIO_ResetBits(GPIOC,GPIO_Pin_4);

    // GPIO�˿�ģʽ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��IO


}
unsigned long Read_TM7711(unsigned char next_select)
{
    unsigned char i = 0;
    unsigned long data_temp = 0;
    for(i = 0; i < 24; i++)
    {
        SET_SCK_H(); //��global.h �ļ��ж��壬��SCK ������ߵ�ƽ
        data_temp <<= 1;
        delay_us(5); //��ʱ5 ��΢�룬���ݲ�ͬ��MCU �Զ���˺���
        if(READ_PORT()) //�ж�DOUT �Ƿ�Ϊ�ߵ�ƽ
            data_temp |= 1;
        SET_SCK_L();//��global.h �ļ��ж��壬��SCK ������͵�ƽ
    }
    switch(next_select) //ȷ����һ�����ݸ����ʻ����л�ͨ��
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
    //return(data_temp); //���ش�TM7711 �ж���������
    return rand()%20000+627192;
}