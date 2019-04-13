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
//                              ���ļ������޸�!!!                                      @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifndef _SCALES_SDK_INTERFACE_H_
#define _SCALES_SDK_INTERFACE_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ �ӿ�׃�� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// RW ���x�Ɍ�, Rֻ���x,���܌�!!!
extern volatile bit gbv_IsNeedTare;                         // RW   1 ����ȡ���c,��ǰ�����鷀�������r��ǰ������0
extern volatile unsigned char gu8v_ScalesSDKState; 		    // RW   ������B�xȡ�c�ГQ
extern volatile unsigned int gu16v_CurrentWeight_g;	        // R    ��ǰ����ֵ,��λ��g
extern volatile unsigned long filterADCDataCurrent;         // R    ����ADC�V���󔵓�
extern volatile bit gbv_WeightisN;			                // R    1 ������ֵؓ 0 ��������ֵ
extern volatile unsigned char SourceADCHigh, SourceADCMid , SourceADCLow;  // R ԭʼADC����
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ �ӿں��� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_ScalesSDK();            // ������,������ѭ�h�{��
void fun_ScalesSDK_PowerOn();    // ��늳�ʼ��,MCU��늺��{��һ��
void fun_ScalesSDK_PowerDown();  // ���߳�ʼ��,MCU����ǰ�{��һ��

unsigned char Read_EEPROMByte(unsigned char addr);                  // �xһ��Byte����
void Write_EEPROMByte(unsigned char addr, unsigned char WriteData); // ��һ��Byte����
unsigned long fun_unsigned32BitABS(unsigned long a, unsigned long b);// ȡ32λ�o��̖��ֵ
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// gu8v_ScalesSDKState ��x
enum BodyfatSDKState{
    // �P�]SDK
    ENTER_SDK_NONE,           // 0 �M���ѭ�h,ADC �� LDO Power Off
    STATE_SDK_NONE,           // 1 SDK̎춿�ѭ�h
    // ��ͨ�Q��
    ENTER_WEIGHT_NORMAL,      // 2 �M�������Q��ģʽ
    STATE_WEIGHT_PREPARE,     // 3 �Q�؜ʂ���
    STATE_WEIGHT_WEIGHTING,   // 4 �������y��,�˕r�����xȡgu16v_CurrentWeight_g
    // ����У�ʘ˶�
    ENTER_WEIGHT_CAL,         // 5 �M������У��ģʽ
    STATE_WEIGHT_CAL0,        // 6 ���ژ˶����c
    STATE_WEIGHT_CAL1,        // 7 ���ژ˶���1�c
    STATE_WEIGHT_CAL2,        // 8 ���ژ˶���2�c
    STATE_WEIGHT_CALPASS,     // 9 �˶��ɹ�
    STATE_WEIGHT_CALFAIL,     // 10 �˶�ʧ��
    // �ض����y,��SDK���ְ��� Temp��Ч
    ENTER_TEMP,               // 11 �M���¶Ȝy��
    STATE_TEMP_CAL,           // 12 �¶�У��
};

typedef struct
{
	unsigned long MinADC;	    // ��С����������ADCֵ
	unsigned long MidADC;	    // ���g����������ADCֵ
	unsigned long MaxADC;	    // �������������ADCֵ
	unsigned int  MidWeightG;	// ����У��ֵ,���g�c
	unsigned int  MaxWeightG;	// ����У��ֵ,����c
	unsigned char WeightSpan;	// 1���ֱ��ʌ�����ADCֵ
}WeightCalData_t;

#endif
