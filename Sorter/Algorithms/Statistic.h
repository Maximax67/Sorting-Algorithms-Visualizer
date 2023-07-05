#pragma once

class Statistic {
private:
	unsigned long comparisons = 0;
	unsigned long swaps = 0;
	unsigned long recursiveDepth = 0;
	unsigned long recursiveDepthMax = 0;
public:
	void reset();
	void addComparisons();
	void addSwaps();
	void addRecursiveDepth();
	void substractRecursiveDepth();
	unsigned long getComparisons() const;
	unsigned long getSwaps() const;
	unsigned long getRecursiveDepth() const;
	unsigned long getMaxRecursiveDepth() const;
};
