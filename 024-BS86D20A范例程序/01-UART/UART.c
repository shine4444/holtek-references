/******************************************************************************
  * file    UART.C (for BS86D20A)
  * author  徐永强 (CrownRich-Tech Application Team)
  * version V1.0
  * date    3-Jun-2015
  * brief   This file contains the main function for UART example.
  * Tel     0755-26506087
  ******************************************************************************
  * attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, CrownRich-Tech SHALL NOT BE HELD LIABLE FOR ANY DIRECT, 
  * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM
  * THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
  * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  * <h2><center>&copy; COPYRIGHT 2015 CrownRich-Tech </center></h2>
  *******************************************************************************/
#include "BS86D20A-3.h"

unsigned char gc_UART_RcvData;
//=======================================================================================
//* brief : UART Interrupt
//* param : None
//* retval: None
//=======================================================================================
DEFINE_ISR (Interrupt_UART, 0x2C)
{
	gc_UART_RcvData = _txr_rxr;
	
	while(_txif == 0)
	{
		_clrwdt();
	};
	
	_txr_rxr = gc_UART_RcvData + 0x01;//收到数据+1后发回给主机
	
}

//=========================================================================
//UART初始化
//输入：none
//输出：none
//=========================================================================
void UART_Init()
{
	
	//bit7 uarten; bit6 bno 8bit; bi5 pren奇偶校验使能; bit4 prt奇偶校验类型; 
	//bit3 STOPS停止位长度选择; bit2 TXBRK暂停字控制位; bit1 RX8发送第九位; bit0 TX8发送第九位
	_ucr1 = 0x80;  //1000 0000
	
	//bit7 TXEN; bit6 RXEN; bit5 BRGH 波特率高低选择; bit4 ADDEN地址检测使能;
	//bit3 RX唤醒使能; bit2 接收中断使能; bit1 发送空闲中断使能; bit0 发送寄存器为空中断使能
	_ucr2 = 0xC4;  //1100 0100

	//------选择不同的时钟频率，并设定UART波特率---------
	//_hircs1 = 0; _hircs0 = 0;//8M时钟选择，需要跟配置里面一样，保证精度
	//_brg = 25; //4800bps @ 8MHz

	//_hircs1 = 0; _hircs0 = 1;//12M时钟选择，需要跟配置里面一样，保证精度
	//_brg = 37; //4800bps @ 12MHz
	
	_hircs1 = 1; _hircs0 = 0;//16M时钟选择，需要跟配置里面一样，保证精度
	_brg = 51; //4800bps @ 16MHz
	//---------------------------------------------------
	
	
	_uarte = 1;//使能UART中断
	_emi = 1;//使能全局中断
}

//=========================================================================
//UART发送命令
//输入参数
//输出：none
//=========================================================================
void UART_SEND(unsigned char tc_Data)
{
	while(_txif == 0)
	{
		_clrwdt();
	};
	_txr_rxr = tc_Data;
}
//=========================================================================
void Dealy()
{//延时程序
	unsigned int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<500;j++)
		{
			_clrwdt();
			_nop();
		}
	}	
}
//=========================================================================
void main()
{
	//_hirc1 = 1;//16M HIRC --set UART to 19200
	//_hirc0 = 0;
	
	UART_Init();
	
	while(1)
	{
		_clrwdt();
		Dealy();
		UART_SEND(0x51);
		UART_SEND(0x52);
		UART_SEND(0x53);
		UART_SEND(0x54);
		UART_SEND(0x55);
	}
}