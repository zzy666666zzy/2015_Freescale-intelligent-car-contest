#ifndef _FOUR_X_FOUR_KEYS_H_
#define _FOUR_X_FOUR_KEYS_H_

#define KL2X

#if (defined(KL2X))
#include "MKL26Z4.h"

#include "common.h"
#include "include.h"

#define LINE1_OUT       (GPIOB_PDDR |= 1<<1)
#define LINE2_OUT       (GPIOB_PDDR |= 1<<3)
#define LINE3_OUT       (GPIOB_PDDR |= 1<<8)
#define LINE4_OUT       (GPIOB_PDDR |= 1<<10)

#define LINE1_H         (PTB0_OUT = 1)
#define LINE1_L         (PTB0_OUT = 0)
#define LINE2_H         (PTB2_OUT = 1)
#define LINE2_L         (PTB2_OUT = 0)
#define LINE3_H         (PTB7_OUT = 1)
#define LINE3_L         (PTB7_OUT = 0)
#define LINE4_H         (PTB9_OUT = 1)
#define LINE4_L         (PTB9_OUT = 0)
//#define LINE5_OUT
//#define LINE6_OUT
//#define LINE7_OUT
//#define LINE8_OUT
#define LINE5_IN        (GPIOB_PDDR &=~ (1<<16))
#define LINE6_IN        (GPIOB_PDDR &=~ (1<<18))
#define LINE7_IN        (GPIOB_PDDR &=~ (1<<20))
#define LINE8_IN        (GPIOB_PDDR &=~ (1<<22))

#define LINE5_READ      (PTB11_IN)
#define LINE6_READ      (PTB17_IN)
#define LINE7_READ      (PTB19_IN)
#define LINE8_READ      (PTB21_IN)
//#define LINE1_OUT       (GPIOB_PDDR |= 1<<1)
//#define LINE2_OUT       (GPIOB_PDDR |= 1<<3)
//#define LINE3_OUT       (GPIOB_PDDR |= 1<<8)
//#define LINE4_OUT       (GPIOB_PDDR |= 1<<10)
//
//#define LINE1_H         (GPIOB_PDOR |= (1<<1))
//#define LINE1_L         (GPIOB_PDOR &=~ (1<<1))
//#define LINE2_H         (GPIOB_PDOR |= (1<<3))
//#define LINE2_L         (GPIOB_PDOR &=~ (1<<3))
//#define LINE3_H         (GPIOB_PDOR |= (1<<8))
//#define LINE3_L         (GPIOB_PDOR &=~ (1<<8))
//#define LINE4_H         (GPIOB_PDOR |= (1<<10))
//#define LINE4_L         (GPIOB_PDOR &=~ (1<<10))
////#define LINE5_OUT
////#define LINE6_OUT
////#define LINE7_OUT
////#define LINE8_OUT
//#define LINE5_IN        (GPIOB_PDDR &=~ (1<<16))
//#define LINE6_IN        (GPIOB_PDDR &=~ (1<<18))
//#define LINE7_IN        (GPIOB_PDDR &=~ (1<<20))
//#define LINE8_IN        (GPIOB_PDDR &=~ (1<<22))
//
//#define LINE5_READ      (1&(GPIOB_PDIR >> 16))
//#define LINE6_READ      (1&(GPIOB_PDIR >> 18))
//#define LINE7_READ      (1&(GPIOB_PDIR >> 20))
//#define LINE8_READ      (1&(GPIOB_PDIR >> 22))

//Function
extern void init_4x4_port(void);
extern int keys_scan_4x4(void);
#endif

#endif
