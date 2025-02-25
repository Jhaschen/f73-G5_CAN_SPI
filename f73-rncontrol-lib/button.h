#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/**
 * Sets internal pull-up resistor @PA7 for button readings. 
*/
void buttonInit(void);

/**
 * Read button status.
 * Returns -1 if no button is pressed and no. of bpressed button otherwise.
 * Pressing multiple buttons at once is currently unsupported. 
*/
int8_t buttonRead(void);

#ifdef __cplusplus
}
#endif