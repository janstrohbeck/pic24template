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

/// The LAT Register corresponding to LED1
#define LED1LAT LATB
/// The TRIS Register corresponding to LED1
#define LED1TRIS TRISB

#ifdef __DEBUG
#define DELAY_MS 0
#define DELAY_US 0
#else
/// The number of 16-bit-Additions it takes to create a
/// 1ms Delay
#define DELAY_MS 5500
/// The number of 16-bit-Additions it takes to create a
/// 1us Delay
#define DELAY_US 5
#endif

/// Turn the LED off (write 0 to LAT)
#define OFF 0
/// Turn the LED on (write 1 to LAT)
#define ON 1
/// "Disable" the LED (configure it as input)
#define DISABLED 2
/// Enable the LED (configure it as output)
#define ENABLED 3
/// Toggle the state of the LED (on->off, off->on)
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
 * Simple Delay Function.
 * 
 * Creates an approximately one millisecond delay. This function
 * is a wrapper to the delayMs-Function.
 * 
 * @param u16delay Number of Milliseconds to wait
 */
void delay_ms (uint16_t u16delay);

/**
 * Simple Delay Function.
 * 
 * Creates an approximately one microsecond delay.
 * 
 * @param u16delay Number of Microseconds to wait
 */
void delay_us (uint16_t u16delay);

/**
 * LED Configuration Function.
 *
 * Can enable, disable, switch on/off/toggle a LED
 *
 * @param u16ledtris The corresponding TRIS Register of the LED
 * @param u16ledlat The corresponding LAT Register of the LED
 * @param u8led The Bit offset in the Registers (Port number)
 * @param u8action The action to perform (ENABLE, OFF, ON, TOGGLE, DISABLE)
 */ 
void LED ( volatile uint16_t *u16ledtris, volatile uint16_t *u16ledlat, uint8_t u8led, uint8_t u8action );

/**
 * LED Configuration Function.
 *
 * Can enable, disable, switch on/off/toggle LED1 (This is just a wrapper
 * function of the LED-Function)
 *
 * @param u8action The action to perform (ENABLE, OFF, ON, TOGGLE, DISABLE)
 */ 
void LED1 (uint8_t action);

/**
 * Displays the bits of a number using (at least) 8 LEDs.
 *
 * The LEDs have to be specified by passing the corresponding
 * TRIS and LAT-Registers as well as the offset of the LED in
 * both Registers as Arrays. The length of the arrays ( = number
 * of LEDs) has to be passed as well.
 *
 * @param apvu16conf An array containing pointers to the TRIS-Register
 * corresponding to each LED.
 * @param apvu16ports An array containing pointers to the LAT/PORT-
 * corresponding to each LED.
 * @param au8offsets An array containing the offsets of each LED in
 * both Registers.
 * @param u8leds The number of LEDs ( = Length of the arrays)
 */
void leds_display_hex (volatile uint16_t **apvu16conf,
        volatile uint16_t **apvu16ports, uint8_t *au8offsets, uint8_t u8leds,
        uint8_t u8num);

/**
 * Implements a running light using external LEDs.
 *
 * At the end of the LED-row, the light can either be "reflected"
 * to switch its direction, or it can restart at the beginning.
 * This function expects the LEDs to be pre-configured as outputs
 * and turned off initially. Call this function periodically in a loop.
 * The LEDs have to be specified by passing the corresponding
 * TRIS and LAT-Registers as well as the offset of the LED in
 * both Registers as Arrays. The length of the arrays ( = number
 * of LEDs) has to be passed as well.
 *
 * @param apvu16conf An array containing pointers to the TRIS-Register
 * corresponding to each LED.
 * @param apvu16ports An array containing pointers to the LAT/PORT-
 * corresponding to each LED.
 * @param au8offsets An array containing the offsets of each LED in
 * both Registers.
 * @param u8leds The number of LEDs ( = Length of the arrays)
 * @param b8switch_directions If the running light should be reflected
 * at the end of the LED-row or not.
 */
void leds_running_light (volatile uint16_t **apvu16conf,
        volatile uint16_t **apvu16ports, uint8_t *au8offsets,
        uint8_t u8leds, bool b8switch_directions);

/**
 * Wrapper fuction for (safely) getting the state of a button.
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
