#ifndef _SDK_HARDWARE_H_
#define _SDK_HARDWARE_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                LDO   基本設置                                        @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_LDO_EN2_4()	  	        { _pwrc = 0x80; }
#define SET_LDO_EN2_6()		        { _pwrc = 0x81; }
#define SET_LDO_EN2_9()		        { _pwrc = 0x82; }
#define SET_LDO_EN3_3()		        { _pwrc = 0x83; }
#define SET_LDO_ENBYPASS()	        { _pwrc = 0x84; }
#define SET_LDO_DISABLE()	        { _ldoen = 0; }
#define SET_LDO_ENABLE()	        { _ldoen = 1; }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              24Bit ADC 基本設置                                      @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_ADCINTERRUPT_ENABLE()	{ _adf = 0; _ade = 1; _emi = 1;}
#define SET_ADCINTERRUPT_DISABLE()	{ _ade = 0;}
#define SET_ADCPOWER_ON()			{ _adoff = 0; }
#define SET_ADCPOWER_OFF()			{ _adoff = 1; }
#define SET_ADCMODE_SLEEP()			{ _adslp = 1; }
#define SET_ADCMODE_NORMAL()		{ _adslp = 0; }
#define SET_ADCVREF_VREFPVREFN()	{ _vrefs = 1; }
#define SET_ADCVREF_VCMAVSS()		{ _vrefs = 0; }
#define SET_ADCBUF_ENABLE()		    { _vrbufp = 1; _vrbufp = 1;}
#define SET_ADCBUF_DISABLE()		{ _vrbufp = 0; _vrbufp = 0;}
#define SET_ADC_STARTCONVERT()		{ _adrst = 0; _adrst = 1; _adrst = 0; _adcdl = 0; _eoc = 0; }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ADC CLK 預處理 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ADC DATA RARE 計算方式如下:
// FMCLK = Fsys = 4000000,CHOP = 2, N = 12,OSR = 16384
// FADCK = FMCLK/(CHOP/N) =166667=167K
// DataRate = FADCK/OSR = 10.2HZ
#define CHOP2_FLMS30()              { _flms2=0; _flms1=0; _flms0=0;}
#define CHOP2_FLMS12()              { _flms2=0; _flms1=1; _flms0=0;}
#define CHOP1_FLMS30()              { _flms2=1; _flms1=0; _flms0=0;}
#define CHOP1_FLMS12()              { _flms2=1; _flms1=1; _flms0=0;}
#define OSR_16384()                 { _ador2=0; _ador1=0; _ador0=0;}
#define OSR_8192()                  { _ador2=0; _ador1=0; _ador0=1;}
#define OSR_4096()                  { _ador2=0; _ador1=1; _ador0=0;}
#define OSR_2048()                  { _ador2=0; _ador1=1; _ador0=1;}
#define OSR_1024()                  { _ador2=1; _ador1=0; _ador0=0;}
#define OSR_512()                   { _ador2=1; _ador1=0; _ador0=1;}
#define OSR_256()                   { _ador2=1; _ador1=1; _ador0=0;}
#define OSR_128()                   { _ador2=1; _ador1=1; _ador0=1;}

#ifdef SYS_HIGH_FREQUENCY_OSC_4MHZ
#define SET_ADC_DATARATE_5HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_16384();}
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_16384();}
#define SET_ADC_DATARATE_20HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_8192(); }
#define SET_ADC_DATARATE_40HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_4096(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x1F; CHOP2_FLMS30(); OSR_1024(); }
#define SET_ADC_DATARATE_80HZ()		{ _adcs=0x1F; CHOP2_FLMS12(); OSR_2048(); }
#define SET_ADC_DATARATE_160HZ()	{ _adcs=0x1F; CHOP2_FLMS12(); OSR_1024(); }
#define SET_ADC_DATARATE_320HZ()	{ _adcs=0x1F; CHOP2_FLMS12(); OSR_512();  }
#define SET_ADC_DATARATE_1300HZ()	{ _adcs=0x1F; CHOP2_FLMS12(); OSR_128();  }
#define SET_ADC_DATARATE_2600HZ()	{ _adcs=0x1F; CHOP1_FLMS12(); OSR_128();  }
#endif
#ifdef SYS_HIGH_FREQUENCY_OSC_8MHZ
#define SET_ADC_DATARATE_5HZ()		{ _adcs=0x01; CHOP2_FLMS12(); OSR_16384();}
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_16384() }
#define SET_ADC_DATARATE_20HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_8192(); }
#define SET_ADC_DATARATE_40HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_4096(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x00; CHOP2_FLMS30(); OSR_1024(); }
#define SET_ADC_DATARATE_80HZ()		{ _adcs=0x00; CHOP2_FLMS12(); OSR_2048(); }
#define SET_ADC_DATARATE_160HZ()	{ _adcs=0x00; CHOP2_FLMS12(); OSR_1024(); }
#define SET_ADC_DATARATE_320HZ()	{ _adcs=0x00; CHOP2_FLMS12(); OSR_512();  }
#define SET_ADC_DATARATE_1300HZ()	{ _adcs=0x00; CHOP2_FLMS12(); OSR_128();  }
#define SET_ADC_DATARATE_3200HZ()	{ _adcs=0x00; CHOP1_FLMS12(); OSR_128();  }
#endif
#ifdef SYS_HIGH_FREQUENCY_OSC_12MHZ
#define SET_ADC_DATARATE_5HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_16384();}
#define SET_ADC_DATARATE_10HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_8192(); }
#define SET_ADC_DATARATE_20HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_4096(); }
#define SET_ADC_DATARATE_40HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_2048(); }
#define SET_ADC_DATARATE_64HZ()		{ _adcs=0x02; CHOP2_FLMS30(); OSR_512();  }
#define SET_ADC_DATARATE_80HZ()		{ _adcs=0x02; CHOP2_FLMS12(); OSR_1024(); }
#define SET_ADC_DATARATE_160HZ()	{ _adcs=0x02; CHOP2_FLMS12(); OSR_512();  }
#define SET_ADC_DATARATE_320HZ()	{ _adcs=0x02; CHOP2_FLMS12(); OSR_256();  }
#define SET_ADC_DATARATE_1300HZ()	{ _adcs=0x1F; CHOP2_FLMS30(); OSR_128();  }
#define SET_ADC_DATARATE_3200HZ()	{ _adcs=0x1F; CHOP1_FLMS30(); OSR_128();  }
#endif
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              DACO  基本設置                                       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_DAC_ENABLE()		        { _dsdacen = 1; }
#define SET_DAC_DISABLE()		        { _dsdacen = 0; }
#define SET_DACVREF_VOREG()	            { _dsdacvrs1 = 0; _dsdacvrs0 = 0;}
#define SET_DACVREF_VDD()	            { _dsdacvrs1 = 0; _dsdacvrs0 = 1;}
#define SET_DACVREF_VCM()	            { _dsdacvrs1 = 1; _dsdacvrs0 = 0;}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                                稱重  硬件配置                                        @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_ADCGAIN_WEIGHT()        { _pgac0 = 0x36;}   // 稱重ADC放大設置,VGS=0.5,ADGN =4,PGA=64
#define SET_DCSET_WEIGHT()          { _pgac1 = 0x3E;}   // 交換輸入輸出 稱重DCSET設置,DCSET = -0.75*VR
#define SET_ADCCHAN_WEIGHT()        { _pgacs = 0x10;}   // 稱重ADC 通道AN0&AN1




#endif