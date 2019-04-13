/********************************* Tips *****************************
********************************************************************/
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 公共參數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_UIProtocol();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Userdefine @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define PROTOCOL_TX_LENGTH 5 // 協議中最大的長度
#define PROTOCOL_RX_LENGTH 4 // 協議中最大的長度

extern volatile unsigned char gu8v_ProtocolTxBuf[PROTOCOL_TX_LENGTH];
extern volatile unsigned char gu8v_ProtocolRxBuf[PROTOCOL_RX_LENGTH];
extern volatile unsigned char lu8v_ProtocolTxBufoffset;
extern volatile unsigned char lu8v_ProtocolRxBufoffset;
extern volatile unsigned char gu8v_CalStatusNeedSend;
extern volatile bit gbv_IICRxSuccess;	// ADC第一次鎖定值保存（用於對比前次AD值是否大於）
extern volatile bit gbv_UartRxSuccess;
extern volatile bit gbv_IsHaveCal0;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Userdefine @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define UART_RX_HEADER              0xA1
#define UART_RX_FRAME               0x5A
#define UART_TX_HEADER              0xB2
#define UART_TX_FRAME               0xA5

#define CM_READ_ADC					0xAD
#define CM_READ_WEIGHT				0xAE
#define CM_READ_TEMP  				0xAF

#define CM_WEIGHT_TARE  			0xCA
#define CM_WEIGHT2_CAL  			0xC2    // 兩點標定
#define CM_WEIGHT3_CAL  			0xC3    // 三點標定
#define CM_READ_CAL_STATUS  		0xCB

#define CM_FW_VERSION				0xAB
#define CM_WRITE_TO_HALT			0xC0

#define P_ADC                       0xD0    // 正ADC
#define N_ADC                       0xD1    // 負ADC
#define P_WEIGHT                    0xE0    // 正重量
#define N_WEIGHT                    0xE1    // 負重量
#define P_TEMP                      0xF0    // 正溫度
#define N_TEMP                      0xF1    // 負溫度

#define CALING_STATUS_0             0x01    // 正在標定0點
#define CALING_STATUS_1             0x02    // 正在標定1點
#define CALING_STATUS_2             0x05    // 正在標定2點
#define CALING_STATUS_PASS          0x06    // 標定成功
#define CALING_STATUS_FAIL          0x07    // 標定失敗


#define TEMP_CALING 5
#define TEMP_CALEND 6

#endif
