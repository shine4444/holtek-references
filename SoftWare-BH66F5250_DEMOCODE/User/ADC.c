//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2018 BY HOLTEK SEMICONDUCTOR INC
//  File Name : ADC.c
// Description: 
//Targer Board: 
//   MCU      : BH67F5270
//   Author   : ming
//   Date     : 2018/03/26
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________

#include "common.h"

volatile	u8  gu8v_Sample_Count ;
volatile	s16	gs16v_adc_buff[10];	
volatile	u8  gbv_adc_Sample_Mode;
volatile	__byte_type  gbv_adc_flag;


/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_INIT()
{

	SET_ADC_PGA_1();
	SET_ADC_CHSP_VCM();
	SET_ADC_CHSN_VCM();
	//SET_ADC_CHSP_AN8();
	//SET_ADC_CHSN_AN9();
	//SET_ADC_CHSP_AN2();
	//SET_ADC_CHSN_AN3();
	SET_ADC_DATARATE_10HZ();
	SET_LDO_EN2_9();
	SET_DSOP_VCM();

		
}

/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_Enable()
{
	gu8v_Sample_Count = 0;
	gbv_adc_Sample_Mode = 0;
	gbv_adc_Sample_lock = 0;
	gbv_adc_success = 0;	
	SET_ADCPOWER_ON();
	SET_ADCMODE_NORMAL();
	//�����?ʽ?��?����??��?ʽ?��ͬһ??Դ
	//���????????VCM��?��׼,ע��AN+AN- ��???�뷶?
	SET_ADCVREF_VCMAVSS();
	SET_ADC_STARTCONVERT();

}

/********************************************************************
Function:	fun_ADC_Disable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_Disable()
{
	gu8v_Sample_Count = 0;
	gbv_adc_Sample_Mode = 0;
	gbv_adc_Sample_lock = 0;
	gbv_adc_success = 0;	
	SET_ADCPOWER_OFF();
	SET_ADCMODE_SLEEP();
	SET_LDO_DISABLE();
}

/********************************************************************
Function:	fun_ADC_Polling
INPUT	:
OUTPUT	:	
NOTE	:   �@ȡ���P��������ȥ�����Сֵ��ƽ��
********************************************************************/
void fun_filter_adc()
{	


}

/********************************************************************
Function:	fun_ADC_Polling
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_Polling()
{

	if(_eoc!=0)
	{
		//�i�攵��
		_adcdl=1;
		//�������D�Q��32bit ���з�̖����
		gu32v_adc_data.u32 = 0;
		gu32v_adc_data.byte.byte0	= _adrl;
		gu32v_adc_data.byte.byte1	= _adrm;				
		gu32v_adc_data.byte.byte2	= _adrh;
		if(gu32v_adc_data.bits.b23)
		{
			gu32v_adc_data.byte.byte3 = 0xff;
		}

		_adcdl=0;
		_eoc =0;
		
		
		
	//��G��ǰ���P����
		array_uart_txbuff[0] = 0x55;
		array_uart_txbuff[1] = gu32v_adc_data.byte.byte3;			
		array_uart_txbuff[2] = gu32v_adc_data.byte.byte2;			
		array_uart_txbuff[3] = gu32v_adc_data.byte.byte1;			
		array_uart_txbuff[4] = gu32v_adc_data.byte.byte0;						
		array_uart_txbuff[5] = array_uart_txbuff[0]+array_uart_txbuff[1]+array_uart_txbuff[2]+array_uart_txbuff[3]+array_uart_txbuff[4];						
		gu8v_tx_guide = 0;
		_utxr_rxr = array_uart_txbuff[gu8v_tx_guide];		
		
		//���Ӌ��
		gu8v_Sample_Count++;
		if(gbv_adc_Sample_Mode==0)
		{
			//�G��ǰ���P����
			if(gu8v_Sample_Count>3)
			{
				gu8v_Sample_Count=0;
				gbv_adc_Sample_Mode = 1;

			}
		}
		else if(gbv_adc_Sample_Mode==1)
		{	
			gbv_adc_success		= 1;
		}	 
	}		
}
