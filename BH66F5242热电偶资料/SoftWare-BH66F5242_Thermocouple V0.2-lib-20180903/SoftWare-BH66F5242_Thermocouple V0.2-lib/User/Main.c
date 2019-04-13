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
	//�Д��Ƿ�����늏�λ������������r�µķ�������λ
	//��������t������늳�ʼ����������֮�t����WDT�����ʼ��
	if(_to ==0 || _pdf ==0)									//WDT1	Reset
	{	
		//��늏�λ������������r�µķ�������λ
		fun_PowerOnInit();	                                   
		//��һ����늿��M��У��ģʽ
		Change_Mode(Sys_Normal_mode);
				
	}
	else													
	{
		//WDT �����λ
		fun_ResetInit();

	}

	while(1)
	{	
		//������T��
		GCC_CLRWDT();
		//���Ӌ�r
		fun_500ms_polling();
		fun_ADC_Polling();
		Uart_manage();		
		//�Д��Ƿ�Ҫ�M��˯��
		if(gu8v_halt_time<LU8C_HALT_TIME)
		{
			if(_ctmaf)
			{
				//10ms ѭ�h					
				_ctmaf = 0;
				//ʱ���־λ����work_pollingʹ��
				sys_time();
				//����ɨ��
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





