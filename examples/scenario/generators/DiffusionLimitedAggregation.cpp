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
  visited.clear();
  for (int i = 0; i < sideSize * sideSize; i++) {
      heightmap.push_back(0);
  }

  //Particle2D* highestPoint = Particle2D::particles[0];
  for (Particle2D* p : Particle2D::particles) {
  	  int distanceToNearestEdge = abs(sideSize - std::max(abs(sideSize / 2 - p->x), abs(sideSize / 2 - p->y)));
	  // height decreases linearly from 1 at the center to 0.5 at the edge
      heightmap[p->x * sideSize + p->y] = ((distanceToNearestEdge / float(sideSize)));
      //if (heightmap[p->x * sideSize + p->y] > heightmap[highestPoint->x * sideSize + highestPoint->y]) {
          //highestPoint = p;
      //}
      frontier.push_back(p->x * sideSize + p->y);
      visited.push_back(p->x * sideSize + p->y);
  }

  // the frontier is pushed outward with height values lowering until everything is filled
  //frontier.push_back(highestPoint->x * sideSize + highestPoint->y);
  while (!frontier.empty()){
    recalculateFrontier(sideSize);
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
      	neighborAvg /= validNeighbors;
	  }
      heightmap[i] = neighborAvg - 0.005;
	}
  }

  std::vector<Color32> colors;
  for (int i = 0; i < heightmap.size(); i++) {
    if (heightmap[i] < 0.2) {
      colors.push_back(Color32(10, 10, 10));
    } else if (heightmap[i] < 0.5) {
      colors.push_back(Color32(50,50,50));
    } else if (heightmap[i] < 0.7) {
      colors.push_back(Color32(180,180,180));
    } else if (heightmap[i] < 0.9) {
      colors.push_back(Color32(220,220,220));
	} else {
      colors.push_back(Color32(255,255,255));
	}
  }
  for (Particle2D* p : Particle2D::particles) {
	delete p;
  }
  Particle2D::particles.clear();
  return colors;
}


void DiffusionLimitedAggregation::recalculateFrontier(int sideSize) {
  std::vector<int> newFrontier;
  for (int index : frontier) {
    if (heightmap[index] != 0) {
      if (index > 0) {
        if (std::find(visited.begin(), visited.end(), index - 1) == visited.end()) {
          newFrontier.push_back(index - 1);
          visited.push_back(index-1);
        }
      }
      if (index >= sideSize) {
        if (std::find(visited.begin(), visited.end(), index - sideSize) == visited.end()) {
          newFrontier.push_back(index - sideSize);
          visited.push_back(index - sideSize);
        }
      }
      if (index < heightmap.size() - sideSize) {
        if (std::find(visited.begin(), visited.end(), index + sideSize) == visited.end()) {
          newFrontier.push_back(index + sideSize);
          visited.push_back(index + sideSize);
        }
      }
      if (index < heightmap.size() - 1) {
        if (std::find(visited.begin(), visited.end(), index + 1) == visited.end()) {
          newFrontier.push_back(index + 1);
          visited.push_back(index + 1);
        }
      }
    } else {
      newFrontier.push_back(index);
	}
  }
  frontier = newFrontier;
}

std::string DiffusionLimitedAggregation::GetName() { return "Diffusion-limited aggregation"; }