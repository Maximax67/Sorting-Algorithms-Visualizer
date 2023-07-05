#pragma once

#include "Algorithm.h"

class QuickSort : public Algorithm {
private:
	unsigned int partition(std::vector<double>&, const int, const int);
	void sorting(std::vector<double>&, const int, const int);
protected:
	void sort();
	~QuickSort();
};
