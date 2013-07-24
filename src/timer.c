/** @addtogroup timer
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @since 2013-07-24
 * @brief Timer Implementation
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
#include "PIC24HJ64GP502init.h"
#include "types.h"
#include "timer.h"

void timer_init (void)
{
    T1CON = 0;
    PMD1bits.T1MD = 0;
    T1CONbits.TCKPS = 3;
    T1CONbits.TCS = 0;
    T1CONbits.TON = 1;
    TMR1 = 0;
}
/** @} */
