#include "DiffusionLimitedAggregation.h"

// reference: https://www.youtube.com/watch?v=gsJHzBTPG0Y
// 0. start with a small grid
// 1. place a singe pixel at center of grid
// 2. add another pixel at a random position
// 3. move it randomly until it is adjacent to other pixel (pick a random spot on frontier)
// 4. repeat steps 2 and 3 as many times as desired
// 5. if grid is sufficiently populated, expand and repeat 2-4
// 6. set outermost cells to be height of 1
// 7. cells closer to center are higher

std::vector<Color32> DiffusionLimitedAggregation::Generate(int sideSize, float displacement) {
    std::vector<bool> base;
    for (int x = 0; x < sideSize; x++) {
        for (int y = 0; y < sideSize; y++) {
            base.push_back(false);
        }
    }
    base[base.size() / 2] = true;
    int numberOfPoints = 1;
    int maxNumberOfPoints = sideSize * sideSize / 4;
    bool particleExists = false;
    int pointX = 0;
    int pointY = 0;

    while (numberOfPoints < maxNumberOfPoints) {
      if (particleExists) {
        
      }
    }
    
    std::vector<Color32> colors;
    for (int x = 0; x < sideSize; x++) {
        for (int y = 0; y < sideSize; y++) {
            
        }
    }
    return colors;
}
std::string DiffusionLimitedAggregation::GetName() { return "Diffusion-limited aggregation"; }