/* TM7711.h м╥нд╪Ч*/
#ifndef _TM7711_H_
#define _TM7711_H_
#define CH1_10HZ 0x01
#define CH1_40HZ 0x02
#define CH2_TEMP 0x03
 void TM7711_init();
unsigned long Read_TM7711(unsigned char next_select);
#endif