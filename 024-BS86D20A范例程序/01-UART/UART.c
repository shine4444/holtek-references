/******************************************************************************
  * file    UART.C (for BS86D20A)
  * author  ����ǿ (CrownRich-Tech Application Team)
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
	
	_txr_rxr = gc_UART_RcvData + 0x01;//�յ�����+1�󷢻ظ�����
	
}

//=========================================================================
//UART��ʼ��
//���룺none
//�����none
//=========================================================================
void UART_Init()
{
	
	//bit7 uarten; bit6 bno 8bit; bi5 pren��żУ��ʹ��; bit4 prt��żУ������; 
	//bit3 STOPSֹͣλ����ѡ��; bit2 TXBRK��ͣ�ֿ���λ; bit1 RX8���͵ھ�λ; bit0 TX8���͵ھ�λ
	_ucr1 = 0x80;  //1000 0000
	
	//bit7 TXEN; bit6 RXEN; bit5 BRGH �����ʸߵ�ѡ��; bit4 ADDEN��ַ���ʹ��;
	//bit3 RX����ʹ��; bit2 �����ж�ʹ��; bit1 ���Ϳ����ж�ʹ��; bit0 ���ͼĴ���Ϊ���ж�ʹ��
	_ucr2 = 0xC4;  //1100 0100

	//------ѡ��ͬ��ʱ��Ƶ�ʣ����趨UART������---------
	//_hircs1 = 0; _hircs0 = 0;//8Mʱ��ѡ����Ҫ����������һ������֤����
	//_brg = 25; //4800bps @ 8MHz

	//_hircs1 = 0; _hircs0 = 1;//12Mʱ��ѡ����Ҫ����������һ������֤����
	//_brg = 37; //4800bps @ 12MHz
	
	_hircs1 = 1; _hircs0 = 0;//16Mʱ��ѡ����Ҫ����������һ������֤����
	_brg = 51; //4800bps @ 16MHz
	//---------------------------------------------------
	
	
	_uarte = 1;//ʹ��UART�ж�
	_emi = 1;//ʹ��ȫ���ж�
}

//=========================================================================
//UART��������
//�������
//�����none
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
{//��ʱ����
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