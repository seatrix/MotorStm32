//#include "HexString.h"


//����λת����ASC
u8 LowF2ASC(u8 ByteIN);

//����ASCת����λ
u8 ASC2DEC(u8 ByteIN);

//����ASCתByte
u8  ASC2Byte(u8 * ByteIN);
//ASCתushort
u16 ASC2Uint(u8 * ByteIN);
//����ת16����ASC�� ByteIN �������룻 ASCPλλ�ã�0�ұߵ�һ����λ��1�ұߵڶ�����λ
u8 Uint2HexASC(long ByteIN,u8 ASCP);
//����ת10����ASC buff ���ɺ�Ļ����� bufflen����������
void Uint2DecASC(long ByteIN,u8* buff,u8 buffLen);

//2Byteתu16
u16 Byte22Uint(u8 * ByteIN);