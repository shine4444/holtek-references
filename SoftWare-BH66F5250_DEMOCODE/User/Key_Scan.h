//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2018 BY HOLTEK SEMICONDUCTOR INC
//  File Name : key_scan
// Description: 
//Targer Board: 
//   MCU      : BH67F5270
//   Author   : ming
//   Date     : 2018/03/26
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________


#ifndef _Key_Scan_H_
#define	_Key_Scan_H_


/********************************************************************
Function:	function
********************************************************************/	
void	fun_Key_Scan(void);
void	fun_Key_dealwith(void);
void	fun_Key_init();
void	fun_iir_filter1(u16 lu16_current_adc_data);
/********************************************************************
Function:	KEY
********************************************************************/
//按鍵消抖時間設置 1 代表 10ms
#define		LUCC_KEY_DEBOUNCE	5		
#define		LUCC_LONG_KEY_TIME	200	

/********************************************************************
Function:	GPIO
********************************************************************/
#define		GPIO_KEY_START_WU		
#define		GPIO_KEY_START_PU		_pbpu3
#define		GPIO_KEY_START_IO		_pbc3
#define		GPIO_KEY_START			_pb3


#define		GPIO_KEY_SET_WU			_pawu7
#define		GPIO_KEY_SET_PU			_papu7
#define		GPIO_KEY_SET_IO			_pac7
#define		GPIO_KEY_SET			_pa7

//
//#define		GPIO_KEY_MEMORY_WU		_pawu1
//#define		GPIO_KEY_MEMORY_PU		_papu1
//#define		GPIO_KEY_MEMORY_IO		_pac1
//#define		GPIO_KEY_MEMORY			_pa1




/********************************************************************
Function:	volatile
********************************************************************/				

/************************Key_Scan Variable****************/					
extern	volatile			__byte_type 		gu8v_KeyCurrent;
#define KeyCurrent0 		gu8v_KeyCurrent.bits.b0
#define KeyCurrent1 		gu8v_KeyCurrent.bits.b1
#define KeyCurrent2 		gu8v_KeyCurrent.bits.b2
#define KeyCurrent3 		gu8v_KeyCurrent.bits.b3
#define KeyCurrent4 		gu8v_KeyCurrent.bits.b4
#define KeyCurrent5 		gu8v_KeyCurrent.bits.b5
#define KeyCurrent6 		gu8v_KeyCurrent.bits.b6
#define KeyCurrent7 		gu8v_KeyCurrent.bits.b7


extern	volatile			__byte_type			gu8v_KeyDown;
#define gbv_start_down	 	gu8v_KeyDown.bits.b0
#define gbv_memory_down		gu8v_KeyDown.bits.b1
#define gbv_set_down 		gu8v_KeyDown.bits.b2
//#define gbv_model_down 		gu8v_KeyDown.bits.b3
//#define KeyDown4			gu8v_KeyDown.bits.b4
//#define KeyDown5 			gu8v_KeyDown.bits.b5
//#define KeyDown6 			gu8v_KeyDown.bits.b6
//#define KeyDown7 			gu8v_KeyDown.bits.b7

extern	volatile			__byte_type 	gu8v_Key_status;
#define gbv_start_click			gu8v_Key_status.bits.b0
#define gbv_start_long_Press 	gu8v_Key_status.bits.b1
#define gbv_memory_click		gu8v_Key_status.bits.b2
#define gbv_memory_long_Press	gu8v_Key_status.bits.b3
#define gbv_set_click 			gu8v_Key_status.bits.b4
#define gbv_set_long_Press		gu8v_Key_status.bits.b5
//#define gbv_model_click		gu8v_Key_status.bits.b6
//#define gbv_model_long_Press 	gu8v_Key_status.bits.b7


extern	volatile			u8	gu8v_KeyOld;
extern	volatile			u8	gu8v_KeyNoChangedTime;
//extern	volatile			U8	gu8v_KeyPress;
extern	volatile	__byte_type  gu8v_KeyPress;
#define gbv_start_press		gu8v_KeyPress.bits.b0
#define gbv_memory_press		gu8v_KeyPress.bits.b1
#define gbv_set_press			gu8v_KeyPress.bits.b2

//#define gbv_recall_press	gu8v_KeyPress.bits.b2
//#define gbv_model_press		gu8v_KeyPress.bits.b3
//#define gu8v_KeyPress4		gu8v_KeyPress.bits.b4
//#define gu8v_KeyPress5	 	gu8v_KeyPress.bits.b5
//#define gu8v_KeyPress6		gu8v_KeyPress.bits.b6
//#define gu8v_KeyPress7 		gu8v_KeyPress.bits.b7




//extern	volatile			U8	gu8v_KeyUp;
extern	volatile	__byte_type	gu8v_KeyUp;
#define gbv_start_up	 	gu8v_KeyUp.bits.b0
#define gbv_memory_up			gu8v_KeyUp.bits.b1
#define gbv_set_up			gu8v_KeyUp.bits.b2

//#define gbv_recall_up 		gu8v_KeyUp.bits.b2
//#define gbv_model_up 		gu8v_KeyUp.bits.b3
//#define gu8v_KeyUp4			gu8v_KeyUp.bits.b4
//#define gu8v_KeyUp5	 		gu8v_KeyUp.bits.b5
//#define gu8v_KeyUp6			gu8v_KeyUp.bits.b6
//#define gu8v_KeyUp7			gu8v_KeyUp.bits.b7


extern	volatile			u8	gu8v_KeyLast;
extern 	volatile			u8 	gu8v_KeyCanChange;	
extern	volatile			u8 	gu8v_Keypress_time;

#endif
