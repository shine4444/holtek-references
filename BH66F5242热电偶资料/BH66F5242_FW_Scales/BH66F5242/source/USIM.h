//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : UART.c
// Description: UART收發
//   Customer : Holtek Demo Code
//Targer Board: None
//     Note   :
//___________________________________________________________________
//___________________________________________________________________
#ifndef _USIM_H_
#define _USIM_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用變量 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern volatile unsigned char  lu8v_ProtocolTxBufoffset;
extern volatile unsigned char  lu8v_RxBufoffset;

extern volatile unsigned char  gu8v_TBRxTimeOutCnt;
extern volatile unsigned char  gu8v_TBTxCycle;
extern volatile bit gbv_UartTxBusy;
extern volatile bit gbv_UartRxSuccess;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_USIM_PowerOn();
void fun_UART_Manger();
void fun_UART_SendSourceADCData();
void fun_UART_send_Impedance();
void fun_UART_SendSourceADCData();
// 只能SPI/IIC/UART三選一
// #define USIM_MODE_SPI
#define USIM_MODE_IIC
#define USIM_MODE_UART
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                MCU 及CFG   修改                                      @
//                                 VFG 1.0                                             @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define USIM_VECTOR  0x018
#define _simc0  _sim0c0
#define _uucr1  _u0ucr1
#define _ubrgh  _u0brgh
#define _ubrg   _u0brg
#define _uadden _u0adden
#define _urie   _u0rie
#define _utiie  _u0tiie
#define _simen  _sim0en
#define _urxen  _u0rxen
#define _utxen  _u0txen
#define _utxif  _u0txif
#define _urxif  _u0rxif
#define _unf    _u0nf
#define _uteie  _u0teie
#define _utidle  _u0tidle
#define _utxr_rxr  _u0txr_rxr
#define _htx    _htx0
#define _srw    _srw0
#define _iamwu  _iamwu0
#define _haas   _haas0
#define _simd   _sim0d
#define _simtoen _sim0toen
#define _uren   _ur0en
#define _uferr  _u0ferr
#define _uoerr  _u0oerr
#define _uusr   _u0usr
#define _rxak   _rxak0
#define _txak   _txak0
#define _simtof _sim0tof
#define _sima   _sim0a
#define _simtoc _sim0toc
#define _uwake  _u0wake
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                SPI  基本設置                                         @
//                            只能SPI/IIC/UART三選一                                    @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_SPI_MASTER()            { _simc0 = 0x00;}
#define SET_SPI_SLAVE()             { _simc0 = 0xA0;}
#define SET_SPI_DISABLE()           { _simen = 0;}
#define SET_SPI_ENABLE()            { _simen = 1;}
#define SET_SPI_ISR_DISABLE()       { _usime = 0;}
#define SET_SPI_ISR_ENABLE()        { _usime = 1; _usimf = 0;}
// PA2=SCS  PA4=SDI  PA5=SDO  PA6=SCK
#define SET_SPI_PIN()               { _pas1 &= 0xc0;_pas1 |= 0x16; _pas04 = 0; _pas05 = 1;}

#define SET_SPI_SCK_HIGH_RISING()   { _ckpolb = 0; _ckeg = 0;}
#define SET_SPI_SCK_HIGH_FALLING()  { _ckpolb = 0; _ckeg = 1;}
#define SET_SPI_SCK_LOW_RISING()    { _ckpolb = 1; _ckeg = 0;}
#define SET_SPI_SCK_LOW_FALLING()   { _ckpolb = 1; _ckeg = 1;}

#define SET_SPI_DATA_LSB()          { _mls = 0;}
#define SET_SPI_DATA_MSB()          { _mls = 1;}
#define SET_SPI_CSEN_DISABLE()      { _csen = 0;}
#define SET_SPI_CSEN_ENABLE()       { _csen = 1;}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                IIC  基本設置                                         @
//                            只能SPI/IIC/UART三選一                                    @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_IIC_ADDRESS(x)          { _sima = x;}
#define SET_IIC_ENABLE()            { _simen = 1;}
#define SET_IIC_DISABLE()           { _simen = 0;}
#define SET_IIC_ISR_DISABLE()       { _usime = 0;}
#define SET_IIC_ISR_ENABLE()        { _usime = 1; _usimf = 0;}
// PA4=SDA PA5=IO PA6=SCL
#define SET_IIC_PIN()               { _pas1 &= 0xC0;_pas1 |= 0x12; }
#ifdef _HIRC_4M_
    #define SET_IIC_SLAVE_SLOW()     { _simc0 = 0xC0;}
#endif
#ifdef _HIRC_8M_
    #define SET_IIC_SLAVE_FAST()     { _simc0 = 0xC0;}
    #define SET_IIC_SLAVE_SLOW()     { _simc0 = 0xC4;}
#endif
#ifdef _HIRC_12M_
    #define SET_IIC_SLAVE_FAST()     { _simc0 = 0xC4;}
    #define SET_IIC_SLAVE_SLOW()     { _simc0 = 0xC8;}
#endif

#define SET_IIC_WAKEUP_DISABLE()     { _iamwu = 0;}
#define SET_IIC_WAKEUP_ENABLE()      { _iamwu = 1;}
#define SET_IIC_TIMEOUT_DISABLE()    { _simtoc = 0;}
#define SET_IIC_TIMEOUT_ENABLE()     { _simtoc = 1;}
#define SET_IIC_TIMEOUT_X_MS(x)       { _simtoc = x-1;}  // x = 1~64
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                UART  基本設置                                        @
//                            只能SPI/IIC/UART三選一                                    @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_UART_MODE()             { _simc0 = 0x10;}
// PA4=RXD PA5=TXD PA6=IO
#define SET_UART_PIN()              { _pas1 &= 0xC0;_pas1 |= 0x06;}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 預定義@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_UART_ISR_DISABLE()      { _usime = 0;}
#define SET_UART_ISR_ENABLE()       { _usime = 1; _usimf = 0;}

#define SET_UART_ENABLE()	        { _simen =1; _uren = 1;_urxen = 1;_utxen = 1;_utxif = 0; _emi = 1;}
#define SET_UART_DISABLE()	        { _simen =0; _uren = 0;_urxen = 0;_utxen = 0;}

#define SET_UART_Format_D8_P0_S1()			    { _uucr1 = 0x00; }// 傳輸8bit = (8bit-Data  None-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D7_PEVEN_S1()		    { _uucr1 = 0x20; }// 傳輸8bit = (7bit-Data  Enen-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D7_PODD_S1()		    { _uucr1 = 0x30; }// 傳輸8bit = (7bit-Data  Odd -Parity  None-Add)1bit-Stop
#define SET_UART_Format_D9_P0_S1()			    { _uucr1 = 0x40; }// 傳輸9bit = (9bit-Data  None-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D8_PEVEN_S1()		    { _uucr1 = 0x60; }// 傳輸9bit = (8bit-Data  Even-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D8_PODD_S1()		    { _uucr1 = 0x70; }// 傳輸9bit = (8bit-Data  Odd-Parity   None-Add)1bit-Stop

#define SET_UART_Format_D8_P0_S2()			    { _uucr1 = 0x00; }// 傳輸8bit = (8bit-Data  None-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D7_PEVEN_S2()		    { _uucr1 = 0x20; }// 傳輸8bit = (7bit-Data  Enen-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D7_PODD_S2()		    { _uucr1 = 0x30; }// 傳輸8bit = (7bit-Data  Odd -Parity  None-Add)2bit-Stop
#define SET_UART_Format_D9_P0_S2()			    { _uucr1 = 0x40; }// 傳輸9bit = (9bit-Data  None-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D8_PEVEN_S2()		    { _uucr1 = 0x60; }// 傳輸9bit = (8bit-Data  Even-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D8_PODD_S2()		    { _uucr1 = 0x70; }// 傳輸9bit = (8bit-Data  Odd-Parity   None-Add)2bit-Stop

#define SET_UART_WAKEUP_ENABLE()			    { _uwake  = 1;}
#define SET_UART_WAKEUP_DISABLE()				{ _uwake  = 0;}
#define SET_UART_ADDRESS_ENABLE()				{ _uadden = 1;}
#define SET_UART_ADDRESS_DISABLE()				{ _uadden = 0;}
#define SET_UART_RECEIVER_IE_ENABLE()			{ _urie   = 1;} // OERR(溢出)/RXIF(有有效數據)置位時可置中斷標誌位
#define SET_UART_RECEIVER_IE_DISABLE()			{ _urie   = 0;}
#define SET_UART_TRANSMITTER_IE_ENABLE()		{ _utiie = 1;} // TIDLE(無數據傳輸)置位，可置中斷標誌位
#define SET_UART_TRANSMITTER_IE_DISABLE()		{ _utiie = 0;}
#define SET_UART_TRANSMITTER_EMPTY_ENABLE()		{ _uteie = 1;} // TXIF(數據已加載到移位暫存器，TXR為空)置位時，可置中斷標誌位
#define SET_UART_TRANSMITTER_EMPTY_DISABLE()	{ _uteie = 0;}

#ifdef _HIRC_4M_
    #define SET_UART_BAUTRATE_300()			    { _ubrgh = 0; _ubrg = 207;}
    #define SET_UART_BAUTRATE_1200()			{ _ubrgh = 1; _ubrg = 207;}
    #define SET_UART_BAUTRATE_2400()			{ _ubrgh = 1; _ubrg = 103;}
    #define SET_UART_BAUTRATE_4800()			{ _ubrgh = 1; _ubrg =  51;}
    #define SET_UART_BAUTRATE_9600()			{ _ubrgh = 1; _ubrg =  25;}
    #define SET_UART_BAUTRATE_19200()		    { _ubrgh = 1; _ubrg =  12;}
    #define SET_UART_BAUTRATE_250000()		    { _ubrgh = 1; _ubrg =   0;}
#endif
#ifdef _HIRC_8M_
    #define SET_UART_BAUTRATE_1200()			{ _ubrgh = 0; _ubrg = 103;}
    #define SET_UART_BAUTRATE_2400()			{ _ubrgh = 1; _ubrg = 207;}
    #define SET_UART_BAUTRATE_4800()			{ _ubrgh = 1; _ubrg = 103;}
    #define SET_UART_BAUTRATE_9600()			{ _ubrgh = 1; _ubrg =  51;}
    #define SET_UART_BAUTRATE_19200()		    { _ubrgh = 1; _ubrg =  25;}
    #define SET_UART_BAUTRATE_38400()		    { _ubrgh = 1; _ubrg =  12;}
    #define SET_UART_BAUTRATE_250000()		    { _ubrgh = 1; _ubrg =   1;}
#endif
#ifdef _HIRC_12M_
    #define SET_UART_BAUTRATE_1200()			{ _ubrgh = 0; _ubrg = 155;}
    #define SET_UART_BAUTRATE_2400()			{ _ubrgh = 0; _ubrg =  77;}
    #define SET_UART_BAUTRATE_4800()			{ _ubrgh = 1; _ubrg = 155;}
    #define SET_UART_BAUTRATE_9600()			{ _ubrgh = 1; _ubrg =  77;}
    #define SET_UART_BAUTRATE_19200()		    { _ubrgh = 1; _ubrg =  38;}
    #define SET_UART_BAUTRATE_57600()		    { _ubrgh = 1; _ubrg =  12;}
    #define SET_UART_BAUTRATE_250000()		    { _ubrgh = 1; _ubrg =   2;}
#endif

#endif
