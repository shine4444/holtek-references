#ifndef _SCALES_SDK_LIBSETTING_H_
#define _SCALES_SDK_LIBSETTING_H_


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 封庫修改  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include "BH66F5242.h"
#define ADC_VECTOR				0x00C   // 根據MCU的ADC中斷地址修改

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                稱重  接口配置                                        @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define EEPROM_ADDR_START		 0x01	// EEPROM 存儲開始位置
// Cal ADC    =3*4byte=12
// Cal Weight =2*2byte=4
//    Span    =1*1byte=1
//   總長度    = 12 + 4 + 1 + 1 = 18 = 0x12
#define EEPROM_ADDR_END		     0x12	// EEPROM 存儲結束位置
#define EEPROM_DATA_CALID_CODE	 0xAA   // 校準成功標誌數據,偵測到此數據,認為校準成功

#define TRACK_ZERO_WEIGHT_G     3       // 小於此重量固定時間追為0點, =0則關閉此功能
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//             User setting  LIB接口                     @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_LoadUserSetting();
void fun_LoadWeightSetting();

#endif