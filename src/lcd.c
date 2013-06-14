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
#include <p24HJ64GP502.h>
#include "types.h"
#include "lcd.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void lcd_cmd (uint8_t u8cmd)
{
    RS = 0;               // Command mode
    CSB = 0;              // Select display
    LCD_BUF;              // Read Buffer -> Clear RBF bit
    LCD_BUF = u8cmd;      // Write command bits
    LCD_BUF;              // Read Buffer -> Clear RBF bit

    while (LCD_STATbits.SPITBF); // wait until all bits are sent
    uint16_t i;
    for (i = 0; i < 150; i++);  // Create a small delay
    CSB = 1;                    // Unselect display
}

void lcd_display_char (c8_t c8character)
{
    RS = 1;               // Beginning of Data mode
    CSB = 0;              // Select display

    LCD_BUF;              // Read Buffer -> Clear RBF bit
    LCD_BUF = c8character;      // Write command bits
    LCD_BUF;              // Read Buffer -> Clear RBF bit

    while (LCD_STATbits.SPITBF); // wait until all bits are sent

    uint16_t i;
    for (i = 0; i < 150; i++); // Create a small delay

    RS = 0;               // Quit data mode
    CSB = 1;              // Unselect display
}

void lcd_display_string (c8_t *pac8string)
{
    // Simply write each character
    while (*pac8string)
    {
        // Hack to add support for linebreak in strings :)
        if (*pac8string == '\n')
        {
            // Jump to the second line
            lcd_set_cursor (1,0);
            pac8string++;
        }
        else
            // Otherwise display the character
            lcd_display_char (*pac8string++);
    }
}

void lcd_display_number (int16_t i16num)
{
    c8_t ac8buf[17];
    sprintf (ac8buf, "%-6d %4x", i16num, i16num);
    lcd_display_string (ac8buf);
}

void lcd_display_long_string (c8_t *pac8string, uint16_t u16delay)
{
    // Used later to remember the passed string.
    static c8_t *pc8char = NULL;
    // Array to hold our single lines
    static c8_t *ac8buf[30];
    // Line count
    static uint8_t u8count = 0;
    // Array index
    uint8_t u8index = 0;
    // If the string hasn't already been parsed
    if (pc8char == NULL || pc8char != pac8string)
    {
        pc8char = pac8string;

        // Split string by using linebreaks as delimiters
        pc8char = strtok (pac8string, "\n");

        // While there are still linebreaks in the string
        while (pc8char != NULL)
        {
            // Store the line in the array
            ac8buf[u8index++] = pc8char;
            // Get next line in string
            pc8char = strtok (NULL, "\n");
            // Increment Line count
            u8count++;
        }
        // Remember this string
        pc8char = pac8string;
    }

    u8index = 0;
    // to handle two \n's in sequence: Insert a newline
    bool b8skipline = false;
    // Iterate over the lines
    while (u8index < u8count)
    {
        lcd_clear ();
        // If the line does not have to be clear because of a second newline
        if (!b8skipline)
            // Display the line
            lcd_display_string (ac8buf[u8index]);
        // Go to the second line
        lcd_set_cursor (1, 0);
        // If the previous line didn't have to be clear
        if (!b8skipline)
            // Look if the line has a second \n
            if (*(ac8buf[u8index+1]-1) == '\n')
                // Then skip this line and next time, put this line in the second line
                b8skipline = true;
            else
                // Otherwise display the line
                lcd_display_string (ac8buf[++u8index]);
        else
        {
            // Otherwise display the line in the second line instead of the first line.
            lcd_display_string (ac8buf[++u8index]);
            // Finally done.
            b8skipline = false;
        }
        delayMs (u16delay);
    }
}

void lcd_conf_display (bool b8display, bool b8cursor, bool b8position)
{
    lcd_cmd (0x08 | (b8display << 2) | (b8cursor << 1) | b8position);
    delayMs (1);
}

void spi_init (void)
{
    RPOR3bits.RP7R = 9; // RP7 -> SS1
    RPOR2bits.RP4R = 8; // RP4 -> SCK1
    RPOR2bits.RP5R = 7; // RP5 -> SDO1
    RPINR20bits.SDI1R = 6; // RP6 -> SDI1

    TRISBbits.TRISB4 = 0; // SCK -> Output
    TRISBbits.TRISB5 = 0; // SDO -> Output
    TRISBbits.TRISB6 = 1; // SDI -> Input
    TRISBbits.TRISB7 = 0; // SS -> Output
    TRISAbits.TRISA3 = 0; // RS  -> Output
    TRISAbits.TRISA4 = 0; // CSB -> Output

    CSB = 1; // Unselect Display

    IFS0bits.SPI1IF = 0; // Clear Interrupt Flag
    IFS0bits.SPI1EIF = 0; // Disable Interrupts

    LCD_CON1bits.CKP = 1;    // Idle state for clock is a high level
    LCD_CON1bits.CKE = 0;    // Data out on idle to active edge
    LCD_CON1bits.MODE16 = 0; // 8-bit data transfer mode
    LCD_CON1bits.MSTEN = 1;  // Enable Master mode
    LCD_CON1bits.PPRE = 1;   // Set Primary Pre-scalar for 16:1 ratio
    LCD_CON1bits.SPRE = 1;   // Set Secondary Pre-scalar for 7:1 ratio
    LCD_CON1bits.SMP = 0;    // Sample Input Data at middle of data output time
    LCD_CON1bits.DISSDO = 0; // Enable SDO output
    LCD_CON1bits.DISSCK = 0; // Enable SCK output
    LCD_CON1bits.SSEN = 0;   // Disable SS
    LCD_CON2bits.FRMEN = 0;  // Disable Framed SPI mode
    LCD_STATbits.SPIROV = 0; // Clear Overflow Bit
    LCD_STATbits.SPISIDL = 0;// Continue Operation in Idle mode

    delayMs (50);
    LCD_STATbits.SPIEN = 1;  // Enable SPI module
}

void lcd_clear (void)
{
    lcd_cmd (0x01); // Clear Display
    delayMs (5);
    lcd_cmd (0x39); // Function Set
    delayMs (5);
    lcd_cmd (0x06); // Cursor auto-increment
    delayMs (5);
}

void lcd_set_cursor (uint8_t u8line, uint8_t u8col)
{
    lcd_cmd (0x80 | (u8line << 6) | u8col);
    delayMs (5);
}

void lcd_init (void)
{
    // Display Initialisation Commands
    lcd_cmd (0x39); // Function Set
    delayMs (5);
    lcd_cmd (0x14); // Bias Set
    delayMs (5);
    lcd_cmd (0x55); // Power Control
    delayMs (500);
    lcd_cmd (0x6D); // Follower Control
    delayMs (5);
    lcd_cmd (0x78); // Contrast Set
    delayMs (5);
    lcd_cmd (0x38); // Instruction Table 0
    delayMs (5);
    lcd_cmd (0x0F); // Display ON, Curson on, blink
    delayMs (5);
    lcd_cmd (0x01); // Clear Display
    delayMs (5);
    lcd_cmd (0x06); // Cursor auto-increment
    delayMs (5);
}
/** @} */ 
