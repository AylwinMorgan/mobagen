#include "../GeneratorBase.h"

// reference: https://www.youtube.com/watch?v=gsJHzBTPG0Y
class DiffusionalLimitedAggregation : ScenarioGeneratorBase {
	// 0. start with a small grid
	// 1. place a singe pixel at center of grid
	// 2. add another pixel at a random position
	// 3. move it randomly until it is adjacent to other pixel (pick a random spot on frontier)
	// 4. repeat steps 2 and 3 as many times as desired
	// 5. if grid is sufficiently populated, expand and repeat 2-4
	// 6. set outermost cells to be height of 1
	// 7. cells closer to center are higher
};