#include "adc.h"

#include <stdint.h> 
#include <avr/io.h> 

void adcInit() {
    ADCSRA = (1 << ADEN) | ((1<<ADSC)) | (7 << ADPS0);

    // Wait until first conversion is ready to get rid of first faulty conversion.
    while(ADCSRA & (1<<ADSC)){
        // wait
    }
}

uint16_t adcRead(uint8_t channel) {

    if (channel > 7 ) return 0;

    //set the multiplexer to the according single-ended channel (see datasheet)
    ADMUX = (ADMUX & 0b11100000) | (channel & 0b00011111);

    //Start single mode conversion, turns automaticly to 0 when conversion complete:
    ADCSRA |= (1<<ADSC);

    //wait until the conversion is done and the ADSC bit is changed to 0
    while(ADCSRA & (1<<ADSC)){
        // wait
    }

    return ADCW;
}