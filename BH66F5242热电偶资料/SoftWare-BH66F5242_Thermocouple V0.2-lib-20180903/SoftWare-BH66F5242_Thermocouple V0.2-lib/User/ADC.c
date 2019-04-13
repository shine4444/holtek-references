/*************************************************************************************/
//**	Copyright	:	2016 BY HOLTEK SEMICONDUCTOR INC                            **
//** 	File Name   :	adc.c 	       	                                            **
//**	Description	: 																**
//**	MCU      	: 	HT67F5652													**
//**	Author   	: 	Leo														**
//**	Date     	: 	2016/10/28													**
//**	Version  	: 	V00															**
//**	History  	:																**
/*************************************************************************************/

#include "common.h"

volatile	u8  gu8v_Sample_Count ;
volatile	s16	gs16v_adc_buff[10];	
volatile	u8  gbv_adc_Sample_Mode;
//volatile	bit  gbv_adc_Sample_lock;
//volatile	bit  gbv_adc_success;
volatile	__byte_type  gbv_adc_flag;
/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_VTP_ZERO_INIT()
{
	SET_ADC_PGA_16();
	SET_ADC_CHSP_VCM();
	SET_ADC_CHSN_VCM();	
	SET_ADC_DATARATE_40HZ();
	SET_ADC_INX_00();	
	SET_LDO_EN2_4();
	SET_DSOP_VCM();
	fun_ADC_Enable();

}
/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_VTP_CH0_INIT()
{
	SET_ADC_PGA_16();
	SET_ADC_CHSP_AN8();
	SET_ADC_CHSN_VCM();	
	SET_ADC_INX_00();	
	SET_ADC_DATARATE_40HZ();
	SET_LDO_EN2_4();
	SET_DSOP_VCM();
	fun_ADC_Enable();

}


/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_VTP_CH1_INIT()
{
	SET_ADC_PGA_16();
	SET_ADC_CHSP_VCM();
	SET_ADC_CHSN_AN9();	
	SET_ADC_DATARATE_40HZ();
	SET_ADC_INX_11();		
	SET_LDO_EN2_4();
	SET_DSOP_VCM();
	fun_ADC_Enable();

}

/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_VTP_CH2_INIT()
{
	SET_ADC_PGA_16();
	SET_ADC_CHSP_AN10();
	SET_ADC_CHSN_VCM();	
	SET_ADC_DATARATE_40HZ();
	SET_ADC_INX_00();		
	SET_LDO_EN2_4();
	SET_DSOP_VCM();
	fun_ADC_Enable();

}
/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_VTP_CH3_INIT()
{
	SET_ADC_PGA_16();
	SET_ADC_CHSP_AN4();
	SET_ADC_CHSN_VCM();		
	SET_ADC_DATARATE_40HZ();
	SET_ADC_INX_00();		
	SET_LDO_EN2_4();
	SET_DSOP_VCM();
	fun_ADC_Enable();

}


/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_TEMP1_INIT()
{
	SET_ADC_PGA_1();
	SET_ADC_CHSP_VCM();
	SET_ADC_CHSN_AN0();	
	SET_ADC_DATARATE_160HZ();
	SET_ADC_INX_00();
	SET_LDO_EN2_4();
	SET_DSOP_VCM();
	fun_ADC_Enable();
}
/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_TEMP2_INIT()
{

	SET_ADC_PGA_1();
	SET_ADC_CHSP_AN0();
	SET_ADC_CHSN_AN1();	
	SET_ADC_INX_00();	
	SET_ADC_DATARATE_160HZ();
	SET_LDO_EN2_4();
	SET_DSOP_VCM();
	fun_ADC_Enable();
	
}


/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:
NOTE	:  
********************************************************************/
void fun_ADC_Power_Enable()
{

//	mac_SET_AVDD_2_4();  
//	//以下參數在後續應用中不會變化所以在此進行設置
//	mac_SET_VGS_0();
//	mac_SET_AGS_1();
//	mac_SET_VRBUFF_DIS();
//	mac_SET_ADC_CLOCK_FSYS();
//	mac_LDO_Enable();
//	GCC_NOP();




}

/********************************************************************
Function:	fun_ADC_Enable
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_Power_Disable()
{
//	mac_LDO_Disable();
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
//	SET_ADCPOWER_OFF();
//	SET_ADCMODE_SLEEP();
//	SET_LDO_DISABLE();
}

/********************************************************************
Function:	fun_ADC_Polling
INPUT	:
OUTPUT	:	
NOTE	:   獲取六筆數據，除去最大最小值求平均
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
		//鎖存數據
		_adcdl=1;
		//將數據轉換為32bit 的有符號數據
		gu32v_adc_data.u32 = 0;
		gu32v_adc_data.byte.byte0	= _adrl;
		gu32v_adc_data.byte.byte1	= _adrm;				
		gu32v_adc_data.byte.byte2	= _adrh;
		if(gu32v_adc_data.bits.b23)
		{
			gu32v_adc_data.byte.byte3 = 0xff;
		}

		#if(mac_Test_Mode==mac_Test_On)
		// 測試模式 
		gu32v_adc_data.s32 >>= 6;
		#else
		// 取 24bit adc 中的 18bit 數據作為有效數據
		gu32v_adc_data.s32 >>= 6;
		#endif
		_adcdl=0;
		_eoc =0;
		
		//採樣計數
		gu8v_Sample_Count++;
		if(gbv_adc_Sample_Mode==0)
		{
			//丟棄前三筆數據
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

/********************************************************************
Function:	fun_ADC_NTC_Test
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_NTC_Test()
{


}

/********************************************************************
Function:	fun_ADC_OPA_ZeroTest
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_OPA_ZeroTest()
{


}
/********************************************************************
Function:	fun_ADC_OPA_VTPTest
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_OPA_VTPTest()
{

}

/********************************************************************
Function:	fun_ADC_OPA_ZeroTest_2
INPUT	:
OUTPUT	:	
NOTE	:   
********************************************************************/
void fun_ADC_OPA_ZeroTest_2()
{

}