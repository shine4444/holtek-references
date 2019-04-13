//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Sys_init.c
// Description: 系統初始化子程序
//   Customer : Holtek Demo Code
//Targer Board: PICOOC_Display
//     MCU    : BH66F5242
//___________________________________________________________________
//___________________________________________________________________
#ifndef SYS_INIT_H_
#define SYS_INIT_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_PowerOnInit();
void fun_PrepareToHalt();
void fun_ResumeWork();

extern  volatile unsigned char gu8v_haltTime;
extern  volatile bit gbv_HALTMODE;		// 休眠模式 1 使能  0 除能

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Userdefine @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//					@---------------WDT config---------------@
#define SETWDTDISABLE()			{ _wdtc = 0xA8;}
#define SETWDTTIME_8MS()		{ _wdtc = 0x50;}
#define SETWDTTIME_32MS()		{ _wdtc = 0x51;}
#define SETWDTTIME_125MS()		{ _wdtc = 0x52;}
#define SETWDTTIME_500MS()		{ _wdtc = 0x53;}
#define SETWDTTIME_1000MS()		{ _wdtc = 0x54;}
#define SETWDTTIME_2000MS()		{ _wdtc = 0x55;}
#define SETWDTTIME_4000MS()		{ _wdtc = 0x56;}
#define SETWDTTIME_8000MS()		{ _wdtc = 0x57;}
//					@-------------LVR config--------------@
#define  SETLVR_2_1V()			{ _lvrc = 0x55;}
#define  SETLVR_2_55V()			{ _lvrc = 0x33;}
#define  SETLVR_3_15V()			{ _lvrc = 0x88;}
#define  SETLVR_3_8V()			{ _lvrc = 0xAA;}
#define SET_MCU_RESET()         { _rstc = 0x00;}
//					@-------------LED Current-------------@
#define SETLEDCURRENT_LEVEL0()	{ _sledc0 = 0x00; _sledc1 = 0x00;}
#define SETLEDCURRENT_LEVEL1()	{ _sledc0 = 0x15; _sledc1 = 0x01;}
#define SETLEDCURRENT_LEVEL2()	{ _sledc0 = 0x2A; _sledc1 = 0x02;}
#define SETLEDCURRENT_LEVEL3()	{ _sledc0 = 0x3F; _sledc1 = 0x03;}
//					@-------------LVD config--------------@
//Setting in LVD.h
//					@-------------EEPROM config----------@
//Setting in EEPROM.h
//					@-------------IO config--------------@
//Setting in GPIO.h
//                  @---------------CTMnC0---------------@
#define CTMC0_Default		0x20        // CLOCK  fsys/16  // 4us
#define CTMC1_Default		0xC1		// 定時器模式,A比較器中斷
#define CTMAL_Default		600%256
#define CTMAH_Default		600/256
//                     @--------------TBC-------- - ------@
#define SETTIMEBASE0_8MS()		{ _pscr = 0x03; _tb0c = 0x00;}
#define SETTIMEBASE0_16MS()		{ _pscr = 0x03; _tb0c = 0x01;}
#define SETTIMEBASE0_32MS()		{ _pscr = 0x03; _tb0c = 0x02;}
#define SETTIMEBASE0_62MS()		{ _pscr = 0x03; _tb0c = 0x03;}
#define SETTIMEBASE0_124MS()	{ _pscr = 0x03; _tb0c = 0x04;}
#define SETTIMEBASE0_250MS()	{ _pscr = 0x03; _tb0c = 0x05;}
#define SETTIMEBASE0_500MS()	{ _pscr = 0x03; _tb0c = 0x06;}
#define SETTIMEBASE0_1000MS()	{ _pscr = 0x03; _tb0c = 0x07;}
#define SETTIMEBASE0_ENABLE()	{ _tb0f = 0x00; _tb0e = 0x01; _tb0on = 1;}
#define SETTIMEBASE0_DISABLE()	{ _tb0on = 0;}

#define SETTIMEBASE1_8MS()		{ _pscr = 0x03; _tb1c = 0x00;}
#define SETTIMEBASE1_16MS()		{ _pscr = 0x03; _tb1c = 0x01;}
#define SETTIMEBASE1_32MS()		{ _pscr = 0x03; _tb1c = 0x02;}
#define SETTIMEBASE1_62MS()		{ _pscr = 0x03; _tb1c = 0x03;}
#define SETTIMEBASE1_124MS()	{ _pscr = 0x03; _tb1c = 0x04;}
#define SETTIMEBASE1_250MS()	{ _pscr = 0x03; _tb1c = 0x05;}
#define SETTIMEBASE1_500MS()	{ _pscr = 0x03; _tb1c = 0x06;}
#define SETTIMEBASE1_1000MS()	{ _pscr = 0x03; _tb1c = 0x07;}
#define SETTIMEBASE1_ENABLE()	{ _tb1f = 0x00; _tb1e = 0x01; _tb1on = 1;}
#define SETTIMEBASE1_DISABLE()	{ _tb1on = 0;}
//						@-------Internal Power config--------@
//Setting in ADC.h
//						@------------ADC config--------------@
//Setting in ADC.h
//						@-------------SIM config-------------@
//Setting in SIM.h
#endif
