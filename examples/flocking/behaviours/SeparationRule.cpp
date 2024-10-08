#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  
    
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();
  float desiredDistance = desiredMinimalDistance;
  
  float forceScalar = 0.4f;
  // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  if (!neighborhood.empty()) {
    Vector2f position = boid->transform.position;
    int countCloseFlockmates = 0;
    for (Boid* b : neighborhood) {
      Vector2f force = position - b->transform.position;
      float distance = force.getMagnitude();
      if (distance < desiredDistance && distance > 0.01f) {
        force = Vector2f::normalized(force) / (distance / desiredDistance);
        separatingForce += force;
      } 
      else if (distance == 0){
        return Vector2f::zero();
      }
    }
  }

  return separatingForce * forceScalar;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
