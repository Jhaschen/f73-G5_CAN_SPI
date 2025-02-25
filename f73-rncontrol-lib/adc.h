#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * F73 -- Helper API for RNControl Board with ATmega32
*/

/**
 * Init ADC of ATmega32
*/
void adcInit(void);

/**
 * Read a single value from ADC channel. 
*/
uint16_t adcRead(uint8_t channel);

#ifdef __cplusplus
}
#endif