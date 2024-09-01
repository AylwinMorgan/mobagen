#include "WindRule.h"
#include <imgui.h>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // todo: add a wind force here
  Vector2 windForce = Vector2f::zero();
  // hint: use the windAngle variable
  if (isEnabled) {
    windForce.x = cos(windAngle);
    windForce.y = sin(windAngle);
  }
  return Vector2f::normalized(windForce);
}

bool WindRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::SliderAngle("Wind Direction", &windAngle, 0)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}