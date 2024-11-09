#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

struct Point2DWithDist {
  Point2D point = Point2D(0,0);
  int accDistance = 0;
  int heuristicDistance = 0;

  bool operator<(const Point2DWithDist& rhs) const { 
    return (accDistance + heuristicDistance > rhs.accDistance + rhs.heuristicDistance);
  }
};

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<Point2DWithDist> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  Point2DWithDist catPos;
  catPos.point = w->getCat();
  catPos.accDistance = 0;
  catPos.heuristicDistance = getManhattanDistanceToBorder(catPos.point,w);

  frontier.push(catPos);
  frontierSet.insert(catPos.point);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points
  
  

  while (!frontier.empty()) {
    Point2DWithDist current = frontier.top();
    frontier.pop();
    // get the current from frontier
    // remove the current from frontierset
    frontierSet.erase(current.point);
    // mark current as visited
    visited[current.point] = true;
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors;
    std::vector<Point2D> visitableNeighbors;

    neighbors = w->neighbors(current.point);

    for (int i = 0; i < neighbors.size(); i++) {
      if (!w->isValidPosition(neighbors[i])) {
        borderExit = current.point;
      }
        // point is not cat                 // point has no wall              // point is not in queue            // point has not been visited
      else if (w->getCat() != neighbors[i] && !w->getContent(neighbors[i]) && !frontierSet.contains(neighbors[i]) && !visited[neighbors[i]]) {
        visitableNeighbors.push_back(neighbors[i]);
        cameFrom[neighbors[i]] = current.point;
        Point2DWithDist newPoint;
        newPoint.point = neighbors[i];
        newPoint.accDistance = current.accDistance + 1;
        newPoint.heuristicDistance = getManhattanDistanceToBorder(newPoint.point, w);

        frontier.push(newPoint);
        frontierSet.insert(neighbors[i]);
      }
    }
    
    // iterate over the neighs:
    
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    if (borderExit != Point2D::INFINITE) {
      break;
    }
  }
  vector<Point2D> path;
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  if (borderExit != Point2D::INFINITE) {
    path.push_back(borderExit);
    bool hasReachedCat = false;
    int maxIterations = 500;
    int iterations = 0;
    Point2D currentPoint = borderExit;
    while (!hasReachedCat && iterations < maxIterations) {
      if (w->getCat() == cameFrom[currentPoint]) {
        hasReachedCat = true;
      }
      else {
        currentPoint = cameFrom[currentPoint];
        path.push_back(currentPoint);
        iterations++;
      }
    }
  }
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}

// heuristic function for A* pathfinding
int Agent::getManhattanDistanceToBorder(Point2D point,World* world) { 
    if (abs(point.x) > abs(point.y)) {
        return world->getWorldSideSize()/2 - abs(point.x);
    }
    else {
      return world->getWorldSideSize() / 2 - abs(point.y);
    }
}