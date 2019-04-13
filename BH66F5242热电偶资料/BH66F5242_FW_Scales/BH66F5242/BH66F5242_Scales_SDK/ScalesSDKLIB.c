#include "ScalesSDK_Hardware.h"
#include "ScalesSDK_Interface.h"
#include "ScalesSDK_UserSetting.h"
#include "ScalesSDK_LIBSetting.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@變量結構體聲明@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 變量定義  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile unsigned char gu8v_ScalesSDKState;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                    EEPROM 讀寫				             		     @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/****************************************************
 Function: Write_EEPROM
 INPUT	: @addr 寫地址 @寫數據
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
	//_WREN與_WR需在連續的兩個指令週期內完成
	asm("set [0x02].3");	// WREN
	asm("set [0x02].2");	// WR
	asm("sz  [0x02].2");	// WR
	asm("jmp $-1");
	_iar1 = 0; //disable WREN
	_emi = EMI_Protect;
}
/*****************************************************
 Function: Read_EEPROM
 INPUT	: @addr 讀地址
 OUTPUT	: @讀到的數據
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
//                              24Bit ADC基本讀取                                       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile bit gbv_GetADCSourceDataOK; // 得到一筆原始的ADC值
volatile unsigned char lu8v_ADCCnt;  // ADC採集次數
volatile unsigned char SourceADCHigh, SourceADCMid , SourceADCLow;  // 原始ADC數據
/*************************************************
 Function: 開始ADC 採樣
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
 Function: 停止ADC 採樣
 INPUT	:
 OUTPUT	:
 NOTE	: 關閉ADC模塊耗電
 *************************************************/
void fun_ADCStop()
{
	SET_LDO_DISABLE();
	SET_ADCPOWER_OFF();
}
/*********************************
Function: ADC中斷,獲取ADC值
INPUT	:
OUTPUT	:
NOTE	:
*********************************/
//@------------ADC 中斷入口函數---------------@
DEFINE_ISR(ADC_ISR, ADC_VECTOR)
{
	if (_eoc == 1 && gbv_GetADCSourceDataOK == 0)
	{ //ADC 轉換完成
		_eoc = 0;
		lu8v_ADCCnt++;
		//前三筆數據丟掉，第四筆才開始處理
		if (lu8v_ADCCnt > 3)
		{
			_adcdl = 1;
			SourceADCLow  = _adrl;
			SourceADCMid  = _adrm;
			SourceADCHigh = _adrh;
			_adcdl = 0; //數據讀取完成，取消鎖存
			gbv_GetADCSourceDataOK = 1;
		}
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                ADC 濾波算法                                          @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define   FILTER_CNT      008        //濾波次數
// 濾波結果
volatile bit gbv_GetFilterADCDataOK;   			// 1 得到一筆濾波后的ADC值
volatile bit gbv_AdcDataIsStable;	   			// 1 ADC值穩定, 0 ADC不穩定
// sinc4 濾波
bit gbv_FirstFilterI;   // 第一次積分濾波
bit gbv_FirstFilterD;   // 第一次微分濾波
unsigned char filterBufI1H , filterBufI1M , filterBufI1L , filterBufI1HH;  // 積分變量1
unsigned char filterBufI2H , filterBufI2M , filterBufI2L , filterBufI2HH;  // 積分變量2
unsigned char filterBufI3H , filterBufI3M , filterBufI3L , filterBufI3HH;  // 積分變量3
// unsigned char filterBufI4H , filterBufI4M , filterBufI4L , filterBufI4HH;  // 積分變量4
unsigned char filterBufIOutputH,filterBufIOutputM,filterBufIOutputL;       // 積分變量输出,取最高20bit
unsigned char filterBufD1H , filterBufD1M , filterBufD1L;  	// 微分變量1
unsigned char filterBufD2H , filterBufD2M , filterBufD2L;  	// 微分變量2
unsigned char filterBufD3H , filterBufD3M , filterBufD3L;  	// 微分變量3
// unsigned char filterBufD4H , filterBufD4M , filterBufD4L;  	// 微分變量4
unsigned char filterBufAH , filterBufAM , filterBufAL;		// 微分變量中間量A
unsigned char filterBufBH , filterBufBM , filterBufBL;		// 微分變量中間量B
// unsigned char _filterADCDataCurrent[2],_filterADCDataCurrent[1],_filterADCDataCurrent[0];    // 濾波輸出數據
volatile unsigned long filterADCDataCurrent;          // R    重量ADC濾波后數據
volatile unsigned long filterADCDataLast;             // R    重量ADC濾波后數據
// 穩定判斷
volatile unsigned char lu8v_FiltLockCnt;		 // 當前濾波穩度次數
volatile unsigned long gu32v_FilterADCDataMax;	 // 濾波中最大的ADC值
volatile unsigned long gu32v_FilterADCDataMin;	 // 濾波中最小的ADC值
volatile unsigned int gu16v_FiltThreshold;		 // 濾波鎖定閥值
volatile unsigned char gu8v_FiltThresholdCnt;	 // 濾波鎖定次數閥值


// 用戶設置值
volatile WeightCalData_t WeightCalData;
/***********************************************
 Function: 取得兩個值之間的差值
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
    //  取最高20bit
    asm("mov     a, 4H");
    asm("_LI1:");
    asm("clr     c");
    asm("rrc     _SourceADCHigh");
    asm("rrc     _SourceADCMid");
    asm("rrc     _SourceADCLow");
    asm("sdz     acc");
    asm("jmp     _LI1");
    gbv_FirstFilterI = 1;   // 第一次積分濾波
	gbv_FirstFilterD = 1;   // 第一次微分濾波
    // 快速初始化
    asm("SZ	_gbv_FirstFilterI");
    asm("JMP _FilterI");
    //asm("_init_FilterI:");
	asm("SET	_gbv_FirstFilterI");
    // 積分器1=積分器2=積分器3=積分器4=原始adc數據
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
    // 原始adc數據 + 積分器1 = 積分器1
    asm("mov     a, _SourceADCLow");
    asm("addm    a, _filterBufI1L");
    asm("mov     a, _SourceADCMid");
    asm("adcm    a, _filterBufI1M");
    asm("mov     a, _SourceADCHigh");
    asm("adcm    a, _filterBufI1H");
    asm("CLR     acc");
    asm("adcm    a, _filterBufI1HH");
    // 積分器1 + 積分器2 = 積分器2
    asm("mov     a, _filterBufI1L");
    asm("addm    a, _filterBufI2L");
    asm("mov     a, _filterBufI1M");
    asm("adcm    a, _filterBufI2M");
    asm("mov     a, _filterBufI1H");
    asm("adcm    a, _filterBufI2H");
    asm("mov     a, _filterBufI1HH");
    asm("adcm    a, _filterBufI2HH");
    // 積分器2 + 積分器3 = 積分器3
    asm("mov     a, _filterBufI2L");
    asm("addm    a, _filterBufI3L");
    asm("mov     a, _filterBufI2M");
    asm("adcm    a, _filterBufI3M");
    asm("mov     a, _filterBufI2H");
    asm("adcm    a, _filterBufI3H");
    asm("mov     a, _filterBufI2HH");
    asm("adcm    a, _filterBufI3HH");
    // 等待獲取8筆數據 	2^3   原始20Bit+3*3=29Bit
	#define  DownLoadSample  8
	#if (DownLoadSample == 8)
    asm("mov     a, (8+2)");
    asm("sub     a, _lu8v_ADCCnt");
    asm("sz      c");
    asm("RET");     // 沒有8筆數據返回
    asm("MOV     a,3"); // 已經有8筆數據,取出最高的20bit
    asm("MOV     _lu8v_ADCCnt,a");
    // 積分器輸出 = 積分器4     取出最高的20Bit,即Bit32~Bit12
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

    // 快速初始化
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
    //  去除正負轉換為單向線性
    asm("mov     a, 08H");
    asm("addm    a, _filterADCDataCurrent[2]");
    asm("mov     a, 0FH");
    asm("andm    a, _filterADCDataCurrent[2]");
	asm("CLR     _filterADCDataCurrent[3]");

	filterADCDataLast = filterADCDataCurrent;
	//取得變化的最大值和最小值
	if (filterADCDataCurrent > gu32v_FilterADCDataMax)
	{
		gu32v_FilterADCDataMax = filterADCDataCurrent;
	}
	if (filterADCDataCurrent < gu32v_FilterADCDataMin)
	{
		gu32v_FilterADCDataMin = filterADCDataCurrent;
	}
	//如果連續多次範圍內最大值和最小值差值較小(變化平衡)，鎖定該值
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
//                                    稱重模塊 代碼				             		  @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ========================================@
//                  校準 代碼	    	    @
// ========================================@
volatile unsigned char gu8v_TracZeroTime;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ========================================@
//               正常稱重 代碼	     	  @
// ========================================@
// 接口變量
volatile unsigned int gu16v_CurrentWeight_g; // 当前重量值,單位為g
volatile bit gbv_IsNeedTare; 				 // 1 主動取零點,當前重量為穩定重量時當前重量為0
volatile bit gbv_WeightisN;					 // 1 重量為負值 0 重量為正數
volatile unsigned long gu32v_CurrentChangeADC;
volatile unsigned long gu32v_LastChangeADC;
volatile unsigned long gu32v_StableChangeADC;
unsigned char gu8v_UpdateZeroCnt;
unsigned char gu8v_UpdateWeightCnt;
extern volatile bit gbv_CalStatusHaveSend;	// 美的案特殊需求
/***********************************
Function: 稱重硬件配置
INPUT	:
OUTPUT	:
NOTE	:
***********************************/
// void fun_WeightHardwareSetting()
// {
// 	SET_ADCCHAN_WEIGHT();
// 	SET_ADCGAIN_WEIGHT();
// 	SET_DCSET_WEIGHT();
// 	SET_ADCVREF_VREFPVREFN(); //選擇來自外部參考電壓
// }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                  SDK 對外總接口				             	       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/********************************************************************
Function: SDK上電初始化
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
Function: SDK掉電/休眠初始化
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
Function: 工作模式調用
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_ScalesSDK()
{
	// 切換工作模式
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
			SET_ADCVREF_VREFPVREFN(); //選擇來自外部參考電壓
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
			SET_ADCVREF_VREFPVREFN(); //選擇來自外部參考電壓
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
					// 主動去皮
					if (gbv_IsNeedTare)
					{
						gbv_IsNeedTare = 0;
						WeightCalData.MinADC = filterADCDataCurrent;
						gu32v_CurrentChangeADC = 0;
						gu32v_StableChangeADC = gu32v_CurrentChangeADC;
						// gu32v_LastChangeADC = gu32v_CurrentChangeADC;
					}
					// 無重量時 零點更新
					if (gu16v_CurrentWeight_g < TRACK_ZERO_WEIGHT_G)
					{
						// gu8v_TracZeroTime++;
						// if (gu8v_TracZeroTime > (3000 / 25))	// 採樣率40Hz
						// {
							WeightCalData.MinADC = filterADCDataCurrent;
						// }
					}
					else
					{
						// gu8v_TracZeroTime = 0;
					}
				}
				// 正負號判斷
				if (filterADCDataCurrent < WeightCalData.MinADC)
				{
					gbv_WeightisN = 1; // 重量為負值
				}
				else
				{
					gbv_WeightisN = 0; // 重量為正值
				}
				// 蠕變處理
				if (fun_unsigned32BitABS(gu32v_CurrentChangeADC, gu32v_LastChangeADC) < WeightCalData.WeightSpan)
				{
					gu8v_UpdateZeroCnt++;   					 // 25ms進來一次
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
				// 抖動處理
//				unsigned long ChangeADCForGetWeight;
				if (fun_unsigned32BitABS(gu32v_CurrentChangeADC, gu32v_StableChangeADC) < WeightCalData.WeightSpan*2/3)
				{
					// 變化小於Span,不更新穩定值
					gu8v_UpdateWeightCnt = 0;
				}
				else
				{
					gu8v_UpdateWeightCnt++;
					if(gu8v_UpdateWeightCnt > 1)
					{
						// 連續三次變化大於span,更新當前值
						gu32v_StableChangeADC = gu32v_CurrentChangeADC;
					}
				}
				// 重量計算
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
					// 兩點標定
					if (gu8v_ScalesSDKState == STATE_WEIGHT_CAL1 && WeightCalData.MaxWeightG == 0)
					{
						WeightCalData.MaxADC = 0;
						WeightCalData.MaxWeightG = 0;
						WeightCalData.MidADC = WeightCalData.MidADC - WeightCalData.MinADC;

						// 每 g 的ADC
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
