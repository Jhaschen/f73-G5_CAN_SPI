#include "button.h"
#include "bitops.h"
#include "adc.h"

#include <stdint.h>
#include <avr/io.h>


void buttonInit() {
    // set PA7 to input
    clrBit(DDRA, 7);

    // pull-up enable
    setBit(PORTA, 7);

    // init ADC
    adcInit();
} 

int8_t buttonRead() {
    uint16_t valArray[10];
    for (int i = 0; i < sizeof(valArray)/sizeof(valArray[0]); i++) {
        valArray[i] = adcRead(7);
    }

    int sorted = 0;
    int run = 0;
    while(!sorted) {
        sorted = 1;
        for (int i = 0; i + run + 1 < sizeof(valArray)/sizeof(valArray[0]); i++) {
            if (valArray[i] > valArray[i+1]) {
                uint16_t temp = valArray[i];
                valArray[i] = valArray[i+1];
                valArray[i+1] = temp;
                sorted = 0;
            }
        }
    }

    if (valArray[5] >= 390 && valArray[5] <= 420) return 1;
    if (valArray[5] >= 320 && valArray[5] <= 380) return 2;
    if (valArray[5] >= 250 && valArray[5] <= 280) return 3;
    if (valArray[5] >= 175 && valArray[5] <= 205) return 4;
    if (valArray[5] >= 95 && valArray[5] <= 125) return 5;
    return -1;
}