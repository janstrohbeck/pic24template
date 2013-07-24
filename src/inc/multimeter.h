/** @defgroup multimeter Multimeter
 * This module contains a function which allows the PIC to work as a Multimeter.
 * Supported working-modes are Voltmeter, Ohmmeter and Capacity-Meter.
 * @{
*/
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @since 2013-07-24
 * @brief Multimeter
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
#ifndef MULTIMETER_H
#define MULTIMETER_H

#ifdef __cplusplus
extern "C" {
#endif

/// Voltmeter-Mode (to measure voltages)
#define MODE_VOLT 0
/// Ohmmeter-Mode (to measure resistor-values)
#define MODE_OHM 1
/// Capacity-Meter-Mode (to measure capacities)
#define MODE_CAP 2

/**
 * Multimeter function.
 *
 * This function allow the PIC to work as a multimeter. It writes
 * the result of the measuring to the Character-Array located at pac8buf.
 * This can then be displayed using an LCD-Display or similar display-methods.
 * Additionally, It can display voltage in analog mode using the LEDs when in MODE_VOLT.
 *
 * @param pac8buf A pointer to a pre-allocated character-Array (50 Chars)
 * @param u8mode One of MODE_VOLT, MODE_OHM, MODE_CAP
 * @param buse_lights If the voltage should be displayed using the LEDs
 */
void multimeter (c8_t *pac8buf, uint8_t u8mode, bool buse_lights);

#ifdef __cplusplus
}
#endif

#endif /* MULTIMETER_H */
/** @} */
