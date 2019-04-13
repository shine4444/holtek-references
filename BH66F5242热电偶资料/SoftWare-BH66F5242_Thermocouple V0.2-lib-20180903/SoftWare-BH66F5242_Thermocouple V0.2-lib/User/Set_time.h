//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : ADC.h
// Description: ADC”µ“þÞD“Q
//Targer Board: None
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/11/20
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________


#ifndef _Set_time_H_
#define _Set_time_H_


void 	sys_time_init();
void 	Sys_Set_Time();
void	fun_init_time(void);
u8	fun_TIME_ADD(u8 lu8c_guide);
u8	fun_TIME_ADD1(u8 lu8c_guide);
u8	fun_TIME_SUB(u8 lu8c_guide);
// typedef struct {
// 	u8 		year;
// 	u8		month;
// 	u8		day;
// 	u8 		hour;
// 	u8		minute;
// 	u8		second;	
// } __time;
// static volatile __time	gu8t_time __attribute__((at(0x4fa)));;

extern	u8	gu8t_time[6]; //__attribute__((at(0x1fa)));
#define	gu8t_time_year			gu8t_time[0]
#define	gu8t_time_month			gu8t_time[1]
#define	gu8t_time_day			gu8t_time[2]
#define	gu8t_time_hour			gu8t_time[3]
#define	gu8t_time_minute		gu8t_time[4]
#define	gu8t_time_second 		gu8t_time[5]
#endif

