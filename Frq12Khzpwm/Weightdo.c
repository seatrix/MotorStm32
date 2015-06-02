#include "Weightdo.h"

WeightParmentT WeightParment;


unsigned short Callback_HoldRegRead(unsigned char Regaddr)
{
    unsigned short Rval;

    switch(Regaddr)
    {
    case 0:

        Rval=(unsigned short)(WeightParment.Wval&0xFFFF);
        break;
    case 1:
        Rval=(unsigned short)(WeightParment.Wval>>16);
        break;
    case 2:
        Rval=(unsigned short)(WeightParment.ADval&0xFFFF);
        break;
    case 3:
        Rval=(unsigned short)(WeightParment.ADval>>16);
        break;
    case 4:
        Rval=(unsigned short)(WeightParment.ZeroADval&0xFFFF);
        break;
    case 5:
        Rval=(unsigned short)(WeightParment.ZeroADval>>16);
        break;
    case 6:
        Rval=(unsigned short)(WeightParment.FullADval&0xFFFF);
        break;
    case 7:
        Rval=(unsigned short)(WeightParment.FullADval>>16);
        break;
    case 8:
        Rval=(unsigned short)(WeightParment.FullWval&0xFFFF);
        break;
    case 9:
        Rval=(unsigned short)(WeightParment.FullWval>>16);
        break;
    case 10:
        Rval=(unsigned short)(WeightParment.SlaveAddr);
        break;
    case 11:
        Rval=(unsigned short)(WeightParment.BadeRate);
        break;
    case 12:
        Rval=(unsigned short)(WeightParment.SumTimes);
        break;
    case 13:
        Rval=(unsigned short)(WeightParment.OutInterval);
        break;
    case 14:
        Rval=(unsigned short)(WeightParment.AutoZero);
        break;
    case 15:
        Rval=(unsigned short)(WeightParment.AutoValfudong);
        break;
    }
    return Rval;
}

void Callback_HoldRegWrite(unsigned char Regaddr,unsigned short RegVal)
{

    switch(Regaddr)
    {

    case 4:
        WeightParment.ZeroADval=RegVal;
        break;
    case 5:
        WeightParment.ZeroADval&= 0x0000FFFF;
        WeightParment.ZeroADval|=((unsigned long)RegVal)<<16;
        break;
    case 6:
        WeightParment.FullADval=RegVal;
        break;
    case 7:
        WeightParment.FullADval&= 0x0000FFFF;
        WeightParment.FullADval|=((unsigned long)RegVal)<<16;
        break;
    case 8:
        WeightParment.FullWval=RegVal;
        break;
    case 9:
        WeightParment.FullWval&= 0x0000FFFF;
        WeightParment.FullWval|=((unsigned long)RegVal)<<16;
        break;
    case 10:
        WeightParment.SlaveAddr=(unsigned char)RegVal ;
        break;
    case 11:
        WeightParment.BadeRate= RegVal ;
        break;
    case 12:
        WeightParment.SumTimes=(unsigned char)RegVal;
		  if((WeightParment.SumTimes)<1) WeightParment.SumTimes=1;
		  if((WeightParment.SumTimes)>50) WeightParment.SumTimes=50;		
        break;
    case 13:
        WeightParment.OutInterval=(unsigned char)RegVal;
        break;
    case 14:
        WeightParment.AutoZero= RegVal;
        break;
    case 15:
        WeightParment.AutoValfudong= RegVal;
        break;
    }

}

void wd_init()
{
    WeightParment.Wval=0;
    WeightParment.ADval=0;
    WeightParment.ZeroADval=0;
    WeightParment.FullADval=8327192;
    WeightParment.FullWval=1000;
    WeightParment.SlaveAddr=1;
    WeightParment.BadeRate=9600;
    WeightParment.SumTimes=1;
    WeightParment.OutInterval=0;
    WeightParment.AutoZero=1;	//0検強
    WeightParment.AutoValfudong=1;	//val検強
}