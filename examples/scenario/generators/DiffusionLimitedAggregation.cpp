#include "DiffusionLimitedAggregation.h"

// reference: https://www.youtube.com/watch?v=gsJHzBTPG0Y
// 0. start with a small grid (sidesize 5)
// 1. place a single frozen pixel at center of grid
// 2. add pixel at random position
// 3. move it randomly until it is adjacent to frozen pixel and freeze it
// 4. repeat step 3 until a frozen particle is adjacent to edge (x or y equals 0 or sideSize)
// 5. expand grid by 5 (up to max sideSize) and repeat 2-4
// 6. set outermost cells to be height of 1
// 7. cells closer to center are higher

std::vector<Color32> DiffusionLimitedAggregation::Generate(int sideSize, float displacement) {
  int particleDeviation = 2;
  // start with a 'seed' particle in the center of the grid to build off of
  Particle2D* center = Particle2D::Particle2DFixed(particleDeviation + 1, particleDeviation + 1);
  Particle2D::particles.push_back(center);
  center->frozen = true;
  while (particleDeviation * 2 + 1 < sideSize + 1) {
    if (particleDeviation > 2) {
      Particle2D::scaleVectorUp();
	}
    // create particles within 'particleDeviation' units of the center of the grid
    for (int i = 0; i < particleDeviation * 2; i++) {
      Particle2D* p = new Particle2D(particleDeviation);
      Particle2D::particles.push_back(p);
	}
	bool allFrozen = false;
    while (!allFrozen) {
	  allFrozen = true;
      for (Particle2D* p : Particle2D::particles) {
        p->update();
        //if (p->frozen && (p->x == Particle2D::minSize || p->x == Particle2D::maxSize || p->y == Particle2D::minSize || p->y == Particle2D::maxSize)) {
        if (!p->frozen){
		  allFrozen = false;
        }
      }
	}
    particleDeviation*=2;
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