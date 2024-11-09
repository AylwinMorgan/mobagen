#include "Particle2D.h"

Particle2D::Particle2D(int sideSize) {
	x = std::rand() % sideSize;
	y = std::rand() % sideSize;
	maxSize = sideSize;
	frozen = false;
}

Particle2D::Particle2D(int pointX, int pointY, int sideSize) { 
	x = pointX;
	y = pointY;
	maxSize = sideSize;
	frozen = true;
}

void Particle2D::update() { 
	if (!frozen) {
		int randomX = std::rand() % 3 - 1;
        int randomY = std::rand() % 3 - 1;

		x += randomX;
        y += randomY;

		if (x < 0) {
			x = maxSize - 1;
		}
		if (y < 0) {
			y = maxSize - 1;
        }
        if (x >= maxSize) {
            x = 0;
		}
        if (y >= maxSize) {
        	y = 0;
		}
		checkShouldFreeze();
	}
}

void Particle2D::checkShouldFreeze() { 
	for (Particle2D* p : particles) {
		if (p->frozen) {
            int totalDistance = abs(x - p->x) + abs(y - p->y);
            if (totalDistance == 1) {
				frozen = true;
				return;
			}
		}
	}
}