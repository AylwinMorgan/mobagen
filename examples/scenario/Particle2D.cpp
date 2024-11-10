#include "Particle2D.h"

Particle2D::Particle2D(int deviation) {
	x = std::rand() % (2*deviation + 1);
    y = std::rand() % (2*deviation + 1);

	maxSize = deviation*2;
	minSize = 0;
	frozen = false;
}

Particle2D::Particle2D() {

}

Particle2D* Particle2D::Particle2DFixed(int pointX, int pointY) { 
	Particle2D* p = new Particle2D();
	p->x = pointX;
	p->y = pointY;
	p->frozen = true;
	return p;
}

void Particle2D::update() { 
	if (!frozen) {
		int randomX = std::rand() % 2;
        int randomY = std::rand() % 2;

		if (x > (maxSize + minSize) / 2) {
        	randomX *= -1;
		}
		if (y > (maxSize + minSize) / 2) {
        	randomY *= -1;
		}

		x += randomX;
        y += randomY;

		if (x < minSize) {
			x = maxSize;
		}
		if (y < minSize) {
			y = maxSize;
        }
        if (x >= maxSize) {
            x = minSize;
		}
        if (y >= maxSize) {
        	y = minSize;
		}
		checkShouldFreeze();
	}
}

// if a frozen particle is next to the particle, the particle will freeze
void Particle2D::checkShouldFreeze() { 
	for (Particle2D* p : particles) {
		if (p->frozen) {
            int totalDistance = abs(x - p->x) + abs(y - p->y);
            if (totalDistance == 1 || (x == (maxSize + minSize) / 2 && y == (maxSize+minSize) / 2)) {
				frozen = true;
                if (abs(x - p->x) == 1) {
                    neighborX = true;
					p->neighborX = true;
			    } else {
                	neighborY = true;
					p->neighborY = true;
				}
                if (!neighborX && !neighborY) {
                    int j = 0;            
		        }
			}
		}
	}
}

// scales the vector of particles up to a higher resolution
/*
particles with a neighbor on the x axis will become two adjacent particles on the lower x axis
eg:  o o ->  - - - -
             o o o o
y axis neighbors become two particles on right y axis
eg:  o  ->   - o
     o       - o
	         - o
			 - o

eg:   o ->  - - - o
    o o     - - - o
	        - - - o
			o o o o

eg: o o ->  - - - o
    o o     o o o o
	        - - - o
			o o o o
*/
void Particle2D::scaleVectorUp() { 
    std::vector<Particle2D*> newVector = {};
    for (Particle2D* p : particles){
        if (p->frozen) {
            Particle2D* newP = Particle2DFixed(p->x * 2 + 1, p->y * 2 + 1);
            if (p->neighborX) {
                Particle2D* pX = Particle2DFixed(p->x * 2, p->y * 2 + 1);
				pX->neighborX = true;
				newP->neighborX = true;
                newVector.push_back(pX);
	        }
		    if (p->neighborY) {
                  Particle2D* pY = Particle2DFixed(p->x * 2 + 1, p->y * 2);
                  pY->neighborY = true;
				  newP->neighborY = true;
                  newVector.push_back(pY);
            }
            newVector.push_back(newP);
		}
	}
    for (Particle2D* p : particles) {
    	delete p;
	}
    particles.clear();
    for (Particle2D* p : newVector){
      particles.push_back(p);
	}
}