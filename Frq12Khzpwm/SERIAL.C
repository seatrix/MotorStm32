//|数据包头 |数据包长|数据包内容|校验和|
//|0xAA 0x55|  0xHH  |0xXX......|0xHH  |

#include "stm32f10x.h"
#include "delay.h"
#include "serial.h"
#include "GxdQueque.h"
#include "GXDmodbus.h"
//#define  revbufflen 16   //缓冲区长度
volatile unsigned char revbuff2[revbufflen2];// 接收数据缓冲
volatile unsigned char revbuff1[revbufflen1];// 接收数据缓冲

volatile  unsigned char comstate1;//串口1状态
volatile unsigned char comstate2;//串口2状态
//使能
void Max3222Enable(u8 val)
{
    if(val)
    {

        GPIO_SetBits(GPIOC,GPIO_Pin_2);
        delay_us(10);

    }
    else
    {
        delay_us(10);
        //先断电
        // GPIO_ResetBits(GPIOC,GPIO_Pin_2);
    }

}
void init_Max3222(void)//232初始化
{
    //硬件初始化
    GPIO_InitTypeDef GPIO_InitStructure;
//串口时钟使能，GPIO时钟使能，复用时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);      //使能
// GPIO端口模式设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //初始化
//先断电
    GPIO_ResetBits(GPIOC,GPIO_Pin_2);

}

//serial1队列
Quque QuqueSerial1;
//串口1
void USART1_IRQHandler(void)
{
    static unsigned char SBUF;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET  )
    {
        USART_ClearITPendingBit(USART1,  USART_IT_RXNE);          //清除中断标志
        SBUF=USART_ReceiveData(USART1);//  //读取接收到的数据
//接收状态机,串口中断中调用
  IRQ_xMBRTUReceiveFSM(SBUF );
        comstate1=Com_RevData;//串口1状态

    }
    //溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART1,USART_FLAG_ORE);  //读 SR
        USART_ReceiveData(USART1);       //读 DR
    }
}

//serial2队列
Quque QuqueSerial2;
//串口2
void USART2_IRQHandler(void)
{
    static unsigned char SBUF;

    if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET  )
    {
        USART_ClearITPendingBit(USART2,  USART_IT_RXNE);          //清除中断标志
        SBUF=USART_ReceiveData(USART2);//  //读取接收到的数据
        comstate2=Com_RevData;//串口2状态
    }
    //溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE);  //读 SR
        USART_ReceiveData(USART2);       //读 DR
    }
}

//发送字符
void sndcharDev(unsigned char singlechar,unsigned char Dev)
{

    switch(Dev)
    {
    case 1:

//先等待发送寄存器空 再发送
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!=SET);
        USART_SendData(USART1,singlechar);
        break;

    case 2:
        //先等待发送寄存器空 再发送
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!=SET);
        USART_SendData(USART2,singlechar);
        break;

    }

}
//发送二进制,设备 1 2
void ComSndBytes(  char *str,int len,unsigned char Dev)
{
    //使能
    Max3222Enable(1);
    for(; len>0; len--)
    {
        sndcharDev(*str++,Dev);

    }
    //使能
    Max3222Enable(0);

}

//发送字符串,设备 1 2
void ComPrintString(  char *sendstring,unsigned char Dev)
{

    //使能
    Max3222Enable(1);
    while(*sendstring!=0)
    {
        sndcharDev(*sendstring++,Dev);
    }
    //使能
    Max3222Enable(0);
}





void init_serial2(void)
{
    //硬件初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
//①串口时钟使能，GPIO时钟使能，复用时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);      //使能USART1,GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      //使能USART1,GPIOA时钟
//②串口复位
    USART_DeInit(USART2);                                                                 //复位串口1
//③GPIO端口模式设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                                    //ISART1_TX PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);                     //初始化GPIOA.9

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                                  //USART1_RX  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                         //初始化GPIOA.10
//④串口参数初始化
    USART_InitStructure.USART_BaudRate = 9600;                              //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                      //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl
        = USART_HardwareFlowControl_None;          //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
    USART_Init(USART2, &USART_InitStructure);                    //初始化串口
//使能接收
//⑤初始化NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;                //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                    //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //IRQ 通道使能
    NVIC_Init(&NVIC_InitStructure);                                                          //中断优先级初始化
//⑤开启中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         //开启中断




//⑥使能串口
    USART_Cmd(USART2, ENABLE);                                                      //使能串口


}
void init_serial1(void)//串口初始化
{


    //硬件初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
//①串口时钟使能，GPIO时钟使能，复用时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|
                           RCC_APB2Periph_GPIOA, ENABLE);      //使能USART1,GPIOA时钟
//②串口复位
    USART_DeInit(USART1);                                                                 //复位串口1
//③GPIO端口模式设置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                    //ISART1_TX PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);                     //初始化GPIOA.9

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                  //USART1_RX  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                         //初始化GPIOA.10
//④串口参数初始化
    USART_InitStructure.USART_BaudRate = 9600;                              //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                      //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl
        = USART_HardwareFlowControl_None;          //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
    USART_Init(USART1, &USART_InitStructure);                    //初始化串口
//使能接收
//⑤初始化NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;                //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                    //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //IRQ 通道使能
    NVIC_Init(&NVIC_InitStructure);                                                          //中断优先级初始化
//⑤开启中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         //开启中断




//⑥使能串口
    USART_Cmd(USART1, ENABLE);                                                      //使能串口



}

//关闭串口
void Close_serial(u8 dev)
{
    if(dev==1)
    {
  

    } else if(dev==2)
    {


    }


}


void init_serialBuf(void)//2串口初始化
{

    comstate1=Com_NoData;//串口1状态
    comstate2=Com_NoData;//串口2状态

}
void init_serial(void)//串口初始化
{
    init_serialBuf();
    init_serial1( );//串口初始化
    init_serial2( );//串口初始化
    init_Max3222();//232初始化
	Max3222Enable(1);




}










