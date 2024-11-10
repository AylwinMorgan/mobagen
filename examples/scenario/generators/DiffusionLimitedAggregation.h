#pragma once
#include "../GeneratorBase.h"
#include <Random>
#include "../Particle2D.h"

class DiffusionLimitedAggregation : public ScenarioGeneratorBase {
	public:
		std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
        std::string GetName() override;
	private:
        std::vector<float> heightmap;
		std::vector<int> frontier;
		std::vector<int> visited;
        void recalculateFrontier(int sideSize);
};

class HeightMapTile {
	public:
	  int x, y;
      int height;
	  std::vector<int> getNeighborValues();
};