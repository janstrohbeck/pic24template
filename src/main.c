/** @defgroup main Main Program
 *  This module contains the main function.
 *  @{
 */
/**
 * @file
 * @author Jan Strohbeck
 * @version 1.0
 * @date 2013-05-23
 * @brief Main Program
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
#include <p24HJ64GP502.h>
#include <math.h>
#include "PIC24HJ64GP502init.h"
#include "types.h"
#include "utils.h"
#include "lcd.h"
#include "timer.h"
#include "leds.h"
#include "multimeter.h"
#include "adc.h"
#include "interrupts.h"

// Sample string for lcd_display_long_string
// c8_t ac8string[] = "Hello World!\n\nThis is just\na simple text\nto attract your\nattention";

uint32_t u32ms_ticker = 0;

int main (void)
{
    // Initialize hardware (with PLL enabled)
    init (true);
    // Initialise Interrupts
    interrupt_init ();
    // Setup Timer1
    timer1_init (false);
    // Setup Timer2
    timer2_init (true);
    // Setup the AD-Converter
    ADCinit ();
    // Setup SPI
    spi_init ();
    // Initialize the LCD-Display
    lcd_init ();

    // Turn on display, but disable cursor and position marker
    lcd_conf_display (ON, OFF, OFF);

    // Configure LED1
    LED1 (ENABLED);
    LED1 (OFF);


    uint8_t u8count;
    // Configure all LEDs as Outputs + Off
    for (u8count = 0; u8count < u8leds; u8count++)
    {
        LED (apvu16leds_conf[u8count], apvu16leds_ports[u8count], au8leds_offsets[u8count], ENABLED);
        LED (apvu16leds_conf[u8count], apvu16leds_ports[u8count], au8leds_offsets[u8count], OFF);
    }

    // The character array which is sent to the display
    c8_t ac8buf[50];

    // The measuring-mode in use
    uint8_t u8mode = 0;
    // If the mode-switch-button has been pressed
    bool bbut_pressed = false;

    // Reference execution point for main loop
    uint32_t u32reference = 0;

    while (true)
    {
        if ((int32_t) (u32reference - u32ms_ticker) < 0)
        {
            // Set reference point 100ms into the future
            u32reference += 100;

            if (button_is_pressed (&TRISB, &PORTB, 10))
                bbut_pressed = true;
            // Switch mode when button is released
            else if (bbut_pressed)
            {
                u8mode++;
                u8mode %= 3;
                bbut_pressed = false;
            }
            // Set cursor to first row, first column
            lcd_set_cursor (0,0);
            multimeter (ac8buf, u8mode, false);
            // Send the character-array to the display
            lcd_display_string (ac8buf);

            running_light (true);
        }
    }
    return 0;
}
/** @} */
