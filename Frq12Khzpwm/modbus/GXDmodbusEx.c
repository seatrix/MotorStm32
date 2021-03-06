#include "GXDmodbus.h"
#include "GXDmodbusEx.h"
#include <string.h>

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "TimerDevc.h"
#include "serial.h"


#define REG_HOLDING_NREGS_Start   ( 0 )
#define REG_HOLDING_NREGS   ( 18 )
//static USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];       //Holding Register buffer

//modbus地址
#define ucRcvAddress 0
#define ucRcvCMD     1
//寄存器修改
  char RegsterModfied;
void MBRTUSendChar(unsigned char snd)
{

    sndcharDev( snd,1);

}
void vMBPortTimersEnable( void )
{
    TIM3_Start(1);
}




void vMBPortTimersDisable( void )
{
    TIM3_Start(0);
}


USHORT Bytes2Ushort(unsigned char *bytes)
{
    USHORT re;
    re=bytes[0];
    re<<=8;
    re|=bytes[1];
    return ;

}

//数组,寄存器，寄存器长度
void Buf2Regster(unsigned char *buf,unsigned char StartRegaddr,unsigned char Reglength)
{
    unsigned short  val;
    unsigned char  i;
    //读取变量
    for(i=0; i<Reglength; i++)
    {
        val=buf[i*2];
        val<<=8;
        val|=buf[i*2+1];
        Callback_HoldRegWrite(StartRegaddr+i,val);
    }
}

//数组,寄存器，寄存器长度
void  Regster2buf(unsigned char *buf,unsigned char StartRegaddr,unsigned char Reglength)
{
    unsigned short  val;
    unsigned char  i;
    //读取变量
    for(i=0; i<Reglength; i++)
    {
        val=Callback_HoldRegRead(StartRegaddr+i);
        buf[i*2]=(unsigned char)(val>>8);
        buf[i*2+1] =(unsigned char)(val&0xFF);
    }
}
#define MBTxbufsize 40
void  MBCallback()
{
    unsigned short StartRegaddr;
    unsigned short RegLength,val;
    unsigned char i;
    unsigned char  ucRTUTxBuf[MBTxbufsize];
    if( (ucRTUBuf[ucRcvAddress]   == MBSlaveAddr ) )
    {
        StartRegaddr=Bytes2Ushort((unsigned char *)&ucRTUBuf[2]);
        RegLength=Bytes2Ushort((unsigned char *)&ucRTUBuf[4]);

        switch(ucRTUBuf[ucRcvCMD])
        {
        case 0x03:

            if(StartRegaddr>=REG_HOLDING_NREGS_Start &&
                    StartRegaddr<(REG_HOLDING_NREGS+REG_HOLDING_NREGS_Start) &&
                    RegLength<REG_HOLDING_NREGS
              )
            {

                //读保持寄存器
                ucRTUTxBuf[0]=MBSlaveAddr;
                ucRTUTxBuf[1]=0x03;
                ucRTUTxBuf[2]=(unsigned char)(0xFF & (RegLength*2));

//                 //读取变量
//                 for(i=0; i<RegLength; i++)
//                 {
//                     val=Callback_HoldRegRead(StartRegaddr+i);
//                     ucRTUTxBuf[3+i*2]=(unsigned char)(val>>8);
//                     ucRTUTxBuf[3+i*2+1] =(unsigned char)(val&0xFF);
//                 }
                Regster2buf(&ucRTUTxBuf[3],StartRegaddr,RegLength);
                MBRTUSend(ucRTUTxBuf,3+RegLength*2);
            }
            break;


        case 0x10:

            if(StartRegaddr>=REG_HOLDING_NREGS_Start &&
                    StartRegaddr<(REG_HOLDING_NREGS+REG_HOLDING_NREGS_Start) &&
                    RegLength<REG_HOLDING_NREGS
              )
            {
//                 //读取变量
//                 for(i=0; i<RegLength; i++)
//                 {
// 									     val=ucRTUBuf[7+i*2];
// 									     val<<=8;
// 									     val|=ucRTUBuf[7+i*2+1];
//                       Callback_HoldRegWrite(StartRegaddr+i,val);
//                 }
                Buf2Regster(&ucRTUBuf[7],StartRegaddr,RegLength);
						  	RegsterModfied=1;
                //写保持寄存器
                ucRTUTxBuf[0]=MBSlaveAddr;
                ucRTUTxBuf[1]=0x10;
                ucRTUTxBuf[2]=(unsigned char)(0xFF & (StartRegaddr>>8));
                ucRTUTxBuf[3]=(unsigned char)(0xFF & (StartRegaddr));
                ucRTUTxBuf[4]=(unsigned char)(0xFF & (RegLength>>8));
                ucRTUTxBuf[5]=(unsigned char)(0xFF & (RegLength));
                MBRTUSend(ucRTUTxBuf,6);
            }
            break;

        }


    }




}



