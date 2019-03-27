//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2018 BY HOLTEK SEMICONDUCTOR INC
//  File Name : mcuconfig
// Description: 
//Targer Board: 
//   MCU      : BH67F5270
//   Author   : ming
//   Date     : 2018/03/26
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#ifndef _MCUCONFIG_H_
#define _MCUCONFIG_H_


#define SYS_HIGH_FREQUENCY_OSC_12MHZ
//#define SYS_BH67F5270


//#define Debug
//定義 IAR1 方便 bit 操作
static volatile __byte_type  SFR_iar1 __attribute__((at(0x02)));

//設置初始化 rambank 個數
#define RamBankSectorSum	4
#define LU8C_HALT_TIME		20

//__________________________________________________________________//
//					-----ISR VECTOR Defination------;
//中斷入口地址
#define	START_VECTOR			0x000		//主程序
#define	INT0_VECTOR				0x004		//Intrrupt 0
#define	INT1_VECTOR				0x008		//Intrrupt 1
#define ADC_VECTOR				0x0C		//ADC 中斷
#define	MF0_VECTOR				0x0010		//復合中斷 0
#define	MF1_VECTOR				0x0014		//復合中斷 1
#define MF2_VECTOR				0x018		//復合中斷 2
#define SCF_VECTOR				0x01C		//SCF中斷 
#define TB0_VECTOR				0x020		//TB0中斷 
#define TB1_VECTOR				0x024		//TB1中斷 
#define UART_VECTOR				0x028		//UART中斷 
#define SIM_VECTOR				0x02C		//SIM中斷 
#define SPIA_VECTOR				0x030		//SPIA中斷 




#endif
