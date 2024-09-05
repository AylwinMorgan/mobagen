#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f centerOfMass = Vector2f::zero();
  float forceScalar = 4.0f;
  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  // find center of mass
  float distance;
  if (!neighborhood.empty()) {
    for (Boid* b : neighborhood) {
      centerOfMass += b->transform.position;
    }
    centerOfMass /= neighborhood.size();
    cohesionForce = centerOfMass - boid->transform.position;
    distance = cohesionForce.getMagnitude();
    cohesionForce = Vector2f::normalized(cohesionForce) * (distance/boid->getDetectionRadius());
  }

  return cohesionForce * forceScalar;
}