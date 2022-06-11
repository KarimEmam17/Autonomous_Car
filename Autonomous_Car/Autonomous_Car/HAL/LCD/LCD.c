/*
 * LCD.c
 *
 * Created: 5/27/2022 4:41:34 PM
 *  Author: K.EMAM
 */
#include "LCD.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <math.h>

void LCD_INIT(void)
{
	/*Set direction of command pins (RS, RW, E)*/
	GPIO_SetPinDir(LCD_4_BIT_CMD_PORT, RS_PIN, GPIO_PIN_OUTPUT);
	GPIO_SetPinDir(LCD_4_BIT_CMD_PORT, RW_PIN, GPIO_PIN_OUTPUT);
	GPIO_SetPinDir(LCD_4_BIT_CMD_PORT, E_PIN , GPIO_PIN_OUTPUT);
	/*Set direction of data pins*/
	GPIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN4, GPIO_PIN_OUTPUT);
	GPIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN5, GPIO_PIN_OUTPUT);
	GPIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN6, GPIO_PIN_OUTPUT);
	GPIO_SetPinDir(LCD_4_BIT_DATA_PORT, LCD_PIN7, GPIO_PIN_OUTPUT);
	_delay_ms(100);
	/*choose 4-bit mode*/
	LCD_WriteCMD(0x33);
	LCD_WriteCMD(0x32);
	LCD_WriteCMD(LCD_4_Bit_Mode);
	///////////////////////////
	LCD_WriteCMD(Clear_Display_Screen);
	LCD_WriteCMD(Return_Home);
	LCD_WriteCMD(Shift_cursor_Right_Per_Read_Write);
	LCD_WriteCMD(Display_ON_Cursor_OFF);
	
}
void LCD_WriteCMD(u8 cmd)
{
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, RS_PIN, GPIO_PIN_LOW);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, RW_PIN, GPIO_PIN_LOW);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN , GPIO_PIN_LOW);
	
	LCD_4_BIT_BUS = (cmd & 0xF0) | (LCD_4_BIT_BUS & 0x0F);
	
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_HIGH);
	_delay_ms(1);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_LOW);
	
	LCD_4_BIT_BUS = (cmd << 4) | (LCD_4_BIT_BUS & 0x0F);
	
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_HIGH);
	_delay_ms(1);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_LOW);	
	
	_delay_ms(5);
}
void LCD_WriteCHAR(u8 chr)
{
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, RS_PIN, GPIO_PIN_HIGH);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, RW_PIN, GPIO_PIN_LOW);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN , GPIO_PIN_LOW);
	
	LCD_4_BIT_BUS = (chr & 0xF0) | (LCD_4_BIT_BUS & 0x0F);
	
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_HIGH);
	_delay_ms(1);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_LOW);
	
	LCD_4_BIT_BUS = (chr << 4) | (LCD_4_BIT_BUS & 0x0F);
	
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_HIGH);
	_delay_ms(1);
	GPIO_SetPinVal(LCD_4_BIT_CMD_PORT, E_PIN, GPIO_PIN_LOW);
	
	_delay_ms(5);	
}
void LCD_WriteSTRING(u8 * str)
{
	u8 counter = 0;
	while (str[counter] != '\0')
	{
		LCD_WriteCHAR(str[counter]);
		counter++;
	}
	
}
void LCD_WriteINTEGER(u32 integer)
{
	u32 Revers_num = 0;
	u8 displayed_num = 0;
	u32 multiplier = 1, i = 0;
	if(integer == 0)
	{
		LCD_WriteCHAR('0');
	}
	else if(integer < 0)
	{
		LCD_WriteCHAR('-');
		integer *= -1;
	}
	
	while (integer != 0)
	{
		Revers_num = (Revers_num * 10) + integer % 10;
		if (Revers_num == 0)	
		multiplier *= 10;
		integer /= 10;
	}	
	while (Revers_num != i)
	{
		displayed_num = Revers_num % 10;
		LCD_WriteCHAR(displayed_num + 48);
		Revers_num/=10;
		if (Revers_num == 0 && multiplier >= 10)
		{
			i = 1;
			Revers_num = multiplier;
		}	
	}
}
void LCD_WriteDECIMAL(f32 decimal)
{
   int val,i;
   val = (int) decimal;
   LCD_WriteINTEGER(val);
   LCD_WriteCHAR('.');
   decimal -= val;
   for (i = 0; i < 5; i++)
   {
	   decimal *=10;
	   val = (int)decimal;
	   LCD_WriteINTEGER(val);
	   decimal -=val;
   }	
}
void LCD_BurnCustomCHAR(u8 loc, u8 *arr)
{
	int i;
	LCD_WriteCMD(0X40 + (loc * 8));
	for (i = 0; i < 8; i++)
	{
		LCD_WriteCHAR(arr[i]);
	}
}
void LCD_ModifyDDRAM_CHAR(u8 loc, u8 *arr)
{
	int i;
	
}
void LCD_GoTo(u8 row, u8 col)
{
	u8 arr[2] = {Cursor_Begin_1st_Line, Cursor_Begin_2st_Line};
	LCD_WriteCMD(arr[row] + col);
}
void LCD_Clear(void)
{
	LCD_WriteCMD(Clear_Display_Screen);
}
