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

c8_t ac8string[] = "Hello World!\n\nThis is just\na simple text\nto attract your\nattention";

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

    while (TRUE)
    {
        lcd_display_long_string (ac8string, 1500);
        delayMs (1500);
    }
    return 0;
}
/** @} */
