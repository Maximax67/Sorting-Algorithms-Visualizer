#pragma once

#include "Algorithm.h"

class HeapSort : public Algorithm {
private:
	void sorting(std::vector<double>&);
	void heapify(std::vector<double>&, const unsigned int, const unsigned int);
protected:
	void sort();
	~HeapSort();
};
