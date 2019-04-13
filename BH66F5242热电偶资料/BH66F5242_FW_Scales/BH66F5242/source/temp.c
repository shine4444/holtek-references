//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2016 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Weigh.c
// Description: 高度量測子程序
//   MCU      : BH66F5242
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"

#ifdef TEMP_ENABLE

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 變量定義 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile bit gbv_IsTempMode;
volatile bit gbv_TogetCalTemp;
volatile bit gbv_isChangeTempMode;
volatile bit gbv_TempisN;
volatile unsigned long CalTempADC;    // 校準點溫度的ADC值
volatile unsigned int gu16v_CalTemp;  // 校準點的溫度，通常為25℃ * 100
volatile __16_type gu16v_CurrentTemp; // 當前的溫度
volatile bit gbv_ReadyGetTemp;
volatile unsigned long TempAdcSourceDataSum;
volatile unsigned char gu8v_TempGetTime; // 溫度採集間隔時間
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 子程序 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/********************************************************************
Function: 對溫度進行單點校準
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_TempCal()
{
    if (gbv_TogetCalTemp && gbv_ReadyGetTemp)
    {
        gbv_TogetCalTemp = 0;
        gbv_ReadyGetTemp = 0;

        CalTempADC = TempAdcSourceDataSum - DEFAULT_ZEROTEMPOFFSET;
        gu16v_CurrentTemp.u16 = gu16v_CalTemp;

        unsigned int temp;
        temp = CalTempADC >> 16;
        Write_EEPROMByte(EEPROM_ADDR_CALTEMPADC, temp);
        temp = CalTempADC & 0xFFFF;
        Write_EEPROMByte((EEPROM_ADDR_CALTEMPADC + 2), temp);
        Write_EEPROMByte(EEPROM_ADDR_CALTEMP, gu16v_CalTemp);

        gu8v_CalStatusNeedSend = TEMP_CALEND;
        TempAdcSourceDataSum = 0;
    }
}
/********************************************************************
Function: 得到溫度值
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_GetTemp()
{
    if (gbv_ReadyGetTemp)
    {
        gbv_ReadyGetTemp = 0;
        unsigned int temp;
        temp = fun_unsigned32BitABS(TempAdcSourceDataSum, CalTempADC);
        gu16v_CurrentTemp.u16 = temp * 100 / DEFAULT_TEMPSCALE;
        if (TempAdcSourceDataSum < CalTempADC) // 已經以0零度為基準
        {
            gu16v_CurrentTemp.u16 |= 0x8000; // 溫度為負值
        }
        TempAdcSourceDataSum = 0;
    }
}
/********************************************************************
Function: 進入溫度量測模式
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_ToTempMode()
{
    SETADCVREF_VCMAVSS(); // 溫度必須使用內部參考電壓,否則每次上下電差異很大
                          // SETGAINADC_2();
                          // SETGAINVRF_1();
                          // SETGAINPGA_1();
                          // SETDCOFSET_0V();
                          // SETADCCHANN_VTSON();
                          // SETADCCHANP_VTSOP();
    _pgac0 = 0x08;
    _pgac1 = 0x00;
    _pgacs = 0x3F;
    SETADCDATARATE_10HZ();

    // SETADCBUF_ENABLE();
    // SETADCINTERRUPT_ENABLE();
    // SETDCOFSET_0V();
    fun_ADCStart();
    gbv_IsTempMode = 1;
    gbv_IsWEIGH_MODE = 0;
}

void fun_TempPowerOnInit()
{
    gu16v_CalTemp = Read_EEPROMByte(EEPROM_ADDR_CALTEMP);
    if (gu16v_CalTemp == DEFAULT_CALTEMP)
    {
        CalTempADC = Read_EEPROMByte(EEPROM_ADDR_CALTEMPADC);
        CalTempADC = CalTempADC << 16;
        CalTempADC |= Read_EEPROMByte(EEPROM_ADDR_CALTEMPADC + 2);
    }
    else
    {
        // 溫度進入校準模式
        gbv_TogetCalTemp = 1;
        gu8v_CalStatusNeedSend = TEMP_CALING;
        gu16v_CalTemp = DEFAULT_CALTEMP;
    }
    gbv_isChangeTempMode = 1;
}

void fun_TempFiltering()
{
    if (gbv_GetADCSourceDataOK)
    {
        gbv_GetADCSourceDataOK = 0;
        TempAdcSourceDataSum += gu32v_SourceADCDataCurrent.u32;
        if (gu8v_ADCCnt > 10)
        {
            gbv_ReadyGetTemp = 1;
            TempAdcSourceDataSum = TempAdcSourceDataSum / 8;
            gu8v_ADCCnt = 0;
        }
    }
}

#endif