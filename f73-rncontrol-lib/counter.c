#include <stdint.h>
#include <avr/io.h>
#include <stdbool.h>

#include "counter.h"
#include "bitops.h"

/**
 * Start the counter:
*/
void counter0Start(uint8_t prescaler) {
    TCCR0 = (TCCR0 & 0b11111000) | prescaler; 
}

void counter1Start(uint8_t prescaler) {
    TCCR1B = (TCCR1B & 0b11111000) | prescaler;
}

void counter2Start(uint8_t prescaler) {
    TCCR2 = (TCCR2 & 0b11111000) | prescaler;
}

/**
 * Stop the counter:
*/
void counter0Stop() {
    TCCR0 = (TCCR0 & 0b11111000); // set prescaler pattern to all-zero
}

void counter1Stop() {
    TCCR1B = (TCCR1B & 0b11111000);
}

void counter2Stop() {
    TCCR2 = (TCCR2 & 0b11111000);
}

/**
 * Get counter value:
*/
uint8_t counter0GetValue() {
    return TCNT0;
}

uint16_t counter1GetValue() {
    return TCNT1;
}

uint8_t counter2GetValue() {
    return TCNT2;
}

/**
 * Set counter value:
*/
void counter0SetValue(uint8_t val) {
    TCNT0 = val;
}

void counter1SetValue(uint16_t val) {
    TCNT1 = val;
}

void counter2SetValue(uint8_t val) {
    TCNT2 = val;
}

/**
 * Check overflow flag:
*/
bool counter0HasOverflow() {
    //return (TIFR & (1 << TOV0));
    return isBitSet(TIFR, TOV0);
}

bool counter1HasOverflow() {
    return isBitSet(TIFR, TOV1);
}

bool counter2HasOverflow() {
    return isBitSet(TIFR, TOV2);
}

/**
 * Clear overflow flag:
*/
void counter0ClearOverflow() {
    setBit(TIFR, TOV0);
}

void counter1ClearOverflow() {
    setBit(TIFR, TOV1);
}

void counter2ClearOverflow() {
    setBit(TIFR, TOV2);
}

/**
 * Enable overflow interrupt:
*/

void counter0EnableOverflowInterrupt() {
    setBit(TIMSK, TOIE0); 
}

void counter1EnableOverflowInterrupt() {
    setBit(TIMSK, TOIE1);
}

void counter2EnableOverflowInterrupt() {
    setBit(TIMSK, TOIE2);
}

/**
 * Disable overflow interrupt:
*/

void counter0DisableOverflowInterrupt() {
    clrBit(TIMSK, TOIE0);
}

void counter1DisableOverflowInterrupt() {
    clrBit(TIMSK, TOIE1);
}

void counter2DisableOverflowInterrupt() {
    clrBit(TIMSK, TOIE2);
}

void counter0SetCompare(uint8_t val) {
    OCR0 = val;
}

void counter1SetCompare(uint16_t val) {
    OCR1A = val;
}

void counter2SetCompare(uint8_t val) {
    OCR2 = val;
}

void counter0EnableCompareMatchInterrupt() {
    setBit(TIMSK, OCIE0);
}

void counter1EnableCompareMatchInterrupt() {
    setBit(TIMSK, OCIE1A);
}

void counter2EnableCompareMatchInterrupt() {
    setBit(TIMSK, OCIE2);
}

void counter0DisableCompareMatchInterrupt() {
    clrBit(TIMSK, OCIE0);
}

void counter1DisableCompareMatchInterrupt() {
    clrBit(TIMSK, OCIE1A);
}

void counter2DisableCompareMatchInterrupt() {
    clrBit(TIMSK, OCIE2);
}