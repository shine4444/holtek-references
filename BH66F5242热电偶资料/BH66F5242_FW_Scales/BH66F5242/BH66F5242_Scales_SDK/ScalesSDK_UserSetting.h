#ifndef _SCALES_SDK_USERSETTING_H_
#define _SCALES_SDK_USERSETTING_H_
// Note
// 依據自己產品需求修改以下參數
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                系統頻率  設置                                        @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// #define  SYS_HIGH_FREQUENCY_OSC_4MHZ
#define  SYS_HIGH_FREQUENCY_OSC_8MHZ
// #define  SYS_HIGH_FREQUENCY_OSC_12MHZ
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                稱重規格  設置                                        @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// operate : numeric    function: cal weight
// WEIGHT_CAL_MAX > WEIGHT_CAL_MID
// WEIGHT_CAL_MAX = 0表示兩點標定
#define CAL_WEIGHT_MID_G      10000   // Range 0~65535 中間點校準重量 SDK都以 1g分辨率 Default 2000g
#define CAL_WEIGHT_MAX_G         0    // Range 0~65535 最大點校準重量 SDK都以 1g分辨率 Default 5000g
#define CAL_WEIGHTSPAN         150    // Range 2~255   默認1分辨率對應ADC值
//**************量校準參數預設***********
#define CAL0DATA_DEFAULT		127990  // 0點默認校準值
#define CAL1DATA_DEFAULT		 168245 // 第1點默認校準值
#define CAL2DATA_DEFAULT		     0  // 第2點默認校準值
// // operate : numeric    function: min weight
// #define WEIGHT_G_MIN            100     // Range    70~100 最小稱重重量= x公斤*20 ,SDK都以 1g分辨率 Default 100
// // operate : numeric    function: scales auto on from halt weight
// #define WEIGHT_G_AUTOON         100     // Range   100~140 自動喚醒重量= x公斤*20 ,SDK都以 1g分辨率 Default 100
#define	WAKEUPWEIGHT            20  // 喚醒重量,單位g
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                稱重濾波  設置                                        @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//operate : numeric  	fution: ~~
#define ADCSTABLE_WEIGHT_CNT        6  //  range:  8~20 	數值越大，濾波要求越嚴格
//operate : numeric  	fution: ~~
#define ADCSTABLE_WEIGHT_THRESHOLD  20 // range: 80~400    數值越大，濾波比較寬松,建議使用1個分辨率對應的ADC值

#endif