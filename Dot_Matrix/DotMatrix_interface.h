/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  HAL            **************/
/***************  SWC: DOT Matrix        **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/


#ifndef DOT_INTERFACE_H_
#define DOT_INTERFACE_H_


/*
 * @brief : Used to Define Initialization status of Dot Matrix
 */
typedef enum
{
	Failed  = 0,
	Success = 1
}Init_Status;


/*
 * @brief : used to initialize Ports for Dot Matrix
 * @param : void
 * @return: Init Status
 */

Init_Status Dot_Matrix_INIT();


/*
 * @brief : Used to Represent Letters or Signs in Dot Matrix
 * @param : pointer to Pattern
 * @return: void
 */

void Dot_Draw_Pattern(u8 *Copy_pu8Pattern);

/*
 * @brief  : Used to Represent Letters in Dot Matrix
 * @param  : name of character to represent
 * @return : void
 */

void Dot_Draw_Letter(u8 copy_u8Letter);


/*
 * @brief  : Used to Represent Numbers
 * @param  : number to Represent
 * @return : void
 */

void Dot_Draw_Number(u8 copy_u8Number);


#endif
