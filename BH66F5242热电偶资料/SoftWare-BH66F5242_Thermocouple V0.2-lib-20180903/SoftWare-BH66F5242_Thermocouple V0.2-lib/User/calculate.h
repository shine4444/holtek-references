
#ifndef _CALCULATE_H_
#define _CALCULATE_H_

#define mac_CorrTemp_Low    100
#define mac_CorrTemp_High   600



//ntc
#define		LU16C_K1_RANGE		10000
//VTP
#define		LU16C_K2_RANGE		10000

//ntc
#define		LU16C_K1_RANGE_Default		6600
//VTP
#define		LU16C_K2_RANGE_Default		10000




void	fun_RNTC_Calculate(void);	
u16		fun_Vsen_Calculate(u16	lu8v_res);

u8 		fun_get_NTC();
u8 		fun_get_VTP();
void	fun_Tobj_Calculate(void);
void	fun_get_Vobj_25(s32 lu16v_vobj_25);
void	fun_CORRECTION_Calculate();


#define	LU16C_NTC_RES	(10000)

#define	LU16C_37_C_RES		3274  
#define	LU16C_NTC_RES_MAX	(LU16C_37_C_RES*1.1)
#define	LU16C_NTC_RES_MIN	(LU16C_37_C_RES*0.9)

extern	volatile	__16_type gu16v_correction_K1;
extern	volatile	__16_type gu16v_correction_K2;


extern	__16_type gu16v_ntc_adc;
extern	__16_type gu16v_std_res_adc;
extern  __16_type gu16v_ntc_res;



extern	__32_type	gu32v_adc_data;	
extern	__32_type	gu16v_adc_vtp[4];	
extern	__32_type	gu16v_adc_vtpL[4];	
extern	__16_type	gu16v_tp_temp[4];
extern	__16_type	gu16v_adc_res;
extern	__16_type	gu16v_adc_res1;
extern	__16_type	gu16v_adc_res2;
extern	__16_type	gu16v_temp;
extern	__32_type	gu16v_vtp;
extern	__32_type	gu16v_vtp_buff1;
extern	__16_type	gu16v_current_temp;
extern	__16_type	gu16v_body_temp;
extern	__16_type	gu16v_adc_max;
extern	__32_type	gu16v_vtp_buff2;
extern	__16_type	gu16v_adc_min;
extern	__32_type	gu32v_adc_sum;
extern	__16_type	gu16v_temp_temp;	
extern	__32_type	gu16v_adc_VtpZero;

extern	__16_type	gu16v_cal_templ;	
extern	__16_type	gu16v_cal_temph;

extern	u8	gu8v_NTCMode;
extern	u8	gu8v_obj_temp_mode;
#endif

