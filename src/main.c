/** @defgroup main Main Program
 *  This module contains the main function.
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @date 2013-05-23
 * @brief Main Program
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
#include "PIC24HJ64GP502init.h"
#include "utils.h"
#include "lcd.h"

int main (void)
{
    // Initialize hardware (with PLL enabled)
    init (TRUE);

    // Configure LED1
    LED1 (ENABLED);
    LED1 (OFF);

    spi_init ();
    lcd_init ();

    // Turn on display, but disable cursor and position marker
    lcd_conf_display (ON, OFF, OFF);

    lcd_display_string ("Hello World!\n");
    lcd_display_string ("(C) JanStrohbeck");
    delayMs (3000);

    uint8_t u8test = 0;
    while (1)
    {
        // Clear Display first
        lcd_clear ();
        uint8_t u8copy = u8test, u8len = 0, au8nums[5];
        int8_t i8count;

        // Write decimal digits of number to array
        while (u8copy != 0)
        {
            au8nums[u8len++] = u8copy % 10;
            u8copy /= 10;
        }
        // Print out decimals
        for (i8count = u8len-1; i8count > -1; i8count--)
            lcd_display_char (48 + au8nums[i8count]);
        // Handle 0 seperately
        if (u8len == 0)
            lcd_display_char (48);

        lcd_display_char (':');
        lcd_display_char (' ');
        // Print out corresponding character
        lcd_display_char (u8test);
        u8test++;

        // Toggle LED1 every second
        LED1 (TOGGLE);
        delayMs (1000);
    }
    return 0;
}
/** @} */
