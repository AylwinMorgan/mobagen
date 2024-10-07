#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

class Catcher : public Agent {
public:
  explicit Catcher() : Agent(){};
  Point2D Move(World*) override;
  int getAdjacentWalledBorders(Point2D point, World* world);
};

#endif  // CATCHER_H
