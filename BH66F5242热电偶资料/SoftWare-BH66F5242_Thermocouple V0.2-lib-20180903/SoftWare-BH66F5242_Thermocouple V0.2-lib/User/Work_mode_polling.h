//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : work_mode_polling.h
// Description: 
//Targer Board: None
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/11/24
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________


#ifndef _Work_mode_polling_H_
#define	_Work_mode_polling_H_




void fun_work_polling(void);
void fun_500ms_polling(void);
//void	fun_CAL_REEPROM();
void	goto_halt();
void Change_Mode(u8 lu8v_work_mode);

void	goto_low_sleep();
void	goto_deep_sleep();
	
extern	u8	gu8v_work_mode;
extern	u8	gu8v_halt_time;
extern	__byte_type	gu8v_time_flag;
extern	u8	gu8v_public_time;
extern	u8	gu8v_public_count1;
extern	u8	gu8v_public_count;
extern	u8	gu8v_err_code;
#define	gbv_work_polling	gu8v_time_flag.bits.b0
#define	gbv_250ms			gu8v_time_flag.bits.b1
#define	gbv_250ms_tigger	gu8v_time_flag.bits.b2
#define	gbv_500ms			gu8v_time_flag.bits.b3
#define	gbv_500ms_tigger	gu8v_time_flag.bits.b4
#define	gbv_tb1_flag		gu8v_time_flag.bits.b5
#define	gbv_bat_low			gu8v_time_flag.bits.b6

extern	__byte_type			gu8v_sys_flag;
#define	gbv_deep_sleep		gu8v_sys_flag.bits.b0
#define	gbv_get_ntc_temp		gu8v_sys_flag.bits.b1
#define	gbv_corr_ntc		gu8v_sys_flag.bits.b2
#define	gbv_temp_success		gu8v_sys_flag.bits.b3
#define	gbv_uart_start		gu8v_sys_flag.bits.b4
#define	gbv_uart_cal		gu8v_sys_flag.bits.b5
#define	gbv_cal_templ		gu8v_sys_flag.bits.b6
#define	gbv_cal_temph		gu8v_sys_flag.bits.b7

#define	Sys_Normal_mode			0
#define	Sys_Power_On_mode		1
#define	Sys_Wakeup_mode		2
#define	Sys_Measure_mode		3
#define	Sys_Find_History_mode	4
#define	Sys_Set_Time_mode		5
#define	Sys_Pressure_Test_mode	6
#define	Sys_Calibration_mode	7
#define	Sys_Comparison_mode		8
#define	Sys_HALT_mode			9

#define	LU8C_CAL_START_ADDR	0


void 	Sys_Normal();
void 	sys_time();
void 	Sys_Power_On();
void 	Sys_Time_Dis();
void 	Sys_Measure();
//void Sys_Measure_test();
void 	Sys_Find_History();
void 	Sys_Set_Time();
void 	Sys_Pressure_Test();
void 	Sys_Calibration_Time();
void	fun_CAL_REEPROM();
void	fun_cal_pressure(u16 lu16v_pressure);
void 	Sys_init_heart_wave();
void 	Sys_Comparison();
void 	Sys_HALT();
void 	Change_Mode(u8 lu8v_work_mode);
void 	Sys_lower_power();


#endif
