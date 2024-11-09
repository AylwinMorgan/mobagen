#pragma once
#include <Random>

class Particle2D {
public:
  static inline std::vector<Particle2D*> particles = {};
  int x;
  int y;
  bool frozen;
  int maxSize;

  Particle2D(int sideSize);
  Particle2D(int pointX, int pointY, int sideSize);
  void update();
  void checkShouldFreeze();
};