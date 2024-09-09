#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      Point2D point = Point2D(i, j);
      if (world.Get(point)) {
        int neighbors = CountNeighbors(world, point);
        if (neighbors < 2 || neighbors > 3) {
          world.SetNext(point, false);
        }
      }
      else {
        int neighbors = CountNeighbors(world, point);
        if (neighbors == 3) {
          world.SetNext(point, true);
        }
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int neighbors = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        continue;
      } 
      else {
        Point2D neighbor = Point2D(i, j) + point;
        if (world.Get(neighbor)) {
          neighbors++;
        }
      }
    }
  }
  return neighbors;
}
