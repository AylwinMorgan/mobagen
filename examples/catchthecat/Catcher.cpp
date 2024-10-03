#include "Catcher.h"
#include "World.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>

Point2D Catcher::Move(World* world) {
  // first check if cat is one step from winning
  bool imminentCatWin = false;
  Point2D catPosition = world->getCat();
  Point2D winningPosition;
  std::vector<Point2D> catNeighbors = world->neighbors(catPosition);

  for (int i = 0; i < catNeighbors.size(); i++) {
    if (world->catWinsOnSpace(catNeighbors[i]) && world->catCanMoveToPosition(catNeighbors[i])) {
      imminentCatWin = true;
      winningPosition = catNeighbors[i];
      break;
    }
  }

  if (imminentCatWin) {
    return winningPosition;
  }

  // otherwise find the nearest winning tile that has no walls in an adjacent winning tile
  // find closest exit with generatePath(world)
  // uses a similar search to the cat but it only looks at border tiles (valid cat win points)
  int distanceFromCenter = world->getWorldSideSize() / 2;
  bool hasFoundPoint = false;
  queue<Point2D> frontier;
  unordered_set<Point2D> frontierSet;
  unordered_map<Point2D, bool> visited;
  Point2D nearestEdge;
  if (abs(catPosition.x) < abs(catPosition.y)) {
    nearestEdge = Point2D(catPosition.x,catPosition.y/abs(catPosition.y)*distanceFromCenter);
  }
  else {
    nearestEdge = Point2D(catPosition.x / abs(catPosition.x)*distanceFromCenter, catPosition.y);
  }

  frontier.push(nearestEdge);
  frontierSet.insert(nearestEdge);
  while (!frontier.empty()) {
    Point2D point = frontier.front();
    visited[point] = true;
    frontier.pop();

    vector<Point2D> neighbors = world->neighbors(point);
    

  }



  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}