#include "common.h"

extern volatile WeightCalData_t WeightCalData;
volatile unsigned char gu8v_ProtocolTxBuf[PROTOCOL_TX_LENGTH];
volatile unsigned char gu8v_ProtocolRxBuf[PROTOCOL_RX_LENGTH];
volatile unsigned char lu8v_ProtocolTxBufoffset;
volatile unsigned char lu8v_ProtocolRxBufoffset;
volatile unsigned char gu8v_CalStatusCurrent;
volatile unsigned char gu8v_CalStatusNeedSend;

unsigned char gu8v_WeightCalCnt;
volatile bit gbv_IICRxSuccess;	// ADC第一次鎖定值保存（用於對比前次AD值是否大於）
volatile unsigned int  gu16_lastCalData;
volatile bit gbv_CalStatusHaveSend;
volatile bit gbv_IsHaveCal0;
static void fun_WeightCalACK()
{
    __16_type temp;
    temp.byte.byte1 = gu8v_ProtocolRxBuf[1];
    temp.byte.byte0 = gu8v_ProtocolRxBuf[2];
	if (temp.u16 == 0x00 )
    {
		gu8v_ScalesSDKState = ENTER_WEIGHT_CAL;
		gbv_CalStatusHaveSend = 0;
		gu8v_WeightCalCnt = 0;
	}
	else
	{
		if ( gu16_lastCalData != temp.u16)
		{
			gu16_lastCalData = temp.u16;
			if (gu8v_WeightCalCnt == 0)
			{
				WeightCalData.MidWeightG = temp.u16;
			}
			if (gu8v_WeightCalCnt == 1 &&gu8v_ProtocolRxBuf[0] == CM_WEIGHT3_CAL)
			{
				WeightCalData.MaxWeightG = temp.u16;
			}
			else
			{
				WeightCalData.MaxWeightG  = 0;
			}
			gu8v_WeightCalCnt++;
		}
	}
    gu8v_ProtocolTxBuf[2] = 0x00;
    gu8v_ProtocolTxBuf[3] = 0x00;
	gu16_lastCalData = temp.u16;
}


void fun_UIProtocol()
{
	if (gbv_IICRxSuccess || gbv_UartRxSuccess)
	{
		unsigned char checksum;
		checksum = gu8v_ProtocolRxBuf[0] + gu8v_ProtocolRxBuf[1] + gu8v_ProtocolRxBuf[2];
		if (gbv_UartRxSuccess)
		{
			checksum = checksum + UART_RX_FRAME;
		}
		checksum = (~checksum);
		checksum++;
		// RX checksum
		if (checksum == gu8v_ProtocolRxBuf[3])
		{
			switch (gu8v_ProtocolRxBuf[0])
			{
				case CM_READ_ADC:// READ ADC
					gu8v_ProtocolTxBuf[1] = P_ADC;
					__16_type temp;
					temp.u16 = filterADCDataCurrent / 16;
					gu8v_ProtocolTxBuf[2] = temp.byte.byte1;
					gu8v_ProtocolTxBuf[3] = temp.byte.byte0;
					break;
				case CM_READ_WEIGHT:// READ WEIGHT
					gu8v_ProtocolTxBuf[1] = P_WEIGHT | gbv_WeightisN;
					__16_type gu16v_CurrentWeight;
					if(gbv_IsNeedTare)
					{
						gu16v_CurrentWeight.u16 = 0xFFFF;
					}
					else
					{
						gu16v_CurrentWeight.u16 = gu16v_CurrentWeight_g;
					}			
					gu8v_ProtocolTxBuf[2] = gu16v_CurrentWeight.byte.byte1;
					gu8v_ProtocolTxBuf[3] = gu16v_CurrentWeight.byte.byte0;
					break;
			#ifdef TEMP_ENABLE
				case CM_READ_TEMP:// READ TEMP
					gu8v_ProtocolTxBuf[1] = P_TEMP | gbv_TempisN;
					gu8v_ProtocolTxBuf[2] = gu16v_CurrentTemp.byte.byte1;
					gu8v_ProtocolTxBuf[3] = gu16v_CurrentTemp.byte.byte0;
					break;
			#endif
				case CM_WEIGHT_TARE:// Tare
					gbv_IsNeedTare = 1;
					gu8v_ProtocolTxBuf[1] = CM_WEIGHT_TARE;
					gu8v_ProtocolTxBuf[2] = 0x00;
					gu8v_ProtocolTxBuf[3] = 0x00;
					break;
				case CM_FW_VERSION:// Read FW version
					gu8v_ProtocolTxBuf[1] = CM_FW_VERSION;
					gu8v_ProtocolTxBuf[2] = BH_ID;
					gu8v_ProtocolTxBuf[3] = FW_VERSION;
					break;
				case CM_READ_CAL_STATUS:// Read CAL Status
					// 需要注意必須等主控讀取后才能切換為下一個狀態
					gu8v_ProtocolTxBuf[1] = CM_READ_CAL_STATUS;
					if (gu8v_ScalesSDKState == STATE_WEIGHT_CAL0)
					{
						gu8v_CalStatusCurrent = CALING_STATUS_0;
					}
					else if (gu8v_ScalesSDKState == STATE_WEIGHT_CAL1)
					{
						gu8v_CalStatusCurrent = CALING_STATUS_1;
					}
					else if (gu8v_ScalesSDKState == STATE_WEIGHT_CAL2)
					{
						gu8v_CalStatusCurrent = CALING_STATUS_2;
					}
					else if (gu8v_ScalesSDKState == STATE_WEIGHT_CALPASS)
					{
						gu8v_CalStatusCurrent = CALING_STATUS_PASS;
					}
					else if (gu8v_ScalesSDKState == STATE_WEIGHT_CALFAIL)
					{
						gu8v_CalStatusCurrent = CALING_STATUS_FAIL;
					}
					else
					{
						gu8v_CalStatusCurrent = 0x00;
					}
					gu8v_ProtocolTxBuf[2] = gu8v_CalStatusCurrent;
					gu8v_ProtocolTxBuf[3] = 0x00;
					gbv_CalStatusHaveSend = 1;
					break;
				case CM_WRITE_TO_HALT:// ENTER HALT
					gbv_HALTMODE = 1;
					gu8v_ProtocolTxBuf[1] = CM_WRITE_TO_HALT;
					gu8v_ProtocolTxBuf[2] = 0x00;
					gu8v_ProtocolTxBuf[3] = 0x00;
					break;
				case CM_WEIGHT2_CAL:// ENTER CAL2
					gu8v_ProtocolTxBuf[1] = CM_WEIGHT2_CAL;
					fun_WeightCalACK();
					break;
				case CM_WEIGHT3_CAL:// ENTER CAL3
					gu8v_ProtocolTxBuf[1] = CM_WEIGHT3_CAL;
					fun_WeightCalACK();
					break;
				default:
					gu8v_ProtocolTxBuf[1] = 0x00;
					gu8v_ProtocolTxBuf[2] = 0x00;
					gu8v_ProtocolTxBuf[3] = 0x00;
					gbv_IICRxSuccess  = 0;
					gbv_UartRxSuccess = 0;
					break;
			}
			// UART 需要主動發送,IIC 從機 等待主機讀取數據即可
			if (gbv_UartRxSuccess)
			{
				gbv_UartTxBusy = 1; //uart 忙碌
				lu8v_ProtocolTxBufoffset = 0;
				gu8v_ProtocolTxBuf[0] = UART_TX_FRAME;	// UART 發送此位固定為UART_TX_FRAME,若為IIC在上面已經清0
				_urxen = 0;		// 發送時關閉收,防止衝突
				_acc = _uusr;
				_utxr_rxr = UART_TX_HEADER;
			}
			else
			{
				gu8v_ProtocolTxBuf[0] = 0x00;
			}
		}
		gbv_UartRxSuccess = 0;
		gbv_IICRxSuccess  = 0;
		// Tx checksum
		gu8v_ProtocolTxBuf[4] = ~(gu8v_ProtocolTxBuf[0] + gu8v_ProtocolTxBuf[1] + gu8v_ProtocolTxBuf[2] + gu8v_ProtocolTxBuf[3]) + 1;
	}
}

