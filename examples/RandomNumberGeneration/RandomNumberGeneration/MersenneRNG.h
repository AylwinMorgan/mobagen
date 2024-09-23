#pragma once
#include <stdint.h>

#define n 624
#define m 397
#define w 32
#define r 31
#define UMASK (0xfffffff << r)
#define LMASK (0xfffffff >> (w - r))
#define a 0x9908b0dfUL
#define u 11
#define s 7
#define t 15
#define l 18
#define b 0x9d2c5680UL
#define c 0xefc60000UL
#define g 1812433253UL

class State {
public:
  State(){};
  ~State(){};
  uint32_t* getStateArray() { return stateArray; };
  void setStateArray(int index, uint32_t value) { stateArray[index] = value; };
  int getStateIndex() { return stateIndex; };
  void setStateIndex(int value) { stateIndex = value; };

private:
  uint32_t stateArray[n];
  int stateIndex = 0;
};
void initializeState(State* state, uint32_t seed);

uint32_t randomInt32(State* state);