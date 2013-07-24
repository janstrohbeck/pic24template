/** @defgroup leds LED Functions
 * This module contains Functions to do cool stuff using some LEDs.
 * @{
*/
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @since 2013-07-24
 * @brief LED Functions
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
#ifndef LEDS_H
#define LEDS_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Function to create a running light using the connected LEDs.
 *
 * Creates a running light using the connected LEDs (see configuration arrays).
 * Call this function repeatedly with some delay (e.g. 100ms) in between.
 *
 * @param btwo_directions If the light should be "reflected" on the right side or not.
 */
void running_light (bool btwo_directions);

/**
 * Displays a 8-Bit Number using the connected LEDs (bit-wise).
 *
 * @param u8num The number to be displayed.
 */
void leds_display_hex (uint8_t u8num);

extern uint8_t u8leds;
extern volatile uint16_t *apvu16leds_conf[];
extern volatile uint16_t *apvu16leds_ports[];
extern uint8_t au8leds_offsets[];

#ifdef __cplusplus
}
#endif

#endif /* LEDS_H */
/** @} */
