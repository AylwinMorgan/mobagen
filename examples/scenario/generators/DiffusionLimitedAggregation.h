#include "../GeneratorBase.h"
#include <Random>;

class DiffusionLimitedAggregation : ScenarioGeneratorBase {
	public:
		std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
        std::string GetName() override;
};