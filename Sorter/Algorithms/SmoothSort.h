#pragma once

#include "Algorithm.h"

class SmoothSort : public Algorithm {
private:
	unsigned int leonardo(const int) const;
	void heapify(std::vector<double>&, const int, const int);
	void sorting(std::vector<double>&);
protected:
	void sort();
	~SmoothSort();
};
