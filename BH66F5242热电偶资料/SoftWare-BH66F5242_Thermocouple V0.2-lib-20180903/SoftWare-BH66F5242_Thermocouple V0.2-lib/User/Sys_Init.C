//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : sys_init.c
// Description: 系統初始化相關程序
//Targer Board: 
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/11/20
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
	SETCTM_10MS();
// 	
// 	//TimeBase 

//	_emi  = 1;	//開啟TimeBase 1作為喚醒檢測
	fun_Key_init();
	Uart_Init();
	
	
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
   	SETHIRC_8MHZ();
 // 	SETLXT_32768(); 
	//WDT
	SETWDTtime8192ms();
	//LVR
	SETLVR_Voltage2_1();
	//IO
	fun_ResetInit();
	
	
	//fun_CAL_REEPROM();	
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

