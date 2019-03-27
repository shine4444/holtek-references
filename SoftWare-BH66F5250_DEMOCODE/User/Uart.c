#include "common.h"

/*************************************************************************************/
//**	Copyright	:	2016 BY HOLTEK SEMICONDUCTOR INC                            **
//** 	File Name   :	Uart.c                                                      **
//**	Description	: 	Uart Í¨ÐÅ													**
//**	TargerBoard	: 	None														**
//**	MCU      	: 	HT67F5650													**
//**	Author   	: 	LJQ															**
//**	Date     	: 	2015/11/20													**
//**	Version  	: 	V00															**
//**	History  	:																**
/*************************************************************************************/


/********************************************************************
Function:	DEFINE
********************************************************************/
#define		cmd_return_op1adnum			30
#define		cmd_return_op2adnum			31
#define		cmd_adjust_bandgap_up		32
#define		cmd_adjust_bandgap_down		33
#define		cmd_data_to_pref			34
#define		cmd_data_to_rom				35
#define		cmd_adjust_daco_up			37
#define		cmd_adjust_daco_down		38
#define		UCR1_8_N_1     				0x80      //8bits-Data  NONE-Parity 1bit-Stop Format
#define 	UCR1_7_O_1     				0x0B0     //7bits-Data  Odd-Parity  1bit-Stop Format
#define		UCR1_7_E_1     				0x0A0     //7bits-Data  Even-Parity 1bit-Stop Format
#define		UCR1_9_N_1     				0x0C0     //9bits-Data  NONE-Parity 1bit-Stop Format
#define		UCR1_8_O_1    				0x0F0     //8bits-Data  Odd-Parity  1bit-Stop Format
#define		UCR1_8_E_1     				0x0E0     //8bits-Data  Even-Parity 1bit-Stop Format
#define		UCR1_8_N_2     				0x88      //8bits-Data  NONE-Parity 2bits-Stop Format
#define		UCR1_7_O_2     				0x0B8     //7bits-Data  Odd-Parity  2bits-Stop Format
#define		UCR1_7_E_2     				0x0A8     //7bits-Data  Even-Parity 2bits-Stop Format
#define		UCR1_9_N_2     				0x0C8     //9bits-Data  NONE-Parity 2bits-Stop Format
#define		UCR1_8_O_2     				0x0F8     //8bits-Data  Odd-Parity  2bits-Stop Format
#define		UCR1_8_E_2     				0x0E8     //8bits-Data  Even-Parity 2bits-Stop Format
#define		UCR2Data       				0x0E4     //Enable TXEN RXEN BRGH RIE 
#define		UCR2Data1       			0x0Ef     //Enable TXEN RXEN BRGH RIE 
#define		BRGData        				12		  //4mhz0x19       //Baud=9600,BRGH=1,N=25 



volatile	u8	gu8v_rx_guide;
volatile	u8	gu8v_tx_guide;
volatile	__byte_type	gu8v_uart_flag;
volatile	u8	array_uart_txbuff[LU8C_TX_BUFF_LENGHT];
volatile	u8	array_uart_rxbuff[6];

//-------------------------------------- IO ¼ÒÀÀ Uart ---------------------------------------------
//	
//	 9600 --> 104 us / bit
//

#define UART_IO_DELAY  4
#define Uart_IO_TX _pa1

 
void delay_uart(volatile u16 lu8v_Uart_time)
{
	while(lu8v_Uart_time--)
	{
	//	GCC_CLRWDT();
	}		
}



void Uart_IO_SendOneByte(u8 lu8v_Uart_byte)
{
//	u8 lu8v_Uart_i;
//	_pac1 =0;
//	Uart_IO_TX	= 0;
////	delay_uart(UART_IO_DELAY);
//	GCC_DELAY(99);
//	
//	for(lu8v_Uart_i=0;lu8v_Uart_i<8;lu8v_Uart_i++)
//	{	
//		if(lu8v_Uart_byte & 0x01)
//		{
//			Uart_IO_TX = 1;
//		} 
//		else
//		{
//			GCC_DELAY(3);
//			Uart_IO_TX = 0;
//		}
//		
//		GCC_DELAY(93);
//	
//		lu8v_Uart_byte = lu8v_Uart_byte >> 1;
//	}	
//	GCC_DELAY(3);
//	Uart_IO_TX	= 1;
//	delay_uart(UART_IO_DELAY);
//	GCC_DELAY(5);
	
}







/********************************************************************
Function:	Key_Scan
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void Uart_Init(void)
{
	_umd = 1;
//	_pds0 = 0b10100000;//set tx rx pin
	
	_pbs07 = 1;
	_pbs06 = 1;
	_pas17 = 1;
	_pas16 = 1;
	
	_rxps = 0;

    _uucr1 = UCR1_8_N_1;     //enable UART function,8bits-Data  NONE-Parity 1bit-Stop Format
    _uucr2 = UCR2Data1;       //enable TXEN,RXEN,Hige Speed Baud Rate, Receiver interrupt enable 
	_urie = 1;

   	_ubrg = 12;      	   //19200 Baud Rate	

//	_euti = 1;      			//UART interrupt enable
	_usime = 1;      			//UART interrupt enable	
	_emi = 1;
}

/********************************************************************
Function:	Key_Scan
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void Uart_off(void)
{
	_uren = 0;
	_uucr1 = 0;
	_uucr2 = 0;	
	_usime = 0;
}


/********************************************************************
Function:	UART_ISR
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
//@------------uart--------------@

void __attribute((interrupt(0X24)))  UART_ISR()
{	
	u8	lu8v_isr_temp0;
		//clear urf flag
	   	if(_uperr || _unf || _uferr || _uoerr)		// error found?
	   	{
	   	   lu8v_isr_temp0 = _uusr;				//read USR to clear error flag 
	   	   lu8v_isr_temp0 =  _utxr_rxr;				//read USR to clear error flag 	   	       
	   	}
	   	else									// no error found
	   	{
	   	   if(_urxif)							//RXR	data register has available	data
	   	   {	   	  
				for(lu8v_isr_temp0 = 0;lu8v_isr_temp0<4;lu8v_isr_temp0++)
				{
					array_uart_rxbuff[lu8v_isr_temp0] = array_uart_rxbuff[lu8v_isr_temp0+1];		
				}
		 		   array_uart_rxbuff[4] = _utxr_rxr; 
				if(array_uart_rxbuff[0]==0x55&&array_uart_rxbuff[4]==(u8)(array_uart_rxbuff[0]+array_uart_rxbuff[1]+array_uart_rxbuff[2]+array_uart_rxbuff[3]))
				{
					gbv_rx_success = 1;
					
					
					if(array_uart_rxbuff[2] == 0)
					{
						SET_ADC_PGA_1();		
						
					}
					else if(array_uart_rxbuff[2] == 1)
					{
						SET_ADC_PGA_2();				
					}
					else if(array_uart_rxbuff[2] == 2)
					{
						SET_ADC_PGA_4();	
					}					
					else if(array_uart_rxbuff[2] == 3)
					{
						SET_ADC_PGA_8();
					}
					else if(array_uart_rxbuff[2] == 4)
					{
						SET_ADC_PGA_16();
					}					
					else if(array_uart_rxbuff[2] == 5)
					{
						SET_ADC_PGA_32();
					}					
					else if(array_uart_rxbuff[2] == 6)
					{
						SET_ADC_PGA_64();
					}					
					else if(array_uart_rxbuff[2] == 7)
					{
						SET_ADC_PGA_128();
					}					
					
					
					if(array_uart_rxbuff[3] == 0)
					{
						SET_ADC_DATARATE_10HZ();		
						
					}
					else if(array_uart_rxbuff[3] == 1)
					{
						SET_ADC_DATARATE_20HZ();				
					}
					else if(array_uart_rxbuff[3] == 2)
					{
						SET_ADC_DATARATE_40HZ();	
					}					
					else if(array_uart_rxbuff[3] == 3)
					{
						SET_ADC_DATARATE_80HZ();
					}
					else if(array_uart_rxbuff[3] == 4)
					{
						SET_ADC_DATARATE_160HZ();
					}						
					
					
					
				}	   	   	  
	   	   	  GCC_NOP();
	   	   }
	   	   if(_utxif)							//TXR	data register is empty
	   	   {
	   	   		gu8v_tx_guide++; 	   		
	   	   		if(gu8v_tx_guide<LU8C_TX_BUFF_LENGHT)			//
	   	   		{
		   	   		_utxr_rxr= array_uart_txbuff[gu8v_tx_guide];	  	   	   			
	   	   		}
	   	   		else 
	   	   		{
					
	   	   		}
					
	   	   }
	   	}	
}






//-----------------------------------------------------END------------------------------------------------------//
