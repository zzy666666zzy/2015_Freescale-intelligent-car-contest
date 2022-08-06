#ifndef _S_VALUE_TRANS_H_
#define _S_VALUE_TRANS_H_

extern int find_object_in_chars(unsigned char *s,unsigned char o);
extern void char_2_float_get_rid_of_head(unsigned char **s);
extern float char_2_float(unsigned char * s);
extern float char_2_float_with_index(unsigned char *s,unsigned char i1,unsigned char i2);
extern float char_2_float_with_char(unsigned char *s,unsigned char c1,unsigned char c2);
extern unsigned char * int_2_char(int tnum);
extern unsigned char get_int_length(int i);
extern void float_2_char_valuetrans(unsigned char *s1,int *s1_len,unsigned char *s2);
extern unsigned char * float_2_char(float f,unsigned char accuracy);

#endif
