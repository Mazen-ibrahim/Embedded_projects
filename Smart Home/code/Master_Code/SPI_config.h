/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: SPI               **************/
/***************  Version: 1.00           *************/
/******************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/*

Options:
  1-Rising
  2-Falling
 
*/
#define Clock_Polarity    Rising


/*

Options:
  1-sample
  2-setup
 
*/

#define Clock_Phase       sample



/*
   
Options:
 1-Enable
 2-Disable

*/

#define SPI_Interrupt     Disable

#endif
