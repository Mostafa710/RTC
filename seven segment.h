#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

void seven_segment_init(unsigned char portname);
void seven_segment_write(unsigned char portname,unsigned char counter);
void seven_segment_init_bcd(unsigned char portname,unsigned char nibble);
void seven_segment_write_bcd(unsigned char portname,unsigned char nibble,unsigned char val);

#endif