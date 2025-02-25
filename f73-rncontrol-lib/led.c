#include "bitops.h"
#include "led.h"

#include <avr/io.h>

void ledInit() {
    DDRC = 0xFF;
    PORTC = 0xFF;
}


void ledSet(int id) {
    if (id < 1 || id > 8) return;  
    PORTC = PORTC & ~(1 << (id-1));
    // Alternativ: clrBit(PORTC, id - 1);

    // Zur Erklärung:
    // Bsp.: PORTC is 0b00110001
    // Schritt 1: Bitverschiebung um "bit" Stellen: (1 << bit)
    // Bsp.: bit == 4:
    // (1 << 4) == 0b00010000
    // Schritt 2: Negation dieses Bitmusters:
    // ~(1 << 4) == 0b11101111
    // Schritt 3: Undverknüpfung der beiden Bitmuster: 
    // 0b00110001 & ~(1 << 4) == 0b00100001;
    //PORTC &= ~(1 << (id-1))
}

void ledClear(int id) {
    if (id < 1 || id > 8) return;
    PORTC = PORTC | (1 << (id - 1));
    // Alternativ: setBit(PORTC, id - 1);
    // Bsp.: PORTC is 0b00110001
    // Schritt 1: Bitverschiebung um "bit" Stellen: (1 << bit)
    // Bsp.: bit == 3:
    // (1 << 3) == 0b00001000
    // andere Beispiele zur Verdeutlichung vom Bit-Shift:
    // (3 << 3) == 0b00011000
    // (5 << 4) == 0b01010000
    // Schritt 2: Veroderung des alten Bitmusters mit dem gerade erzeugten:
    // 0b00110001 | (1 << 3) == 0b00111001;
    // Geht auch mehrfach:
    // PORTC = PORTC | (1 << bit) | (1 << anderesBit);
}

void ledToggle(int id) {
    if (id < 1 || id > 8) return;
    PORTC = PORTC ^ (1 << (id - 1));
    // Alternativ: tglBit(PORTC, id - 1);
}