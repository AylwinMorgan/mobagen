#include "MersenneRNG.h"
#include <iostream>

int main() { 
  int lowerBound = 0;
  int upperBound = 100;
  int numbersToGenerate = 100;
  State* state = new State;
  uint32_t seed = time(0);
  initializeState(state, seed);

  for (int i = 0; i < 100; i++) {
    std::cout << lowerBound + randomInt32(state)%(upperBound-lowerBound+1) << std::endl;
  }
}
