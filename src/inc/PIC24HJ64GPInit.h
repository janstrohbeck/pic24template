/** @defgroup init PIC24HJ64GP502 Init Functions
 *  This module includes Functions to set up the PIC24H Microcontroller.
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @date 2013-05-23
 * @brief PIC Init functions
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
#ifndef PIC24HJ64GPINIT_H
#define PIC24HJ64GPINIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <p24HJ64GP502.h>
#include "types.h"

/**
 * Init function for the PIC24HJ64GP502.
 * 
 * Initializes the PIC to fit our needs.
 * 
 * @param PLL Activate PLL (increase CPU Frequency)
 */
void init (bool PLL);

#ifdef __cplusplus
}
#endif

#endif /* PIC24HJ64GPINIT_H */
/** @} */
