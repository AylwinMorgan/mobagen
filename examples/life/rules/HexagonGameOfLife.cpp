//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) 
{
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      Point2D point = Point2D(i, j);
      if (world.Get(point)) {
        int neighbors = CountNeighbors(world, point);
        if (neighbors < 2 || neighbors > 2) {
          world.SetNext(point, false);
        } 
        else {
          world.SetNext(point, true);
        }
      } 
      else {
        int neighbors = CountNeighbors(world, point);
        if (neighbors == 2) {
          world.SetNext(point, true);
        }
      }
    }
  }
}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {    
  int xOffset = (point.y) % 2;
  int neighbors = 0;
  for (int i = -1; i <= 0; i++) {
    for (int j = -1; j <= 1; j++) {
      int neighborX = i + xOffset * abs(j);
      int neighborY = j;
      if (i == 0 && j == 0) {
        neighborX++;
      }
      Point2D neighbor = Point2D(neighborX, neighborY) + point;
      if (world.Get(neighbor)) {
        neighbors++;
      }
    }
  }
  return neighbors;
}

