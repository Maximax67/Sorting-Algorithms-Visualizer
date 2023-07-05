#include "Algorithm.h"

void Algorithm::reset() {
	st.reset();
	clock.restart();
}

sf::Time Algorithm::calculateDelay(const float d) const {
	return sf::milliseconds((sf::Int32)d);
}

void Algorithm::makeDelay() const {
	if (!makestep) {
		sf::sleep(calculateDelay(delay));
	}
}

void Algorithm::start() {
	if (!shuffling) {
		if (thread.joinable()) {
			thread.join();
		}

		reset();
		pointers.clear();
		pointersVisible = true;
		sorting = true;
		thread = std::thread(&Algorithm::sort, this);
	}
}

void Algorithm::stop() {
	sorting = false;
	paused = false;

	if (thread.joinable()) {
		thread.join();
	}
}

void Algorithm::pause() {
	paused = !paused;
}

void Algorithm::step() {
	makestep = true;
}

bool Algorithm::checkSorting() {
	bool to_continue = true;
	do {
		if (!sorting) {
			return false;
		}

		if (makestep) {
			makestep = false;
			to_continue = true;
		}
		else if (paused) {
			to_continue = false;
		}
		else {
			to_continue = true;
		}
	} while (!to_continue);
	return true;
}

void Algorithm::sortingFinished() {
	pointersVisible = false;
	sorting = false;
}

void Algorithm::shuffle() {
	if (!shuffling && !sorting) {
		shuffling = true;
		reset();
		array.resize(arraySize);
		for (unsigned int i = 0; i < arraySize; i++) {
			array[i] = Random::getRandomDouble(rangeMin, rangeMax);
		}
		shuffling = false;
	}
}

Statistic Algorithm::getStats() const {
	return st;
}

void Algorithm::setArraySize(const unsigned int size) {
	arraySize = size;
}

void Algorithm::setRange(const double min, const double max) {
	rangeMin = min;
	rangeMax = max;
}

void Algorithm::setDelay(const float newDelay) {
	delay = newDelay;
}

unsigned int Algorithm::getSize() const {
	return arraySize;
}

double Algorithm::getMinRange() const {
	return rangeMin;
}

double Algorithm::getMaxRange() const {
	return rangeMax;
}

float Algorithm::getDelay() const {
	return delay;
}

const std::vector<double>* Algorithm::getNumbers() const {
	return &array;
}

void Algorithm::setNumbers(const std::vector<double>& nums, const double min_val, const double max_val) {
	setRange(min_val, max_val);
	setArraySize((unsigned int)nums.size());
	array = nums;
}

const std::vector<unsigned int>& Algorithm::getPointers() const {
	return pointers;
}

bool Algorithm::isPaused() const {
	return paused;
}

bool Algorithm::isSorting() const {
	return sorting;
}

bool Algorithm::isShuffling() const {
	return shuffling;
}

bool Algorithm::showPointers() const {
	return pointersVisible;
}
