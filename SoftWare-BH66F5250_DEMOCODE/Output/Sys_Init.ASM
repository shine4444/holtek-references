; Generated by holtek-gcc v3.19, Wed Apr 10 09:43:26 2019
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
mduwr0 equ [59h]
mduwr1 equ [5ah]
mduwr2 equ [5bh]
mduwr3 equ [5ch]
mduwr4 equ [5dh]
mduwr5 equ [5eh]
mduwrctrl equ [5fh]

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
___ptm2c0 equ [296]
___ptm2c1 equ [297]
___ptm2al equ [300]
___ptm2ah equ [301]
public _fun_ResetInit
#pragma debug scope 2 1
#line 24 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
_fun_ResetInit .section 'code'
_fun_ResetInit proc
#line 29 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	mov a,72
	lmov [296],a
	mov a,193
	lmov [297],a
	mov a,164
	lmov [300],a
	lclr [301]
#line 34 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	call _fun_Key_init
	ret
_fun_ResetInit endp
#line 34 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
#pragma debug scope 1 1
public _fun_PrepareToHalt
#pragma debug scope 3 1
#line 72 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
_fun_PrepareToHalt .section 'code'
_fun_PrepareToHalt proc
	ret
_fun_PrepareToHalt endp
#line 72 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
#pragma debug scope 1 1
public _fun_GPIO
#pragma debug scope 4 1
#line 104 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
_fun_GPIO .section 'code'
_fun_GPIO proc
	ret
_fun_GPIO endp
#line 104 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
#pragma debug scope 1 1
___mp1h equ [4]
___mp1l equ [3]
___tblp equ [7]
___iar1 equ [2]
public _fun_RamInit
#pragma debug scope 5 1
#line 117 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
_fun_RamInit .section 'code'
_fun_RamInit proc
#line 118 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	clr [4]
#line 119 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	mov a,128
	mov [3],a
#line 120 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	jmp _L5
_L8:
#line 122 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	clr [7]
_L6:
	sz [7].7
	jmp _L10
#line 124 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	clr [2]
#line 125 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	inc [3]
#line 122 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	inc [7]
	jmp _L6
_L10:
#line 127 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	mov a,128
	mov [3],a
#line 128 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	inc [4]
_L5:
#line 120 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	mov a,3
	sub a,[4]
	sz c
	jmp _L8
	ret
_fun_RamInit endp
#line 120 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
#pragma debug scope 1 1
___lvrc equ [25]
___scc equ [16]
___hircc equ [17]
___wdtc equ [30]
public _fun_PowerOnInit
#pragma debug scope 6 1
#line 46 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
_fun_PowerOnInit .section 'code'
_fun_PowerOnInit proc
#line 48 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	mov a,85
	mov [25],a
#line 52 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	call _fun_RamInit
#line 53 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	clr [16].3
	set [17].3
	clr [17].2
	set [17].0
#line 54 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	clr [16].2
#line 56 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	mov a,85
	mov [30],a
#line 58 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	mov a,85
	mov [25],a
#line 60 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
	call _fun_ResetInit
	ret
_fun_PowerOnInit endp
#line 60 "E:\旧电脑资料\收集的资料\手册\合泰\SoftWare-BH66F5250_DEMOCODE\User\Sys_Init.C"
#pragma debug scope 1 1
#pragma debug variable 8 1 ___mp1l "__mp1l" 1
#pragma debug variable 8 1 ___mp1h "__mp1h" 1
#pragma debug variable 8 1 ___tblp "__tblp" 1
#pragma debug struct_begin 42 "__scc_bits"
#pragma debug field 21 8 0 1 "__fsiden" ;0,1
#pragma debug field 21 8 0 1 "__fhiden" ;1,1
#pragma debug field 21 8 0 1 "__fss" ;2,1
#pragma debug field 21 8 0 1 "__fhs" ;3,1
#pragma debug field 21 8 0 1 ;4,1
#pragma debug field 21 8 0 1 "__cks0" ;5,1
#pragma debug field 21 8 0 1 "__cks1" ;6,1
#pragma debug field 21 8 0 1 "__cks2" ;7,1
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___scc "__scc" 1
#pragma debug struct_begin 44 "__hircc_bits"
#pragma debug field 21 8 0 1 "__hircen" ;0,1
#pragma debug field 21 8 0 1 "__hircf" ;1,1
#pragma debug field 21 8 0 1 "__hirc0" ;2,1
#pragma debug field 21 8 0 1 "__hirc1" ;3,1
#pragma debug field 21 8 0 4 ;4,4
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___hircc "__hircc" 1
#pragma debug struct_begin 46 "__lvrc_bits"
#pragma debug field 21 8 0 1 "__lvs0" ;0,1
#pragma debug field 21 8 0 1 "__lvs1" ;1,1
#pragma debug field 21 8 0 1 "__lvs2" ;2,1
#pragma debug field 21 8 0 1 "__lvs3" ;3,1
#pragma debug field 21 8 0 1 "__lvs4" ;4,1
#pragma debug field 21 8 0 1 "__lvs5" ;5,1
#pragma debug field 21 8 0 1 "__lvs6" ;6,1
#pragma debug field 21 8 0 1 "__lvs7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___lvrc "__lvrc" 1
#pragma debug struct_begin 48 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 49 ""
#pragma debug field 2 48 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 49 1 ___wdtc "__wdtc" 1
#pragma debug struct_begin 50 "__ptm2c0_bits"
#pragma debug field 21 8 0 3 ;0,3
#pragma debug field 21 8 0 1 "__pt2on" ;3,1
#pragma debug field 21 8 0 1 "__pt2ck0" ;4,1
#pragma debug field 21 8 0 1 "__pt2ck1" ;5,1
#pragma debug field 21 8 0 1 "__pt2ck2" ;6,1
#pragma debug field 21 8 0 1 "__pt2pau" ;7,1
#pragma debug struct_end
#pragma debug union_begin 51 ""
#pragma debug field 2 50 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 51 1 ___ptm2c0 "__ptm2c0" 1
#pragma debug struct_begin 52 "__ptm2c1_bits"
#pragma debug field 21 8 0 1 "__pt2cclr" ;0,1
#pragma debug field 21 8 0 1 "__pt2capts" ;1,1
#pragma debug field 21 8 0 1 "__pt2pol" ;2,1
#pragma debug field 21 8 0 1 "__pt2oc" ;3,1
#pragma debug field 21 8 0 1 "__pt2io0" ;4,1
#pragma debug field 21 8 0 1 "__pt2io1" ;5,1
#pragma debug field 21 8 0 1 "__pt2m0" ;6,1
#pragma debug field 21 8 0 1 "__pt2m1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 53 ""
#pragma debug field 2 52 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 53 1 ___ptm2c1 "__ptm2c1" 1
#pragma debug variable 8 1 ___ptm2al "__ptm2al" 1
#pragma debug variable 8 1 ___ptm2ah "__ptm2ah" 1
#pragma debug variable 8 1 ___iar1 "__iar1" 1
extern _fun_Key_init:near

; 
; Generated by holtek-gcc v3.19, Wed Apr 10 09:43:26 2019
; Rebuild 115
; end of file
