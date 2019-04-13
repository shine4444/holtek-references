//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2016 BY HOLTEK SEMICONDUCTOR INC
//  File Name : main.c
// Description: 主程式
//   MCU      : BH66F5242
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"


void main()
{
	//判断是上电复位或者非正常下情况的复位
	//如果是上电复位就执行上电初始化化，如果是非正常的情况就执行WDT复位初始化
	if (_to == 0 || _pdf ==0)
	{
		//上电复位初始化
		fun_PowerOnInit();
		fun_ScalesSDK_PowerOn();
        fun_USIM_PowerOn();
	}
	else
	{
		//WDT溢出喚醒
		fun_PowerOnInit();
		fun_ScalesSDK_PowerOn();
        fun_USIM_PowerOn();
	}
//主循环
	while(1)
	{
		GCC_CLRWDT();
		fun_ScalesSDK();
		fun_UIProtocol();
		if (gu8v_haltTime > 4)
		{
			//休眠准备
			fun_ScalesSDK_PowerDown(); // 休眠初始化,MCU休眠前調用一次
			gu8v_haltTime = 0;
			gbv_HALTMODE = 0;
			fun_PrepareToHalt();
			GCC_HALT();
			GCC_NOP();
			GCC_NOP();
			_emi = 1;
			_tb1on = 1;
			SETWDTTIME_125MS();
			gu8v_ScalesSDKState = ENTER_WEIGHT_NORMAL;
		}
	}
}





