/** @addtogroup LCD
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @brief Implements LCD functions
 * @date 2013-05-23
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
#include "types.h"
#include "lcd.h"
#include "utils.h"

void lcd_cmd (uint8_t u8cmd)
{
    CSB = 0;             // Beginning of data transfer
    RS = 0;              // Command mode
    LCD_BUF &= 0xFF00;   // prepare RD0 - RD7
    LCD_BUF |= u8cmd;      // Write command bits

    while (LCD_STATbits.SPITBF); // wait until all bits are sent
    CSB = 1;             // End of data transfer
    delayMs (100);
}

void lcd_display_char (c8_t c8character)
{
    CSB = 0;              // Beginning of data transfer
    RS = 1;               // Data mode
    LCD_BUF &= 0xFF00;    // prepare RD0 - RD7
    LCD_BUF |= c8character; // Write data bits

    // Test -> Oscilloscope
    if (LCD_STATbits.SPITBF)
        LATB |= (1<<15);

    while (LCD_STATbits.SPITBF); // wait until all bits are sent

    LATB &= ~(1<<15);

    RS = 0;               // Quit data mode
    CSB = 1;              // End of data transfer
    delayMs (100);
}

void lcd_init (void)
{
    RPOR2 = 0x708; // Use RP4 as SCK1 and RP5 as SDO1

    TRISB &= ~(1<<4); // SCK -> Output
    TRISB &= ~(1<<5); // SDO -> Output
    TRISB &= ~(1<<7); // SS  -> Output
    TRISB |= (1<<6);  // SDI -> Input
    TRISA &= ~(1<<3); // RS  -> Output
    TRISA &= ~(1<<4); // CSB -> Output

    CSB = 1;

    LATB |= (1<<7); // Make Slave listen (SS)

    LCD_CON1bits.CKP = 0;    // Idle state for clock is a low level
    LCD_CON1bits.CKE = 1;    // Data out on Active to Idle Edge
    LCD_CON1bits.MODE16 = 0; // 8-bit data transfer mode
    LCD_CON1bits.MSTEN = 1;  // Enable Master mode
    LCD_CON1bits.SPRE = 0;   // Set Primary Pre-scalar for 64:1 ratio
    LCD_CON1bits.PPRE = 0;   // Set Secondary Pre-scalar for 8:1 ratio
    LCD_CON1bits.DISSDO = 0; // Enable SDO output
    LCD_CON1bits.DISSCK = 0; // Enable SCK output
    LCD_CON1bits.SSEN = 0;   // Disable SS

    LCD_STATbits.SPIEN = 1;  // Enable SPI module
    LCD_STATbits.SPIROV = 0; // Clear Overflow Bit

    // Display Initialisation Commands
    lcd_cmd (0x39);
    lcd_cmd (0x14);
    lcd_cmd (0x55);
    lcd_cmd (0x6D);
    lcd_cmd (0x78);
    lcd_cmd (0x38);
    lcd_cmd (0x0F);
    lcd_cmd (0x01);
    lcd_cmd (0x06);
}
/** @} */ 
