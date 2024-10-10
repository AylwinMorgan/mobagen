#include "Catcher.h"
#include "World.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>

Point2D Catcher::Move(World* world) {
  // first check if cat is one step from winning and fill in the winning space if needed
  // otherwise check if the cat is two steps from winning on a tile that has less than 2 filled border neighbors, fill if needed
  // otherwise check if there is a border space with no border neighbors, if there is, fill the closest one
  // otherwise fill the cats target (closest border tile) if one is reachable
  // otherwise fill randomly

  // watch out for corners, they require special logic
  
  vector<Point2D> catPath = generatePath(world);
  Point2D catTarget = Point2D(0,0);
  if (!catPath.empty()) {
    catTarget = catPath.front();
    if (catPath.size() == 1) {
      return catTarget;
    }
    
    vector<Point2D> borders = world->getBorderSpaces();
    int targetBorderIndex = world->getBorderIndex(catTarget);
    int numberOfBorders = borders.size();

    // returns the tile before the exit if the exit is adjacent to one of the corners (disregarding the true left corners because they cannot be
    // reached) this prevents the catcher from getting tricked on the corners
    if (abs(catPath[1].x) == world->getWorldSideSize() / 2 - 1 && abs(catPath[1].y) == world->getWorldSideSize() / 2 - 1) {
      return catPath[1];
    }

    if (catPath.size() == 2) {
      for (int i = -2; i <= 2; i++) {
        Point2D point = borders[(targetBorderIndex + numberOfBorders + i) % numberOfBorders];
        if (point == catTarget) {
          continue;
        }
        if (!world->getContent(point) && world->isNeighbor(point, catPath[1])) {
          return catPath[1];
        }
      }
    }

    for (int i = 0; i < numberOfBorders; i++) {
      int baseIndex = i / 2 * pow(-1, i) + numberOfBorders;
      if (world->getContent(borders[(baseIndex + targetBorderIndex) % numberOfBorders])) {
        continue;
      }
      int numberOfAdjacentBorderWalls = 0;
      if (world->getContent(borders[(baseIndex + targetBorderIndex - 1) % numberOfBorders])) {
        numberOfAdjacentBorderWalls++;
      }
      if (world->getContent(borders[(baseIndex + targetBorderIndex + 1) % numberOfBorders])) {
        numberOfAdjacentBorderWalls++;
      }
      if (numberOfAdjacentBorderWalls == 0
          || (numberOfAdjacentBorderWalls < 2 && borders[(targetBorderIndex + baseIndex) % numberOfBorders] == catTarget && catPath.size() == 2)) {
        return borders[(targetBorderIndex + baseIndex) % numberOfBorders];
      }
    }

    if (catTarget != Point2D(0, 0)) {
      return catTarget;
    }
  }
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}