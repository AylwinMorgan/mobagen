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


  // translate particles to heights + colors
  // iterate through the vector of particles calculating height and adding non particle spaces to frontier
  // particles will have a base height of 1, getting lower as they approach the edge
  // for every space in frontier, set height to slightly less than the average of all adjacent non 0 spaces
  // 

  heightmap.clear();
  frontier.clear();
  for (int i = 0; i < sideSize * sideSize; i++) {
      heightmap.push_back(0);
  }

  for (Particle2D* p : Particle2D::particles) {
  	  int distanceToNearestEdge = sideSize - std::max(abs(sideSize / 2 - p->x), abs(sideSize / 2 - p->y));
	  // height decreases linearly from 1 at the center to 0.5 at the edge
      heightmap[p->x * sideSize + p->y] = (distanceToNearestEdge / float(sideSize))*2;
  }

  // the frontier is pushed outward with height values lowering until everything is filled
  recalculateFrontier(sideSize);
  while (!frontier.empty()){
    for (int i : frontier) {
      int neighbors[4] = {i-1, i-sideSize, i+sideSize, i+1};
	  int validNeighbors = 0;
	  float neighborAvg = 0;
      for (int n : neighbors) {
        if (n > 0 && n < sideSize * sideSize) {
          if (heightmap[n] > 0) {
            validNeighbors++;
            neighborAvg += heightmap[n];
		  }
		}
	  }
      if (validNeighbors > 0) {
      	neighborAvg / validNeighbors;
	  }
      heightmap[i] = neighborAvg - 1/sideSize;
      auto pos = std::find(frontier.begin(), frontier.end(), i);
      if (pos != frontier.end()) {
        frontier.erase(pos);
	  }
	}
    recalculateFrontier(sideSize);
  }

  std::vector<Color32> colors;
  for (int i = 0; i < heightmap.size(); i++) {
    colors.push_back(Color32(heightmap[i] * 255, heightmap[i] * 255, heightmap[i] * 255));
  }
  for (Particle2D* p : Particle2D::particles) {
	delete p;
  }
  Particle2D::particles.clear();
  return colors;
}


void DiffusionLimitedAggregation::recalculateFrontier(int sideSize) {
  for (int i = 0; i < heightmap.size(); i++) {
    if (heightmap[i] != 0) {
      if (i > 0) {
        if (heightmap[i - 1] == 0 && std::find(frontier.begin(), frontier.end(), i - 1) == frontier.end()) {
          frontier.push_back(i - 1);
        }
      }
      if (i >= sideSize) {
        if (heightmap[i - sideSize] == 0 && std::find(frontier.begin(), frontier.end(), i - sideSize) == frontier.end()) {
          frontier.push_back(i - sideSize);
        }
      }
      if (i < heightmap.size() - sideSize) {
        if (heightmap[i + sideSize] == 0 && std::find(frontier.begin(), frontier.end(), i + sideSize) == frontier.end()) {
          frontier.push_back(i + sideSize);
        }
      }
      if (i < heightmap.size() - 1) {
        if (heightmap[i + 1] == 0 && std::find(frontier.begin(), frontier.end(), i + 1) == frontier.end()) {
          frontier.push_back(i + 1);
        }
      }
    }
  }
}

std::string DiffusionLimitedAggregation::GetName() { return "Diffusion-limited aggregation"; }