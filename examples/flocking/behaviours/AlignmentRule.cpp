#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  float forceScalar = 3.0f;

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  for (Boid* b : neighborhood) {
    averageVelocity += b->getVelocity();
  }
  if (neighborhood.size() != 0) {
    averageVelocity /= neighborhood.size();
  }
  return Vector2f::normalized(averageVelocity) * forceScalar;
}