//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : Temp.h
// Description: 體重量測子程序
//Targer Board: PICOOC_Display
//   MCU      : BH66F5242
//___________________________________________________________________
//___________________________________________________________________
#ifndef _TEMP_H_
#define _TEMP_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Userdefine @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@函數聲明@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_TempCal();
void fun_GetTemp();
void fun_ToTempMode();
void fun_TempPowerOnInit();
void fun_TempFiltering();

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@變量聲明@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifdef TEMP_ENABLE
extern volatile bit gbv_IsTempMode;
extern volatile bit gbv_isChangeTempMode;
extern volatile bit gbv_TogetCalTemp;
extern volatile bit gbv_TempisN;
extern volatile __16_type gu16v_CurrentTemp;   // 當前的溫度
extern volatile unsigned int gu16v_CalTemp;     // 校準點的溫度，通常為25℃ * 100
extern volatile bit gbv_ReadyGetTemp;
extern volatile unsigned long  TempAdcSourceDataSum;
extern  volatile unsigned char gu8v_TempGetTime;
#endif


#endif
