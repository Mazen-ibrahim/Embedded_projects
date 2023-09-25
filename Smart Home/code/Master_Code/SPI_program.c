/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: SPI               **************/
/***************  Version: 1.00           *************/
/******************************************************/



/************************ Include Libraries *************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
/*******************************************************************/

/*********************** Include MCAL ******************************/
#include"SPI_registers.h"
#include"SPI_private.h"
#include"SPI_interface.h"
#include"SPI_config.h"
/*******************************************************************/


//Pointer To Fucntion to Hold Notification Fucntion
static void(*SPI_CallBack)(void) = NULL;

//Pointer To Variable To Hold SPI DATA
static u8 *SPI_DATA = NULL;

void SPI_void_MasterInit()
{

    //Master Intialization
	SET_BIT(SPCR,SPCR_MSTR);

	//Select Clock Polarity
   #if Clock_Polarity == Rising
	  CLR_BIT(SPCR,SPCR_CPOL);

   #elif Clock_Polarity == Falling
	  SET_BIT(SPCR,SPCR_CPOL);

 #endif

	//Select Clock Phase
   #if Clock_Phase == sample
      CLR_BIT(SPCR,SPCR_CPHA);

   #elif Clock_Phase == setup
      SET_BIT(SPCR,SPCR_CPHA);

 #endif
 
 
    #if SPI_Interrupt == Enable
	  SET_BIT(SPCR,SPCR_SPIE)
 
 #endif

    //select Clock prescalar(divide by 16)
       SET_BIT(SPCR,SPCR_SPR0);
       CLR_BIT(SPCR,SPCR_SPR1);
       CLR_BIT(SPSR,SPSR_SPI2X);

	//Enable SPI
	SET_BIT(SPCR,SPCR_SPE);

}


void SPI_void_SlaveInit()
{
	//Slave Intialization
	CLR_BIT(SPCR,SPCR_MSTR);

	//Select Clock Polarity
   #if Clock_Polarity == Rising
	  CLR_BIT(SPCR,SPCR_CPOL);

   #elif Clock_Polarity == Falling
	  SET_BIT(SPCR,SPCR_CPOL);

 #endif

	//Select Clock Phase
   #if Clock_Phase == sample
      CLR_BIT(SPCR,SPCR_CPHA);

   #elif Clock_Phase == setup
      SET_BIT(SPCR,SPCR_CPHA);

 #endif
  
    #if SPI_Interrupt == Enable
	  SET_BIT(SPCR,SPCR_SPIE)
 
 #endif


	//Enable SPI
	SET_BIT(SPCR,SPCR_SPE);

}


u8 SPI_u8_Synctransceive(u8 copy_u8Data)
{
    //Send The Data
	SPDR = copy_u8Data;

	//Wait (Busy waiting) until transfer is complete
	while(GET_BIT(SPSR,SPSR_SPIF)==0);

	//Get Exchange Data
	return SPDR;

}


void SPI_u8_Asynctransceive(u8 copy_u8Data)
{
	//Send The Data
	SPDR = copy_u8Data;
	
}


void SPI_void_EnableInterrupt()
{
    SET_BIT(SPCR,SPCR_SPIE);
}


void SPI_void_DisableInterrupt()
{
	CLR_BIT(SPCR,SPCR_SPIE);
}



u8 SPI_NotificationFucntion(u8 *Copy_u8Value , void(*SPI_CallBackFucntion)(void))
{
	u8 Local_Status  = SPI_OK;
	
	if( Copy_u8Value == NULL || SPI_CallBackFucntion == NULL)
	    Local_Status = NULL_POINTER;
    else 
	{
		SPI_DATA = Copy_u8Value;
		SPI_CallBack = SPI_CallBackFucntion;
	}
	
	return Local_Status;
}



// ISR Of SPI
void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	//Get SPI Data
	*SPI_DATA = SPDR;
	
	//Call Notification Fucntion 
	SPI_CallBack();
}
