#pragma once

#define setBit(register, bit) ((register) |= (1 << (bit)))
#define clrBit(register, bit) ((register) &= (~(1 << (bit))))
#define tglBit(register, bit) ((register) ^= (1 << (bit)))
#define isBitSet(register, bit) (1 & ((register) >> (bit)))
#define isBitClr(register, bit) (!(1 & ((register) >> (bit))))
