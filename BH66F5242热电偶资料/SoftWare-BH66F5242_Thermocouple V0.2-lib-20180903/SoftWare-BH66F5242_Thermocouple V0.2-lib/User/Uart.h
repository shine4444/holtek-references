#ifndef _UART_H_
#define _UART_H_


#include "typedef.h"

//static volatile u8 gu8v_Uart_Buff[14] __attribute__ ((at(0x280)));
void Uart_Send_OneByte(u8 data);
void Uart_IO_SendOneByte(u8 lu8v_Uart_byte);
void delay_uart(volatile u16 lu8v_Uart_time);

void Uart_Send_AD_DATA();
void Uart_Send_ACK();
void Set_AD_Parameter();
void Init_UART();
void	Uart_manage(void);



/********************************************************************
Function:	
********************************************************************/
extern	volatile	u8	gu8v_rx_guide;
extern	volatile	u8	gu8v_tx_guide;
extern	volatile	u8	gu8v_tx_lenght;
#define		LU8C_TX_BUFF_LENGHT	20
#define		LU8C_RX_BUFF_LENGHT	10
extern	volatile	u8	array_uart_txbuff[LU8C_TX_BUFF_LENGHT];
extern	volatile	u8	array_uart_rxbuff[LU8C_RX_BUFF_LENGHT];
extern	volatile	__byte_type	gu8v_uart_flag;
#define gbv_tx_success 			gu8v_uart_flag.bits.b0
#define gbv_rx_success			gu8v_uart_flag.bits.b1
#define gu8v_uart_flag2 		gu8v_uart_flag.bits.b2
#define gu8v_uart_flag3 		gu8v_uart_flag.bits.b3
#define gu8v_uart_flag4			gu8v_uart_flag.bits.b4
#define gu8v_uart_flag5	 		gu8v_uart_flag.bits.b5
#define gu8v_uart_flag6			gu8v_uart_flag.bits.b6
#define gu8v_uart_flag7			gu8v_uart_flag.bits.b7



#define	UART_continuous_MODE	0
#define	UART_single_MODE		1	
#define	UART_check_MODE			2
#define	UART_old_MODE			3
#define	UART_stop_MODE			4
#define	UART_cal_MODE			0x10
#define	UART_cal_templ_MODE		0x11
#define	UART_cal_temph_MODE		0x12


/********************************************************************
Function:	
********************************************************************/
void 	Uart_Init(void);
void	Uart_off(void);
void	Uart_manage(void);


#endif 