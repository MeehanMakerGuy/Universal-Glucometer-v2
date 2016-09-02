/********************************************************************
*
*
*
*********************************************************************
* FileName:         LCD.c
* Dependencies:     See INCLUDES section below
* Processor:        PIC16LF1786
* Compiler:         XC8
* Company:          Microchip Technology, Inc.
*
* Software License Agreement:
*
* The software supplied herewith by Microchip Technology Incorporated
* (the "Company") for its PICmicro® Microcontroller is intended and
* supplied to you, the Company's customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*********************************************************************
* File Description: This file contains functions related to the LCD.
*                   All advanced features related to printing to the
*                   LCD, moving the cursor or clearing LCD are stored
*                   here. Also backlight on/off function are stored.
* Change History:
* Author               Date        Version
* Chris Tucker        5/2/11         1.1  (Initial Release)
********************************************************************/

/**
*   @file lcd.c
*   @brief
*   @defgroup
*
*/
//*****************************************************************************
// Include and Header files
//*****************************************************************************
#include <xc.h>
#include <pic.h>
#include "local_stdint.h"
#include "ST7032_cmds.h"
#include "lcd.h"
#include "user.h"

//*****************************************************************************
// Global Variable Strings
//*****************************************************************************
//extern uint8_t BkLight;
extern uint8_t DutyCycle;
//*****************************************************************************
//Local Function Prototypes
//*****************************************************************************
#define Delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define Delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
//*****************************************************************************
// Global Constant Strings
//*****************************************************************************
const char line_address[] = {ST7032_ADDRESS_LINE_1,ST7032_ADDRESS_LINE_2};
//*****************************************************************************
// SUPPORT FUNCTIONS
//*****************************************************************************
/********************************************************************
* Function:             SPI_TX
*
* PreCondition: 	LCD must be setup.
*
* Side Effects: 	Writes to screen
*/
/**
* @ingroup  		LCD
*
* @brief    		This function writes to the LCD screen.
*
* @note    		Send byte via spi to the lcd
*/
/*******************************************************************/
void SPI_TX(uint8_t Command)
{
    uint8_t mask;

    for(mask = 0x80; mask != 0; mask >>= 1)
    {
        LCD_SCL = LCD_LOW;
        NOP();
        if(Command & mask) LCD_SDI = LCD_HIGH; else LCD_SDI = LCD_LOW;
        LCD_SCL = LCD_HIGH;
        NOP();
    }
    LCD_CS  = LCD_nSELECTED;
    Delay_us(85);
}

/********************************************************************
* Function:             lcd_backlight_on
*
* PreCondition: 	None
*
* Side Effects: 	Turns LCD backlight on.
*/
/**
* @ingroup  		LCD
*
* @brief    		This function turns on backlight. Tris/Lat bit.
*
* @note    		None
*/
/*******************************************************************/
//void lcd_backlight_on()
//{
//        TRIS_LCD_BKLIGHT  = LCD_POWER_ON;
//        LCD_BKLIGHT = LCD_POWER_ON;
//        BkLight == ON;
//}

/********************************************************************
* Function:             lcd_backlight_off
*
* PreCondition: 	None
*
* Side Effects: 	Turns off LCD backlight.
*/
/**
* @ingroup  		LCD
*
* @brief    		This function turns on backlight. Tris/Lat bit.
*
* @note    		None
*/
/*******************************************************************/
//void lcd_backlight_off()
//{
//    TRIS_LCD_BKLIGHT  = LCD_POWER_OFF;
//    LCD_BKLIGHT = LCD_POWER_OFF;
//    BkLight == OFF;
//}

/********************************************************************
* Function:             lcd_goto
*
* PreCondition: 	None
*
* Side Effects: 	Moves cursor.
*/
/**
* @ingroup  		LCD
*
* @brief    		This function points to an LCD position.
*
* @note    		None
*/
/*******************************************************************/
void lcd_goto(uint8_t x,uint8_t y)
{
    lcd_putcmd(ST7032_DDRAM_ADDRESS(line_address[y] + x));
}

/********************************************************************
* Function:             lcd_clear
*
* PreCondition: 	None
*
* Side Effects: 	Clears LCD
*/
/**
* @ingroup  		LCD
*
* @brief    		This function clears the LCD screen.
*
* @note    		None
*/
/*******************************************************************/
void lcd_clear(void)
{
    lcd_putcmd(ST7032_CLEAR);   //clear
    Delay_us(20);
}
/********************************************************************
* Function:             lcd_clear
*
* PreCondition: 	None
*
* Side Effects: 	Clears LCD
*/
/**
* @ingroup  		LCD
*
* @brief    		This function clears the LCD screen.
*
* @note    		None
*/
/*******************************************************************/
void lcd_home(void)
{
    lcd_putcmd(ST7032_HOME);   //clear
    Delay_us(20);
}
/********************************************************************
* Function:             lcd_putline
*
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief    		This function sends an LCD message.
*
* @note    		Sends LCD message and line location
*/
/*******************************************************************/
void lcd_putline(const uint8_t l, const char *buffer) 
{
    lcd_putcmd(line_address[l]);
    lcd_putstr(buffer);
}

/********************************************************************
* Function:             lcd_putstr
*
* PreCondition: 	None
*
* Side Effects: 	Writes message to LCD
*/
/**
* @ingroup  		LCD
*
* @brief    		This function writes a string to the LCD.
*
* @note    		Write data to LCD up to null
*/
/*******************************************************************/
void lcd_putstr(const char *s)
{
    while(*s)              
    {
	lcd_putchar(*s++); 
    }
}

/********************************************************************
* Function:             lcd_init
*
* PreCondition: 	None
*
* Side Effects: 	Sets up LCD
*/
/**
* @ingroup  		LCD
*
* @brief    		This function initialises the LCD.
*
* @note    		None
*/
/*******************************************************************/
void lcd_init(void)
{
    TRIS_LCD_PWR = 0;
    //TRIS_LCD_BKLIGHT = 0;
    
   LCD_PWR = LCD_POWER_ON;        // power up the lcd controller
// LCD_PWR = LCD_POWER_OFF;

//   if (BkLight == ON)
//   {
//        LCD_BKLIGHT = LCD_POWER_ON;        // turn on the LCD backlight
//   }
//   else if (BkLight == OFF)
//   {
//        LCD_BKLIGHT = LCD_POWER_OFF;        // turn on the LCD backlight
//   }
   
   TRIS_LCD_RST   = 0;
   TRIS_LCD_CS    = 0;
   TRIS_LCD_RS    = 0;

   TRIS_LCD_SDI   = 0;
   TRIS_LCD_SCL   = 0;
   
   LCD_RST        = 0;  // RESET
   Delay_ms(2);       // Burn some time
   LCD_RST        = 1;  // end reset

   Delay_ms(40);
   
   lcd_putcmd(ST7032_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set
   Delay_ms(2);
      
   lcd_putcmd(ST7032_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set
   lcd_putcmd(ST7032_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set

   // Enter the second page of instructions
   lcd_putcmd(ST7032_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_2_LINE | FUNCTION_IS);   //function set
   lcd_putcmd(ST7032_OSC_FREQ | BIAS_1_5 | FREQ_CNTRL(4));   //internal osc frequency
   lcd_putcmd(ST7032_PWR_CONTROL | nICON | BOOST | CONTRAST(2));   //power control
   lcd_putcmd(ST7032_FOLLOWER_ON | FOLLOWER_GAIN(5));   //follower control
   lcd_putcmd(ST7032_CONTRAST(0));   //contrast
   // leave second instruction page
   
//   lcd_putcmd(ST7032_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_2_LINE | FUNCTION_nIS);   //function set
   lcd_putcmd(ST7032_DISPLAY_ON | CURSOR_OFF | BLINK_OFF);   //display on
   lcd_putcmd(ST7032_ENTRY_MODE | CURSOR_nSHIFT | DATA_INCREMENT);   //entry mode
   lcd_putcmd(ST7032_CLEAR);   //clear

   Delay_ms(20);
}

/********************************************************************
* Function:             lcd_putcmd
*
* PreCondition: 	None
*
* Side Effects: 	Sends command to the LCD.
*/
/**
* @ingroup  		LCD
*
* @brief    		This function sends a command to the LCD.
*
* @note    		Send comand byte to the lcd
*/
/*******************************************************************/
void lcd_putcmd(uint8_t Command)
{		
   LCD_CS = LCD_SELECTED;
   LCD_RS = LCD_RS_COMMAND;
   SPI_TX(Command);
}

/********************************************************************
* Function:             lcd_putchar
*
* PreCondition: 	None
*
* Side Effects: 	Puts character on LCD
*/
/**
* @ingroup  		LCD
*
* @brief    		This function puts a character onto the screen.
*
* @note    		Write data to the lcd
*/
/*******************************************************************/     
void lcd_putchar(const char c)
{
   LCD_CS = LCD_SELECTED;
   LCD_RS = LCD_RS_DATA;
   SPI_TX(c);
}


//----------------------------------------------------------------------------
