/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: SPI               **************/
/***************  Version: 1.00           *************/
/******************************************************/


#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

#define SPCR          *((volatile u8*)0x2D)           //SPI Control Register
#define SPCR_SPIE     7                               //SPI Interrupt Enable
#define SPCR_SPE      6                               //SPI Enable
#define SPCR_DORD     5                               //SPI Data Order
#define SPCR_MSTR     4                               //SPI Master/Slave Select
#define SPCR_CPOL     3                               //SPI Clock Polarity
#define SPCR_CPHA     2                               //SPI Clock Phase
#define SPCR_SPR1     1                               //SPI Clock Rate Bit(1)
#define SPCR_SPR0     0                               //SPI Clock Rate Bit(0)


#define SPSR          *((volatile u8*)0x2E)           //SPI Status Register
#define SPSR_SPIF     7                               //SPI Interrupt Flag
#define SPSR_WCOL     6                               //SPI Write Collision Flag
#define SPSR_SPI2X    0


#define SPDR          *((volatile u8*)0x2F)             //SPI Data Register


#endif
