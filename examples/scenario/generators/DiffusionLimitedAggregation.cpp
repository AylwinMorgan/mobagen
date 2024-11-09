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
  for (int i = 0; i < sideSize*sideSize/2; i++) {
    Particle2D* p = new Particle2D(sideSize);
    Particle2D::particles.push_back(p);
  }
  Particle2D* center = new Particle2D(sideSize / 2, sideSize / 2, sideSize);
  Particle2D::particles.push_back(center);

  int maxFrozenCount = sideSize*sideSize/4;
  int frozenCount = 0;
  while (frozenCount < maxFrozenCount) {
    frozenCount = 0;
    for (Particle2D* p : Particle2D::particles) {
      p->update();
      if (p->frozen) {
        frozenCount++;
      }
    }
  }

  std::vector<Color32> colors;
  for (int x = 0; x < sideSize; x++) {
    for (int y = 0; y < sideSize; y++) {
      colors.push_back(Color::Black);
    }
  }
  for (Particle2D* p : Particle2D::particles) {
    if (p->frozen) {
      colors[p->x * sideSize + p->y] = Color::White;
	}
	delete p;
  }
  Particle2D::particles.clear();
  return colors;
}
std::string DiffusionLimitedAggregation::GetName() { return "Diffusion-limited aggregation"; }