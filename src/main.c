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
#include "PIC24HJ64GPInit.h"
#include "utils.h"
#include "lcd.h"

#define LEDLAT LATB
#define LEDTRIS TRISB

int main (void)
{
    init (TRUE);

    // Configure LED1
    LED (&LEDTRIS, &LEDLAT, 15, ENABLED);
    LED (&LEDTRIS, &LEDLAT, 15, OFF);

    uint8_t u8count;
    while (1)
    {
        // Toggle LED1 every second
        LED (&LEDTRIS, &LEDLAT, 15, TOGGLE);
        delayMs (1000);
    }
    return 0;
}
/** @} */
