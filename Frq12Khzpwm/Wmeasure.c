#include <math.h>
#include "GXDmodbusEx.h"
#include "Weightdo.h"
#include "TM7711.h"
#include "Wmeasure.h"

//启动转换
//char Event_ADConvert;
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
unsigned long ADConvertTime=0;
unsigned long WeightParmentOutInterval=0;
//========================================
float Ad2wetXishu;
unsigned char WeightParmentSumTimes;
long WeightParmentWval_Old;//wt long
long WeightParmentADval_avrage;//ad long
long WeightParmentZeroADval;//0 long
//========================================
__forceinline long Get_24Buma(unsigned long val)
{

    if((val & 0x800000)==0x800000)
    {
        val=~(val-1);
    }
    return (long)val;
}
//========================================
#define  AdvalLongSize (20)
long AdvalLong[AdvalLongSize];
char AdvalLongPos;
long ADfiltersum;
void Filter_init()
{char i;
	AdvalLongPos=0;

    for(i=0; i<AdvalLongSize; i++)
    {
        AdvalLong[i]=WeightParmentADval_avrage;
    }
		ADfiltersum=WeightParment.SumTimes*WeightParmentADval_avrage;
	  
}
 long ADfilter(long val)
{
    char i;
    char sumtimes;
    sumtimes=WeightParment.SumTimes<AdvalLongSize?WeightParment.SumTimes:AdvalLongSize;
	
    ADfiltersum-=AdvalLong[AdvalLongPos];//减去要丢掉的数据
    ADfiltersum+=val;//加上新数据;
    AdvalLong[AdvalLongPos++]=val;//存储新数据
    if(AdvalLongPos==sumtimes)  AdvalLongPos=0;



    return ADfiltersum/sumtimes;
}
//========================================
void caclAd2wetXishu()
{
    WeightParmentZeroADval=Get_24Buma(WeightParment.ZeroADval);
    //y1/(x1-x0)
    Ad2wetXishu=(float )WeightParment.FullWval/(float)(Get_24Buma(WeightParment.FullADval)-WeightParmentZeroADval);

}

__forceinline unsigned short AbSlong(long val)
{
    if(val<0) val=0-val;
    return (unsigned short)val;
}

//========================================
void MeasurePoll_init()
{

    WeightParmentOutInterval=0;
    WeightParmentSumTimes=0;
    WeightParmentWval_Old=0;
   
    caclAd2wetXishu();
		Filter_init();
}
void MeasurePoll()
{
    if(RegsterModfied==1)
    {
        //更新系数
        caclAd2wetXishu();
			Filter_init();
    }

    ADConvertTime++;
    if(ADConvertTime>500)
    {   //sample
        ADConvertTime=0;
        WeightParment.ADval=Read_TM7711(CH1_10HZ);
        //滑动滤波
        WeightParmentADval_avrage=ADfilter(Get_24Buma(WeightParment.ADval));
    }

    WeightParmentOutInterval++;
    if(WeightParmentOutInterval>5000)
    {
        WeightParmentOutInterval=0;

        WeightParment.Wval=(long)(Ad2wetXishu*(WeightParmentADval_avrage-WeightParmentZeroADval));
        //wave yizhi
        if(AbSlong(WeightParment.Wval-WeightParmentWval_Old)<WeightParment.AutoValfudong)
        {
            WeightParment.Wval=WeightParmentWval_Old;
        }
        //process zero
        if(AbSlong(WeightParment.Wval)<WeightParment.AutoZero)
        {
            WeightParment.Wval=0;
        }
        //缓存
        WeightParmentWval_Old=WeightParment.Wval;
    }

}