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
<<<<<<< HEAD
#define LCD_CON2bits SPI1CON2bits
#define LCD_BUF SPI1BUF
#define RS LATAbits.LATA3
#define CSB LATAbits.LATA4
#define SS LATBbits.LATB7

/**
 * SPI Function to display characters on the display.
 * 
 * Generally it sends data to the LCD Display. <br />
 * But most times this will be a character.
=======
#define LCD_BUF SPI1BUF
#define CSB LATAbits.LATA4
#define RS LATAbits.LATA3

/**
 * SPI Function to display Characters on the display.
 * 
 * Generally it sends data to the LCD Display
 * But most times this will be a character
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
 * 
 * @param c8character The Character to be displayed
 */
void lcd_display_char (c8_t c8character);

/**
<<<<<<< HEAD
 * Displays a string on the display.
 * 
 * Takes an array of characters and simply sends them all
 * to the display.
 * 
 * @param pac8string A pointer to the beginning of a string
 */
void lcd_display_string (c8_t *pac8string);

/**
=======
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
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

<<<<<<< HEAD
/**
 * Clears the LCD display.
 * 
 * Sends the commands needed to clear the LCD display.
 */
void lcd_clear (void);

/**
 * Configures the LCD display.
 *
 * Can configure the display: <br>
 *  - Turn display on/off
 *  - Turn displaying of cursor on/off
 *  - Turn displaying of cursor position on/off
 *
 * @param b8display If the display should be on/off
 * @param b8cursor If the displaying of the cursor should be on/off
 * @param b8position If the displaying of the cursor position should be on/off
 */
void lcd_conf_display (bool b8display, bool b8cursor, bool b8position);

/**
 * Initializes SPI1 to work properly.
 * 
 * Configures the Registers relevant to SPI so that it works correctly.
 */
void spi_init (void);

=======
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
#ifdef __cplusplus
}
#endif

#endif /* LCD_H */
/** @} */
