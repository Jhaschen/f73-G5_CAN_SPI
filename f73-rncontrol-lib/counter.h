#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define ATMEGA32_COUNTER_0_PRESCALER_1 (0x01)
#define ATMEGA32_COUNTER_0_PRESCALER_8 (0x02)
#define ATMEGA32_COUNTER_0_PRESCALER_64 (0x03)
#define ATMEGA32_COUNTER_0_PRESCALER_256 (0x04)
#define ATMEGA32_COUNTER_0_PRESCALER_1024 (0x05)

#define ATMEGA32_COUNTER_1_PRESCALER_1 (0x01)
#define ATMEGA32_COUNTER_1_PRESCALER_8 (0x02)
#define ATMEGA32_COUNTER_1_PRESCALER_64 (0x03)
#define ATMEGA32_COUNTER_1_PRESCALER_256 (0x04)
#define ATMEGA32_COUNTER_1_PRESCALER_1024 (0x05)

#define ATMEGA32_COUNTER_2_PRESCALER_1 (0x01)
#define ATMEGA32_COUNTER_2_PRESCALER_8 (0x02)
#define ATMEGA32_COUNTER_2_PRESCALER_32 (0x03)
#define ATMEGA32_COUNTER_2_PRESCALER_64 (0x04)
#define ATMEGA32_COUNTER_2_PRESCALER_128 (0x05)
#define ATMEGA32_COUNTER_2_PRESCALER_256 (0x06)
#define ATMEGA32_COUNTER_2_PRESCALER_1024 (0x07)

/**
 * Start the counter i with prescaler:
*/
void counter0Start(uint8_t prescaler);
void counter1Start(uint8_t prescaler);
void counter2Start(uint8_t prescaler);

/**
 * Stop the counter:
*/
void counter0Stop(void);
void counter1Stop(void);
void counter2Stop(void);

/**
 * Get counter value:
*/
uint8_t counter0GetValue(void);
uint16_t counter1GetValue(void);
uint8_t counter2GetValue(void);

/**
 * Set counter value:
*/
void counter0SetValue(uint8_t val);
void counter1SetValue(uint16_t val);
void counter2SetValue(uint8_t val);

/**
 * Check overflow flag:
*/
bool counter0HasOverflow(void);
bool counter1HasOverflow(void);
bool counter2HasOverflow(void);

/**
 * Clear overflow flag:
*/
void counter0ClearOverflow(void);
void counter1ClearOverflow(void);
void counter2ClearOverflow(void);

/**
 * Enable overflow interrupt
*/
void counter0EnableOverflowInterrupt(void);
void counter1EnableOverflowInterrupt(void);
void counter2EnableOverflowInterrupt(void);

/**
 * Disable overflow interrupt
*/
void counter0DisableOverflowInterrupt(void);
void counter1DisableOverflowInterrupt(void);
void counter2DisableOverflowInterrupt(void);

/**
 * Set compare value:
*/
void counter0SetCompare(uint8_t val);
void counter1SetCompare(uint16_t val);
void counter2SetCompare(uint8_t val);

/**
 * Enable compare match interrupt
*/
void counter0EnableCompareMatchInterrupt(void);
void counter1EnableCompareMatchInterrupt(void);
void counter2EnableCompareMatchInterrupt(void);

/**
 * Disable compare match interrupt
*/

void counter0DisableCompareMatchInterrupt(void);
void counter1DisableCompareMatchInterrupt(void);
void counter2DisableCompareMatchInterrupt(void);

#ifdef __cplusplus
}
#endif