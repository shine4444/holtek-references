asm (" message' **************************************************** ' ");
asm (" message' *       2018 BY BEST HEALTH ELECTRONIC INC         * ' ");
asm (" message' *__________________________________________________* ' ");
asm (" message' *        SDK  NAME  : 	  Scales_SDK	           * ' ");
asm (" message' *           MCU     :      BH66F5242               * ' ");
asm (" message' *      CFG  Version :      1.0                     * ' ");
asm (" message' *      IDE  Version :      7.95                    * ' ");
asm (" message' *      CODE Version :      1.0                     * ' ");
asm (" message' *      DATA RELEASE :     2018/01/20               * ' ");
asm (" message' **************************************************** ' ");
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              此文件不能修改!!!                                      @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifndef _SCALES_SDK_INTERFACE_H_
#define _SCALES_SDK_INTERFACE_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 接口變量 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// RW 可讀可寫, R只能讀,不能寫!!!
extern volatile bit gbv_IsNeedTare;                         // RW   1 主動取零點,當前重量為穩定重量時當前重量為0
extern volatile unsigned char gu8v_ScalesSDKState; 		    // RW   工作狀態讀取與切換
extern volatile unsigned int gu16v_CurrentWeight_g;	        // R    当前重量值,單位為g
extern volatile unsigned long filterADCDataCurrent;         // R    重量ADC濾波后數據
extern volatile bit gbv_WeightisN;			                // R    1 重量為負值 0 重量為正值
extern volatile unsigned char SourceADCHigh, SourceADCMid , SourceADCLow;  // R 原始ADC數據
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 接口函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_ScalesSDK();            // 主函數,主程序循環調用
void fun_ScalesSDK_PowerOn();    // 上電初始化,MCU上電后調用一次
void fun_ScalesSDK_PowerDown();  // 休眠初始化,MCU休眠前調用一次

unsigned char Read_EEPROMByte(unsigned char addr);                  // 讀一個Byte數據
void Write_EEPROMByte(unsigned char addr, unsigned char WriteData); // 寫一個Byte數據
unsigned long fun_unsigned32BitABS(unsigned long a, unsigned long b);// 取32位無符號差值
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// gu8v_ScalesSDKState 釋義
enum BodyfatSDKState{
    // 關閉SDK
    ENTER_SDK_NONE,           // 0 進入空循環,ADC 及 LDO Power Off
    STATE_SDK_NONE,           // 1 SDK處於空循環
    // 普通稱重
    ENTER_WEIGHT_NORMAL,      // 2 進入正常稱重模式
    STATE_WEIGHT_PREPARE,     // 3 稱重準備中
    STATE_WEIGHT_WEIGHTING,   // 4 重量量測中,此時可以讀取gu16v_CurrentWeight_g
    // 重量校準標定
    ENTER_WEIGHT_CAL,         // 5 進入重量校準模式
    STATE_WEIGHT_CAL0,        // 6 正在標定零點
    STATE_WEIGHT_CAL1,        // 7 正在標定第1點
    STATE_WEIGHT_CAL2,        // 8 正在標定第2點
    STATE_WEIGHT_CALPASS,     // 9 標定成功
    STATE_WEIGHT_CALFAIL,     // 10 標定失敗
    // 溫度量測,若SDK名字包含 Temp有效
    ENTER_TEMP,               // 11 進入温度測量
    STATE_TEMP_CAL,           // 12 温度校準
};

typedef struct
{
	unsigned long MinADC;	    // 最小重量對應的ADC值
	unsigned long MidADC;	    // 中間重量對應的ADC值
	unsigned long MaxADC;	    // 最大重量對應的ADC值
	unsigned int  MidWeightG;	// 重量校準值,中間點
	unsigned int  MaxWeightG;	// 重量校準值,最大點
	unsigned char WeightSpan;	// 1個分辨率對應的ADC值
}WeightCalData_t;

#endif
