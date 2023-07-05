#include "Statistic.h"

void Statistic::reset() {
	comparisons = 0;
	swaps = 0;
	recursiveDepth = 0;
	recursiveDepthMax = 0;
}

void Statistic::addComparisons() {
	comparisons += 1;
}

void Statistic::addSwaps() {
	swaps += 1;
}

void Statistic::addRecursiveDepth() {
	recursiveDepth += 1;
	if (recursiveDepth > recursiveDepthMax) {
		recursiveDepthMax = recursiveDepth;
	}
}

void Statistic::substractRecursiveDepth() {
	recursiveDepth -= 1;
}

unsigned long Statistic::getComparisons() const {
	return comparisons;
}

unsigned long Statistic::getSwaps() const {
	return swaps;
}

unsigned long Statistic::getRecursiveDepth() const {
	return recursiveDepth;
}

unsigned long Statistic::getMaxRecursiveDepth() const {
	return recursiveDepthMax;
}
