//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Userdefine.c
// Description:
//Targer Board:
//   MCU      : BH66F5242
//___________________________________________________________________
//___________________________________________________________________
#ifndef _USERDEFINE_H_
#define _USERDEFINE_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Userdefine @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//<<<<<< A: HIRC_HXT_select >>>>>>>
//#define _HIRC_4M_
#define _HIRC_8M_
// #define _HIRC_12M_

#define UART_INTERFACE

#define IIC_INTERFACE

//#define TEMP_ENABLE

#define TIMEBASE1_250MS         250
#define FW_VERSION              0x02
#define BH_ID                   0x01
#define	I2CADDR				    0xA0
////@@@@@@@@@@@@@@@@@ 校準參數 @@@@@@@@@@@@@@@@@@@@@

#define DEFAULT_CALTEMP				250 	// 默認校準溫度,包含一位小數點,放大10倍
#define DEFAULT_TEMPSCALE			101 	// 溫度靈敏度,需要和ADC對應,放大10倍
#define DEFAULT_ZEROTEMPOFFSET		(DEFAULT_CALTEMP*DEFAULT_TEMPSCALE/100) 	// 溫度靈敏度,需要和ADC對應

#define WEIGHT_FILTER_CNT			10		// 重量濾波次數
#define IIC_SALVE_ADDRESS			0xA0	// 默認IIC地址


#endif
