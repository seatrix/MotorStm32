//|���ݰ�ͷ |���ݰ���|���ݰ�����|У���|
//|0xAA 0x55|  0xHH  |0xXX......|0xHH  |

#include "stm32f10x.h"
#include "delay.h"
#include "serial.h"
#include "GxdQueque.h"
#include "GXDmodbus.h"
//#define  revbufflen 16   //����������
volatile unsigned char revbuff2[revbufflen2];// �������ݻ���
volatile unsigned char revbuff1[revbufflen1];// �������ݻ���

volatile  unsigned char comstate1;//����1״̬
volatile unsigned char comstate2;//����2״̬
//ʹ��
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
        //�ȶϵ�
        // GPIO_ResetBits(GPIOC,GPIO_Pin_2);
    }

}
void init_Max3222(void)//232��ʼ��
{
    //Ӳ����ʼ��
    GPIO_InitTypeDef GPIO_InitStructure;
//����ʱ��ʹ�ܣ�GPIOʱ��ʹ�ܣ�����ʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);      //ʹ��
// GPIO�˿�ģʽ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��
//�ȶϵ�
    GPIO_ResetBits(GPIOC,GPIO_Pin_2);

}

//serial1����
Quque QuqueSerial1;
//����1
void USART1_IRQHandler(void)
{
    static unsigned char SBUF;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET  )
    {
        USART_ClearITPendingBit(USART1,  USART_IT_RXNE);          //����жϱ�־
        SBUF=USART_ReceiveData(USART1);//  //��ȡ���յ�������
//����״̬��,�����ж��е���
  IRQ_xMBRTUReceiveFSM(SBUF );
        comstate1=Com_RevData;//����1״̬

    }
    //���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART1,USART_FLAG_ORE);  //�� SR
        USART_ReceiveData(USART1);       //�� DR
    }
}

//serial2����
Quque QuqueSerial2;
//����2
void USART2_IRQHandler(void)
{
    static unsigned char SBUF;

    if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET  )
    {
        USART_ClearITPendingBit(USART2,  USART_IT_RXNE);          //����жϱ�־
        SBUF=USART_ReceiveData(USART2);//  //��ȡ���յ�������
        comstate2=Com_RevData;//����2״̬
    }
    //���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ��� �������������жϵ�����
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE);  //�� SR
        USART_ReceiveData(USART2);       //�� DR
    }
}

//�����ַ�
void sndcharDev(unsigned char singlechar,unsigned char Dev)
{

    switch(Dev)
    {
    case 1:

//�ȵȴ����ͼĴ����� �ٷ���
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!=SET);
        USART_SendData(USART1,singlechar);
        break;

    case 2:
        //�ȵȴ����ͼĴ����� �ٷ���
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!=SET);
        USART_SendData(USART2,singlechar);
        break;

    }

}
//���Ͷ�����,�豸 1 2
void ComSndBytes(  char *str,int len,unsigned char Dev)
{
    //ʹ��
    Max3222Enable(1);
    for(; len>0; len--)
    {
        sndcharDev(*str++,Dev);

    }
    //ʹ��
    Max3222Enable(0);

}

//�����ַ���,�豸 1 2
void ComPrintString(  char *sendstring,unsigned char Dev)
{

    //ʹ��
    Max3222Enable(1);
    while(*sendstring!=0)
    {
        sndcharDev(*sendstring++,Dev);
    }
    //ʹ��
    Max3222Enable(0);
}





void init_serial2(void)
{
    //Ӳ����ʼ��
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
//�ٴ���ʱ��ʹ�ܣ�GPIOʱ��ʹ�ܣ�����ʱ��ʹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);      //ʹ��USART1,GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      //ʹ��USART1,GPIOAʱ��
//�ڴ��ڸ�λ
    USART_DeInit(USART2);                                                                 //��λ����1
//��GPIO�˿�ģʽ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                                    //ISART1_TX PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);                     //��ʼ��GPIOA.9

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                                  //USART1_RX  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                         //��ʼ��GPIOA.10
//�ܴ��ڲ�����ʼ��
    USART_InitStructure.USART_BaudRate = 9600;                              //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�Ϊ8λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                      //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl
        = USART_HardwareFlowControl_None;          //��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure);                    //��ʼ������
//ʹ�ܽ���
//�ݳ�ʼ��NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;                //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                    //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //IRQ ͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                                                          //�ж����ȼ���ʼ��
//�ݿ����ж�
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         //�����ж�




//��ʹ�ܴ���
    USART_Cmd(USART2, ENABLE);                                                      //ʹ�ܴ���


}
void init_serial1(void)//���ڳ�ʼ��
{


    //Ӳ����ʼ��
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
//�ٴ���ʱ��ʹ�ܣ�GPIOʱ��ʹ�ܣ�����ʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|
                           RCC_APB2Periph_GPIOA, ENABLE);      //ʹ��USART1,GPIOAʱ��
//�ڴ��ڸ�λ
    USART_DeInit(USART1);                                                                 //��λ����1
//��GPIO�˿�ģʽ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                    //ISART1_TX PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);                     //��ʼ��GPIOA.9

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                  //USART1_RX  PA.10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                         //��ʼ��GPIOA.10
//�ܴ��ڲ�����ʼ��
    USART_InitStructure.USART_BaudRate = 9600;                              //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�Ϊ8λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                      //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl
        = USART_HardwareFlowControl_None;          //��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure);                    //��ʼ������
//ʹ�ܽ���
//�ݳ�ʼ��NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;                //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                    //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //IRQ ͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                                                          //�ж����ȼ���ʼ��
//�ݿ����ж�
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         //�����ж�




//��ʹ�ܴ���
    USART_Cmd(USART1, ENABLE);                                                      //ʹ�ܴ���



}

//�رմ���
void Close_serial(u8 dev)
{
    if(dev==1)
    {
  

    } else if(dev==2)
    {


    }


}


void init_serialBuf(void)//2���ڳ�ʼ��
{

    comstate1=Com_NoData;//����1״̬
    comstate2=Com_NoData;//����2״̬

}
void init_serial(void)//���ڳ�ʼ��
{
    init_serialBuf();
    init_serial1( );//���ڳ�ʼ��
    init_serial2( );//���ڳ�ʼ��
    init_Max3222();//232��ʼ��
	Max3222Enable(1);




}









