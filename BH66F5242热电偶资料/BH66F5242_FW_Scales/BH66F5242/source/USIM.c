#include "common.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 變量定義 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
volatile unsigned char  gu8v_TBRxTimeOutCnt;
volatile unsigned char  gu8v_TBTxCycle;
volatile unsigned char  lu8v_RxBufoffset;
volatile bit gbv_UartTxBusy;
volatile bit gbv_UartRxSuccess;
volatile bit gbv_UartFrameRxing;
volatile bit gbv_IsUartMode;
/********************************************************************
Function: Uart初始化程序
INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_USIM_PowerOn()
{
	if (gbv_IsUartMode)
	{
	#ifdef USIM_MODE_UART
		SET_UART_MODE();	// 選擇UART MODE
		SET_UART_PIN();		// IO 設置為UART
		// 數據傳輸格式設定
		SET_UART_Format_D8_P0_S1();
		// 波特率設定
		SET_UART_BAUTRATE_9600();
		SET_UART_ADDRESS_DISABLE();
		SET_UART_WAKEUP_ENABLE();
		SET_UART_RECEIVER_IE_ENABLE();
		SET_UART_TRANSMITTER_IE_ENABLE();
		SET_UART_TRANSMITTER_EMPTY_ENABLE();
		SET_UART_ENABLE();
		SET_UART_ISR_ENABLE();
	#endif
	}
	else
	{
	#ifdef USIM_MODE_IIC
		SET_IIC_SLAVE_FAST();
		SET_IIC_PIN();
		// IIC 地址設定
		SET_IIC_ADDRESS(0xA0);
		SET_IIC_WAKEUP_ENABLE();
		SET_IIC_TIMEOUT_X_MS(64);
		SET_IIC_TIMEOUT_ENABLE();
		SET_IIC_ENABLE();
		SET_IIC_ISR_ENABLE();
	#endif
	}
}

///********************************************************************
//Function: USIM
//INPUT	:
//OUTPUT:
//NOTE	: SPI/IIC/UART三選一
//********************************************************************/
DEFINE_ISR(USIM_ISR, USIM_VECTOR)
{
	if(gbv_IsUartMode)
	{
		#ifdef USIM_MODE_UART
		// 奇偶校验出错
		// if (_perr0)
		// {
		// 	_acc = _usr;
		// 	_acc = _txr_rxr;
		// }
		// 錯誤處理
		if (_unf | _uferr | _uoerr)	//  噪声干扰错误 | 帧错误 | 溢出错误
		{
			_acc = _uusr;
			_acc = _utxr_rxr;
			lu8v_ProtocolRxBufoffset = 0;
		}
		// 发送数据
		if (_utxif && gbv_UartTxBusy)
		{
			if ( lu8v_ProtocolTxBufoffset < PROTOCOL_TX_LENGTH)
			{
				_utxr_rxr = gu8v_ProtocolTxBuf[lu8v_ProtocolTxBufoffset];
				lu8v_ProtocolTxBufoffset++;
			}
			else
			{
				if (_utidle)
				{
					gbv_UartTxBusy = 0;
					_urxen = 1;
				}
			}
		}
		// 接收数据
		if (_urxif && gbv_UartRxSuccess == 0 && gbv_UartTxBusy == 0)
		{
			_utxen = 0;
			gu8v_ProtocolRxBuf[lu8v_ProtocolRxBufoffset] = _utxr_rxr;
			lu8v_ProtocolRxBufoffset++;
			if(gbv_UartFrameRxing)
			{
				if (lu8v_ProtocolRxBufoffset >= 4)
				{
					lu8v_ProtocolRxBufoffset = 0;
					gbv_UartRxSuccess = 1;
					gbv_UartFrameRxing = 0;
					_utxen = 1;
				}
			}
			else
			{
				if (gu8v_ProtocolRxBuf[0] == UART_RX_HEADER)
				{
					if (gu8v_ProtocolRxBuf[1] == UART_RX_FRAME)
					{
						lu8v_ProtocolRxBufoffset = 0x00;
						gbv_UartFrameRxing = 1;
					}
				}
				else
				{
					lu8v_ProtocolRxBufoffset = 0x00;
				}
			}
		}
		#endif
	}
	else
	{
		#ifdef USIM_MODE_IIC
		if (_simtof)		// TimeOut溢出中斷
		{
			_simtof  = 0;
			_simtoen = 1;	// reset TimerOut
			_iamwu   = 1;
			lu8v_ProtocolRxBufoffset = 0;
			lu8v_ProtocolTxBufoffset = 1;
		}
		else
		{
			if(_haas && _srw)	// addres match and IIC tx mode
			{
				_htx = 1;		// config SLAVE TO TX
				lu8v_ProtocolTxBufoffset = 1;
				_simd = gu8v_ProtocolTxBuf[lu8v_ProtocolTxBufoffset];
				lu8v_ProtocolTxBufoffset++;
			}
			else if (_haas && !_srw)	// addres match and IIC rx mode
			{
				_htx      = 0; 		// config SLAVE TO RX
				_txak     = 0;		// SET ACK signal
				_acc      = _simd;	// Dummy read from SIMD to release SCL line
				lu8v_ProtocolRxBufoffset = 0;
			}
			else if (!_haas && _htx)	// addres not match and IIC tx mode
			{
				if(_rxak)
				{//rxak=1:主機停止拒絕接收下個字節，發出停止信號
					_htx  = 0;
					_txak = 0;
					_acc  = _simd;		//虛度數值釋放總線
				}
				else					//發送數據
				{
					_simd = gu8v_ProtocolTxBuf[lu8v_ProtocolTxBufoffset];
					lu8v_ProtocolTxBufoffset ++;
				}
			}
			else if (!_haas && !_htx)	// addres not match and IIC rx mode
			{
				gu8v_ProtocolRxBuf[lu8v_ProtocolRxBufoffset] = _simd;
				lu8v_ProtocolRxBufoffset++;
				if (lu8v_ProtocolRxBufoffset >= 4)
				{
					lu8v_ProtocolRxBufoffset = 0;
					gbv_IICRxSuccess = 1;
				}
			}
		}
		#endif
	}
}