; Generated by holtek-gcc v3.19, Wed Apr 10 15:18:42 2019
; 
; Configuration:
;       with long instruction
;       Single ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 32
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.19" "build 20130711"
; Rebuild 115

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [32]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
___ctmc0 equ [80]
___ctmc1 equ [81]
___ctmal equ [84]
___ctmah equ [85]
public _fun_ResetInit
#pragma debug scope 2 1
#line 24 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
_fun_ResetInit .section 'code'
_fun_ResetInit proc
#line 29 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	mov a,56
	mov [80],a
	mov a,193
	mov [81],a
	mov a,136
	mov [84],a
	mov a,2
	mov [85],a
#line 34 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	call _fun_Key_init
#line 35 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	call _Uart_Init
	ret
_fun_ResetInit endp
#line 35 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
#pragma debug scope 1 1
public _fun_PrepareToHalt
#pragma debug scope 3 1
#line 72 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
_fun_PrepareToHalt .section 'code'
_fun_PrepareToHalt proc
	ret
_fun_PrepareToHalt endp
#line 72 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
#pragma debug scope 1 1
public _fun_GPIO
#pragma debug scope 4 1
#line 103 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
_fun_GPIO .section 'code'
_fun_GPIO proc
	ret
_fun_GPIO endp
#line 103 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
#pragma debug scope 1 1
___mp1h equ [4]
___mp1l equ [3]
___tblp equ [7]
___iar1 equ [2]
public _fun_RamInit
#pragma debug scope 5 1
#line 116 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
_fun_RamInit .section 'code'
_fun_RamInit proc
#line 117 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	clr [4]
#line 118 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	mov a,128
	mov [3],a
#line 119 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	jmp _L5
_L8:
#line 121 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	clr [7]
_L6:
	sz [7].7
	jmp _L10
#line 123 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	clr [2]
#line 124 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	inc [3]
#line 121 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	inc [7]
	jmp _L6
_L10:
#line 126 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	mov a,128
	mov [3],a
#line 127 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	inc [4]
_L5:
#line 119 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	mov a,1
	sub a,[4]
	sz c
	jmp _L8
	ret
_fun_RamInit endp
#line 119 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
#pragma debug scope 1 1
___lvrc equ [25]
___hircc equ [17]
___wdtc equ [30]
public _fun_PowerOnInit
#pragma debug scope 6 1
#line 46 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
_fun_PowerOnInit .section 'code'
_fun_PowerOnInit proc
#line 48 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	mov a,85
	mov [25],a
#line 52 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	call _fun_RamInit
#line 53 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	clr [17].3
	set [17].2
	set [17].0
#line 56 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	mov a,87
	mov [30],a
#line 58 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	mov a,85
	mov [25],a
#line 60 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
	call _fun_ResetInit
	ret
_fun_PowerOnInit endp
#line 60 "E:\旧电脑资料\收集的资料\手册\合泰\BH66F5242热电偶资料\SoftWare-BH66F5242_Thermocouple V0.2-lib-20180903\SoftWare-BH66F5242_Thermocouple V0.2-lib\User\Sys_Init.C"
#pragma debug scope 1 1
#pragma debug variable 8 1 ___mp1l "__mp1l" 1
#pragma debug variable 8 1 ___mp1h "__mp1h" 1
#pragma debug variable 8 1 ___tblp "__tblp" 1
#pragma debug struct_begin 42 "__hircc_bits"
#pragma debug field 21 8 0 1 "__hircen" ;0,1
#pragma debug field 21 8 0 1 "__hircf" ;1,1
#pragma debug field 21 8 0 1 "__hirc0" ;2,1
#pragma debug field 21 8 0 1 "__hirc1" ;3,1
#pragma debug field 21 8 0 4 ;4,4
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___hircc "__hircc" 1
#pragma debug struct_begin 44 "__lvrc_bits"
#pragma debug field 21 8 0 1 "__lvs0" ;0,1
#pragma debug field 21 8 0 1 "__lvs1" ;1,1
#pragma debug field 21 8 0 1 "__lvs2" ;2,1
#pragma debug field 21 8 0 1 "__lvs3" ;3,1
#pragma debug field 21 8 0 1 "__lvs4" ;4,1
#pragma debug field 21 8 0 1 "__lvs5" ;5,1
#pragma debug field 21 8 0 1 "__lvs6" ;6,1
#pragma debug field 21 8 0 1 "__lvs7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___lvrc "__lvrc" 1
#pragma debug struct_begin 46 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___wdtc "__wdtc" 1
#pragma debug struct_begin 48 "__ctmc0_bits"
#pragma debug field 21 8 0 1 "__ctrp0" ;0,1
#pragma debug field 21 8 0 1 "__ctrp1" ;1,1
#pragma debug field 21 8 0 1 "__ctrp2" ;2,1
#pragma debug field 21 8 0 1 "__cton" ;3,1
#pragma debug field 21 8 0 1 "__ctck0" ;4,1
#pragma debug field 21 8 0 1 "__ctck1" ;5,1
#pragma debug field 21 8 0 1 "__ctck2" ;6,1
#pragma debug field 21 8 0 1 "__ctpau" ;7,1
#pragma debug struct_end
#pragma debug union_begin 49 ""
#pragma debug field 2 48 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 49 1 ___ctmc0 "__ctmc0" 1
#pragma debug struct_begin 50 "__ctmc1_bits"
#pragma debug field 21 8 0 1 "__ctcclr" ;0,1
#pragma debug field 21 8 0 1 "__ctdpx" ;1,1
#pragma debug field 21 8 0 1 "__ctpol" ;2,1
#pragma debug field 21 8 0 1 "__ctoc" ;3,1
#pragma debug field 21 8 0 1 "__ctio0" ;4,1
#pragma debug field 21 8 0 1 "__ctio1" ;5,1
#pragma debug field 21 8 0 1 "__ctm0" ;6,1
#pragma debug field 21 8 0 1 "__ctm1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 51 ""
#pragma debug field 2 50 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 51 1 ___ctmc1 "__ctmc1" 1
#pragma debug variable 8 1 ___ctmal "__ctmal" 1
#pragma debug variable 8 1 ___ctmah "__ctmah" 1
#pragma debug variable 8 1 ___iar1 "__iar1" 1
extern _fun_Key_init:near
extern _Uart_Init:near

; 
; Generated by holtek-gcc v3.19, Wed Apr 10 15:18:43 2019
; Rebuild 115
; end of file
