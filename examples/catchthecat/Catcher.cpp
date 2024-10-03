#include "Catcher.h"
#include "World.h"

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




  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
