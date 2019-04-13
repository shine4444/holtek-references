//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2018 BY HOLTEK SEMICONDUCTOR INC
//  File Name : ADC
// Description: 
//Targer Board: 
//   MCU      : BH67F5270
//   Author   : ming
//   Date     : 2018/03/26
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#ifndef _ADC_H_
#define _ADC_H_

extern	volatile	u8 	gu8v_Sample_Count ;	
extern	volatile	s16	gs16v_adc_buff[10];

extern	volatile	u8  gbv_adc_Sample_Mode;
extern	volatile	__byte_type  gbv_adc_flag;
#define	gbv_adc_Sample_lock	gbv_adc_flag.bits.b0
#define	gbv_adc_success		gbv_adc_flag.bits.b1
//
volatile	static	__32_type	gu32v_adc_data		__attribute__ ((at(0x280)));	
	



void 	fun_ADC_Polling();
void 	fun_ADC_Enable();
void 	fun_ADC_Disable();
void 	fun_ADC_Power_Enable();
void 	fun_ADC_Power_Disable();
void fun_ADC_INIT();



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
//                              定電流 OPA 基本設置                                     @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//static volatile u8 _dsopc __attribute__ ((at(0x072)));  
//1.1CFG  没有此寄存器，后续有后可以将上面定义拿掉
#define SET_DSOP_CURRENT()          { _dsopc = 0x05; }
#define SET_DSOP_VCM()              { _dsopc = 0x0A; }
#define SET_DSOP_DACBUFF()          { _dsopc = 0x09; }

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
#define SET_ADCBUF_DISABLE()		{ _vrbufp = 1; _vrbufp = 1;}
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
#define SET_DACVREF_VOREG()	            {_dsdacvrs = 0;}
#define SET_DACVREF_VDD()	            {_dsdacvrs = 1;}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              DACO  基本設置                                       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_ADC_PGA_1()		        { _pgs2 = 0; _pgs1 = 0; _pgs0 = 0; }
#define SET_ADC_PGA_2()		        { _pgs2 = 0; _pgs1 = 0; _pgs0 = 1; }
#define SET_ADC_PGA_4()		        { _pgs2 = 0; _pgs1 = 1; _pgs0 = 0; }
#define SET_ADC_PGA_8()		        { _pgs2 = 0; _pgs1 = 1; _pgs0 = 1; }
#define SET_ADC_PGA_16()		    { _pgs2 = 1; _pgs1 = 0; _pgs0 = 0; }
#define SET_ADC_PGA_32()		    { _pgs2 = 1; _pgs1 = 0; _pgs0 = 1; }
#define SET_ADC_PGA_64()		    { _pgs2 = 1; _pgs1 = 1; _pgs0 = 0; }
#define SET_ADC_PGA_128()		    { _pgs2 = 1; _pgs1 = 1; _pgs0 = 1; }


#define SET_ADC_VGA_1_1()		    { _vgs1 = 0; _vgs0 = 0; }
#define SET_ADC_VGA_1_2()		    { _vgs1 = 0; _vgs0 = 1; }
#define SET_ADC_VGA_1_4()		    { _vgs1 = 1; _vgs0 = 0; }
#define SET_ADC_AGA_1()		    	{ _ags1 = 0; _ags0 = 0; }
#define SET_ADC_AGA_2()		   	 	{ _ags1 = 0; _ags0 = 1; }
#define SET_ADC_AGA_4()		    	{ _ags1 = 1; _ags0 = 0; }


#define SET_ADC_INX_00()		    { _inx1 = 0; _inx0 = 0; }
#define SET_ADC_INX_01()		    { _inx1 = 0; _inx0 = 1; }
#define SET_ADC_INX_10()		    { _inx1 = 1; _inx0 = 0; }
#define SET_ADC_INX_11()		    { _inx1 = 1; _inx0 = 1; }


	#define SET_ADC_CHSN_AN0()		    { _chsn3 = 0;_chsn2 = 0;_chsn1 = 0;_chsn0 = 0;}	
	#define SET_ADC_CHSN_AN1()		    { _chsn3 = 0;_chsn2 = 0;_chsn1 = 0;_chsn0 = 1;}	
	#define SET_ADC_CHSN_AN3()		    { _chsn3 = 0;_chsn2 = 0;_chsn1 = 1;_chsn0 = 0;}	
	#define SET_ADC_CHSN_AN5()		    { _chsn3 = 0;_chsn2 = 0;_chsn1 = 1;_chsn0 = 1;}	
	#define SET_ADC_CHSN_AN7()		    { _chsn3 = 0;_chsn2 = 1;_chsn1 = 0;_chsn0 = 0;}	
	#define SET_ADC_CHSN_AN9()		    { _chsn3 = 0;_chsn2 = 1;_chsn1 = 0;_chsn0 = 1;}		
	#define SET_ADC_CHSN_AN11()		    { _chsn3 = 0;_chsn2 = 1;_chsn1 = 1;_chsn0 = 0;}		
	#define SET_ADC_CHSN_AN13()		    { _chsn3 = 0;_chsn2 = 1;_chsn1 = 1;_chsn0 = 1;}		
	#define SET_ADC_CHSN_AN15()		    { _chsn3 = 1;_chsn2 = 0;_chsn1 = 0;_chsn0 = 0;}	
	#define SET_ADC_CHSN_OPIP()		    { _chsn3 = 1;_chsn2 = 0;_chsn1 = 0;_chsn0 = 1;}	
	#define SET_ADC_CHSN_AVSS()		    { _chsn3 = 1;_chsn2 = 0;_chsn1 = 1;_chsn0 = 0;}	
	#define SET_ADC_CHSN_VCM()		    { _chsn3 = 1;_chsn2 = 0;_chsn1 = 1;_chsn0 = 1;}		
	#define SET_ADC_CHSN_VTSON()	    { _chsn3 = 1;_chsn2 = 1;_chsn1 = 0;_chsn0 = 0;}		
		
	#define SET_ADC_CHSP_AN0()		    { _chsp3 = 0;_chsp2 = 0;_chsp1 = 0;_chsp0 = 0;}	
	#define SET_ADC_CHSP_AN2()		    { _chsp3 = 0;_chsp2 = 0;_chsp1 = 0;_chsn0 = 1;}	
	#define SET_ADC_CHSP_AN4()		    { _chsp3 = 0;_chsp2 = 0;_chsp1 = 1;_chsp0 = 0;}	
	#define SET_ADC_CHSP_AN6()		    { _chsp3 = 0;_chsp2 = 0;_chsp1 = 1;_chsp0 = 1;}	
	#define SET_ADC_CHSP_AN8()		    { _chsp3 = 0;_chsp2 = 1;_chsp1 = 0;_chsn0 = 0;}	
	#define SET_ADC_CHSP_AN10()		    { _chsp3 = 0;_chsp2 = 1;_chsp1 = 0;_chsp0 = 1;}		
	#define SET_ADC_CHSP_AN12()		    { _chsp3 = 0;_chsp2 = 1;_chsp1 = 1;_chsp0 = 0;}		
	#define SET_ADC_CHSP_AN14()		    { _chsp3 = 0;_chsp2 = 1;_chsp1 = 1;_chsp0 = 1;}
			
	#define SET_ADC_CHSP_OPIP()		    { _chsp3 = 1;_chsp2 = 0;_chsp1 = 0;_chsp0 = 1;}	
	#define SET_ADC_CHSP_VSS()		    { _chsp3 = 1;_chsp2 = 0;_chsp1 = 1;_chsp0 = 0;}	
	#define SET_ADC_CHSP_VCM()		    { _chsp3 = 1;_chsp2 = 0;_chsp1 = 1;_chsp0 = 1;}		
	#define SET_ADC_CHSP_VTSOP()	    { _chsp3 = 1;_chsp2 = 1;_chsp1 = 0;_chsp0 = 0;}		







#endif

