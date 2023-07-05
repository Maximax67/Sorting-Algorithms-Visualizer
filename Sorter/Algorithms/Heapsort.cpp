#include "Heapsort.h"

void HeapSort::heapify(std::vector<double>& array, const unsigned int n, const unsigned int i) {
    st.addRecursiveDepth();

    unsigned int largest = i;
    unsigned int left = 2 * i + 1;
    unsigned int right = 2 * i + 2;

    pointers[0] = left;
    pointers[1] = largest;
    if (left < n){
        if (!checkSorting()) return;
        makeDelay();
        st.addComparisons();
        if (array[left] > array[largest]) {
            largest = left;
        }
    }

    pointers[0] = right;
    pointers[1] = largest;
    if (right < n) {
        if (!checkSorting()) return;
        makeDelay();
        st.addComparisons();
        if (array[right] > array[largest]) {
            largest = right;
        }
    }

    pointers[1] = largest;
    if (largest != i) {
        pointers[0] = i;
        std::swap(array[i], array[largest]);
        st.addSwaps();
        if (!checkSorting()) return;
        makeDelay();

        heapify(array, n, largest);
    }

    st.substractRecursiveDepth();
}

void HeapSort::sorting(std::vector<double>& array) {
    unsigned int n = (unsigned int)array.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        pointers[0] = 0;
        pointers[1] = i;
        std::swap(array[0], array[i]);
        st.addSwaps();
        if (!checkSorting()) return;
        makeDelay();

        heapify(array, i, 0);
    }
}

void HeapSort::sort() {
    pointers.resize(2);
    st.addRecursiveDepth();
    sorting(array);
    st.substractRecursiveDepth();
    sortingFinished();
}

HeapSort::~HeapSort() {
    if (thread.joinable()) {
        thread.join();
    }
}

