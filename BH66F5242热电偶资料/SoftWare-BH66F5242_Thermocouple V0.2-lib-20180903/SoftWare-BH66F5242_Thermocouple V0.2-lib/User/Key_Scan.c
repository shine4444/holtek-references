//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : ISR.c
// Description: 所有中斷函數入口
//Targer Board: None
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/11/20
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"

/************************Key_Scan Variable****************/
volatile	__byte_type  gu8v_KeyCurrent;
volatile	__byte_type   gu8v_KeyDown;			
volatile	u8	gu8v_KeyOld;
volatile	u8	gu8v_KeyNoChangedTime;
volatile	__byte_type  gu8v_KeyPress;

volatile	__byte_type	gu8v_KeyUp;
volatile	u8	gu8v_KeyLast;
volatile	u8 	gu8v_KeyCanChange;
volatile	__byte_type 	gu8v_Key_status;
volatile	u8 	gu8v_Keypress_time;


/********************************************************************
Function:	fun_Key_dealwith
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	fun_Key_init(void)
{
	GPIO_KEY_START_WU = 1;	
	GPIO_KEY_START_PU = 1;
	GPIO_KEY_START_IO = 1;

//	GPIO_KEY_MEMORY_WU	= 1;	
//	GPIO_KEY_MEMORY_PU	= 1;
//	GPIO_KEY_MEMORY_IO	= 1;
		
//	GPIO_KEY_SET_WU	= 1;	
//	GPIO_KEY_SET_PU	= 1;
//	GPIO_KEY_SET_IO	= 1;	
}
/********************************************************************
Function:	fun_Key_dealwith
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	fun_Key_dealwith(void)
{

}

/********************************************************************
Function:	Key_Scan
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	fun_Key_Scan(void)
{

	gu8v_KeyCurrent.u8 = 0;
	
	if(GPIO_KEY_START == 0)
	{
		gu8v_KeyCurrent.bits.b0 = 1;;
	}
//	if(GPIO_KEY_MEMORY == 0)
//	{
//		gu8v_KeyCurrent.bits.b1 = 1;;
//	}
//	if(GPIO_KEY_SET == 0)
//	{
//		gu8v_KeyCurrent.bits.b2 = 1;;
//	}	

	if(gu8v_KeyCurrent.u8 != gu8v_KeyOld)  			//
	{
		gu8v_KeyNoChangedTime = 0;       				//
		gu8v_KeyOld = gu8v_KeyCurrent.u8;        		//
		gu8v_KeyDown.u8 = 0;
		gu8v_KeyUp.u8 = 0;
		return;  										//
	}
	else
	{	
		gu8v_KeyNoChangedTime++;	     				//
		if(gu8v_KeyNoChangedTime >= LUCC_KEY_DEBOUNCE)	//50
		{
			gu8v_KeyNoChangedTime = LUCC_KEY_DEBOUNCE;	
			gu8v_KeyPress.u8 = gu8v_KeyOld;      			//
		    gu8v_KeyDown.u8 = gu8v_KeyPress.u8 & (gu8v_KeyPress.u8 ^ gu8v_KeyLast);// 
			gu8v_KeyUp.u8 |= gu8v_KeyLast&(~gu8v_KeyPress.u8);     //	
		    gu8v_KeyLast = gu8v_KeyPress.u8;            	// 
		}
	}
 	if(gu8v_KeyUp.bits.b0)
	{
		gbv_start_click = 1;
	}	
	if(gu8v_KeyDown.u8 != 0)
	{
		gu8v_halt_time=0;	
	}
	gu8v_KeyUp.u8 =0;
}

