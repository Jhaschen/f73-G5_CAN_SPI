#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * F73 -- Helper API for RNControl Board with ATmega32
*/

/**
 * Init DDRC for LED usage and switch all LEDs to off-state.
*/
void ledInit(void);

/**
 * Set LED with id (range: 1 ... 8) to on-state, i.e. illuminated.
*/
void ledSet(int id);

/**
 * Set LED with id (range: 1 ... 8) to off-state, i.e. dark.
*/
void ledClear(int id);

/**
 * Toggle LED state with id (range: 1 ... 8).
*/
void ledToggle(int id);

#ifdef __cplusplus
}
#endif