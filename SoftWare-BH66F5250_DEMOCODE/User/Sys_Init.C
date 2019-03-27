//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2018 BY HOLTEK SEMICONDUCTOR INC
//  File Name : sys_init.c
// Description: 
//Targer Board: 
//   MCU      : BH67F5270
//   Author   : ming
//   Date     : 2018/03/26
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"


/********************************************************************
Function: MCU復位初始化
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_ResetInit()
{
//	//IO
	fun_GPIO();
// 	Uart_Init();	
// 	//ptm2
	SETPTM2_5MS();
// 	
// 	//TimeBase 

//	_emi  = 1;	//開啟TimeBase 1作為喚醒檢測
	fun_Key_init();
	
	
	
}
/********************************************************************
Function: MCU上電初始化
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_PowerOnInit()
{
	//LVR
	SETLVR_Voltage2_1();
	//IAP not need	to init
	//EEPROM not need to init
	//RAM
	fun_RamInit();
   	SETHIRC_12MHZ();
  	SETLIRC_32K(); 
	//WDT
	SETWDTtime2048ms();
	//LVR
	SETLVR_Voltage2_1();
	//IO
	fun_ResetInit();
	
	
//	fun_CAL_REEPROM();	
}
/********************************************************************
Function: 關閉各個模塊進入HLAT模式
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_PrepareToHalt()
{



}


//HALT
//SLEEPMode0	@(IDLEN==0  & LVDEN==Disable & WDT Disable )
//Stop:CPU,Fsub,Fs,Disable WDT,LVDEN must Disable

//SLEEPMode1	@(IDLEN==0  & (LVDEN==Disable || WDT Disable) )
//Stop:CPU,Fsub,Fs,
//Run :Enable WDT or LVDEN

//IDLEMode0		@(IDLEN==1  & FSYSON==0 )
//Stop:CPU,Fs
//Run :Fsub

//IDLEMode1		@(IDLEN==1  & FSYSON==1 )
//Stop:CPU
//Run :Fs,Fsub



/********************************************************************
Function: GPIO初始化
INPUT	: none
OUTPUT	: none
NOTE	: 所有IO config為輸出low
********************************************************************/
void fun_GPIO()
{




}
/********************************************************************
Function:Ram_Init
INPUT	:
OUTPUT	:
NOTE	:BH67F2260 
********************************************************************/
void fun_RamInit()
{
	_mp1h = 0;
	_mp1l = 0x80;
	while(_mp1h<RamBankSectorSum)
	{
		for(_tblp = 0x00;_tblp < 128;_tblp++)
		{
			 _iar1 = 0;
			  _mp1l++;
		}
		_mp1l = 0x80;		
		_mp1h++;
	}		
}

