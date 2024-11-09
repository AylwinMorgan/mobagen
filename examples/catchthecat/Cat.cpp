#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  // if a path to the exit is found, the cat will follow it
  if (!path.empty()) {
    return path.back();
  }
  // otherwise it will move to a random open space
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
