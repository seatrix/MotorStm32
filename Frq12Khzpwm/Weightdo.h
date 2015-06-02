#ifndef __Weightdo_h
#define __Weightdo_h



void wd_init();



typedef struct
{
    long Wval;
    unsigned long ADval;
    unsigned long ZeroADval;
    unsigned long FullADval;
    long FullWval;
    unsigned short BadeRate;
    unsigned short AutoZero;	//0検強
    unsigned short AutoValfudong;	//val検強
    unsigned char SlaveAddr;
    unsigned char SumTimes;
    unsigned char OutInterval;

} WeightParmentT;

// WeightParment.Wval
// WeightParment.ADval
// WeightParment.ZeroADval
// WeightParment.FullADval
// WeightParment.FullWval
// WeightParment.BadeRate
// WeightParment.AutoZero
// WeightParment.AutoValfudong
// WeightParment.SlaveAddr
// WeightParment.SumTimes
// WeightParment.OutInterval

extern WeightParmentT WeightParment;

#endif
