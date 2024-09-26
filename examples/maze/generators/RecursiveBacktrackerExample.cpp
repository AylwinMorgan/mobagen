#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  if (stack.empty()) {
    int min = -w->GetSize() / 2;
    stack.push_back(Point2D(min,min));
  }
  else {
    Point2D point = stack.back();
    w->SetNodeColor(point, Color32(255, 50, 50, 255));
    std::vector<Point2D> neighbors = getVisitables(w,point);
    visited[point.x][point.y] = true;
    if (!neighbors.empty()) {
      int directionIndex = rand() % neighbors.size();
      Point2D newPoint = neighbors[directionIndex];
      if (point + point.UP == newPoint) {
        w->SetNorth(point, true);
      } 
      else if (point + point.DOWN == newPoint){
        w->SetSouth(point, true);      
      } 
      else if (point + point.LEFT == newPoint){
        w->SetWest(point, true);
      }
      else if (point + point.RIGHT == newPoint){
        w->SetEast(point, true);
      }
      stack.push_back(newPoint);
    }
    else {
      w->SetNodeColor(stack.back(),Color32(200,10,10,255));
      stack.pop_back();
    }
  }
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  w->GetNodeColor(p);
  if (!visited[p.x][p.y-1] && p.y > -sideOver2) {
    visitables.push_back(p+p.UP);
  }
  if (!visited[p.x+1][p.y] && p.x < sideOver2) {
    visitables.push_back(p+p.RIGHT);
  }
  if (!visited[p.x-1][p.y] && p.x > -sideOver2) {
    visitables.push_back(p+p.LEFT);
  }
  if (!visited[p.x][p.y+1] && p.y < sideOver2) {
    visitables.push_back(p+p.DOWN);
  }
  // todo: implement this

  return visitables;
}
