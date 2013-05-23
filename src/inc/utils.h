/** @defgroup utils PIC Utility Functions
 *  This module contains some helpful functions for working with PIC
 *  Microcontrollers, like accessing LEDs and Buttons.
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @date 2013-05-23
 * @brief PIC Utility functions
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
#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define OFF 0
#define ON 1
#define DISABLED 2
#define ENABLED 3
#define TOGGLE 4

/**
 * Simple Delay Function.
 * 
 * Creates an approximately one millisecond delay.
 * 
 * @param u16delay Number of Milliseconds to wait
 */
void delayMs (uint16_t u16delay);

/**
 * LED Configuration Function.
 *
 * Can enable, disable, switch on/off/toggle a LED
 *
 * @param u16ledtris The corresponding TRIS Register of the LED
 * @param u16ledlat The corresponding LAT Register of the LED
 * @param u8led The Bit offset in the Registers (Port number)
 * @param u8action The action to perform (e.g. ENABLE, OFF, ON, TOGGLE, etc)
 */ 
void LED ( volatile uint16_t *u16ledtris, volatile uint16_t *u16ledlat, uint8_t u8led, uint8_t u8action );

/**
 * Wrapper fuction for getting the state of a button.
 *
 * @param u16register The corresponding PORT Register
 * @param u8port The bit offset in the Register (Port number)
 */
uint8_t button_is_pressed (volatile uint16_t *u16register, uint8_t u8port);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */
/** @} */
