/********************************* Tips *****************************
********************************************************************/
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ �������� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_UIProtocol();
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Userdefine @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define PROTOCOL_TX_LENGTH 5 // �f�h�������L��
#define PROTOCOL_RX_LENGTH 4 // �f�h�������L��

extern volatile unsigned char gu8v_ProtocolTxBuf[PROTOCOL_TX_LENGTH];
extern volatile unsigned char gu8v_ProtocolRxBuf[PROTOCOL_RX_LENGTH];
extern volatile unsigned char lu8v_ProtocolTxBufoffset;
extern volatile unsigned char lu8v_ProtocolRxBufoffset;
extern volatile unsigned char gu8v_CalStatusNeedSend;
extern volatile bit gbv_IICRxSuccess;	// ADC��һ���i��ֵ���棨��춌���ǰ��ADֵ�Ƿ��춣�
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
#define CM_WEIGHT2_CAL  			0xC2    // ���c�˶�
#define CM_WEIGHT3_CAL  			0xC3    // ���c�˶�
#define CM_READ_CAL_STATUS  		0xCB

#define CM_FW_VERSION				0xAB
#define CM_WRITE_TO_HALT			0xC0

#define P_ADC                       0xD0    // ��ADC
#define N_ADC                       0xD1    // ؓADC
#define P_WEIGHT                    0xE0    // ������
#define N_WEIGHT                    0xE1    // ؓ����
#define P_TEMP                      0xF0    // ���ض�
#define N_TEMP                      0xF1    // ؓ�ض�

#define CALING_STATUS_0             0x01    // ���ژ˶�0�c
#define CALING_STATUS_1             0x02    // ���ژ˶�1�c
#define CALING_STATUS_2             0x05    // ���ژ˶�2�c
#define CALING_STATUS_PASS          0x06    // �˶��ɹ�
#define CALING_STATUS_FAIL          0x07    // �˶�ʧ��


#define TEMP_CALING 5
#define TEMP_CALEND 6

#endif
