#include "ScalesSDK_Hardware.h"
#include "ScalesSDK_Interface.h"
#include "ScalesSDK_UserSetting.h"
#include "ScalesSDK_LIBSetting.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@׃���Y���w��@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef char			s8;
typedef int				s16;
typedef long			s32;
typedef unsigned char 	u8;
typedef unsigned int    u16;
typedef unsigned long   u32;
typedef union {
	struct
	{
		unsigned char byte0;
		unsigned char byte1;
	}byte;
	int		 		 s16;
	unsigned int	 u16;
} __16_type;

typedef union {
	struct
	{
		unsigned char byte0;
		unsigned char byte1;
		unsigned char byte2;
		unsigned char byte3;

	}byte;
	unsigned long 	u32;
	long			s32;
} __32_type;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ׃�����x  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile unsigned char gu8v_ScalesSDKState;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                    EEPROM �x��				             		     @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/****************************************************
 Function: Write_EEPROM
 INPUT	: @addr ����ַ @������
 OUTPUT	: None
 NOTE	: none
 ***************************************************/
void Write_EEPROMByte(unsigned char addr, unsigned char WriteData)
{
	bit EMI_Protect;
	EMI_Protect = _emi;
	_emi = 0;
	_mp1h = 1;
	_mp1l = 0x40;
	_eea = addr;
	_eed = WriteData;
	//_WREN�c_WR�����B�m�ăɂ�ָ���L�ڃ����
	asm("set [0x02].3");	// WREN
	asm("set [0x02].2");	// WR
	asm("sz  [0x02].2");	// WR
	asm("jmp $-1");
	_iar1 = 0; //disable WREN
	_emi = EMI_Protect;
}
/*****************************************************
 Function: Read_EEPROM
 INPUT	: @addr �x��ַ
 OUTPUT	: @�x���Ĕ���
 NOTE	: none
 ****************************************************/
unsigned char Read_EEPROMByte(unsigned char addr)
{
	_eea = addr;
	_mp1h = 1;
	_mp1l = 0x40;
	asm("set [0x02].1");	// RDEN
	asm("set [0x02].0");	// RD
	asm("sz  [0x02].0");	// RD
	asm("jmp $-1");
	_iar1 = 0;
	return _eed;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              24Bit ADC�����xȡ                                       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile bit gbv_GetADCSourceDataOK; // �õ�һ�Pԭʼ��ADCֵ
volatile unsigned char lu8v_ADCCnt;  // ADC�񼯴Δ�
volatile unsigned char SourceADCHigh, SourceADCMid , SourceADCLow;  // ԭʼADC����
/*************************************************
 Function: �_ʼADC ���
 INPUT	:
 OUTPUT	:
 NOTE	:
 *************************************************/
void fun_ADCStart()
{
	SET_LDO_EN2_6();
	SET_ADCPOWER_ON();
	SET_ADCMODE_NORMAL();
	SET_ADCINTERRUPT_ENABLE();
	SET_ADC_STARTCONVERT();
	lu8v_ADCCnt = 0;
	gbv_GetADCSourceDataOK = 0;
}
/*************************************************
 Function: ֹͣADC ���
 INPUT	:
 OUTPUT	:
 NOTE	: �P�]ADCģ�K���
 *************************************************/
void fun_ADCStop()
{
	SET_LDO_DISABLE();
	SET_ADCPOWER_OFF();
}
/*********************************
Function: ADC�Д�,�@ȡADCֵ
INPUT	:
OUTPUT	:
NOTE	:
*********************************/
//@------------ADC �Д���ں���---------------@
DEFINE_ISR(ADC_ISR, ADC_VECTOR)
{
	if (_eoc == 1 && gbv_GetADCSourceDataOK == 0)
	{ //ADC �D�Q���
		_eoc = 0;
		lu8v_ADCCnt++;
		//ǰ���P�����G�������ĹP���_ʼ̎��
		if (lu8v_ADCCnt > 3)
		{
			_adcdl = 1;
			SourceADCLow  = _adrl;
			SourceADCMid  = _adrm;
			SourceADCHigh = _adrh;
			_adcdl = 0; //�����xȡ��ɣ�ȡ���i��
			gbv_GetADCSourceDataOK = 1;
		}
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                ADC �V���㷨                                          @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define   FILTER_CNT      008        //�V���Δ�
// �V���Y��
volatile bit gbv_GetFilterADCDataOK;   			// 1 �õ�һ�P�V�����ADCֵ
volatile bit gbv_AdcDataIsStable;	   			// 1 ADCֵ����, 0 ADC������
// sinc4 �V��
bit gbv_FirstFilterI;   // ��һ�ηe�֞V��
bit gbv_FirstFilterD;   // ��һ��΢�֞V��
unsigned char filterBufI1H , filterBufI1M , filterBufI1L , filterBufI1HH;  // �e��׃��1
unsigned char filterBufI2H , filterBufI2M , filterBufI2L , filterBufI2HH;  // �e��׃��2
unsigned char filterBufI3H , filterBufI3M , filterBufI3L , filterBufI3HH;  // �e��׃��3
// unsigned char filterBufI4H , filterBufI4M , filterBufI4L , filterBufI4HH;  // �e��׃��4
unsigned char filterBufIOutputH,filterBufIOutputM,filterBufIOutputL;       // �e��׃�����,ȡ���20bit
unsigned char filterBufD1H , filterBufD1M , filterBufD1L;  	// ΢��׃��1
unsigned char filterBufD2H , filterBufD2M , filterBufD2L;  	// ΢��׃��2
unsigned char filterBufD3H , filterBufD3M , filterBufD3L;  	// ΢��׃��3
// unsigned char filterBufD4H , filterBufD4M , filterBufD4L;  	// ΢��׃��4
unsigned char filterBufAH , filterBufAM , filterBufAL;		// ΢��׃�����g��A
unsigned char filterBufBH , filterBufBM , filterBufBL;		// ΢��׃�����g��B
// unsigned char _filterADCDataCurrent[2],_filterADCDataCurrent[1],_filterADCDataCurrent[0];    // �V��ݔ������
volatile unsigned long filterADCDataCurrent;          // R    ����ADC�V���󔵓�
volatile unsigned long filterADCDataLast;             // R    ����ADC�V���󔵓�
// �����Д�
volatile unsigned char lu8v_FiltLockCnt;		 // ��ǰ�V�����ȴΔ�
volatile unsigned long gu32v_FilterADCDataMax;	 // �V��������ADCֵ
volatile unsigned long gu32v_FilterADCDataMin;	 // �V������С��ADCֵ
volatile unsigned int gu16v_FiltThreshold;		 // �V���i���yֵ
volatile unsigned char gu8v_FiltThresholdCnt;	 // �V���i���Δ��yֵ


// �Ñ��O��ֵ
volatile WeightCalData_t WeightCalData;
/***********************************************
 Function: ȡ�Ãɂ�ֵ֮�g�Ĳ�ֵ
 INPUT	:
 OUTPUT	:
 NOTE	:
 **********************************************/
unsigned long fun_unsigned32BitABS(unsigned long a, unsigned long b)
{
	if (a > b)	{ return (a - b); }
	else		{ return (b - a); }
}
void fun_LowFreqFiltering()
{
	asm("SNZ _gbv_GetADCSourceDataOK");
	asm("RET");
	asm("CLR _gbv_GetADCSourceDataOK");
    //  ȡ���20bit
    asm("mov     a, 4H");
    asm("_LI1:");
    asm("clr     c");
    asm("rrc     _SourceADCHigh");
    asm("rrc     _SourceADCMid");
    asm("rrc     _SourceADCLow");
    asm("sdz     acc");
    asm("jmp     _LI1");
    gbv_FirstFilterI = 1;   // ��һ�ηe�֞V��
	gbv_FirstFilterD = 1;   // ��һ��΢�֞V��
    // ���ٳ�ʼ��
    asm("SZ	_gbv_FirstFilterI");
    asm("JMP _FilterI");
    //asm("_init_FilterI:");
	asm("SET	_gbv_FirstFilterI");
    // �e����1=�e����2=�e����3=�e����4=ԭʼadc����
    asm("MOV a,_SourceADCLow");
    asm("MOV _filterBufI1L,a");
    asm("MOV _filterBufI2L,a");
    asm("MOV _filterBufI3L,a");
    asm("MOV a,_SourceADCMid");
    asm("MOV _filterBufI1M,a");
    asm("MOV _filterBufI2M,a");
    asm("MOV _filterBufI3M,a");
    asm("MOV a,_SourceADCHigh");
    asm("MOV _filterBufI1H,a");
    asm("MOV _filterBufI2H,a");
    asm("MOV _filterBufI3H,a");
    asm("CLR _filterBufI1HH");
    asm("CLR _filterBufI2HH");
    asm("CLR _filterBufI3HH");
    asm("_FilterI:");
    // ԭʼadc���� + �e����1 = �e����1
    asm("mov     a, _SourceADCLow");
    asm("addm    a, _filterBufI1L");
    asm("mov     a, _SourceADCMid");
    asm("adcm    a, _filterBufI1M");
    asm("mov     a, _SourceADCHigh");
    asm("adcm    a, _filterBufI1H");
    asm("CLR     acc");
    asm("adcm    a, _filterBufI1HH");
    // �e����1 + �e����2 = �e����2
    asm("mov     a, _filterBufI1L");
    asm("addm    a, _filterBufI2L");
    asm("mov     a, _filterBufI1M");
    asm("adcm    a, _filterBufI2M");
    asm("mov     a, _filterBufI1H");
    asm("adcm    a, _filterBufI2H");
    asm("mov     a, _filterBufI1HH");
    asm("adcm    a, _filterBufI2HH");
    // �e����2 + �e����3 = �e����3
    asm("mov     a, _filterBufI2L");
    asm("addm    a, _filterBufI3L");
    asm("mov     a, _filterBufI2M");
    asm("adcm    a, _filterBufI3M");
    asm("mov     a, _filterBufI2H");
    asm("adcm    a, _filterBufI3H");
    asm("mov     a, _filterBufI2HH");
    asm("adcm    a, _filterBufI3HH");
    // �ȴ��@ȡ8�P���� 	2^3   ԭʼ20Bit+3*3=29Bit
	#define  DownLoadSample  8
	#if (DownLoadSample == 8)
    asm("mov     a, (8+2)");
    asm("sub     a, _lu8v_ADCCnt");
    asm("sz      c");
    asm("RET");     // �]��8�P��������
    asm("MOV     a,3"); // �ѽ���8�P����,ȡ����ߵ�20bit
    asm("MOV     _lu8v_ADCCnt,a");
    // �e����ݔ�� = �e����4     ȡ����ߵ�20Bit,��Bit32~Bit12
    asm("MOV    a,_filterBufI3HH");
    asm("MOV    _filterBufIOutputH,a");
    asm("MOV    a,_filterBufI3H");
    asm("MOV    _filterBufIOutputM,a");
    asm("MOV    a,_filterBufI3M");
    asm("MOV    _filterBufIOutputL,a");
    //
    asm("mov     a, 1H");
    asm("_LI2:");
    asm("clr     c");
    asm("rrc     _filterBufIOutputH");
    asm("rrc     _filterBufIOutputM");
    asm("rrc     _filterBufIOutputL");
    asm("sdz     acc");
    asm("jmp     _LI2");
	#endif

    // ���ٳ�ʼ��
    asm("SZ	_gbv_FirstFilterD");
    asm("JMP _FilterD");
    //asm("_init_FilterI:");
    asm("SET	_gbv_FirstFilterD");
    // filterOutputData = FilterBufD1 = FilterBufD2 = FilterBufD3 = FilterBufD4
    asm("MOV a,_filterBufIOutputL");
    asm("MOV _filterBufD1L,a");
    asm("MOV _filterBufD2L,a");
    asm("MOV _filterBufD3L,a");

    asm("MOV a,_filterBufIOutputM");
    asm("MOV _filterBufD1M,a");
    asm("MOV _filterBufD2M,a");
    asm("MOV _filterBufD3M,a");

    asm("MOV a,_filterBufIOutputH");
    asm("MOV _filterBufD1H,a");
    asm("MOV _filterBufD2H,a");
    asm("MOV _filterBufD3H,a");
    asm("_FilterD:");

    // _FilterBufA =  FilterBufIOutput - FilterBufD1
    asm("mov     a, _filterBufIOutputL");
    asm("sub     a, _filterBufD1L");
    asm("mov     _filterBufAL, a");
    asm("mov     a, _filterBufIOutputM");
    asm("sbc     a, _filterBufD1M");
    asm("mov     _filterBufAM, a");
    asm("mov     a, _filterBufIOutputH");
    asm("sbc     a, _filterBufD1H");
    asm("mov     _filterBufAH, a");
    // FilterBufD1 = FilterBufIOutput
    asm("MOV     a,_filterBufIOutputL");
    asm("MOV     _filterBufD1L,a");
    asm("MOV     a,_filterBufIOutputM");
    asm("MOV     _filterBufD1M,a");
    asm("MOV     a,_filterBufIOutputH");
    asm("MOV     _filterBufD1H,a");
    // FilterBufB =  FilterBufA - FilterBufD2
    asm("mov     a, _filterBufAL");
    asm("sub     a, _filterBufD2L");
    asm("mov     _filterBufBL, a");
    asm("mov     a, _filterBufAM");
    asm("sbc     a, _filterBufD2M");
    asm("mov     _filterBufBM, a");
    asm("mov     a, _filterBufAH");
    asm("sbc     a, _filterBufD2H");
    asm("mov     _filterBufBH, a");
    // FilterBufD2 = FilterBufA
    asm("MOV     a,_filterBufAL");
    asm("MOV     _filterBufD2L,a");
    asm("MOV     a,_filterBufAM");
    asm("MOV     _filterBufD2M,a");
    asm("MOV     a,_filterBufAH");
    asm("MOV     _filterBufD2H,a");
    // FilterBufA =  FilterBufB - FilterBufD3
    asm("mov     a, _filterBufBL");
    asm("sub     a, _filterBufD3L");
    asm("mov     _filterBufAL, a");
    asm("mov     a, _filterBufBM");
    asm("sbc     a, _filterBufD3M");
    asm("mov     _filterBufAM, a");
    asm("mov     a, _filterBufBH");
    asm("sbc     a, _filterBufD3H");
    asm("mov     _filterBufAH, a");
    // FilterBufD3 = FilterBufB
    asm("MOV     a,_filterBufBL");
    asm("MOV     _filterBufD3L,a");
    asm("MOV     a,_filterBufBM");
    asm("MOV     _filterBufD3M,a");
    asm("MOV     a,_filterBufBH");
    asm("MOV     _filterBufD3H,a");

    asm("MOV     a,_filterBufAL");
    asm("MOV     _filterADCDataCurrent[0],a");
    asm("MOV     a,_filterBufAM");
    asm("MOV     _filterADCDataCurrent[1],a");
    asm("MOV     a,_filterBufAH");
    asm("MOV     _filterADCDataCurrent[2],a");
    //  ȥ����ؓ�D�Q�������
    asm("mov     a, 08H");
    asm("addm    a, _filterADCDataCurrent[2]");
    asm("mov     a, 0FH");
    asm("andm    a, _filterADCDataCurrent[2]");
	asm("CLR     _filterADCDataCurrent[3]");

	filterADCDataLast = filterADCDataCurrent;
	//ȡ��׃�������ֵ����Сֵ
	if (filterADCDataCurrent > gu32v_FilterADCDataMax)
	{
		gu32v_FilterADCDataMax = filterADCDataCurrent;
	}
	if (filterADCDataCurrent < gu32v_FilterADCDataMin)
	{
		gu32v_FilterADCDataMin = filterADCDataCurrent;
	}
	//����B�m��ι��������ֵ����Сֵ��ֵ�^С(׃��ƽ��)���i��ԓֵ
	if ((gu32v_FilterADCDataMax - gu32v_FilterADCDataMin) < WeightCalData.WeightSpan*3)
	{
		lu8v_FiltLockCnt++;
		if (lu8v_FiltLockCnt > gu8v_FiltThresholdCnt)
		{
			lu8v_FiltLockCnt    = 0;
			gbv_AdcDataIsStable = 1;
		}
	}
	else
	{
		gbv_AdcDataIsStable    = 0;
		lu8v_FiltLockCnt       = 0;
		gu32v_FilterADCDataMax = 0;
		gu32v_FilterADCDataMin = 0xFFFFFFFF;
	}
	gbv_GetFilterADCDataOK = 1;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                    �Q��ģ�K ���a				             		  @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ========================================@
//                  У�� ���a	    	    @
// ========================================@
volatile unsigned char gu8v_TracZeroTime;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ========================================@
//               �����Q�� ���a	     	  @
// ========================================@
// �ӿ�׃��
volatile unsigned int gu16v_CurrentWeight_g; // ��ǰ����ֵ,��λ��g
volatile bit gbv_IsNeedTare; 				 // 1 ����ȡ���c,��ǰ�����鷀�������r��ǰ������0
volatile bit gbv_WeightisN;					 // 1 ������ֵؓ 0 ����������
volatile unsigned long gu32v_CurrentChangeADC;
volatile unsigned long gu32v_LastChangeADC;
volatile unsigned long gu32v_StableChangeADC;
unsigned char gu8v_UpdateZeroCnt;
unsigned char gu8v_UpdateWeightCnt;
extern volatile bit gbv_CalStatusHaveSend;	// ���İ���������
/***********************************
Function: �Q��Ӳ������
INPUT	:
OUTPUT	:
NOTE	:
***********************************/
// void fun_WeightHardwareSetting()
// {
// 	SET_ADCCHAN_WEIGHT();
// 	SET_ADCGAIN_WEIGHT();
// 	SET_DCSET_WEIGHT();
// 	SET_ADCVREF_VREFPVREFN(); //�x������ⲿ����늉�
// }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                  SDK ���⿂�ӿ�				             	       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/********************************************************************
Function: SDK��늳�ʼ��
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_ScalesSDK_PowerOn()
{
	fun_LoadUserSetting();
	// weight PowerOn config
	if (Read_EEPROMByte(EEPROM_ADDR_START) == EEPROM_DATA_CALID_CODE)
	{
		unsigned char *p;
		unsigned char eepromAddress;
		p = &WeightCalData.MinADC;
		for (eepromAddress = EEPROM_ADDR_START+1; eepromAddress <= EEPROM_ADDR_END; eepromAddress++)
		{
			*p = Read_EEPROMByte(eepromAddress);
			p++;
		}
	}
	gu8v_ScalesSDKState = ENTER_WEIGHT_NORMAL;
}
/********************************************************************
Function: SDK���/���߳�ʼ��
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_ScalesSDK_PowerDown()
{
	gu8v_ScalesSDKState    = ENTER_WEIGHT_NORMAL;
	gu16v_CurrentWeight_g  = 0;
	SET_ADCPOWER_OFF();
	SET_LDO_DISABLE();
}
volatile unsigned long *pointerCalWeight;
/********************************************************************
Function: ����ģʽ�{��
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_ScalesSDK()
{
	// �ГQ����ģʽ
	switch (gu8v_ScalesSDKState)
	{
		case ENTER_SDK_NONE:
			gu8v_ScalesSDKState = STATE_SDK_NONE;
			SET_ADCPOWER_OFF();
			SET_LDO_DISABLE();
			break;
		case ENTER_WEIGHT_NORMAL:
			gu8v_ScalesSDKState = STATE_WEIGHT_PREPARE;
			SET_ADCCHAN_WEIGHT();
			SET_ADCGAIN_WEIGHT();
			SET_DCSET_WEIGHT();
			SET_ADCVREF_VREFPVREFN(); //�x������ⲿ����늉�
			SET_LDO_EN2_6();
			fun_LoadWeightSetting();
			SET_ADCPOWER_ON();
			SET_ADCMODE_NORMAL();
			SET_ADCINTERRUPT_ENABLE();
			SET_ADC_STARTCONVERT();
			lu8v_ADCCnt = 0;
			gbv_GetADCSourceDataOK = 0;
			gbv_FirstFilterI = 0;
			gbv_FirstFilterD = 0;
			break;
		case ENTER_WEIGHT_CAL:
		    WeightCalData.MinADC = 0;
			pointerCalWeight = &WeightCalData.MinADC;
			gbv_IsNeedTare = 1;
			gu8v_ScalesSDKState = STATE_WEIGHT_CAL0;
			SET_ADCCHAN_WEIGHT();
			SET_ADCGAIN_WEIGHT();
			SET_DCSET_WEIGHT();
			SET_ADCVREF_VREFPVREFN(); //�x������ⲿ����늉�
			SET_LDO_EN2_6();
			fun_LoadWeightSetting();
			SET_ADCPOWER_ON();
			SET_ADCMODE_NORMAL();
			SET_ADCINTERRUPT_ENABLE();
			SET_ADC_STARTCONVERT();
			lu8v_ADCCnt = 0;
			gbv_GetADCSourceDataOK = 0;
			gbv_FirstFilterI = 0;
			gbv_FirstFilterD = 0;
			break;
		case STATE_WEIGHT_PREPARE:
		case STATE_WEIGHT_WEIGHTING:
			fun_LowFreqFiltering();
			// fun_GetWeightData();
			if (gbv_GetFilterADCDataOK)
			{
				gbv_GetFilterADCDataOK = 0;
				gu8v_ScalesSDKState = STATE_WEIGHT_WEIGHTING;
				gu32v_CurrentChangeADC = fun_unsigned32BitABS(filterADCDataCurrent, WeightCalData.MinADC);
				if (gbv_AdcDataIsStable)
				{
					// ����ȥƤ
					if (gbv_IsNeedTare)
					{
						gbv_IsNeedTare = 0;
						WeightCalData.MinADC = filterADCDataCurrent;
						gu32v_CurrentChangeADC = 0;
						gu32v_StableChangeADC = gu32v_CurrentChangeADC;
						// gu32v_LastChangeADC = gu32v_CurrentChangeADC;
					}
					// �o�����r ���c����
					if (gu16v_CurrentWeight_g < TRACK_ZERO_WEIGHT_G)
					{
						// gu8v_TracZeroTime++;
						// if (gu8v_TracZeroTime > (3000 / 25))	// �����40Hz
						// {
							WeightCalData.MinADC = filterADCDataCurrent;
						// }
					}
					else
					{
						// gu8v_TracZeroTime = 0;
					}
				}
				// ��̖ؓ�Д�
				if (filterADCDataCurrent < WeightCalData.MinADC)
				{
					gbv_WeightisN = 1; // ������ֵؓ
				}
				else
				{
					gbv_WeightisN = 0; // ��������ֵ
				}
				// ��׃̎��
				if (fun_unsigned32BitABS(gu32v_CurrentChangeADC, gu32v_LastChangeADC) < WeightCalData.WeightSpan)
				{
					gu8v_UpdateZeroCnt++;   					 // 25ms�M��һ��
					if (gu8v_UpdateZeroCnt > 200)
					{
						gu8v_UpdateZeroCnt = 0;
						if (gbv_WeightisN)
						{
							WeightCalData.MinADC = filterADCDataCurrent + gu32v_LastChangeADC;
						}
						else
						{
							WeightCalData.MinADC = filterADCDataCurrent - gu32v_LastChangeADC;
						}
						gu32v_LastChangeADC = 0;
					}
				}
				else
				{
					gu32v_LastChangeADC   = gu32v_CurrentChangeADC;
					gu8v_UpdateZeroCnt = 0;
				}
				// ����̎��
//				unsigned long ChangeADCForGetWeight;
				if (fun_unsigned32BitABS(gu32v_CurrentChangeADC, gu32v_StableChangeADC) < WeightCalData.WeightSpan*2/3)
				{
					// ׃��С�Span,�����·���ֵ
					gu8v_UpdateWeightCnt = 0;
				}
				else
				{
					gu8v_UpdateWeightCnt++;
					if(gu8v_UpdateWeightCnt > 1)
					{
						// �B�m����׃�����span,���®�ǰֵ
						gu32v_StableChangeADC = gu32v_CurrentChangeADC;
					}
				}
				// ����Ӌ��
				if (WeightCalData.MaxWeightG !=0 && gu32v_StableChangeADC > WeightCalData.MidADC)
				{
					gu16v_CurrentWeight_g = WeightCalData.MidWeightG + (gu32v_StableChangeADC - WeightCalData.MidADC) * (u32)(WeightCalData.MaxWeightG - WeightCalData.MidWeightG) / WeightCalData.MaxADC;
				}
				else
				{
					gu16v_CurrentWeight_g = gu32v_StableChangeADC * (u32)WeightCalData.MidWeightG / WeightCalData.MidADC;
				}
			}
			break;
		case STATE_WEIGHT_CAL0:
		case STATE_WEIGHT_CAL1:
		case STATE_WEIGHT_CAL2:
			fun_LowFreqFiltering();
			if (gbv_AdcDataIsStable)
			{
				gbv_AdcDataIsStable = 0;
				if (filterADCDataCurrent > (*pointerCalWeight + 25000) && gbv_CalStatusHaveSend)
				{
					gbv_CalStatusHaveSend = 0;
					*pointerCalWeight = filterADCDataCurrent;
					// ���c�˶�
					if (gu8v_ScalesSDKState == STATE_WEIGHT_CAL1 && WeightCalData.MaxWeightG == 0)
					{
						WeightCalData.MaxADC = 0;
						WeightCalData.MaxWeightG = 0;
						WeightCalData.MidADC = WeightCalData.MidADC - WeightCalData.MinADC;

						// ÿ g ��ADC
						WeightCalData.WeightSpan = WeightCalData.MidADC / WeightCalData.MidWeightG;
						unsigned char eepromAddress;
						unsigned char *p;
						p = &WeightCalData.MinADC;
						for (eepromAddress = EEPROM_ADDR_START + 1; eepromAddress <= EEPROM_ADDR_END; eepromAddress++)
						{
							Write_EEPROMByte(eepromAddress, *p);
							p++;
						}
						Write_EEPROMByte(EEPROM_ADDR_START,EEPROM_DATA_CALID_CODE);
						gu8v_ScalesSDKState   = STATE_WEIGHT_CALPASS;
					}
					else if (gu8v_ScalesSDKState == STATE_WEIGHT_CAL2 && WeightCalData.MaxWeightG != 0)
					{
						WeightCalData.MaxADC = filterADCDataCurrent - WeightCalData.MidADC;
						WeightCalData.MidADC = WeightCalData.MidADC - WeightCalData.MinADC;

						WeightCalData.WeightSpan = WeightCalData.MidADC / WeightCalData.MidWeightG;
						unsigned char eepromAddress;
						unsigned char *p;
						p = &WeightCalData.MinADC;
						for (eepromAddress = EEPROM_ADDR_START + 1; eepromAddress <= EEPROM_ADDR_END; eepromAddress++)
						{
							Write_EEPROMByte(eepromAddress, *p);
							p++;
						}
						Write_EEPROMByte(EEPROM_ADDR_START,EEPROM_DATA_CALID_CODE);
						gu8v_ScalesSDKState   = STATE_WEIGHT_CALPASS;
					}
					else
					{
				    	pointerCalWeight++;
					    *pointerCalWeight = filterADCDataCurrent;
						gu8v_ScalesSDKState++;
					}
				}
			}
			break;
		default:
			break;
	}
}
