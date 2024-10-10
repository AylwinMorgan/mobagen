#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  if (!path.empty()) {
    return path.back();
  }
  vector<Point2D> neighbors = world->neighbors(world->getCat());
  vector<Point2D> visitableNeighbors;
  for (Point2D n : neighbors) {
    if (!world->getContent(n)) {
      visitableNeighbors.push_back(n);
    }
  }
  auto rand = Random::Range(0, visitableNeighbors.size() - 1);
  return visitableNeighbors[rand];
}
