#include "MersenneRNG.h"

void initializeState(State* state, uint32_t seed) {
  uint32_t* stateArray = state->getStateArray();
  stateArray[0] = seed;
  
  for (int i = 1; i < n; i++) {
    seed = g * (seed ^ (seed >> (w - 2))) + i;
    stateArray[i] = seed;
  }

  state->setStateIndex(0);
}

uint32_t randomInt32(State* state) { 
  uint32_t* stateArray = state->getStateArray();

  int stateIndex = state->getStateIndex();

  int j = stateIndex - (n - 1);
  if (j < 0) {
    j += n;
  }

  uint32_t x = (stateArray[stateIndex] & UMASK) | (stateArray[j] & LMASK);
  uint32_t xRightShift = x >> 1;
  if (x & 0x00000001UL) {
    xRightShift ^= a;
  }

  j = stateIndex - (n - m);
  if (j < 0) {
    j += n;
  }

  x = stateArray[j] ^ xRightShift;
  stateArray[stateIndex++] = x;

  if (stateIndex > n) {
    stateIndex = 0;
  }
  state->setStateIndex(stateIndex);

  uint32_t y = x ^ (x >> u);
  y = y ^ ((y << s) & b);
  y = y ^ ((y << t) & c);
  uint32_t result = y ^ (y >> 1);

  return result;
}