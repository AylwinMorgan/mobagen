#pragma once
#include <Random>

class Particle2D {
public:
  static inline std::vector<Particle2D*> particles = {};
  int x;
  int y;
  bool frozen;
  bool neighborX = false;
  bool neighborY = false;
  static inline int maxSize = 0;
  static inline int minSize = 0;

  Particle2D(int deviation);
  Particle2D();
  static Particle2D* Particle2DFixed(int pointX, int pointY);
  void update();
  void checkShouldFreeze();
  static void scaleVectorUp();
};