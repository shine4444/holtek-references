//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Main.c
// Description: 
//Targer Board: 
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/11/20
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"
u8	gu8v_halt_time;

void main()
{
//	u8	i;
	//判斷是否是上電復位或者是正常情況下的非正常復位
	//如果成立則執行上電初始化動作，反之則執行WDT溢出初始化
	if(_to ==0 || _pdf ==0)									//WDT1	Reset
	{	
		//上電復位或者是正常情況下的非正常復位
		fun_PowerOnInit();	                                   
		//第一次上電可進入校正模式
		Change_Mode(Sys_Normal_mode);
				
	}
	else													
	{
		//WDT 溢出復位
		fun_ResetInit();

	}

	while(1)
	{	
		//清除看門狗
		GCC_CLRWDT();
		//用於計時
		fun_500ms_polling();
		fun_ADC_Polling();
		Uart_manage();		
		//判斷是否要進入睡眠
		if(gu8v_halt_time<LU8C_HALT_TIME)
		{
			if(_ctmaf)
			{
				//10ms 循環					
				_ctmaf = 0;
				//时间标志位，供work_polling使用
				sys_time();
				//按键扫描
				fun_Key_Scan();	
				//
				switch(gu8v_work_mode)
				{
					case	Sys_Normal_mode:
						Sys_Normal();				
					break;
					case	Sys_Power_On_mode:
						Sys_Power_On();
					break;
		
					case	Sys_Wakeup_mode:
					break;
		
					case	Sys_Measure_mode:
						Sys_Measure();				
		
			
					break;
		
					case	Sys_Find_History_mode:
		//				Sys_Find_History();
					break;		
		
					case	Sys_Set_Time_mode:
		//				Sys_Set_Time();
					break;	
		
					case	Sys_Pressure_Test_mode:
		//				Sys_Pressure_Test();
					break;	
		
					case	Sys_Calibration_mode:
						Sys_Calibration_Time();
					break;	
					case	Sys_Comparison_mode:
		//				Sys_Comparison();
					break;	
					case	Sys_HALT_mode:
						Sys_HALT();
					break;			
					default :
						Change_Mode(Sys_Normal_mode);
					break;
		
				}	

			}
			gbv_500ms = 0;		
			gbv_250ms = 0;	
		}
		else
		{
			Change_Mode(Sys_Normal_mode);
 			fun_PrepareToHalt();
		}
	}
}





