/** @addtogroup utils
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @date 2013-05-23
 * @brief Implements utility functions
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
<<<<<<< HEAD
#include <p24Hxxxx.h>
#include "types.h"
#include "utils.h"

#define LED1LAT LATB
#define LED1TRIS TRISB

=======
#include "types.h"
#include "utils.h"

>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
void delayMs (uint16_t u16delay)
{
    uint16_t u16i;
    for (; u16delay > 0; u16delay--)
        for (u16i = 0; u16i <= 5500; u16i++);
}

<<<<<<< HEAD
void delay_ms (uint16_t u16delay)
{
    delayMs (u16delay);
}

void delay_10us (uint16_t u16delay)
{
    delayMs (1);
}

=======
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
void LED ( volatile uint16_t *u16ledtris, volatile uint16_t *u16ledlat, uint8_t u8led, uint8_t u8action )
{
    switch ( u8action )
    {
        case ON:
<<<<<<< HEAD
            // Create a "1" in LAT -> Logically on
            *u16ledlat |= (1 << u8led);
            break;
        case OFF:
            // Create a "0" in LAT -> Logically off
            *u16ledlat &= ~(1 << u8led);
            break;
        case TOGGLE:
            // Toggle Bit in LAT -> Switch State
            *u16ledlat ^= (1 << u8led);
            break;
        case ENABLED:
            // Create a "0" in TRIS -> Pin is Output -> LED functionallity
=======
            *u16ledlat |= (1 << u8led);
            break;
        case OFF:
            *u16ledlat &= ~(1 << u8led);
            break;
        case TOGGLE:
            *u16ledlat ^= (1 << u8led);
            break;
        case ENABLED:
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
            *u16ledtris &= ~(1 << u8led);
            break;
        case DISABLED:
        default:
<<<<<<< HEAD
            // Create a "1" in TRIS -> Pin is Input -> No LED functionallity
=======
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
            *u16ledtris |= (1 << u8led);
            break;
    }
}

<<<<<<< HEAD
void LED1 (uint8_t action)
{
    return LED (&LED1TRIS, &LED1LAT, 15, action);
}

=======
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
uint8_t button_is_pressed ( volatile uint16_t *u16register, uint8_t u8port )
{
    // Wait for the Button to reach its final state
    delayMs (1);
<<<<<<< HEAD
    // Negate the PORT value (-> Pull-Up) and return it
=======
>>>>>>> ee22a8ccb96d8390f8f63d40a435a91ec46a39f5
    return ! (*u16register & (1<<u8port)); 
}
/** @} */
