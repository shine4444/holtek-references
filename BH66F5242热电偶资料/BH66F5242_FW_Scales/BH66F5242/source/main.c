//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2016 BY HOLTEK SEMICONDUCTOR INC
//  File Name : main.c
// Description: ����ʽ
//   MCU      : BH66F5242
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"


void main()
{
	//�ж����ϵ縴λ���߷�����������ĸ�λ
	//������ϵ縴λ��ִ���ϵ��ʼ����������Ƿ������������ִ��WDT��λ��ʼ��
	if (_to == 0 || _pdf ==0)
	{
		//�ϵ縴λ��ʼ��
		fun_PowerOnInit();
		fun_ScalesSDK_PowerOn();
        fun_USIM_PowerOn();
	}
	else
	{
		//WDT�������
		fun_PowerOnInit();
		fun_ScalesSDK_PowerOn();
        fun_USIM_PowerOn();
	}
//��ѭ��
	while(1)
	{
		GCC_CLRWDT();
		fun_ScalesSDK();
		fun_UIProtocol();
		if (gu8v_haltTime > 4)
		{
			//����׼��
			fun_ScalesSDK_PowerDown(); // ���߳�ʼ��,MCU����ǰ�{��һ��
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





