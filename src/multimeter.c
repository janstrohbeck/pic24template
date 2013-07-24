/** @addtogroup multimeter
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @since 2013-07-24
 * @brief Multimeter Implementation
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
#include <stdio.h>
#include "types.h"
#include "adc.h"
#include "leds.h"
#include "timer.h"
#include "utils.h"
#include "multimeter.h"

void multimeter (c8_t *pac8buf, uint8_t u8mode, bool buse_lights)
{
    // The number of Resistors connected
    const uint8_t RiNum = 3;
    // The Values of the Resistors
    const uint32_t Ri[] = {1000,10000,100000};
    // The Resistor Latches
    volatile uint16_t *RiPorts[] =
    {
        &LATB,
        &LATB,
        &LATB
    };
    // The Resistor TRIS Registers
    volatile uint16_t *RiPins[] =
    {
        &TRISB,
        &TRISB,
        &TRISB
    };
    // The offsets of the Resistors in their respective Registers
    const uint8_t RiOffsets[] =
    {
        7,
        8,
        9
    };

    // Raw ADC-Value
    uint16_t u16res = u16ADCread ();
    // Current measured voltage
    float fcurrent = (float)u16res/4095*VCC;
    // Minimum Voltage that has been measured
    static float fmin = 0.0f;
    fmin = fcurrent;
    // Maximum Voltage that has been measured
    static float fmax = 0.0f;
    fmax = fcurrent;
    // The state of the reset-button
    bool b8buttonstate = false;
    // A counter to measure the time the reset-button has been pressed
    static uint8_t u8butcnt = 0;

    uint8_t u8c;
    // The index of the Resistor which is in use
    static uint8_t u8choice = 2;

    // Configure the button
    TRISB |= (1<<10);

    switch (u8mode)
    {
        // Volt-Meter
        case MODE_VOLT:
            // Disable all resistors
            for (u8c = 0; u8c < RiNum; u8c++)
                *(RiPins[u8c]) |= (1<<RiOffsets[u8c]);

            u16res = u16ADCread ();
            fcurrent = (float)u16res/4095*VCC;

            // Set new Minimum/Maximum
            if (fcurrent > fmax)
                fmax = fcurrent;
            else if (fmin > fcurrent)
                fmin = fcurrent;
            // Get Button state (not working yet)
            //b8buttonstate = ! (PORTB & (1<<10));
            if (b8buttonstate)
                u8butcnt++;
            // Make sure button was pressed long enough
            if (b8buttonstate && u8butcnt > 10)
            {
                fmax = fcurrent;
                fmin = fcurrent;
                u8butcnt = 0;
            }
            // Display the Voltage using the LEDs
            if (buse_lights)
            {
                for (u8c = 0; u8c < u8leds; u8c++)
                {
                    float led_min = 3.3f/u8leds*u8c-.2;
                    float led_max = 3.3f/u8leds*u8c+.2;

                    if (fcurrent > led_max)
                        LED (apvu16leds_conf[u8c], apvu16leds_ports[u8c], au8leds_offsets[u8c], OFF);
                    else if (fcurrent > led_min)
                        LED (apvu16leds_conf[u8c], apvu16leds_ports[u8c], au8leds_offsets[u8c], ON);
                    else
                        LED (apvu16leds_conf[u8c], apvu16leds_ports[u8c], au8leds_offsets[u8c], OFF);
                }
            }
            sprintf (pac8buf, "%4.3f Min: %4.3f\n      Max: %4.3f", fcurrent, fmin, fmax);
            break;
        // Ohm-Meter
        case MODE_OHM:
            // Configure unused Resistor pins as floating -> inputs
            for (u8c = 0; u8c < RiNum; u8c++)
                *(RiPins[u8c]) |= (1<<RiOffsets[u8c]);

            // Configure the Resistor pin of choice to be an output
            *(RiPins[u8choice]) &= ~(1<<RiOffsets[u8choice]);
            *(RiPorts[u8choice]) |= (1<<RiOffsets[u8choice]);

            // Get Voltage on resistor
            u16res = u16ADCread ();
            fcurrent = (float)u16res/4095*VCC;

            // Calculate resistor Value
            float fRx = Ri[u8choice] / (4095/(float)u16res - 1);
            // Resistor nearly infinite?
            if (fRx > 100000000)
                sprintf (pac8buf, "%4.3f V        %1u\n---------", fcurrent, u8choice);
            else
            {
                if (fRx > 100000)
                    sprintf (pac8buf, "%4.3f V        %1u\n%6.2f M", fcurrent, u8choice, fRx/1000000);
                else if (fRx > 1100)
                    sprintf (pac8buf, "%4.3f V        %1u\n%6.2f k", fcurrent, u8choice, fRx/1000);
                else
                    sprintf (pac8buf, "%4.3f V        %1u\n%7.3f  ", fcurrent, u8choice, fRx);
                // Ohm symbol
                pac8buf[25] = 0x1E;
                pac8buf[26] = 0;
            }

            // Select a better resistor, if necessary
            switch (u8choice)
            {
                case 0:
                    if (fRx > 20000)
                        u8choice = 1;
                    break;
                case 1:
                    if (fRx < 7000)
                        u8choice = 0;
                    else if (fRx > 200000)
                        u8choice = 2;
                    break;
                case 2:
                    if (fRx < 70000)
                        u8choice = 1;
                    break;
                default:
                    u8choice = 2;
                    break;
            }
            break;
        // Capacity-Meter
        case MODE_CAP:
            // Configure unused Resistor pins as floating -> inputs
            for (u8c = 0; u8c < RiNum; u8c++)
                *(RiPins[u8c]) |= (1<<RiOffsets[u8c]);
            // Configure the Resistor pin of choice to be an output
            *(RiPins[u8choice]) &= ~(1<<RiOffsets[u8choice]);
            *(RiPorts[u8choice]) &= ~(1<<RiOffsets[u8choice]); // 0 Volt
            // Wait for the Capacity to be (almost) fully discharged
            while (u16res > 15)
                u16res = u16ADCread ();
            // Stop Time from now on
            TMR1 = 0;
            // 3.3 Volt to Capacity
            *(RiPorts[u8choice]) |= (1<<RiOffsets[u8choice]);
            // Wait for the Capacity to be 66,6% charged
            while (u16res < 2482)
                u16res = u16ADCread ();
            // Was there a capacity to be measured?
            if (TMR1 > 10)
            {
                // Calculate the Time in milliseconds
                float ftime = (float) TMR1 / K_1MS;
                // Calculate the Capacity in nF
                float fcap = ftime / (Ri[u8choice] * 0.931558f) * 1000000;

                // Display information to the user
                sprintf (pac8buf, "%4.2f V         %1d\n%5.1f nF   %5u", fcurrent, u8choice, fcap, TMR1);
                //sprintf (pac8buf, "%4.2f V         %1d\n%5.1f nF", fcurrent, u8choice, fcap);

                // Select a better resistor, if necessary
                switch (u8choice)
                {
                    case 0:
                        if (fcap > 30)
                            u8choice = 1;
                        break;
                    case 1:
                        if (fcap < 5)
                            u8choice = 0;
                        else if (fcap > 300)
                            u8choice = 2;
                        break;
                    case 2:
                        if (fcap < 70)
                            u8choice = 1;
                        break;
                    default:
                        u8choice = 2;
                        break;
                }
            }
            // No capacity connected
            else
                sprintf (pac8buf, "----------------\n----------------");
            break;
        default:
            return;
    }
}
/** @} */
