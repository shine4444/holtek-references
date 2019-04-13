//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Set_time.c
// Description: 
//Targer Board: 
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/12/18
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"

u8	gu8t_time[6];

const	u8	T_TIME_MIN[5]= {14,1,1,0,0};
//�
const	u8	T_TIME_MAX[5]= {99,12,31,23,59};
//�
const	u8	T_DAY_MAX[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};


// *******************************************************************
// Function:	Sys_Set_Time
// INPUT	:
// OUTPUT	:	
// NOTE	:   
// *******************************************************************
void 	Sys_Set_Time()
{
//	u8	lu8v_user;
	switch(gu8v_public_count1)
	{
		case	0:
			//�O��user
//			fun_LCD_user(LBC_FFLASH,gu8v_user_num);			
//			lu8v_user = gu8v_user_num;
//			if(gbv_memory_click)
//			{
//				gbv_memory_click = 0;
//				lu8v_user++;
//				gu8v_sys_flag.u8 &= 0xfc;
//				gu8v_sys_flag.u8 |= lu8v_user&0x03;
//				
//			}
//			else
//			{
//				if(gbv_memory_long_Press)
//				{
//					if(gbv_250ms)
//					{
//						gbv_250ms = 0;
//						if(gbv_memory_press)	
//						{
//							sys_time_init();		
//							lu8v_user++;
//							gu8v_sys_flag.u8 &= 0xfc;
//							gu8v_sys_flag.u8 |= lu8v_user&0x03;										
//						}
//						else
//						{
//							gbv_memory_long_Press = 0;
//						}						
//						
//					}
//					
//				}
//				
//			}
//			
//			
//			
//			if(gbv_start_click)
//			{
				gbv_start_click = 0;
				gu8v_public_count1++;
				fun_LCD_user(LBC_CLR,gu8v_user_num);	
//			}		

		break;
		case	1:
			
			if(gbv_memory_click)
			{
				gbv_memory_click = 0;
				sys_time_init();		
				fun_TIME_ADD(gu8v_public_count);
			}
			else
			{
				if(gbv_memory_long_Press)
				{
					if(gbv_250ms)
					{
						gbv_250ms = 0;
						if(gbv_memory_press)	
						{
							sys_time_init();		
							fun_TIME_ADD(gu8v_public_count);	
		//					fun_TIME_SUB(gu8v_public_count);			
						}
						else
						{
							gbv_memory_long_Press = 0;
						}
						
					}				
				}
		
			}	

	
			if(gu8v_public_count == 0)
			{
				//���趨ʱ��
 				fun_play_voice(VOICE_ADD_SET_TIME);				
				LCD_DISP_HOUR_ON(LBC_CLR,20);
				LCD_DISP_MINUTE_ON(LBC_FLASH,gu8t_time_year);
			}
			else if(gu8v_public_count == 1)
			{
				LCD_DISP_MONTH_ON(LBC_FLASH,gu8t_time_month);
				LCD_DISP_DAY_ON(LBC_SET,gu8t_time_day);	
				LCD_DISP_MINUTE_ON(LBC_CLR,gu8t_time_year);
				LCD_ICON(LBC_SET,LCD_M_ADDR);
				LCD_ICON(LBC_SET,LCD_D_ADDR);										
			}
			else if(gu8v_public_count == 2)
			{
				LCD_DISP_MONTH_ON(LBC_SET,gu8t_time_month);
				LCD_DISP_DAY_ON(LBC_FLASH,gu8t_time_day);
						
				
			}
			else if(gu8v_public_count == 3)
			{
				LCD_DISP_HOUR_ON(LBC_FLASH,gu8t_time_hour);
				LCD_DISP_MINUTE_ON(LBC_SET,gu8t_time_minute);
				LCD_ICON(LBC_SET,LCD_COLD_ADDR);		
				LCD_DISP_DAY_ON(LBC_SET,gu8t_time_day);		
			}
			else if(gu8v_public_count == 4)
			{
				LCD_DISP_HOUR_ON(LBC_SET,gu8t_time_hour);
				LCD_DISP_MINUTE_ON(LBC_FLASH,gu8t_time_minute);
		//		LCD_ICON(LBC_SET,LCD_COL_ADDR);		
			}
			else
			{
		
		
			}	
			
			if(gbv_start_click)
			{
				gbv_start_click = 0;
				gu8v_public_count++;
				fun_LCD_user(LBC_CLR,gu8v_user_num);
				if(gu8v_public_count>4)
				{
					gu8v_public_count = 0;
					gu8v_public_count1 ++;
					fun_LCD_all(0);
					fun_play_voice_init();
					//���趨����
					fun_play_voice(VOICE_ADD_SET_VOICE);					
					
				}	
				if(gu8v_public_count == 0)
				{
					fun_play_voice_init();
					
				}
			}					
					
		break;
		case	2:
			
			
			
 //			LCD_UPDATA_vol();
 			LCD_UPDATA_ERR(1);
//			LCD_DISP_SYS_ON(LBC_HID,0);
			LCD_DISP_SYS_ON(LBC_SET,50);
			LCD_DISP_DIA_ON(LBC_SET,gu8v_voice_vol);	
			if(gbv_memory_click)
			{
				gbv_memory_click = 0;
				gu8v_voice_vol++;
				if(gu8v_voice_vol>10)
				{
					gu8v_voice_vol = 4;
				}	
				fun_play_voice_init();
				fun_play_voice(gu8v_voice_vol);				
			}	

			if(gbv_start_click)
			{
				gbv_start_click = 0;
				gu8v_public_count1 =0;
				fun_LCD_all(0);
				fun_play_voice_init();			
			}			
						
		break;
		case	3:
		
			
		break;
									
		
	}
	
	if(gbv_start_long_Press)
	{
		gbv_start_long_Press = 0;
		Change_Mode(Sys_Normal_mode);					
		
	}

}



void	fun_init_time(void)
{
	gu8t_time_year = 14;
	gu8t_time_month = 10;	
	gu8t_time_day = 1;	
	gu8t_time_hour = 12;
	gu8t_time_minute = 30;
	gu8t_time_second = 0;	

	gu16v_sys = 120;
	gu16v_dia = 80;
	gu8v_heart = 80;
	

}



/*******************************************************************************************
** 函数名称: SBR_TIME_ADD
** 函数描述: 相應的位累加
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
u8	fun_TIME_ADD(u8 lu8c_guide)
{
	u8 	lu8c_min,lu8c_max;
	//
	gu8t_time[lu8c_guide]++;
	
	//
	lu8c_min =T_TIME_MIN[lu8c_guide];
	//
	lu8c_max =T_TIME_MAX[lu8c_guide];
	//
	if(gu8v_public_count == 2)
	{
		//
		lu8c_min = 1;
		lu8c_max = T_DAY_MAX[gu8t_time_month];
		if(gu8t_time_month == 2)
		{
			//
			if((gu8t_time_year & 0b00000011) == 0)
			{
				//
				lu8c_max ++;
			}
		}		
	}
	//
//
	if(gu8t_time[lu8c_guide]<lu8c_min)
	{
		gu8t_time[lu8c_guide] = lu8c_min;
	}
	if(gu8t_time[lu8c_guide]>lu8c_max)
	{
		gu8t_time[lu8c_guide] = lu8c_min;	
		return	1;	
	}
		return	0;		
}

/*******************************************************************************************
** 函数名称: SBR_TIME_ADD
** 函数描述: 相應的位累加
** 输入参数: �?
** 输出参数: �?
*******************************************************************************************/
u8	fun_TIME_ADD1(u8 lu8c_guide)
{
	u8 	lu8c_min,lu8c_max;
	//
	gu8t_time[lu8c_guide]++;
	
	//
	lu8c_min =T_TIME_MIN[lu8c_guide];
	//
	lu8c_max =T_TIME_MAX[lu8c_guide];
	//
	if(gu8v_public_count == 2)
	{
		//
		lu8c_min = 1;
		lu8c_max = T_DAY_MAX[gu8t_time_month];
		if(gu8t_time_month == 2)
		{
			//
			if((gu8t_time_year & 0b00000011) == 0)
			{
				//
				lu8c_max ++;
			}
		}		
	}
	//
//
	if(gu8t_time[lu8c_guide]<lu8c_min)
	{
		gu8t_time[lu8c_guide] = lu8c_min;
	}
	if(gu8t_time[lu8c_guide]>lu8c_max)
	{
		gu8t_time[lu8c_guide] = lu8c_min;	
		return	1;	
	}
		return	0;		
}


/*******************************************************************************************
** 函数名称: SBR_TIME_ADD
** 函数描述: 相應的位累加
** 输入参数: 无
** 输出参数: 无 
*******************************************************************************************/
u8	fun_TIME_SUB(u8 lu8c_guide)
{
	u8 	lu8c_min,lu8c_max;
	//
	gu8t_time[lu8c_guide]--;
	
	//
	lu8c_min =T_TIME_MIN[lu8c_guide];
	//
	lu8c_max =T_TIME_MAX[lu8c_guide];
	//
	if(gu8v_public_count == 2)
	{
		//
		lu8c_min = 1;
		lu8c_max = T_DAY_MAX[gu8t_time_month];
		if(gu8t_time_month == 2)
		{
			//
			if((gu8t_time_year & 0b00000011) == 0)
			{
				//
				lu8c_max ++;
			}
		}		
	}
	//
//
	if(gu8t_time[lu8c_guide]<lu8c_min)
	{
		gu8t_time[lu8c_guide] = lu8c_max;
	}
	if(gu8t_time[lu8c_guide]>lu8c_max)
	{
		gu8t_time[lu8c_guide] = lu8c_max;	
		return	1;	
	}
		return	0;		
}
