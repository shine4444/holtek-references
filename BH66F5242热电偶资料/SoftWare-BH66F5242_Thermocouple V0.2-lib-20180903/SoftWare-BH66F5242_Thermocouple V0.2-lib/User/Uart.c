#include "common.h"

/*************************************************************************************/
//**	Copyright	:	2016 BY HOLTEK SEMICONDUCTOR INC                            **
//** 	File Name   :	Uart.c                                                      **
//**	Description	: 	Uart 通信													**
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
volatile	u8	gu8v_tx_lenght;
volatile	__byte_type	gu8v_uart_flag;
volatile	u8	array_uart_txbuff[LU8C_TX_BUFF_LENGHT];
volatile	u8	array_uart_rxbuff[LU8C_RX_BUFF_LENGHT];

//-------------------------------------- IO 家览 Uart ---------------------------------------------
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
	_pas13 = 0;
	_pas12 = 1;
	_pas11 = 1;
	_pas10 = 0;
    _uucr1 = UCR1_8_N_1;     //enable UART function,8bits-Data  NONE-Parity 1bit-Stop Format
    _uucr2 = UCR2Data1;       //enable TXEN,RXEN,Hige Speed Baud Rate, Receiver interrupt enable 
	_urie = 1;
	_umd = 1;
 //  	_u0brg = 22;         //19200 Baud Rate	
   	_ubrg = 25;         //19200 Baud Rate	
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

void __attribute((interrupt(0X18)))  UART_ISR()
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
				for(lu8v_isr_temp0 = 0;lu8v_isr_temp0<6;lu8v_isr_temp0++)
				{
					array_uart_rxbuff[lu8v_isr_temp0] = array_uart_rxbuff[lu8v_isr_temp0+1];		
				}
		 		   array_uart_rxbuff[6] = _utxr_rxr; 
				if(array_uart_rxbuff[0]==0x5A&&array_uart_rxbuff[6]==(u8)(array_uart_rxbuff[0]+array_uart_rxbuff[1]+array_uart_rxbuff[2]+array_uart_rxbuff[3]+array_uart_rxbuff[4]+array_uart_rxbuff[5]))
				{
					gbv_rx_success = 1;

					if(array_uart_rxbuff[0]==0x02)
					{
						GCC_NOP();	
					}
					
				}	   	
				
				   	  
	   	   	  	GCC_NOP();
	   	   }
	   	   if(_utxif)							//TXR	data register is empty
	   	   {

	   	   		gu8v_tx_guide++; 	   		

	   	   		if(gu8v_tx_guide<gu8v_tx_lenght)			//
	   	   		{
		   	   		_utxr_rxr= array_uart_txbuff[gu8v_tx_guide];	  	   	   			
//	   	   			gu16v_an4_votage%256;		//send 0xaa to PC
	   	   		}
	   	   		else 
	   	   		{
//	   	   			gu8v_tx_guide=0;
					
	   	   		}	   	   		
	   	   		
					
	   	   }
	   	}	
}


/********************************************************************
Function:	Uart_manage
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	Uart_single_ack()
{
	gbv_temp_success = 0;	
	u8	i;
	array_uart_txbuff[0] = 0x55;
	array_uart_txbuff[1] = 03;			
	array_uart_txbuff[2] = 01;			
	array_uart_txbuff[3] = 00;	
	array_uart_txbuff[4] = 0;		
	for(i=0;i<=array_uart_txbuff[1];i++)
	{
		array_uart_txbuff[4] += array_uart_txbuff[i];		
		
	}
	gu8v_tx_guide = 0;
	gu8v_tx_lenght = 5;
	_utxr_rxr = array_uart_txbuff[0];			
		
	
}

/********************************************************************
Function:	Uart_manage
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	Uart_check_ack()
{
	u8	i;
	

	array_uart_txbuff[0] = 0x55;
	array_uart_txbuff[1] = 5;	
	array_uart_txbuff[3] = 00;		
	

				
	if(gbv_temp_success)
	{
		gbv_temp_success = 0;
		array_uart_txbuff[2] = 0x81;
		array_uart_txbuff[4] = gu16v_tp_temp[0].byte.byte1;	
		array_uart_txbuff[5] = gu16v_tp_temp[0].byte.byte0;			
//		array_uart_txbuff[6] = gu16v_tp_temp[1].byte.byte1;	
//		array_uart_txbuff[7] = gu16v_tp_temp[1].byte.byte0;		
//		array_uart_txbuff[8] = gu16v_tp_temp[2].byte.byte1;						
//		array_uart_txbuff[9] = gu16v_tp_temp[2].byte.byte0;	
//		array_uart_txbuff[10] = gu16v_tp_temp[3].byte.byte1;	
//		array_uart_txbuff[11] = gu16v_tp_temp[3].byte.byte0;								
	}
	else
	{
		array_uart_txbuff[2] = 0x80;	
		array_uart_txbuff[4] = 00;	
		array_uart_txbuff[5] = 00;			
//		array_uart_txbuff[6] = 00;
//		array_uart_txbuff[7] = 00;	
//		array_uart_txbuff[8] = 00;					
//		array_uart_txbuff[9] = 00;	
//		array_uart_txbuff[10] = 00;	
//		array_uart_txbuff[11] = 00;			
	}				
			

	array_uart_txbuff[6] = 0;		
	for(i=0;i<=array_uart_txbuff[1];i++)
	{
		array_uart_txbuff[6] += array_uart_txbuff[i];		
		
	}
	gu8v_tx_guide = 0;
	gu8v_tx_lenght = 7;
	_utxr_rxr = array_uart_txbuff[0];			
		
	
}



/********************************************************************
Function:	Uart_manage
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	Uart_cal_ack()
{
	gbv_temp_success = 0;	
	u8	i;
	array_uart_txbuff[0] = 0x55;
	array_uart_txbuff[1] = 03;			
	array_uart_txbuff[2] = 0x10;			
	array_uart_txbuff[3] = 00;	
	array_uart_txbuff[4] = 0;		
	for(i=0;i<=array_uart_txbuff[1];i++)
	{
		array_uart_txbuff[4] += array_uart_txbuff[i];		
		
	}
	gu8v_tx_guide = 0;
	gu8v_tx_lenght = 5;
	_utxr_rxr = array_uart_txbuff[0];			
		
	
}

/********************************************************************
Function:	Uart_manage
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	Uart_cal_templ_ack()
{
	gbv_temp_success = 0;	
	u8	i;
	array_uart_txbuff[0] = 0x55;
	array_uart_txbuff[1] = 03;			
	array_uart_txbuff[2] = 0x11;			
	array_uart_txbuff[3] = 00;	
	array_uart_txbuff[4] = 0;		
	for(i=0;i<=array_uart_txbuff[1];i++)
	{
		array_uart_txbuff[4] += array_uart_txbuff[i];		
		
	}
	gu8v_tx_guide = 0;
	gu8v_tx_lenght = 5;
	_utxr_rxr = array_uart_txbuff[0];			
		
	
}

/********************************************************************
Function:	Uart_manage
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	Uart_cal_temph_ack()
{
	gbv_temp_success = 0;	
	u8	i;
	array_uart_txbuff[0] = 0x55;
	array_uart_txbuff[1] = 03;			
	array_uart_txbuff[2] = 0x12;			
	array_uart_txbuff[3] = 00;	
	array_uart_txbuff[4] = 0;		
	for(i=0;i<=array_uart_txbuff[1];i++)
	{
		array_uart_txbuff[4] += array_uart_txbuff[i];		
		
	}
	gu8v_tx_guide = 0;
	gu8v_tx_lenght = 5;
	_utxr_rxr = array_uart_txbuff[0];			
		
	
}


/********************************************************************
Function:	Uart_manage
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void	Uart_manage(void)
{
	if(gbv_rx_success == 1)
	{
		gbv_rx_success = 0;


		switch(array_uart_rxbuff[2])
		{
			//
			case	UART_continuous_MODE:

							
				
				
				
			break;
			case	UART_single_MODE:
				//回传 ack 命令
				Uart_single_ack();			
				//开始测试进入测试模式
				gbv_uart_start = 1;
				Change_Mode(Sys_Normal_mode);
				
				
			break;
			case	UART_check_MODE:
				Uart_check_ack();
				
				
			break;			
			case	UART_old_MODE:

			break;				
			case	UART_stop_MODE:

			break;
			case	UART_cal_MODE:
				//回传 ack 命令
				Uart_cal_ack();			
				//开始测试进入测试模式
				gbv_uart_cal = 1;
				Change_Mode(Sys_Calibration_mode);
			break;
			case	UART_cal_templ_MODE:
				//回传 ack 命令
				Uart_cal_templ_ack();			
				//开始测试进入测试模式
				gbv_cal_templ = 1;
			break;

			case	UART_cal_temph_MODE:
				//回传 ack 命令
				Uart_cal_temph_ack();			
				//开始测试进入测试模式
				gbv_cal_temph = 1;
			break;
				
			default	:
				
			break;			
			
		}				

		
	}
	
}




//-----------------------------------------------------END------------------------------------------------------//
