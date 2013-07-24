#include "types.h"
#include "adc.h"
#include <p24HJ64GP502.h>

// The AD-Channel to be used by the ADC (e.g. AN5)
#define ADCH 5

void ADCinit ()
{
    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0;
    AD1CON4 = 0;
    AD1CHS123 = 0;
    AD1CON1bits.AD12B = 1; // 12-Bit-Mode
    AD1CON1bits.SSRC = 7; // Auto-Convert
    // AD1CON1bits.FORM = 3; // Integer Mode
    // AD1CON1bits.ASAM = 1; // Enable SAMP-Bit
    AD1CON3bits.ADRC = 1;
    AD1CON3bits.SAMC = 31;
    _AD1IE = 0;

    TRISB |= (1<<3);

    AD1CON1bits.ADON = 1;
}

uint16_t u16ADCread ()
{
    AD1PCFGL &= ~(1<<ADCH); // Use PIN in analog mode
    AD1CHS0 = ADCH;
    // select analog input channel
    // start sampling, automatic conversion will follow
    AD1CON1bits.SAMP = 1;
    while (!AD1CON1bits.DONE);		 // wait to complete conversion
    return ADC1BUF0;		 // read the conversion result
}
