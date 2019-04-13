//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              此文件不能修改!!!                                      @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "ScalesSDK_UserSetting.h"
#include "ScalesSDK_Interface.h"
#include "BH66F5242.h"

extern volatile unsigned int gu16v_FiltThreshold;		// 濾波鎖定閥值
extern volatile unsigned char gu8v_FiltThresholdCnt;	// 濾波鎖定次數閥值
extern volatile WeightCalData_t WeightCalData;
// ADC DATA RARE 計算方式:
// FMCLK = Fsys = 4000000,CHOP = 2, N = 12,OSR = 16384
// FADCK = FMCLK/(CHOP/N) =166667=167K
// DataRate = FADCK/OSR = 10.2HZ
#define CHOP2_FLMS30()              { _flms2=0; _flms1=0; _flms0=0;}
#define CHOP2_FLMS12()              { _flms2=0; _flms1=1; _flms0=0;}
#define CHOP1_FLMS30()              { _flms2=1; _flms1=0; _flms0=0;}
#define CHOP1_FLMS12()              { _flms2=1; _flms1=1; _flms0=0;}
#define OSR_16384()                 { _ador2=0; _ador1=0; _ador0=0;}
#define OSR_8192()                  { _ador2=0; _ador1=0; _ador0=1;}
#define OSR_4096()                  { _ador2=0; _ador1=1; _ador0=0;}
#define OSR_2048()                  { _ador2=0; _ador1=1; _ador0=1;}
#define OSR_1024()                  { _ador2=1; _ador1=0; _ador0=0;}
#define OSR_512()                   { _ador2=1; _ador1=0; _ador0=1;}
#define OSR_256()                   { _ador2=1; _ador1=1; _ador0=0;}
#define OSR_128()                   { _ador2=1; _ador1=1; _ador0=1;}
#ifdef SYS_HIGH_FREQUENCY_OSC_4MHZ
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_16384();}
#define SET_ADC_DATARATE_20HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_8192(); }
#define SET_ADC_DATARATE_40HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_4096(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x1F; CHOP2_FLMS30(); OSR_1024(); }
#endif
#ifdef SYS_HIGH_FREQUENCY_OSC_8MHZ
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_16384() }
#define SET_ADC_DATARATE_20HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_8192(); }
#define SET_ADC_DATARATE_27HZ()		{ _adcs=0x05; CHOP2_FLMS12(); OSR_1024(); }
#define SET_ADC_DATARATE_32HZ()		{ _adcs=0x1F; CHOP2_FLMS30(); OSR_4096(); }
#define SET_ADC_DATARATE_40HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_4096(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x00; CHOP2_FLMS30(); OSR_1024(); }
#endif
#ifdef SYS_HIGH_FREQUENCY_OSC_12MHZ
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_8192(); }
#define SET_ADC_DATARATE_20HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_4096(); }
#define SET_ADC_DATARATE_40HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_2048(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x02; CHOP2_FLMS30(); OSR_512();  }
#endif
// #define SET_ADCGAIN_WEIGHT()        { _pgac0 = 0x36;}   // 稱重ADC放大設置,VGS=0.5,ADGN =4,PGA=64
// #define SET_DCSET_WEIGHT()          { _pgac1 = 0x0E;}   // 稱重DCSET設置,DCSET = -0.75*VR
// #define SET_ADCCHAN_WEIGHT()        { _pgacs = 0x10;}   // 稱重ADC 通道AN0&AN1
// #define SET_ADCVREF_VREFPVREFN()	{ _vrefs = 1; }
// #define SET_ADCVREF_VCMAVSS()		{ _vrefs = 0; }
void fun_LoadUserSetting()
{
	WeightCalData.MinADC = CAL0DATA_DEFAULT;
	WeightCalData.MidADC = CAL1DATA_DEFAULT;
	WeightCalData.MaxADC = CAL2DATA_DEFAULT;
	WeightCalData.MidWeightG = CAL_WEIGHT_MID_G;
	WeightCalData.MaxWeightG = CAL_WEIGHT_MAX_G;
	WeightCalData.WeightSpan = CAL_WEIGHTSPAN;
	gu8v_FiltThresholdCnt = ADCSTABLE_WEIGHT_CNT;
	gu16v_FiltThreshold   = ADCSTABLE_WEIGHT_THRESHOLD;
}
void fun_LoadWeightSetting()
{
	SET_ADC_DATARATE_20HZ();
	// SET_ADC_DATARATE_32HZ();
}
