//������ 0���� 1��
void Beep(u8 val);
//��ʼ��Beep
void init_Beep(void);
//�������� ��� ���� ʱ�� ��
void StartBeep(u16 BeepIntver,u16 BeepTime);
//ֹͣbeep
void StopBeep(void);

//�������
u8 BeepVoered(void);

//���з�ת
void BeepFlip(void);
//LED��ת
void LedFlip(void);
//LEd��
void Led(u8 val);