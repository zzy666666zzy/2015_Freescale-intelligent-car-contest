// nRF24L01.c
#include "h_nrf24l01.h"
//#if defined STC51
////#include <intrins.h>
//#endif
//#include "h_uart_fun.h"
//#include "h_c8_uart1.h"

char nrf_ready = 0;


unsigned char TX_ADDRESS[TX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x05}; // Define a static TX address
unsigned char RX_ADDRESS[RX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x05}; // Define a static RX address

#define DATALENTH 128
unsigned char TxBuf[DATALENTH]={0};	 // 
unsigned char RxBuf[DATALENTH]={0};	

void inerDelay_us(unsigned int n)
{
    for(;n>0;n--);
}
#if defined MSP430
void nrf24l01_portinit_4_msp430(void)
{
  //NRF24L01
  CE_DIR_INIT;
  CSN_DIR_INIT;
  SCK_DIR_INIT;
  MISO_DIR_INIT;
  MOSI_DIR_INIT;
  IRQ_DIR_INIT;
  //TEST SHOW
//  KEY1_DIR_INIT;
//  KEY2_DIR_INIT;
//  LED1_DIR_INIT;
//  LED2_DIR_INIT;
}
#endif
#if defined STM32
void nrf24l01_portinit_4_stm32(void)
{
	//NRF24L01
	GPIO_InitTypeDef GPIO_InitStructure;
	//CE--OUTPUT
	RCC_APB2PeriphClockCmd(CE_GPIO_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = CE_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(CE_GPIO,&GPIO_InitStructure);
	//CSN--OUTPUT
	RCC_APB2PeriphClockCmd(CSN_GPIO_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = CSN_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(CSN_GPIO,&GPIO_InitStructure);
	//SCK--OUTPUT
	RCC_APB2PeriphClockCmd(SCK_GPIO_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SCK_GPIO,&GPIO_InitStructure);
	//MISO--INPUT
	RCC_APB2PeriphClockCmd(MISO_GPIO_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = MISO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(MISO_GPIO,&GPIO_InitStructure);
	//MOSI--OUTPUT
	RCC_APB2PeriphClockCmd(MOSI_GPIO_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = MOSI_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(MOSI_GPIO,&GPIO_InitStructure);
	//IRQ--INPUT
	RCC_APB2PeriphClockCmd(IRQ_GPIO_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = IRQ_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(IRQ_GPIO,&GPIO_InitStructure);
//	//TEST SHOW
//	//KEY1
//	RCC_APB2PeriphClockCmd(KEY1_GPIO_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(KEY1_GPIO,&GPIO_InitStructure);
//	//KEY2
//	RCC_APB2PeriphClockCmd(KEY2_GPIO_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(KEY2_GPIO,&GPIO_InitStructure);
//	//LED1
//	RCC_APB2PeriphClockCmd(LED1_GPIO_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(LED1_GPIO,&GPIO_InitStructure);
//	//LED2
//	RCC_APB2PeriphClockCmd(LED2_GPIO_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(LED2_GPIO,&GPIO_InitStructure);
	//Reset NRF24L01 Port
	NRF24L01MOSI_L;
	NRF24L01SCK_L;
	NRF24L01CE_L;
	NRF24L01CSN_L;
//	NRF24L01IRQ_L;
	//Reset TEST Port
//	LED1_L;
//	LED2_L;
	
}
#endif
#if defined KL2x
void nrf24l01_portinit_4_kl2x(void)
{
  //Input
  //IRQ   PC0
  //MISO  PB22
  //Output
  //MOSI  PB20
  //SCK   PB8
  //CE    PB3
  //CSN   PB1
  gpio_init(PTB1,GPO,1);
  gpio_init(PTB3,GPO,1);
  gpio_init(PTB8,GPO,1);
  gpio_init(PTB20,GPO,1);
  gpio_init(PTB22,GPI,0); 
  gpio_init(PTC0,GPI,0); 
}
#endif
void init_24l01(void)
{
#if defined MSP430
  nrf24l01_portinit_4_msp430();
#elif defined STM32
	nrf24l01_portinit_4_stm32();
#elif defined KL2x
        nrf24l01_portinit_4_kl2x();
#endif
  //设置miso为输入
  //设置其它口为输出
  
  //endset 
  inerDelay_us(100);
  NRF24L01CE_L;   // chip enable
  NRF24L01CSN_H;   // Spi disable 
  NRF24L01SCK_L;   // Spi clock line init high
  nrf_ready = 0;
}

//Init your RXBUF or TXBUF
void iniT_nrf_buf(unsigned char *s)
{
  while(*s != '\0')
  {
    *s = '\0';
    s++;
  }
}

void trans_nrf_buf(unsigned char *s1,unsigned char *s2)
{
  unsigned char i =0;
  while((i < DATALENTH)&&(*s2 != '\0'))
  {
    *s1 = *s2;
    s1++;
    s2++;
    i++;
  }
  *s1 = '\0';
}

/**************************************************
Function: SPI_RW();

  Description:
  Writes one byte to nRF24L01, and return the byte read
  from nRF24L01 during write, according to SPI protocol
**************************************************/
uchar SPI_RW(uchar byte)
{
  uchar bit_ctr;
  for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
  {
    if(byte & 0x80)
      NRF24L01MOSI_H;
    else
      NRF24L01MOSI_L;
//          MOSI = (byte & 0x80);         // output 'byte', MSB to MOSI
    byte = (byte << 1);           // shift next bit into MSB..
    NRF24L01SCK_H;                      // Set SCK high..
    byte |= NRF24L01MISO_READ;       		  // capture current MISO bit
    NRF24L01SCK_L;            		  // ..then set SCK low again
  }
  return(byte);           		  // return read byte
}
/**************************************************/

/**************************************************
Function: SPI_RW_Reg();

  Description:
  Writes value 'value' to register 'reg'
**************************************************/
uchar SPI_RW_Reg(BYTE reg, BYTE value)
{
  uchar status;
  NRF24L01CSN_L;                   // CSN low, init SPI transaction
  status = SPI_RW(reg);      // select register
  SPI_RW(value);             // ..and write value to it..
  NRF24L01CSN_H;                   // CSN high again
  return(status);            // return nRF24L01 status byte
}
/**************************************************/

/**************************************************
Function: SPI_Read();

  Description:
  Read one byte from nRF24L01 register, 'reg'
**************************************************/
BYTE SPI_Read(BYTE reg)
{
  BYTE reg_val;
  NRF24L01CSN_L;                // CSN low, initialize SPI communication...
  SPI_RW(reg);            // Select register to read from..
  reg_val = SPI_RW(0);    // ..then read registervalue
  NRF24L01CSN_H;                // CSN high, terminate SPI communication
  return(reg_val);        // return register value
}
/**************************************************/

/**************************************************
Function: SPI_Read_Buf();

  Description:
  
**************************************************/
uchar SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes)
{
  uchar status,byte_ctr;
  NRF24L01CSN_L;                    		// Set CSN low, init SPI tranaction
  status = SPI_RW(reg);       		// Select register to write to and read status byte
  
  for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
          pBuf[byte_ctr] = SPI_RW(0);    // 
  NRF24L01CSN_H;                           
  return(status);                    // return nRF24L01 status byte
}
/**************************************************/

/**************************************************
Function: SPI_Write_Buf();

  Description:
  Writes contents of buffer '*pBuf' to nRF24L01
  Typically used to write TX payload, Rx/Tx address
**************************************************/
uchar SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes)
{
  uchar status,byte_ctr;
  NRF24L01CSN_L;                   
  status = SPI_RW(reg);   
  for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) //
      SPI_RW(*pBuf++);
  NRF24L01CSN_H;                 // Set CSN high again
  return(status);          //
}

//Not support anymore
//uchar clear_pload(BYTE reg,BYTE bytes)
//{
//	uchar status,byte_ctr;
//	NRF24L01CE_L;
//  NRF24L01CSN_L;                   
//  status = SPI_RW(reg);   
//  for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) //
//      SPI_RW('\0');
//  NRF24L01CSN_H;                 // Set CSN high again
//	NRF24L01CE_H;
//  inerDelay_us(10);
//  return(status);          //
//}

/**************************************************/

/**************************************************
Function: RX_Mode();

  Description:
  
**************************************************/
void SetRX_Mode(void)
{
//  NRF24L01CE_L;
  SPI_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // Use the same address on the RX device as the TX device
  SPI_RW_Reg(WRITE_REG_24L01 + EN_AA, 0x01);      // 
  SPI_RW_Reg(WRITE_REG_24L01 + EN_RXADDR, 0x01);  // 
  SPI_RW_Reg(WRITE_REG_24L01 + RF_CH, 0);        // 
  SPI_RW_Reg(WRITE_REG_24L01 + RX_PW_P0, RX_PLOAD_WIDTH); 
  SPI_RW_Reg(WRITE_REG_24L01 + RF_SETUP, 0x07);   
  SPI_RW_Reg(WRITE_REG_24L01 + CONFIG, 0x0f);     
  NRF24L01CE_H; 
  inerDelay_us(600);
}
/**************************************************/
//0 for success and 1 for failed
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
	unsigned char sta;
  sta=SPI_Read(STATUS);	// read register STATUS's value
	SPI_RW_Reg(WRITE_REG_24L01+STATUS,sta);// clear RX_DR or TX_DS or MAX_RT interrupt flag
  if(sta&0x40)				// if receive data ready (RX_DR) interrupt
  {
//      NRF24L01CE_L; 
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		SPI_RW_Reg(FLUSH_RX,0xff);	//Clear RX fifo  
		return 0;
//			SPI_RW_Reg(WRITE_REG_24L01+STATUS,0xff);//sta);// clear RX_DR or TX_DS or MAX_RT interrupt flag
  }
  
	return 1;
}

/**************************************************
Function: nRF24L01_TxPacket();

  Description:
  This function initializes one nRF24L01 device to
  TX mode, set TX address, set RX address for auto.ack,
  fill TX payload, select RF channel, datarate & TX pwr.
  PWR_UP is set, CRC(2 bytes) is enabled, & PRIM:TX.
  
	ToDo: One high pulse(>10us) on CE will now send this
	packet and expext an acknowledgment from the RX device.
**************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
  NRF24L01CE_L;
  SPI_Write_Buf(WRITE_REG_24L01 + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 
  SPI_Write_Buf(WRITE_REG_24L01 + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); 
  SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 
  SPI_RW_Reg(WRITE_REG_24L01 + EN_AA, 0x01);      // 
  SPI_RW_Reg(WRITE_REG_24L01 + EN_RXADDR, 0x01);  // 
  SPI_RW_Reg(WRITE_REG_24L01 + SETUP_RETR, 0x1a); //
  SPI_RW_Reg(WRITE_REG_24L01 + RF_CH, 0);        // 
  SPI_RW_Reg(WRITE_REG_24L01 + RF_SETUP, 0x07);   // 
  SPI_RW_Reg(WRITE_REG_24L01 + CONFIG, 0x0e);     // 
  NRF24L01CE_H;
  inerDelay_us(10);
  //sta=SPI_Read(STATUS);	// read register STATUS's value
  //SPI_RW_Reg(WRITE_REG+STATUS,SPI_Read(READ_REG+STATUS));	// clear interrupt flag(TX_DS)
}
//Init nrf24L01
void init_nrf(void)
{
  init_24l01();
  inerDelay_us(6000);
}
//Not support anymore
////You should run this function to reset the register
//void reset_nrf(void)
//{
//  SPI_RW_Reg(WRITE_REG_24L01+STATUS,0XFF);   //Clear the register
//}

//I have upgraded this function
////Run nrf24l01 function
//void run_nrf(void)
//{
////  nrf_ready = 1;
////  trans_nrf_buf(TxBuf,"woa");
//  if(KEY1_READ ==0)// || KEY2 ==0)
//  {
//      nrf_ready = 1;
//      LED1_L;
//      LED2_H;
//      trans_nrf_buf(TxBuf,"111111111\n");
//  }
//  else if(KEY2_READ ==0)
//  {
//      nrf_ready = 1;
//      LED1_H;
//      LED2_L;
//      trans_nrf_buf(TxBuf,"000000000\n");
//  }

//  if(nrf_ready)
//  {
//      SendStr(TxBuf);
//      nRF24L01_TxPacket(TxBuf);	// Transmit Tx buffer data
////			reset_nrf();
//      nrf_ready = 0;
//      LED1_L;
//      LED2_L;
//  }
//  LED1_H;
//  LED2_H;
//  ///////////////////////////////
//  SetRX_Mode();
//  if(nRF24L01_RxPacket(RxBuf))
//  {
//      LED1_L;
//      LED2_L;
//      SendStr(RxBuf);
//			SPI_RW_Reg(FLUSH_TX,0xff);	//Clear RX fifo
////			clear_pload(RD_RX_PLOAD,RX_PLOAD_WIDTH);
////			reset_nrf();
////		c8_uart1_send_string(RxBuf);
//  }
//  LED1_H;
//  LED2_H;
//	
//  iniT_nrf_buf(TxBuf);
//  iniT_nrf_buf(RxBuf);
//}

//Run nrf24l01 function
void run_nrf(void)
{
//  if(KEY1_READ ==0)
//  {
//      LED1_L;
//      LED2_H;
//			nrf_just_send("111111111\n");
//  }
//  else if(KEY2_READ ==0)
//  {
//      LED1_H;
//      LED2_L;
//			nrf_just_send("000000000\n");
//  }
//	else if(KEY3_READ ==0)
//  {
//      LED1_H;
//      LED2_L;
//			nrf_just_send("rrrrrrrrrr\n");
//  }

//  LED1_H;
//  LED2_H;
//  ///////////////////////////////
//  SetRX_Mode();
//	nrf_just_get();
//  LED1_H;
//  LED2_H;
//	
//  iniT_nrf_buf(TxBuf);
//  iniT_nrf_buf(RxBuf);
}

//Just get
char nrf_just_get(void)
{
  SetRX_Mode();
  if(!nRF24L01_RxPacket(RxBuf))		//Get message
  {
		return 1;
//        LED1_H;
//        LED2_H;
//				SendStr(RxBuf);
				
  }
	return 0;
//  LED1_L;
//  LED2_L;
}
/////////////////////////////////////////
//For nrf24l01's send function
//Return 0 for success,2 for max_times - failed,1,either for failed
unsigned char nrf_just_send(unsigned char *s)
{
	unsigned char sta;
  trans_nrf_buf(TxBuf,s);
  nRF24L01_TxPacket(TxBuf);
	iniT_nrf_buf(TxBuf);					//Reset Txbuf
#if defined IRQ_24L01
	while(NRF24L01IRQ_READ);
#endif
	sta = SPI_Read(STATUS);	// read register STATUS's value
	SPI_RW_Reg(WRITE_REG_24L01 + STATUS,sta);
	if(sta & 0x10)	//Max send times
	{
		SPI_RW_Reg(FLUSH_TX,0xff);	//Clear TX fifo
		return 2;
	}
	if(sta & 0x20)	//Send success
	{
		return 0;
	}
	return 1;	//send faild
  
}
//New
//Check whether connect NRF24L01 correctly
//Return 0 for success and 1 for failed
unsigned char nrf24l01_check(void)
{
//	NRF24L01MOSI_L;
//	NRF24L01SCK_L;
//	NRF24L01CE_L;
//	NRF24L01CSN_L;
//	LED1_L;
//	LED2_L;
//	if(NRF24L01MISO_READ)
//	{
//		NRF24L01MOSI_L;
//		NRF24L01SCK_L;
//		NRF24L01CE_L;
//		NRF24L01CSN_L;
//	}
//	else
//	{
//		NRF24L01MOSI_H;
//		NRF24L01SCK_H;
//		NRF24L01CE_H;
//		NRF24L01CSN_H;	
//	}
//	NRF24L01MOSI_H;
//	NRF24L01SCK_H;
//	NRF24L01CE_H;
//	NRF24L01CSN_H;
//	LED1_H;
//	LED2_H;
//	return 1;
  ///////////////////////////////////
	unsigned char buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	unsigned char i;	 
	SPI_Write_Buf(WRITE_REG_24L01 + TX_ADDR,buf,5);//Write to reg
	SPI_Read_Buf(TX_ADDR,buf,5); //Read from reg
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;
	return 0;	
}

//////////
//New function
void trans_nrf_buf_2(unsigned char *s1,unsigned char *s2,unsigned char *s3)
{
  unsigned char i =0;
  while((i < DATALENTH)&&(*s2 != '\0'))
  {
    *s1 = *s2;
    s1++;
    s2++;
    i++;
  }
  while((i < DATALENTH)&&(*s3 != '\0'))
  {
    *s1 = *s3;
    s1++;
    s3++;
    i++;
  }
  *s1 = '\0';
}

void trans_nrf_buf_3(unsigned char *s1,unsigned char *s2,unsigned char *s3,unsigned char *s4)
{
  unsigned char i =0;
  while((i < DATALENTH)&&(*s2 != '\0'))
  {
    *s1 = *s2;
    s1++;
    s2++;
    i++;
  }
  while((i < DATALENTH)&&(*s3 != '\0'))
  {
    *s1 = *s3;
    s1++;
    s3++;
    i++;
  }
  while((i < DATALENTH)&&(*s4 != '\0'))
  {
    *s1 = *s4;
    s1++;
    s4++;
    i++;
  }
  *s1 = '\0';
}

unsigned char nrf_just_send_2(unsigned char *s1,unsigned char *s2)
{
	unsigned char sta;
  trans_nrf_buf_2(TxBuf,s1,s2);
  nRF24L01_TxPacket(TxBuf);
	iniT_nrf_buf(TxBuf);					//Reset Txbuf
#if defined IRQ_24L01
	while(NRF24L01IRQ_READ);
#endif
	sta = SPI_Read(STATUS);	// read register STATUS's value
	SPI_RW_Reg(WRITE_REG_24L01 + STATUS,sta);
	if(sta & 0x10)	//Max send times
	{
		SPI_RW_Reg(FLUSH_TX,0xff);	//Clear TX fifo
		return 2;
	}
	if(sta & 0x20)	//Send success
	{
		return 0;
	}
	return 1;	//send faild
  
}
/**************************************************/
