 /******************************************************************************
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Ola Mohamed Ahmed
 *
 *******************************************************************************/
#include "lcd.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*this Function for Configure LCD
 * 1- Configure the data port as output port
 *2-Configure the control pins(E,RS,RW) as output pins
 *3- use 2-line lcd + 8-bit Data Mode
 *4-cursor off
 *5-clear LCD

 */

void LCD_init(void)
{
	LCD_DATA_PORT_DIR = 0xFF;
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);

	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);

	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}

/*this function for send command
 * 1-Instruction Mode RS=0
 * 2-write data to LCD
 * 3-Enable LCD
 * 4-out the required command
 * 5- disable LCD
 *
 */

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

/*this function for display character

 *1-Data Mode RS=1
 *2-write data to LCD
 *3-write 3-Enable LCD E=1
 *4- out the required data
 *5- disable LCD
 */

void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

/*this function for display string
 *1-to loop for string until null
 *
 */
void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}
/*this function for move cursor to specific row , column
 *1-calculate the required address
 *
 */
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

/*this function for display string in specific row , column
 *1- go to to the required LCD position
 *2-display the string
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(Str);
}


/*this function for translate any string to integer
 *1- String to hold the ascii result
 *2-10 for decimal
 */
void LCD_intgerToString(int data)
{
   char buff[16];
   itoa(data,buff,10);
   LCD_displayString(buff);
}
/*this function for clear lcd
 * clear display
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}
