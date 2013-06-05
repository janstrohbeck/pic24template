/** @addtogroup init
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @date 2013-05-23
 * @brief Implements init functions
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
#include "PIC24HJ64GP502init.h"
#include "types.h"

#ifdef __PIC24HJ64GP502__
    _FOSCSEL(FNOSC_FRC);    // FRC Oscillator with PLL
    _FOSC( FCKSM_CSECMD &   // Clock Switching is enabled and Fail Safe Clock Monitor is disabled
            OSCIOFNC_ON &   // OSC2 Pin Function: OSC2 is Clock Output
            POSCMD_NONE);    // Primary Oscillator Mode: Disabled
    _FWDT(FWDTEN_OFF);      // turn off watchdog
#endif

void init (bool PLL)
{
    if (PLL)
    {
        // Configure Oscillator to operate the device at 40Mhz
        // Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
        // Fosc= 7.37M*43(2*2)=80Mhz for 7.37M input clock
        PLLFBD = 41;                // M = 43
        CLKDIVbits.PLLPOST = 0;     // N1 = 2
        CLKDIVbits.PLLPRE = 0;      // N2 = 2
        OSCTUN = 0;                 // Tune FRC oscillator, if FRC is used

        RCONbits.SWDTEN = 0;        // Disable Watch Dog Timer

        // Clock switch to incorporate PLL
        __builtin_write_OSCCONH (0x01);	// Initiate Clock Switch to FRC with PLL (NOSC=0b001)
        __builtin_write_OSCCONL (0x01);	// Start clock switching
        while (OSCCONbits.COSC != 0b001);	// Wait for Clock switch to occur
        while (OSCCONbits.LOCK != 1);       // Wait for PLL to lock
    }
    AD1CON1bits.ADON = 0; // Turn off ADC
    CMCONbits.C1EN = 0; // Turn off Comparator1
    CMCONbits.C2EN = 0; // Turn off Comparator2
    PMD1 = 0xFFFF; // Turn off everything
    PMD2 = 0xFFFF;
    PMD3 = 0xFFFF;
    PMD1bits.SPI1MD = 0; // Enable SPI1

    AD1PCFGL = 0xFFFF; // Set All Pins as Digital IOs
    TRISB = 0; // Set all Pins as Outputs
    TRISA = 0;

    LATA = 0; // Set all Pins default value to zero.
    LATB = 0;
}
/** @} */
