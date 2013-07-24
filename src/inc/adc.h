/** @defgroup adc AD-Converter
 * This module contains Functions to setup and use the AD-Converter on the PIC.
 * @{
*/
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @since 2013-07-24
 * @brief AD-Converter
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
#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/// The operating voltage of the PIC
#define VCC 3.25f

/**
 * AD-Converter Init function.
 * 
 * Initializes the AD-Converter on the PIC.
 */
void ADCinit ();

/**
 * Reads a value from the AD-Converter (12-Bit).
 * 
 * Returns the fraction of measured voltage based on VCC in
 * 12-Bit-Representation (0...4095).
 * 
 * @return The result of the AD-Conversion.
 */
uint16_t u16ADCread ();

#ifdef __cplusplus
}
#endif

#endif /* ADC_H */
/** @} */
