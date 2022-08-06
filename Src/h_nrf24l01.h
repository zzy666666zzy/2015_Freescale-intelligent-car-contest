// nRF24L01.h
#ifndef _H_NRF_24L01_
#define _H_NRF_24L01_

//Choose the MCU you are using
//1.STC51
//2.MSP430
//3.STM32
//4.PIC
//5.KL2x
#define KL2x


//This will enable the IRQ interrupt on 24l01
//But I think it's not necessary
#define IRQ_24L01

#if defined STC51
/////////////////////////////
/////////////////////////
//What I set:
//P1^2    CE
//P1^3    CSN
//P1^7    SCK
//P1^6    MISO
//P1^5    MOSI
//P1^4    IRQ
//P3^5    KEY1
//P3^4    KEY2
//P1^0    LED1
//P1^1    LED2
/////////////////////////
//STC89C52 Version
#include "reg52.h"
//Port define
//weihuang
sbit 	MISO	=P3^6;
sbit 	MOSI	=P3^7;
sbit	SCK	    =P1^7;
sbit	CE	    =P1^5;
sbit	CSN		=P1^6;
sbit	IRQ		=P3^5;
//easy to connect
//sbit 	MISO	=P1^6;
//sbit 	MOSI	=P1^5;
//sbit	SCK	=P1^7;
//sbit	CE      =P1^2;
//sbit	CSN	=P1^3;
//sbit	IRQ	=P1^4;
//MISO
#define NRF24L01MISO_READ        MISO
//MOSI
#define NRF24L01MOSI_L          (MOSI=0)
#define NRF24L01MOSI_H          (MOSI=1)
//SCK
#define NRF24L01SCK_L           (SCK=0)
#define NRF24L01SCK_H           (SCK=1)
//CE
#define NRF24L01CE_L            (CE=0)
#define NRF24L01CE_H            (CE=1)
//CSN
#define NRF24L01CSN_L           (CSN=0)
#define NRF24L01CSN_H           (CSN=1)
//IRQ
#define NRF24L01IRQ_READ        IRQ
//#define NRF24L01IRQ_L           (IRQ=0)
//#define NRF24L01IRQ_H           (IRQ=1)
//Key define
sbit    KEY1    =P2^5;
sbit    KEY2    =P2^6;
sbit 		KEY3		=P2^7;
sbit    LED2    =P1^0;
sbit    LED1    =P1^1;
//KEY1
#define KEY1_READ               (KEY1)
//KEY2
#define KEY2_READ               (KEY2)
#define KEY3_READ								(KEY3)
//LED1
#define LED1_L                  (LED1=0)
#define LED1_H                  (LED1=1)
//LED2
#define LED2_L                  (LED2=0)
#define LED2_H                  (LED2=1)
/////////////////////////////

#elif defined MSP430
/////////////////////////////
//MSP430 Version
#include "msp430.h"
/////////////////////////
//What I set:
//P1.3    CE
//P1.4    CSN
//P1.5    SCK
//P2.0    MISO
//P2.1    MOSI
//P2.2    IRQ
//P2.5    KEY1
//P2.4    KEY2
//P1.0    LED1
//P1.6    LED2
//////////////////////////
//Port define
//Init direction
#define CE_DIR_INIT             (P1DIR|=BIT3)
#define CSN_DIR_INIT            (P1DIR|=BIT4)
#define SCK_DIR_INIT            (P1DIR|=BIT5)
#define MISO_DIR_INIT           (P2DIR&=~BIT0)
#define MOSI_DIR_INIT           (P2DIR|=BIT1)
#define IRQ_DIR_INIT            (P2DIR&=~BIT2)
//#define IRQ_DIR_INIT            (P2DIR|=BIT2)
//////////////
//MISO
#define NRF24L01MISO_READ       (P2IN&BIT0)
//MOSI
#define NRF24L01MOSI_L          (P2OUT&=~BIT1)
#define NRF24L01MOSI_H          (P2OUT|=BIT1)
//SCK
#define NRF24L01SCK_L           (P1OUT&=~BIT5)
#define NRF24L01SCK_H           (P1OUT|=BIT5)
//CE
#define NRF24L01CE_L            (P1OUT&=~BIT3)
#define NRF24L01CE_H            (P1OUT|=BIT3)
//CSN
#define NRF24L01CSN_L           (P1OUT&=~BIT4)
#define NRF24L01CSN_H           (P1OUT|=BIT4)
//IRQ
#define NRF24L01IRQ_READ           (P2IN&BIT2)
//#define NRF24L01IRQ_L           (P2OUT&=~BIT2)
//#define NRF24L01IRQ_H           (P2OUT|=BIT2)
////////////////////////
//Key define
//Init direction
#define KEY1_DIR_INIT           (P2DIR&=~BIT5)
#define KEY2_DIR_INIT           (P2DIR&=~BIT4)
//KEY1
#define KEY1_READ             	(P2IN&BIT5)
//KEY2
#define KEY2_READ             	(P2IN&BIT5)
//LED define
#define LED1_DIR_INIT           (P1DIR|=BIT0)
#define LED2_DIR_INIT           (P1DIR|=BIT6)
//LED1
#define LED1_L                  (P1OUT&=~BIT0)
#define LED1_H                  (P1OUT|=BIT0)
//LED2
#define LED2_L                  (P1OUT&=~BIT6)
#define LED2_H                  (P1OUT|=BIT6)
//--------------------------------------------------
//Not Support anymore
//Port define
//#define MISOBIT  BIT1
//#define MOSIBIT  BIT0
//#define SCKBIT   BIT5
//#define CEBIT    BIT3
//#define CSNBIT   BIT4
//#define IRQBIT   BIT2
//////////////
//#define MISODIR  P2DIR
//#define MOSIDIR  P2DIR
//#define SCKDIR   P1DIR
//#define CEDIR    P1DIR
//#define CSNDIR   P1DIR
//#define IRQDIR   P2DIR
//////////////
//#define MISOIN   P2IN
//#define MOSIOUT  P2OUT
//#define SCKOUT   P1OUT
//#define CEOUT    P1OUT
//#define CSNOUT   P1OUT
//#define IRQOUT   P2OUT
//////////////
////MISO
//#define NRF24L01MISO_READ       (MISOIN&MISOBIT)
////MOSI
//#define NRF24L01MOSI_L          (MOSIOUT&=~MOSIBIT)
//#define NRF24L01MOSI_H          (MOSIOUT|=MOSIBIT)
////SCK
//#define NRF24L01SCK_L           (SCKOUT&=~SCKBIT)
//#define NRF24L01SCK_H           (SCKOUT|=SCKBIT)
////CE
//#define NRF24L01CE_L            (CEOUT&=~CEBIT)
//#define NRF24L01CE_H            (CEOUT|=CEBIT)
////CSN
//#define NRF24L01CSN_L            (CSNOUT&=~CSNBIT)
//#define NRF24L01CSN_H            (CSNOUT|=CSNBIT)
////IRQ
//#define NRF24L01IRQ_L           (IRQOUT&=~IRQBIT)
//#define NRF24L01IRQ_H           (IRQOUT|=IRQBIT)
////Key define
//#define KEY1BIT                 BIT3
//#define KEY2BIT                 BIT4
////////////////////
//#define KEY1DIR                 P2DIR
//#define KEY2DIR                 P2DIR
///////////////////
//#define KEY1IN                  P2IN
//#define KEY2IN                  P2IN
////KEY1
//#define KEY1_READ               (KEY1IN&KEY1BIT)
////KEY2
//#define KEY2_READ               (KEY2IN&KEY2BIT)
////LED define
//#define LED1BIT                 BIT0
//#define LED2BIT                 BIT6
//////////////////
//#define LED1DIR                 P1DIR
//#define LED2DIR                 P1DIR
/////////////////
//#define LED1OUT                 P1OUT
//#define LED2OUT                 P1OUT
////LED1
//#define LED1_L                  (LED1OUT&=~LED1BIT)
//#define LED1_H                  (LED1OUT|=LED1BIT)
////LED2
//#define LED2_L                  (LED2OUT&=~LED2BIT)
//#define LED2_H                  (LED2OUT|=LED2BIT)
//------------------------------------------------------
/////////////////////////////
#elif defined STM32
#include "stm32f10x.h"
/////////////////////////
//What I set:
//PB0    CE
//PB1    CSN
//PB7    SCK
//PB4    MISO
//PB5    MOSI
//PB6    IRQ
//PA10   KEY1
//PA11   KEY2
//PB14   LED1
//PB15   LED2
//////////////////////////
//Port define
//GPIOx define
//#define CE_GPIO             GPIOB
//#define CSN_GPIO            GPIOB
//#define SCK_GPIO            GPIOB
//#define MISO_GPIO           GPIOB
//#define MOSI_GPIO           GPIOB
//#define IRQ_GPIO            GPIOB
#define CE_GPIO             GPIOG
#define CSN_GPIO            GPIOG
#define SCK_GPIO            GPIOB
#define MISO_GPIO           GPIOB
#define MOSI_GPIO           GPIOB
#define IRQ_GPIO            GPIOG
//RCC define
#define CE_GPIO_RCC             RCC_APB2Periph_GPIOG
#define CSN_GPIO_RCC            RCC_APB2Periph_GPIOG
#define SCK_GPIO_RCC            RCC_APB2Periph_GPIOB
#define MISO_GPIO_RCC           RCC_APB2Periph_GPIOB
#define MOSI_GPIO_RCC           RCC_APB2Periph_GPIOB
#define IRQ_GPIO_RCC            RCC_APB2Periph_GPIOG
//Pin define
#define CE_PIN             GPIO_Pin_6
#define CSN_PIN            GPIO_Pin_7
#define SCK_PIN            GPIO_Pin_13
#define MISO_PIN           GPIO_Pin_14
#define MOSI_PIN           GPIO_Pin_15
#define IRQ_PIN            GPIO_Pin_8
//#define CE_PIN             GPIO_Pin_0
//#define CSN_PIN            GPIO_Pin_1
//#define SCK_PIN            GPIO_Pin_2
//#define MISO_PIN           GPIO_Pin_3
//#define MOSI_PIN           GPIO_Pin_4
//#define IRQ_PIN            GPIO_Pin_5
//////////////
//MISO
#define NRF24L01MISO_READ       GPIO_ReadInputDataBit(MISO_GPIO,MISO_PIN)
//MOSI
#define NRF24L01MOSI_L          GPIO_ResetBits(MOSI_GPIO,MOSI_PIN)
#define NRF24L01MOSI_H          GPIO_SetBits(MOSI_GPIO,MOSI_PIN)
//SCK
#define NRF24L01SCK_L           GPIO_ResetBits(SCK_GPIO,SCK_PIN)
#define NRF24L01SCK_H           GPIO_SetBits(SCK_GPIO,SCK_PIN)
//CE
#define NRF24L01CE_L            GPIO_ResetBits(CE_GPIO,CE_PIN)
#define NRF24L01CE_H            GPIO_SetBits(CE_GPIO,CE_PIN)
//CSN
#define NRF24L01CSN_L           GPIO_ResetBits(CSN_GPIO,CSN_PIN)
#define NRF24L01CSN_H           GPIO_SetBits(CSN_GPIO,CSN_PIN)
//IRQ
#define NRF24L01IRQ_READ	GPIO_ReadInputDataBit(IRQ_GPIO,IRQ_PIN)
//#define NRF24L01IRQ_L           GPIO_ResetBits(IRQ_GPIO,IRQ_PIN)
//#define NRF24L01IRQ_H           GPIO_SetBits(IRQ_GPIO,IRQ_PIN)
////////////////////////
//Key define
//GPIOx define
#define KEY1_GPIO             GPIOA
#define KEY2_GPIO             GPIOA
//RCC define
#define KEY1_GPIO_RCC            RCC_APB2Periph_GPIOA
#define KEY2_GPIO_RCC            RCC_APB2Periph_GPIOA
//Pin define
//#define KEY1_PIN             GPIO_Pin_10
//#define KEY2_PIN             GPIO_Pin_11
////KEY1
//#define KEY1_READ             GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_PIN)
////KEY2
//#define KEY2_READ             GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_PIN)
////LED define
////GPIOx define
//#define LED1_GPIO             GPIOB
//#define LED2_GPIO             GPIOB
////RCC define
//#define LED1_GPIO_RCC            RCC_APB2Periph_GPIOA
//#define LED2_GPIO_RCC            RCC_APB2Periph_GPIOA
////Pin define
//#define LED1_PIN             GPIO_Pin_14
//#define LED2_PIN             GPIO_Pin_15
////LED1
//#define LED1_L                  GPIO_ResetBits(LED1_GPIO,LED1_PIN)
//#define LED1_H                  GPIO_SetBits(LED1_GPIO,LED1_PIN)
////LED2
//#define LED2_L                  GPIO_ResetBits(LED2_GPIO,LED2_PIN)
//#define LED2_H                  GPIO_SetBits(LED2_GPIO,LED2_PIN)

//PIC
#elif defined PIC
//-----------------------------

//-----------------------------

///////////////////////////////////
//Kinetis MKL2x
#elif defined KL2x

//I build this based on VCAN lib
//So I can use them
#include "common.h"
#include "include.h"

//Input
//IRQ   PC0
//MISO  PB22
//Output
//MOSI  PB20
//SCK   PB8
//CE    PB3
//CSN   PB1
//////////////
//MISO
#define NRF24L01MISO_READ       (PTB22_IN)
//MOSI
#define NRF24L01MOSI_L          (PTB20_OUT=0)
#define NRF24L01MOSI_H          (PTB20_OUT=1)
//SCK
#define NRF24L01SCK_L           (PTB8_OUT=0)
#define NRF24L01SCK_H           (PTB8_OUT=1)
//CE
#define NRF24L01CE_L            (PTB3_OUT=0)
#define NRF24L01CE_H            (PTB3_OUT=1)
//CSN
#define NRF24L01CSN_L           (PTB1_OUT=0)
#define NRF24L01CSN_H           (PTB1_OUT=1)
//IRQ
#define NRF24L01IRQ_READ	(PTC0_IN)

#endif

extern char nrf_ready;
extern unsigned char TxBuf[128];
extern unsigned char RxBuf[128];

#define TX_ADR_WIDTH    5   // 5 bytes TX address width
#define RX_ADR_WIDTH    5   // 5 bytes RX address width
#define TX_PLOAD_WIDTH  32  // 20 bytes TX payload
#define RX_PLOAD_WIDTH  32  // 20 bytes TX payload

#define BYTE unsigned char
#define uchar unsigned char
//****************************************************************//
// SPI(nRF24L01) commands
#define READ_REG_24L01  0x00  // Define read command to register
#define WRITE_REG_24L01 0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define NOP             0xFF  // Define No Operation, might be used to read status register


//***************************************************//
// SPI(nRF24L01) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address

//***************************************************************//
//                   FUNCTION's PROTOTYPES  //
/****************************************************************/
// void SPI_Init(BYTE Mode);     // Init HW or SW SPI
extern BYTE SPI_RW(BYTE byte);                                // Single SPI read/write
extern BYTE SPI_Read(BYTE reg);                               // Read one byte from nRF24L01
extern BYTE SPI_RW_Reg(BYTE reg, BYTE byte);                  // Write one byte to register 'reg'
extern BYTE SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);  // Writes multiply bytes to one register
extern BYTE SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);   // Read multiply bytes from one register
//*****************************************************************/

//extern void inerDelay_us(unsigned char n);

extern void init_24l01(void);
extern void iniT_nrf_buf(unsigned char *s);
extern void trans_nrf_buf(unsigned char *s1,unsigned char *s2);
extern void SetRX_Mode(void);
extern unsigned char nRF24L01_RxPacket(unsigned char* rx_buf);
extern void nRF24L01_TxPacket(unsigned char * tx_buf);
extern void init_nrf(void);
extern void run_nrf(void);
extern char nrf_just_get(void);
extern unsigned char nrf_just_send(unsigned char *s);
extern unsigned char nrf24l01_check(void);

extern unsigned char TX_ADDRESS[TX_ADR_WIDTH];//TX address
extern unsigned char RX_ADDRESS[RX_ADR_WIDTH];//;RX address

extern void trans_nrf_buf_2(unsigned char *s1,unsigned char *s2,unsigned char *s3);
extern unsigned char nrf_just_send_2(unsigned char *s1,unsigned char *s2);

extern void trans_nrf_buf_3(unsigned char *s1,unsigned char *s2,unsigned char *s3,unsigned char *s4);

#endif   //_NRF_24L01_
