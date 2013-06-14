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

/// A long sample string which can be printed out to the display w/ lcd_display_long_string (...)
c8_t ac8string[] = "Hello World!\n\nThis is just\na simple text\nto attract your\nattention";


/**
 * The main program.
 *
 * @return Nothing
 */
int main (void)
{
    // Initialize hardware (with PLL enabled)
    init (true);

    // Configure LED1
    LED1 (ENABLED);
    LED1 (OFF);

    // The number of LEDs we have
    uint8_t u8leds = 8;

    // The configuration Registers (TRIS) of the LEDs
    volatile uint16_t *apvu16conf[] =
    {
        &TRISB,
        &TRISB,
        &TRISB,
        &TRISB,
        &TRISB,
        &TRISA,
        &TRISA,
        &TRISB,
    };

    // The LAT/PORT-Registers of the LEDs
    volatile uint16_t *apvu16ports[] =
    {
        &LATB,
        &LATB,
        &LATB,
        &LATB,
        &LATB,
        &LATA,
        &LATA,
        &LATB,
    };

    // The offsets of the leds in their registers
    uint8_t au8offsets[] =
    {
        10,
        11,
        12,
        13,
        14,
        0,
        1,
        2,
    };

    uint8_t u8count;
    // Enable all LEDs and turn them off
    for (u8count = 0; u8count < u8leds; u8count++)
    {
        LED (apvu16conf[u8count], apvu16ports[u8count], au8offsets[u8count], ENABLED);
        LED (apvu16conf[u8count], apvu16ports[u8count], au8offsets[u8count], OFF);
    }

    // Initialize Display
    spi_init ();
    lcd_init ();

    // Turn on display, but disable cursor and position marker
    lcd_conf_display (ON, OFF, OFF);

    // Display the bits of a Hex number using the LEDs
    // leds_display_hex (apvu16conf, apvu16ports, au8offsets, u8leds, 0xFA);
    // while (1);

    u8count = 0;

    // The first time, the first led has to be manually switched on
    LED (apvu16conf[u8count], apvu16ports[u8count], au8offsets[u8count], ON);
    delayMs (100);

    while (true)
    {
        // lcd_display_long_string (ac8string, 1500);
        leds_running_light (apvu16conf, apvu16ports, au8offsets, u8leds, true);
        delayMs (100);
    }
    return 0;
}
/** @} */
