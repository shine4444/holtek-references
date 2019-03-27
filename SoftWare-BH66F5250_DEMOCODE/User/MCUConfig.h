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
//���x IAR1 ���� bit ����
static volatile __byte_type  SFR_iar1 __attribute__((at(0x02)));

//�O�ó�ʼ�� rambank ����
#define RamBankSectorSum	4
#define LU8C_HALT_TIME		20

//__________________________________________________________________//
//					-----ISR VECTOR Defination------;
//�Д���ڵ�ַ
#define	START_VECTOR			0x000		//������
#define	INT0_VECTOR				0x004		//Intrrupt 0
#define	INT1_VECTOR				0x008		//Intrrupt 1
#define ADC_VECTOR				0x0C		//ADC �Д�
#define	MF0_VECTOR				0x0010		//�ͺ��Д� 0
#define	MF1_VECTOR				0x0014		//�ͺ��Д� 1
#define MF2_VECTOR				0x018		//�ͺ��Д� 2
#define SCF_VECTOR				0x01C		//SCF�Д� 
#define TB0_VECTOR				0x020		//TB0�Д� 
#define TB1_VECTOR				0x024		//TB1�Д� 
#define UART_VECTOR				0x028		//UART�Д� 
#define SIM_VECTOR				0x02C		//SIM�Д� 
#define SPIA_VECTOR				0x030		//SPIA�Д� 




#endif
