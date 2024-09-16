#pragma once
#include <stdint.h>

#define n 624
#define m 397
#define w 32
#define r 31
#define UMASK (0xffffffffUL << r)
#define LMASK (0xffffffffUL >> (w - r))
#define a 0x9908b0dfUL
#define u 11
#define s 7
#define t 15
#define l 18
#define b 0x9d2c5680UL
#define c 0xefc60000UL
#define f 1812433253UL


typedef struct {
  uint32_t stateArray[624];
  int stateIndex;
} State;

void initializeState(State* state, uint32_t seed);

uint32_t randomInt32(State* state);