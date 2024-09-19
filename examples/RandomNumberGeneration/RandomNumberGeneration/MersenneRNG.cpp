#include "MersenneRNG.h"

void initializeState(State* state, uint32_t seed) {
  uint32_t* stateArray = &(state->stateArray[0]);
  stateArray[0] = seed;
  
  for (int i = 1; i < n; i++) {
    seed = g * (seed ^ (seed >> (w - 2))) + i;
    stateArray[i] = seed;
  }

  state->stateIndex = 0;
}

uint32_t randomInt32(State* state) { 
  uint32_t* stateArray = &(state->stateArray[0]);

  int k = state->stateIndex;

  int j = k - (n - 1);
  if (j < 0) {
    j += n;
  }

  uint32_t x = (stateArray[k] & UMASK) | (stateArray[j] & LMASK);
  uint32_t xA = x >> 1;
  if (x & 0x00000001UL) {
    xA ^= a;
  }

  j = k - (n - m);
  if (j < 0) {
    j += n;
  }

  x = stateArray[j] ^ xA;
  stateArray[k++] = x;

  if (k > n) {
    k = 0;
  }
  state->stateIndex = k;

  uint32_t y = x ^ (x >> u);
  y = y ^ ((y << s) & b);
  y = y ^ ((y << t) & c);
  uint32_t z = y ^ (y >> 1);

  return z;
}