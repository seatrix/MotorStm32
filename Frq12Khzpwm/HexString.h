//#include "HexString.h"


//低四位转单个ASC
u8 LowF2ASC(u8 ByteIN);

//单个ASC转低四位
u8 ASC2DEC(u8 ByteIN);

//两个ASC转Byte
u8  ASC2Byte(u8 * ByteIN);
//ASC转ushort
u16 ASC2Uint(u8 * ByteIN);
//数字转16进制ASC， ByteIN 数字输入； ASCP位位置，0右边第一个四位，1右边第二个四位
u8 Uint2HexASC(long ByteIN,u8 ASCP);
//数字转10进制ASC buff 生成后的缓冲区 bufflen缓冲区长度
void Uint2DecASC(long ByteIN,u8* buff,u8 buffLen);

//2Byte转u16
u16 Byte22Uint(u8 * ByteIN);