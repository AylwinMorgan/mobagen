#pragma once
#include "../GeneratorBase.h"
#include <Random>
#include "../Particle2D.h"

class DiffusionLimitedAggregation : public ScenarioGeneratorBase {
	public:
		std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
        std::string GetName() override;
};