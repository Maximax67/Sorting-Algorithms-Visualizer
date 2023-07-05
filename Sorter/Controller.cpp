#include "Controller.h"

#include "Algorithms/QuickSort.h"
#include "Algorithms/Heapsort.h"
#include "Algorithms/SmoothSort.h"

#include "Algorithms/Algorithm.h"

void Controller::init() {
	sorter = new QuickSort();
	Controller::shuffle();
}

Controller::~Controller() {
	delete sorter;
}

void Controller::start() {
	if (!sorter->isPaused()) {
		time = sf::Time::Zero;
	}
	sorter->start();
	clock.restart();
}

void Controller::pause() {
	time += clock.restart();
	sorter->pause();
}

void Controller::step() {
	clock.restart();
	sorter->step();
	time += clock.restart();
}

void Controller::stop() {
	time += clock.restart();
	sorter->stop();
}

void Controller::shuffle() {
	time = sf::Time::Zero;
	sorter->shuffle();
}

bool Controller::isPaused() {
	return sorter->isPaused();
}

bool Controller::isSorting() {
	return sorter->isSorting();
}

bool Controller::isShuffling() {
	return sorter->isShuffling();
}

int Controller::curAlgorithm() {
	return selectedAlgorithm;
}

char* Controller::getAlgorithms() {
	return (char*)algorithms;
}

int Controller::getAlgorithmsNumber() {
	return algorithmsSize;
}

sf::Time Controller::getTime() {
	return time;
}

void Controller::updateTime() {
	if (sorter->isSorting() && !sorter->isPaused()) {
		time += clock.restart();
	}
	else {
		clock.restart();
	}
}

Statistic Controller::getStatistic() {
	return sorter->getStats();
}

void Controller::setDelay(const float newDelay) {
	if (newDelay >= 0) {
		sorter->setDelay(newDelay);
	}
	else {
		throw std::invalid_argument("Invalid delay");
	}
}

void Controller::setArraySize(const unsigned int size) {
	if (size > 0) {
		sorter->setArraySize(size);
	} else {
		throw std::invalid_argument("Size must be > 0");
	}
}

void Controller::setRange(const double min, const double max) {
	if (min <= max) {
		sorter->setRange(min, max);
	} else {
		throw std::invalid_argument("Min value must be less than max");
	}
}

void Controller::changeAlgorithm(const int new_algorithm) {
	if (new_algorithm >= 0 && new_algorithm < algorithmsSize) {
		if (selectedAlgorithm != new_algorithm) {
			selectedAlgorithm = new_algorithm;
			delete sorter;
			switch (selectedAlgorithm)
			{
			case 0:
				sorter = new QuickSort;
				break;
			case 1:
				sorter = new HeapSort;
				break;
			case 2:
				sorter = new SmoothSort;
				break;
			default:
				break;
			};
		}
	} else {
		throw std::invalid_argument("Invalid algorithm number");
	}
}

unsigned int Controller::getSize() {
	return sorter->getSize();
}

double Controller::getMinRange() {
	return sorter->getMinRange();
}

double Controller::getMaxRange() {
	return sorter->getMaxRange();
}

float Controller::getDelay() {
	return sorter->getDelay();
}

const std::vector<double>* Controller::getNumbers() {
	return sorter->getNumbers();
}

void Controller::setNumbers(const std::vector<double>& nums) {
	if (nums.size() > 0 && nums.size() < Constants::ARRAY_RANGE_MAX_LIMIT) {
		double min_value = nums[0];
		double max_value = nums[0];

		for (unsigned int i = 1; i < nums.size(); i++) {
			if (nums[i] < Constants::ARRAY_RANGE_MIN_LIMIT || nums[i] > Constants::ARRAY_RANGE_MAX_LIMIT) {
				throw std::invalid_argument("Error. Numbers in array are too big");
			}

			if (nums[i] < min_value) {
				min_value = nums[i];
			}
			if (nums[i] > max_value) {
				max_value = nums[i];
			}
		}

		sorter->setNumbers(nums, min_value, max_value);
	}
	else {
		throw std::invalid_argument("Error. Invalid array size");
	}
}

const std::vector<unsigned int>& Controller::getPointers() {
	return sorter->getPointers();
}

bool Controller::showPointers() {
	return sorter->showPointers();
}
