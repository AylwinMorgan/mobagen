#include "MersenneRNG.h"

void initializeState(State* state, uint32_t seed) {
  uint32_t* stateArray = &(state->stateArray[0]);
  stateArray[0] = seed;
  
  for (int i = 1; i < n; i++) {
    seed = f * (seed ^ (seed >> (w - 2))) + i;
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

}