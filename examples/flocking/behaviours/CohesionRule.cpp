#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  // find center of mass
  
  if (!neighborhood.empty()) {
    for (Boid* b : neighborhood) {
      cohesionForce += b->transform.position;
    }
    cohesionForce /= neighborhood.size();
    cohesionForce = cohesionForce - boid->transform.position;
  }

  return Vector2f::normalized(cohesionForce);
}