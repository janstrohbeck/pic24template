/** @addtogroup leds
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @since 2013-07-24
 * @brief Led Functions Implementation
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
 */
#include <p24HJ64GP502.h>
#include "types.h"
#include "utils.h"
#include "leds.h"

/// The number of LEDs connected
uint8_t u8leds = 8;

/// The TRIS-Registers of the LEDs to be used
volatile uint16_t *apvu16leds_conf[] =
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

/// The Latches of the LED-pins
volatile uint16_t *apvu16leds_ports[] =
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

/// The offsets of the LEDs in their respective Registers
uint8_t au8leds_offsets[] =
{
    11,
    12,
    13,
    14,
    15,
    0,
    1,
    2,
};

void running_light (bool btwo_directions)
{
    static uint8_t u8count = 0;
    static bool bfirstrun = true;
    static int8_t u8direction = 1;
    // Fix firstrun bug
    if (bfirstrun)
    {
        LED (apvu16leds_conf[u8count], apvu16leds_ports[u8count], au8leds_offsets[u8count], ON);
        bfirstrun = false;
        return;
    }
    // Turn the last LED off
    LED (apvu16leds_conf[u8count], apvu16leds_ports[u8count], au8leds_offsets[u8count], TOGGLE);
    // Move forward
    u8count += u8direction;
    if (btwo_directions)
    {
        if (u8count == u8leds-1)
            u8direction = -1;
        else if (u8count == 0)
            u8direction = 1;
    }
    else
        u8count %= u8leds;
    // Turn the next LED on
    LED (apvu16leds_conf[u8count], apvu16leds_ports[u8count], au8leds_offsets[u8count], TOGGLE);
}

void leds_display_hex (uint8_t u8num)
{
    uint8_t u8count = u8leds-1;
    while (u8num > 0)
    {
        // Turn the LED representing the current bit on if it is set
        LED (apvu16leds_conf[u8count], apvu16leds_ports[u8count], au8leds_offsets[u8count], u8num & 1);
        u8num >>= 1;
        u8count--;
    }
}
/** @} */
