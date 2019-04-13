//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2016 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Sys_init.c
// Description: 系統初始化子程序
//   Customer : Holtek Demo Code
//     MCU    : BH66F5242
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"
volatile unsigned char gu8v_haltTime;
volatile bit gbv_HALTMODE;	  // 休眠模式 1 使能  0 除能
extern volatile bit gbv_IsUartMode;
/********************************************************************
Function: MCU上電初始化
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_PowerOnInit()
{
    // *********系統時鐘設定********//
    #ifdef _HIRC_4M_
        _scc   = 0x00;
        _hircc = 0x01;
        while (!_hircf);    // Wait HIRC Oscillator Stable
    #endif // _HIRC_4M_
    #ifdef _HIRC_8M_
        _scc   = 0x00;
        _hircc = 0x05;
        while (!_hircf);    // Wait HIRC Oscillator Stable
    #endif // _HIRC_8M_
    #ifdef _HIRC_12M_
        _scc   = 0x00;
        _hircc = 0x09;
        while (!_hircf);    // Wait HIRC Oscillator Stable
    #endif // _HIRC_12M_

	//RAM
	_mp1h = 0;
	_mp1l = 0x80;
	while(_mp1h < 2 )
	{
		for(_tblp = 0x00;_tblp < 128;_tblp++)
		{
			_iar1 = 0;
			_mp1l++;
		}
		_mp1l = 0x80;
		_mp1h++;
	}
	//WDT ms
	SETWDTTIME_125MS();
	//LVR
	SETLVR_2_1V();
	_pbc0 = 1;
	_pbpu0= 1;
	GCC_DELAY(100);
	if(_pb0)
	{
		gbv_IsUartMode = 1;
	}
	else
	{
		gbv_IsUartMode = 0;
	}
//********** IO Config  *****************
// PA0-Unused         PA1-Unused
// PA2-Unused         PA3-Unused
// PA4-SDA/RXD        PA5-TXD
// PA6-SCL            PA7-Unused
	_pa  = 0B00000000;
	_pac = 0B01110000;
	_papu= 0B00000000;
	_pawu= 0B00000000;
	_pas0= 0B00000000;
	_pas0= 0B00010110;
// PB0-Unused         PB1-Unused
// PB2-Unused         PB3-Unused
// PB4-None           PB5-None
// PB6-None           PB7-None
	_pb  = 0B00000000;
	_pbc = 0B00000000;
	_pbpu= 0B00000000;
	_pbs0= 0B00000000;
// PC0-Unused         PC1-None
// PC2-None           PC3-None
// PC4-None           PC5-None
// PC6-None           PC7-None
	_pc  = 0B00000000;
	_pcc = 0B00000000;
	_pcpu= 0B00000000;
	_pcs0= 0B00000000;
	// CTM Unused
	// PTM Unused
	//	TimeBase
	SETTIMEBASE0_16MS();
	SETTIMEBASE0_ENABLE();
	SETTIMEBASE1_1000MS();
	SETTIMEBASE1_DISABLE();
	// ADC init
	// interrupt
	// IIC Interface Select
//#ifdef	IIC_INTERFACE
//	_sima = I2CADDR;
//	// IIC debounce Time Select		IIC Standard Mode(100KHz)            IIC Fast Mode(400KHz)
//	//  No  Debounce				     Fsys > 2 MHz			              Fsys > 5Mhz
//	//  2 system Clock                   Fsys > 4 MHz				          Fsys > 10Mhz
//	//  4 system Clock                   Fsys > 8 MHz				          Fsys > 20Mhz
//	SET_IIC_SLAVEMODE_DEB0();
//	SET_IIC_TIMEOUT_62ms();
//#endif
//	// UART Interface Select
//#ifdef UART_INTERFACE
//	_acc     = _usr;
//	_txr_rxr = _acc;
//	_ucr1    = 0x80;
//	_ucr2    = 0xEF;
//	#ifdef _HIRC_4M_
//	    _brg     = 0x19;
//	#endif
//	#ifdef _HIRC_12M_
//	    _brg     = 0x4D;
//	#endif
//#endif
}

/********************************************************************
Function: 關閉各個模塊進入HLAT模式
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_PrepareToHalt()
{
    // 關閉中斷
	_emi = 0;
	//關閉 timer及顯示
	SETTIMEBASE0_DISABLE();
	//關閉ADC及LDO,VCM等
	SETWDTDISABLE();
}

/********************************************************************
Function: 喚醒后有自動上稱重量恢復進入正常稱重模式
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
//void fun_ResumeWork()
//{
//	SETLDO_ENABLE();
//	_tb1on = 1;
//    // 開啟中斷
//	_emi = 1;
//	SETWDTTIME_125MS();
//	fun_ADCStart();
//}

//@------------外部中斷0入口函數--------------@
DEFINE_ISR(INT0_ISR, 0x004)
{

}

//@------------外部中斷0入口函數--------------@
DEFINE_ISR(INT1_ISR, 0x008)
{

}
//@-----------復合中斷0入口函數--------------@
// CTM_P CTM_A PTM_P PTM_A
//DEFINE_ISR(M_FUNCTION0_ISR, 0x010)	//復合中斷0
//{
//
//}
//@-----------復合中斷1入口函數--------------@
// LVD EEPROM
//DEFINE_ISR(M_FUNCTION1_ISR, 0x010)	//復合中斷1
//{
//
//}

//@-----------ADC 中斷入口函數--------------@
// DEFINE_ISR(ADC_ISR, ADC_VECTOR)
// {

// }
//@---------Timebase0 中斷入口函數----------@
DEFINE_ISR(Timebase0_ISR, 0x1C)
{
	if (gbv_HALTMODE)
	{
		gu8v_haltTime++;
	}
}
//@---------Timebase1 中斷入口函數----------@
DEFINE_ISR(Timebase1_ISR, 0x020)
{

}