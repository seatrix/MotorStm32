//蜂鸣器 0不响 1响
void Beep(u8 val);
//初始化Beep
void init_Beep(void);
//设置鸣叫 间隔 毫秒 时长 秒
void StartBeep(u16 BeepIntver,u16 BeepTime);
//停止beep
void StopBeep(void);

//鸣叫完成
u8 BeepVoered(void);

//鸣叫翻转
void BeepFlip(void);
//LED翻转
void LedFlip(void);
//LEd闪
void Led(u8 val);