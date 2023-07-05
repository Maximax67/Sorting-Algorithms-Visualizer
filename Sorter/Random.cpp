#include "Random.h"

double Random::getRandomDouble(double min, double max) {
	if (min <= max) {
		std::uniform_real_distribution<double> dist(min, max);
		std::mt19937 rng;
		rng.seed(std::random_device{}());
		return dist(rng);
	} else {
		throw std::invalid_argument("Can't generate random number, min range > max range");
	}
}

int Random::getRandomInt(int min, int max) {
	if (min <= max) {
		std::uniform_int_distribution<int> dist(min, max);
		std::mt19937 rng;
		rng.seed(std::random_device{}());
		return dist(rng);
	}
	else {
		throw std::invalid_argument("Can't generate random number, min range > max range");
	}
}
