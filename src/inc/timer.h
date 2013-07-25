/** @defgroup timer Timer Module
 * This module contains functions to initialize the onboard-timers of the PIC.
 * @{
*/
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @since 2013-07-24
 * @brief Timer Module
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
#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/// The number of Timer-Increments that represent one Millisecond
#define K_1MS 160

/**
 * Timer1 Initialization Method.
 * 
 * Sets up Timer1 to increment in 1:256 of FCY.
 */
void timer1_init (bool buse_interrupts);

/**
 * Timer2 Initialization Method.
 *
 * Sets up Timer2 to increment in FCY.
 */
void timer2_init (bool buse_interrupts);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */
/** @} */
