//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2018 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Main.c
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
u8	gu8v_halt_time;

u8	gu8v_PGA;
u8	gu8v_SPEED;

void main()
{
//	u8	i;
	//判斷是否是上電復位或者是正常情況下的非正常復位
	//如果成立則執行上電初始化動作，反之則執行WDT溢出初始化
	if(_to ==0 || _pdf ==0)									//WDT1	Reset
	{	
		//上電復位或者是正常情況下的非正常復位
		fun_PowerOnInit();	                                   
		fun_ADC_INIT();
		fun_ADC_Enable();	
		SET_DAC_ENABLE();
		SET_DACVREF_VOREG();
		SET_DSOP_VCM() ;
		Uart_Init();		
	}
	else													
	{
		//WDT 溢出復位
		fun_ResetInit();

	}
   // TEST_LCD()  ;  

	while(1)
	{	
		//清除看門狗
		GCC_CLRWDT();
		//用於計時
		
		//判斷是否要進入睡眠
		if(gu8v_halt_time<LU8C_HALT_TIME)
		{
			if(_ptm2af)
			{	
				//10ms 循環					
				_ptm2af = 0;
				//按键扫描
				fun_Key_Scan();	
				//
				//fun_work_polling();
				

				gu8v_PGA++;
				if(gu8v_PGA>=8)
				{
					gu8v_PGA = 0;
					fun_ADC_Polling();
				}
//				if(gu8v_PGA == 0)
//				{
//					SET_ADC_PGA_1();		
//					
//				}
//				else if(gu8v_PGA == 1)
//				{
//					SET_ADC_PGA_2();				
//				}
//				else if(gu8v_PGA == 2)
//				{
//					SET_ADC_PGA_4();	
//				}					
//				else if(gu8v_PGA == 3)
//				{
//					SET_ADC_PGA_8();
//				}
//				else if(gu8v_PGA == 4)
//				{
//					SET_ADC_PGA_16();
//				}					
//				else if(gu8v_PGA == 5)
//				{
//					SET_ADC_PGA_32();
//				}					
//				else if(gu8v_PGA == 6)
//				{
//					SET_ADC_PGA_64();
//				}					
//				else if(gu8v_PGA == 7)
//				{
//					SET_ADC_PGA_128();
//				}										
					
				
				
				
				if(gbv_set_up)
				{
					gbv_set_up = 0;
					GCC_NOP();
					if(gu8v_SPEED>=4)
					{
						gu8v_SPEED = 0;
						
					}					
					if(gu8v_SPEED == 0)
					{
							
						
					}
					else if(gu8v_SPEED == 1)
					{
						
					}
					else if(gu8v_SPEED == 2)
					{
						
					}					
					else if(gu8v_SPEED == 3)
					{
						
					}					
				}				
				
			}		
		}
		else
		{

		}
	}
}





