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

  // watch out for top and bottom right corners, they require special logic

  vector<Point2D> catPath = generatePath(world);
  Point2D catTarget = catPath.back();
  vector<Point2D> borders = world->getBorderSpaces();
  int targetBorderIndex = world->getBorderIndex(catTarget);
  int numberOfBorders = borders.size();
  int numberOfAdjacentWalls = 0;
  

  if (catPath.size() == 1) {
    return catTarget;
  }
  if (catPath.size() == 2) {
    int numberOfAdjactentBorderWalls = 0;
    if (world->getContent(borders[(targetBorderIndex - 1) % numberOfBorders])) {
      numberOfAdjactentBorderWalls++;
    }
    if (world->getContent(borders[(targetBorderIndex + 1) % numberOfBorders])) {
      numberOfAdjactentBorderWalls++;
    }
    if (numberOfAdjactentBorderWalls < 2) {
      return catTarget;
    }
  }
  for (int i = 0; i < numberOfBorders; i++) {
    
  }
  }


  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}

int Catcher::getAdjacentWalledBorders(Point) {}