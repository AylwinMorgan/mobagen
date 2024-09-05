#include "MouseInfluenceRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f MouseInfluenceRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  ImGuiIO& io = ImGui::GetIO();
  if (ImGui::IsMousePosValid() && io.MouseDown[0]) {
    float forceScalar = 20.0f;
    Vector2f mousePos(io.MousePos.x, io.MousePos.y);
    Vector2f displacement = mousePos - boid->getPosition();

    if (isRepulsive)
        displacement *= -1.f;
    return Vector2f::normalized(displacement) * forceScalar;
  }
  return Vector2f::zero();
}

bool MouseInfluenceRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;

  if (ImGui::RadioButton("Attractive", !isRepulsive)) {
    isRepulsive = false;
    valueHasChanged = true;
  }

  ImGui::SameLine();
  if (ImGui::RadioButton("Repulsive", isRepulsive)) {
    isRepulsive = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}