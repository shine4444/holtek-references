//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2018 BY HOLTEK SEMICONDUCTOR INC
//  File Name : eeprom
// Description: 
//Targer Board: 
//   MCU      : BH67F5270
//   Author   : ming
//   Date     : 2018/03/26
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#ifndef _EEPROM_H__
#define _EEPROM_H__
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_Write_EEPROM(unsigned char addr,unsigned char data);
unsigned char fun_Read_EEPROM(unsigned char addr);


#define	EEPROM_START_ADDR	0x01
#define	EEPROM_300mmhg_H	EEPROM_START_ADDR+1
#define	EEPROM_300mmhg_L	EEPROM_START_ADDR+2
#define	EEPROM_0mmhg_H		EEPROM_START_ADDR+3
#define	EEPROM_0mmhg_L 		EEPROM_START_ADDR+4
//用於測試eeprom讀寫正確性
void	TEST_EEPROM(u8 lu8v_eeprom_length);
#endif
