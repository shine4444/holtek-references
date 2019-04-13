//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : EEPROM.c
// Description: EEPROM�x���ӳ���
//Targer Board: None
//   MCU      : BH67F2260
//   Author   : ming
//   Date     : 2015/11/20
//   Version  : V00
//   History  :
//___________________________________________________________________
//___________________________________________________________________
#include "common.h"


/********************************************************************
Function:Read_EEPROM
INPUT	:@addr �x��ַ
OUTPUT	:@rdata �x���Ĕ���
NOTE	:none
*******************************************************************/
unsigned char fun_Read_EEPROM(unsigned char addr)
{
	u8 rdata,tm_emi;

	tm_emi = _emi;
	_emi = 0;

	_eea = addr;

	_mp1h = 1;
	_mp1l = 0x40;
	_iar1 |=0x2;				//enable RDEN
	_iar1 |=0x1;				//active READ 
	while((_iar1 & 0x01) !=0);		//wait read end
	rdata = _eed;
	_iar1 &=	0xfD;				//disable RDEN	
//	_mp1 = tmp_mp1;   
//	_bp = tmp_bp;
	_emi = tm_emi;
	return (rdata);
}

/********************************************************************
Function:Write_EEPROM
INPUT	:@addr ����ַ @data ������
OUTPUT	:none
NOTE	:none
*******************************************************************/
void fun_Write_EEPROM(unsigned char addr,unsigned char data)
{
	u8 tm_emi;
	tm_emi = _emi;
	_emi = 0;	
	_eea = addr;
	_eed = data;
//	tmp_bp = _bp;
//	tmp_mp1 =	_mp1;
	_mp1h = 1;
	_mp1l = 0x40;
	_iar1	|=	0x8;				//enable WREN
	_iar1	|=	0x4;				//active write 
	GCC_NOP();
	while((_iar1 & 0x04) !=0);		//wait write end
	_iar1	&=	0xf7;				//disable WREN	
//	_mp1	=	tmp_mp1;   
//	_bp		=	tmp_bp;
	_emi = tm_emi;	
}



/********************************************************************
Function:Test_EEPROM
INPUT	:lu8v_eeprom_length �O���x��eeprom���L�ȣ��ɸ�����ͬоƬ�M���O��
OUTPUT	:
NOTE	:none
*******************************************************************/
void	TEST_EEPROM(u8 lu8v_eeprom_length)
{
//	volatile	u8	lu8a_datatemp[64],i;
//	for(i=0;i<lu8v_eeprom_length;i++)
//	{
//		fun_Write_EEPROM(i,i);
//	}
//
//	for(i=0;i<lu8v_eeprom_length;i++)
//	{
//		lu8a_datatemp[i] = fun_Read_EEPROM(i);
//	}
//	
//	//�ڴ�̎�O�Ô��c�鿴lu8a_datatemp[i]��ֵ�����Д��x���Ƿ�ɹ���
//	GCC_NOP();

}





