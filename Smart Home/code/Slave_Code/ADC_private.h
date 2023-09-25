/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: ADC               **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

//To Select Voltage Refrence of ADC
#define AREF          1
#define AVCC          2
#define INTERNAL_VCC  3


//Enable ADC_Left Right Adjust
#define Enable_LRA    1
#define Disable_LRA   2
#define Enable        3
#define Disable       4

//To Select PreScaler
#define two            0b11111000
#define four           0b11111010
#define eight          0b11111011
#define sixthteen      0b11111100
#define thirtyTwo      0b11111101
#define Sixthfour      0b11111110
#define oneTwenyEight  0b11111111
#define Pre_BitsClear  0b11111000

//To Select Channel
#define SingleEnded_ADC0   0
#define SingleEnded_ADC1   1
#define SingleEnded_ADC2   2
#define SingleEnded_ADC3   3
#define SingleEnded_ADC4   4
#define SingleEnded_ADC5   5
#define SingleEnded_ADC6   6
#define SingleEnded_ADC7   7
#define MUX_BITS_Clear     0b11100000

//ADC State
#define IDLE    0
#define Busy    1

//ADC Sources
#define SINGLE_CHANNEL   1
#define CHAIN_CHANNEL    2




#endif
