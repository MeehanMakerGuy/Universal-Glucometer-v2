/********************************************************************
*
*
*
*********************************************************************
* FileName:         ST7032_cmds.h
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
* File Description: This file contains the defines applicable to using
*                   the ST7032 controller. (Insalled on the LCD)
*
* Change History:
* Author               Date        Version
* Chris Tucker        5/2/11         1.1  (Initial Release)
********************************************************************/

/**
*   @file ST7032_cmds.h
*   @brief
*   @defgroup
*
*/

//******************************************************/
//		ST7032_cmds Defines
//******************************************************/
// Command set for the St7032 LCD driver used by the Newhaven NHD-C0216CZ-FSW-FBW

#ifndef __ST7032_CMDS_H
#define __ST7032_CMDS_H

#define ST7032_CLEAR        0x01
#define ST7032_HOME         0x02

#define CURSOR_nSHIFT       0x00
#define CURSOR_SHIFT        0x01
#define DATA_DECREMENT      0x00
#define DATA_INCREMENT      0x02
#define ST7032_ENTRY_MODE   0x04

#define CURSOR_OFF          0x00
#define CURSOR_ON           0x02
#define BLINK_OFF           0x00
#define BLINK_ON            0x01
#define ST7032_DISPLAY_OFF  0x08
#define ST7032_DISPLAY_ON   0x0C


#define FUNCTION_nIS        0x00
#define FUNCTION_IS         0x01
#define FUNCTION_1_HIGH     0x00
#define FUNCTION_2_HIGH     0x04
#define FUNCTION_1_LINE     0x00
#define FUNCTION_2_LINE     0x08
#define FUNCTION_4BITS      0x00
#define FUNCTION_8BITS      0x10

#define ST7032_FUNCTION     0x20

#define ST7032_CGRAM_ADDRESS(adr) (0x40 | (adr & 0x3F))
#define ST7032_DDRAM_ADDRESS(adr) (0x80 | (adr & 0x7F))

//** Second Instruction Page (IS)
#define BIAS_1_5            0x00
#define BIAS_1_4            0x08
#define FREQ_CNTRL(f) (f&0x07)
#define ST7032_OSC_FREQ     0x10


#define ST7032_ICON_ADDRESS(adr) (0x40 | (adr & 0x0F))

#define nICON               0x00
#define ICON                0x08
#define nBOOST              0x00
#define BOOST               0x04
#define CONTRAST(c) (c&0x03)
#define ST7032_PWR_CONTROL  0x50

#define FOLLOWER_GAIN(g) (g&0x07)
#define ST7032_FOLLOWER_OFF 0x60
#define ST7032_FOLLOWER_ON  0x68

#define ST7032_CONTRAST(c) (0x70 | (c & 0x0F))

#define ST7032_BUSY_FLAG_MASK 0x80
#define ST7032_ADDRESS_MASK   0x7F

#define ST7032_ADDRESS_LINE_1 0x00
#define ST7032_ADDRESS_LINE_2 0x40

#endif //__ST7032_CMDS_H