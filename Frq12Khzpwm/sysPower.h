
#ifndef __syspower_H
#define __syspower_H

//��Դ
typedef struct {
    u32 TotalTime;//��ʱ�䵥λ����
    u32 BDTime;	//����ʱ�䵥λ����
    u8   BDOn;//��������
    u8  Timesave;//ÿ��1Сʱ����һ�����ݣ��ػ�Ҳ����
    float sysvolt;//ϵͳ��ѹ

// 	//��λСʱ
// char TotalTimeChar[]="|0000.00";
// char BDTimeChar[]="|0000.00";
} Power_Struct;

extern Power_Struct PowerClca;//����ͳ��
//��ʱ���һ����
void TotalTimeInc(void );
//����ʱ���һ����
void BDTimeInc(void );



//��ʼ����Դ
void init_Power(void);
//�ϵ�
void Power_on(void);
//�ϵ�
void Power_off(void);

//����ϵͳ��ѹ
void SysPowerleveupdate(u16 _adc);
#endif
