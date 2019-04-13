//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : work_mode_polling.c
// Description: 
//Targer Board: 
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/11/24
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"


//u8	gu8v_halt_time;
u8	gu8v_work_mode;
u8	gu8v_sys_time;
u8	gu8v_public_time;
u8	gu8v_public_count;
u8	gu8v_public_count1;
u8	gu8v_ntc_sample_mode;
u8	gu8v_err_code;
u8	gu8v_correction_mode;
__byte_type	gu8v_time_flag;
__byte_type	gu8v_sys_flag;


u8 	get_current_temp();

/********************************************************************
Function:	fun_work_polling
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
inline	void	 fun_work_polling(void)
{
//		switch(gu8v_work_mode)
//		{
//			case	Sys_Normal_mode:
//				Sys_Normal();				
//			break;
//			case	Sys_Power_On_mode:
//				Sys_Power_On();
//			break;
//
//			case	Sys_Wakeup_mode:
//			break;
//
//			case	Sys_Measure_mode:
//				Sys_Measure();				
//
//	
//			break;
//
//			case	Sys_Find_History_mode:
////				Sys_Find_History();
//			break;		
//
//			case	Sys_Set_Time_mode:
////				Sys_Set_Time();
//			break;	
//
//			case	Sys_Pressure_Test_mode:
//				Sys_Pressure_Test();
//			break;	
//
//			case	Sys_Calibration_mode:
//				Sys_Calibration_Time();
//			break;	
//			case	Sys_Comparison_mode:
////				Sys_Comparison();
//			break;	
//			case	Sys_HALT_mode:
//				Sys_HALT();
//			break;			
//			default :
//				Change_Mode(Sys_Normal_mode);
//			break;
//
//		}	
		
}
u8	gu8v_tb1_count;
/********************************************************************
Function:	fun_500ms_polling
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_500ms_polling(void)
{

}



/********************************************************************
Function:	Change_Mode
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void Change_Mode(u8 lu8v_work_mode)
{
	gbv_corr_ntc = 0;
	gu8v_work_mode = lu8v_work_mode;
	gu8v_public_time = 0;
	gu8v_public_count = 0;
	gu8v_public_count1 = 0;	
	gu8v_Key_status.u8 = 0;
	gu8v_ntc_sample_mode = 0;
	gu8v_NTCMode = 0;
	gu8v_obj_temp_mode = 0;
	gu8v_correction_mode =0;
}

/********************************************************************
Function:	Sys_HALT
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void Sys_HALT()
{
	gu8v_halt_time = LU8C_HALT_TIME;
	
}


/********************************************************************
Function:	Sys_Normal
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void Sys_Normal()
{
	

	if(gbv_start_click||gbv_uart_start)
	{
		gbv_start_click = 0;
		gbv_uart_start = 0;
		Change_Mode(Sys_Measure_mode);

	}
	
//	switch(gu8v_public_count)
//	{
//		case	0:
//
//		break;
//		case	1:
//		
//		break;		
//		case	2:
//		
//		break;	
//		case	3:
//	
//		break;		
//		
//		
//	}	
}	

/********************************************************************
Function:	sys_time
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void sys_time()
{
	gu8v_sys_time++;
	if(gu8v_sys_time == 50)
	{
		gbv_250ms = 1;
		gbv_250ms_tigger = ~gbv_250ms_tigger;
			
	}
	else if(gu8v_sys_time>=100)
	{
		gu8v_sys_time = 0;
		gbv_250ms = 1;
		gbv_250ms_tigger = ~gbv_250ms_tigger;
		gbv_500ms = 1;
		gbv_500ms_tigger = ~gbv_500ms_tigger;
//		gu8v_halt_time++;
		
	}
}

/********************************************************************
Function:	sys_time_init
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void sys_time_init()
{
	gu8v_sys_time = 0;
	gbv_250ms = 0;
	gbv_250ms_tigger = 1;
	gbv_500ms = 0;
	gbv_500ms_tigger = 1;
}

/********************************************************************
Function:	Sys_Power_On
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
inline	void 	Sys_Power_On()
{
//	//LCD DISPLAY 2S
//	//如果start 按鍵動作小於3次進入設置時間模式
//	//如果start 按鍵動作小於3-4次進入壓力比對模式模式
//	//如果start 按鍵動作小於5次以上進入校正模式模式	
//	fun_LCD_all(0x0ff);
//	if(gbv_500ms)
//	{
////		gbv_500ms = 0;
//		gu8v_public_time++;
//		if(gu8v_public_time>=4)
//		{
//			gu8v_public_time = 0;
//			
//			//
//			if(gu8v_public_count == 5)
//			{
//				Change_Mode(Sys_Calibration_mode);
//				
//			}
//			else
//			{
//				goto_halt();
//								
//			}
//			gu8v_public_count= 0;
//			fun_LCD_all(0);
//
//		}
//	}
//	//
//	if(gbv_set_click)
//	{
//		gbv_set_click = 0;
//		gu8v_public_time = 2;
//		gu8v_public_count ++;
//		
//	}
}


/********************************************************************
Function:	Sys_Time_Dis
INPUT	:
OUTPUT	:	
NOTE	:    8
********************************************************************/
inline	void 	Sys_Time_Dis()
{


}




/********************************************************************
Function:	Sys_Measure
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
inline	void 	Sys_Measure()
{

	switch(gu8v_public_count)
	{
		case	0:
			//測量NTC 
			if(fun_get_NTC())
			{
				gu8v_public_count++;	
			}
			else
			{
				
				
			}
			
		break;
		case	1:
			//測量熱電偶的輸出電壓
			if(fun_get_VTP())
			{	

				fun_CAL_REEPROM();
				fun_RNTC_Calculate();	
				fun_Vsen_Calculate(gu16v_ntc_res.u16);					
				fun_Tobj_Calculate();
				gu16v_tp_temp[0].S16 = gu16v_current_temp.S16;
				gbv_temp_success = 1;
				gu8v_public_count = 0;
				Change_Mode(Sys_Normal_mode);				
			}
			else
			{
				
			}			
			
		break;			
		case	2:
			
			
			
			
			
		break;		
		case	3:
		
		break;			
		
				
		
	}

	
}




/********************************************************************
Function:	Sys_Find_History
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
inline	void 	Sys_Find_History()
{	
	

	
}


///********************************************************************
//Function:	Sys_Set_Time
//INPUT	:
//OUTPUT	:	
//NOTE	:   
//********************************************************************/
//void 	Sys_Set_Time()
//{
//
//
//}


/********************************************************************
Function:	Sys_Pressure_Test_Time
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
inline	void 	Sys_Pressure_Test()
{

}

/********************************************************************
Function:	Sys_Calibration_Time
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
inline	void 	Sys_Calibration_Time()
{	

	switch(gu8v_correction_mode)
	{
		case	0://進入溫度測量
			gu16v_correction_K2.u16 = LU16C_K2_RANGE_Default;
			gu16v_correction_K1.u16 = LU16C_K1_RANGE_Default;
			gu16v_cal_templ.u16 = mac_CorrTemp_Low;	
			gu16v_cal_temph.u16 = mac_CorrTemp_High;			
			if(fun_get_NTC())
			{		
				gbv_corr_ntc =1;
			}			
			if(gbv_corr_ntc)
			{
				if(gbv_start_click)
				{
					gbv_start_click = 0;
					gu8v_correction_mode =1;					
				}
				if(gbv_cal_templ)
				{
					gbv_cal_templ = 0;
					gu8v_correction_mode = 1;	
					gu16v_cal_templ.u16 = (u16)array_uart_rxbuff[4]*256+array_uart_rxbuff[5];					
									
				}
				
			}
			break;
		case	1:
			if(fun_get_VTP())
			{
				gu8v_correction_mode++;
				gbv_corr_ntc = 0;	
				
				gu16v_vtp_buff1.S32 = gu16v_vtp.S32;
							
			}

		break;
		case	2:
			if(gbv_start_click)
			{
				gbv_start_click = 0;
				gu8v_correction_mode = 3;					
			}
			if(gbv_cal_temph)
			{
				gbv_cal_temph = 0;
				gu8v_correction_mode = 3;	
				gu16v_cal_temph.u16 = (u16)array_uart_rxbuff[4]*256+array_uart_rxbuff[5];					
									
			}					
		break;	
		
		case 	3:
			if(fun_get_VTP())
			{
				gu8v_correction_mode++;
				gbv_corr_ntc = 0;	
				
				gu16v_vtp_buff2.S32 = gu16v_vtp.S32;		
				
			}		

		break;
		case 4:
			
			fun_RNTC_Calculate();	
			fun_Vsen_Calculate(gu16v_ntc_res.u16);	
							
			fun_CORRECTION_Calculate();				
			//將數據存入 eeprom 中
			fun_Write_EEPROM(LU8C_CAL_START_ADDR+0,0x55);			
			fun_Write_EEPROM(LU8C_CAL_START_ADDR+1,gu16v_correction_K1.byte.byte0);
			fun_Write_EEPROM(LU8C_CAL_START_ADDR+2,gu16v_correction_K1.byte.byte1);
			fun_Write_EEPROM(LU8C_CAL_START_ADDR+3,gu16v_correction_K2.byte.byte0);
			fun_Write_EEPROM(LU8C_CAL_START_ADDR+4,gu16v_correction_K2.byte.byte1);					
	
			
			Change_Mode(Sys_Normal_mode);
		break;
		
	


		default: break;
	}
}

/********************************************************************
Function:fun_CAL_WEEPROM
INPUT	:
OUTPUT	:
NOTE	:none
*******************************************************************/
void	fun_CAL_WEEPROM()
{
	fun_Write_EEPROM(0,0x55);
	fun_Write_EEPROM(1,gu16v_correction_K2.byte.byte1);
	fun_Write_EEPROM(2,gu16v_correction_K2.byte.byte0);	
//	fun_Write_EEPROM(EEPROM_0mmhg_H,gu16v_cal_0mmhg.byte.byte1);	
//	fun_Write_EEPROM(EEPROM_0mmhg_L,gu16v_cal_0mmhg.byte.byte0);
}

/********************************************************************
Function:fun_CAL_WEEPROM
INPUT	:
OUTPUT	:
NOTE	:none
*******************************************************************/
void	fun_CAL_REEPROM()
{
	if(fun_Read_EEPROM(0) == 0x55)
	{
		gu16v_correction_K1.byte.byte0 = fun_Read_EEPROM(1);
		gu16v_correction_K1.byte.byte1 = fun_Read_EEPROM(2);	
		gu16v_correction_K2.byte.byte0 = fun_Read_EEPROM(3);
		gu16v_correction_K2.byte.byte1 = fun_Read_EEPROM(4);		
	}
	else
	{
		gu16v_correction_K2.u16 = LU16C_K2_RANGE_Default;
		gu16v_correction_K1.u16 = LU16C_K1_RANGE_Default;
		
	}
}


/********************************************************************
Function:fun_cal_pressure
INPUT	:
OUTPUT	:
NOTE	:none
*******************************************************************/
void	fun_cal_pressure(u16 lu16v_pressure)
{

}



inline	void 	Sys_Comparison()
{

}

void	goto_halt()
{
	gu8v_halt_time = LU8C_HALT_TIME;
	gu8v_work_mode = 0;
}


void	goto_low_sleep()
{
	gu8v_halt_time = LU8C_HALT_TIME;
	gu8v_work_mode = 0;
	gbv_deep_sleep = 0;
}

void	goto_deep_sleep()
{
	gu8v_halt_time = LU8C_HALT_TIME;
	gu8v_work_mode = 0;
	gbv_deep_sleep = 1;
}


u8	gu8v_lower_power_count;
	
/********************************************************************
Function:	Sys_lower_power
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void 	Sys_lower_power()
{	
//	volatile u16 	gu16v_battery_ad;	
//	if(gbv_250ms)
//	{
//		gu16v_battery_ad = fun_Get_ADC(AN7)/16;
//		gu16v_battery_ad = ((u32)gu16v_battery_ad*133)/256;//*3.3*13.3/(256*3.3);
//		gu8v_battery_votage = (u8)gu16v_battery_ad;
//		if(gu8v_battery_votage<43)	
//		{
//			gu8v_lower_power_count ++;
//			if(gu8v_battery_votage>5)
//			{
//				gu8v_battery_votage = 5;
//				gbv_bat_low = 1;
//				
//			}
//			
//			
//		}	
//		else
//		{
//			gu8v_lower_power_count = 0;
//			
//		}
//		
//	}
//	
//	if(gbv_bat_low)
//	{
//		LCD_ICON(LBC_FFLASH,LCD_Battery_ADDR);
//		
//	}
//	else
//	{
//		LCD_ICON(LBC_CLR,LCD_Battery_ADDR);
//	}	
	
}

/********************************************************************
Function:	Sys_lower_power
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
u8 	get_current_temp()
{	
	
//	switch(gu8v_ntc_sample_mode)
//	{
//		case	0:
//		//使能NTC通道测量
//			fun_TEMP1_INIT();
//			fun_ADC_Enable();
//			gu8v_ntc_sample_mode++;					
//		break;
//					
//		case	1:
//		//检测是否采样完成
//			if(gbv_adc_success)
//			{
//				gbv_adc_success = 0;
//				gu16v_ntc_adc.u16 = gu32v_adc_data.u32;
//				gu8v_ntc_sample_mode++;							
//			}
//					
//		break;
//		case	2:
//		//使能标准电阻通道测量
//			fun_TEMP2_INIT();
//			fun_ADC_Enable();
//			gu8v_ntc_sample_mode++;						
//		break;
//					
//		case	3:
//		//检测是否采样完成
//			if(gbv_adc_success)
//			{
//				gbv_adc_success = 0;
//				gu16v_std_res_adc.u16 = gu32v_adc_data.u32;
//				gu8v_ntc_sample_mode=0;	
//				fun_RNTC_Calculate();	
//				fun_Vsen_Calculate(gu16v_ntc_res.u16);
//				return	1;												
//			}					
//					
//		break;					
//						
//		case	4:
//									
//					
//		break;													
//
//	}
	return	0;	
}