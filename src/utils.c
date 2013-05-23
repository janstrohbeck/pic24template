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
#include "types.h"
#include "utils.h"

void delayMs (uint16_t u16delay)
{
    uint16_t u16i;
    for (; u16delay > 0; u16delay--)
        for (u16i = 0; u16i <= 5500; u16i++);
}

void LED ( volatile uint16_t *u16ledtris, volatile uint16_t *u16ledlat, uint8_t u8led, uint8_t u8action )
{
    switch ( u8action )
    {
        case ON:
            *u16ledlat |= (1 << u8led);
            break;
        case OFF:
            *u16ledlat &= ~(1 << u8led);
            break;
        case TOGGLE:
            *u16ledlat ^= (1 << u8led);
            break;
        case ENABLED:
            *u16ledtris &= ~(1 << u8led);
            break;
        case DISABLED:
        default:
            *u16ledtris |= (1 << u8led);
            break;
    }
}

uint8_t button_is_pressed ( volatile uint16_t *u16register, uint8_t u8port )
{
    // Wait for the Button to reach its final state
    delayMs (1);
    return ! (*u16register & (1<<u8port)); 
}
/** @} */
