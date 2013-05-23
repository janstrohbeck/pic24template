/** @defgroup LCD LCD Helper Functions
 *  This module contains functions to handle output and sending data to
 *  the LCD display.
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @date 2013-05-23
 * @brief LCD helper functions
 */
/* Copyright (C) 
 * 2013 - Jan Strohbeck
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */
#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_STAT SPI1STAT
#define LCD_CON1 SPI1CON1
#define LCD_STATbits SPI1STATbits
#define LCD_CON1bits SPI1CON1bits
#define LCD_BUF SPI1BUF
#define CSB LATAbits.LATA4
#define RS LATAbits.LATA3

/**
 * SPI Function to display Characters on the display.
 * 
 * Generally it sends data to the LCD Display
 * But most times this will be a character
 * 
 * @param c8character The Character to be displayed
 */
void lcd_display_char (c8_t c8character);

/**
 * SPI Function to send a command to the lcd display.
 * 
 * Sends a HEX command to the Display over SPI
 * 
 * @param u8cmd The Command to be sent (HEX)
 */
void lcd_cmd (uint8_t u8cmd);            

/**
 * Function to initialize the display.
 * 
 * Configures the Ports and SPI and sends the
 * Initialization commands to the display.
 */
void lcd_init (void);

#ifdef __cplusplus
}
#endif

#endif /* LCD_H */
/** @} */
