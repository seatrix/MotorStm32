#include "stm32f10x.h"
#include "UserTimer.h"
#include "GXDmodbus.h"
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ8M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void init_TIM3(void)//Tim3��ʼ��
{
    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //��ʱ��TIM3ʹ��



//��ʱ��TIM3��ʼ�� Tout= ((arr+1)*(psc+1))/Tclk��//����Ϊ20hz
    TIM_TimeBaseStructure.TIM_Period = 400-1;     //�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =4000-1;  //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //TIM���ϼ���
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                   //�ڳ�ʼ��TIM3
      
    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;               //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;               //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;      //IRQ ͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);                                                 //�ܳ�ʼ��NVIC�Ĵ���
    TIM_Cmd(TIM3,DISABLE);

    //��ʹ��TIM3

}

//0 ��ֹ 1����
void TIM3_Start(unsigned char EnableTIM)
{
    if(EnableTIM==1)
    {
        TIM_Cmd(TIM3,ENABLE);
			    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );                         //����������ж�

    }
    else
    {
        TIM_Cmd(TIM3,DISABLE);

    }
}
unsigned char LED1=0;
//��ʱ��3�жϷ�������
void TIM3_IRQHandler(void)      //TIM3�ж�
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���TIM3�����жϷ������
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update    ); //���TIM3�����жϱ�־
IRQ_xMBRTUTimerT35Expired();


    }
}