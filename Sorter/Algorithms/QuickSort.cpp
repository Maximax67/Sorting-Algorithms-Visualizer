#include "QuickSort.h"

unsigned int QuickSort::partition(std::vector<double>& array, const int p, const int r) {
	unsigned int pivot = Random::getRandomInt(p, r);
	unsigned int pivotIndex = p;
	pointers[0] = pivotIndex;
	pointers[1] = pivot;
	st.addSwaps();
	std::swap(array[pivot], array[r]);
	makeDelay();
	pivot = r;
	pointers[1] = r;
	for (int j = p; j < r; j++) {
		if (!checkSorting()) return -1;
		pointers[2] = j;
		makeDelay();
		st.addComparisons();
		if (array[j] < array[pivot]) {
			st.addSwaps();
			std::swap(array[j], array[pivotIndex]);
			pivotIndex++;
			pointers[0] = pivotIndex;
		}
	}
	makeDelay();
	std::swap(array[pivotIndex], array[pivot]);
	st.addSwaps();
	return pivotIndex;
}

void QuickSort::sorting(std::vector<double>& array, const int p, const int r) {
	if (!checkSorting()) return;
	if (p < r) {
		st.addRecursiveDepth();
		unsigned int pivot = partition(array, p, r);
		sorting(array, p, pivot - 1);
		sorting(array, pivot + 1, r);
		st.substractRecursiveDepth();
	}
}

void QuickSort::sort() {
	pointers.resize(3);
	st.addRecursiveDepth();
	sorting(array, 0, (unsigned int)(array.size() - 1));
	st.substractRecursiveDepth();
	sortingFinished();
}

QuickSort::~QuickSort() {
	if (thread.joinable()) {
		thread.join();
	}
}
