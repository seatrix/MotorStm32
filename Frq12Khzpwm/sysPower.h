
#ifndef __syspower_H
#define __syspower_H

//电源
typedef struct {
    u32 TotalTime;//总时间单位分钟
    u32 BDTime;	//北斗时间单位分钟
    u8   BDOn;//北斗开启
    u8  Timesave;//每隔1小时保存一次数据，关机也保存
    float sysvolt;//系统电压

// 	//单位小时
// char TotalTimeChar[]="|0000.00";
// char BDTimeChar[]="|0000.00";
} Power_Struct;

extern Power_Struct PowerClca;//电量统计
//总时间加一分钟
void TotalTimeInc(void );
//北斗时间加一分钟
void BDTimeInc(void );



//初始化电源
void init_Power(void);
//上电
void Power_on(void);
//断电
void Power_off(void);

//计算系统电压
void SysPowerleveupdate(u16 _adc);
#endif
