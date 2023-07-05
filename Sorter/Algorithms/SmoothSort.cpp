#include "SmoothSort.h"

unsigned int SmoothSort::leonardo(const int k) const {
    if (k < 2) {
        return 1;
    }

    return leonardo(k - 1) + leonardo(k - 2) + 1;
}

void SmoothSort::heapify(std::vector<double>& array, const int p, const int r) {
    if (!checkSorting()) return;
    
    st.addRecursiveDepth();
    int i = p;
    int j = 0;
    int k = 0;

    while (k < r - p + 1) {
        if ((k & 0xAAAAAAAA) != 0) {
            j = j + i;
            i = i >> 1;
        }
        else {
            i = i + j;
            j = j >> 1;
        }

        k = k + 1;
    }

    while (i > 0) {
        j = j >> 1;
        k = i + j;
        while (k < r) {
            if (!checkSorting()) return;

            pointers[0] = k;
            pointers[1] = k - i;
            makeDelay();
            st.addComparisons();
            if (array[k] > array[k - i]) {
                break;
            }

            if (!checkSorting()) return;
            makeDelay();
            std::swap(array[k], array[k - 1]);
            st.addSwaps();
            k = k + i;
        }

        i = j;
    }
    st.substractRecursiveDepth();
}

void SmoothSort::sorting(std::vector<double>& array)
{
    unsigned int n = (unsigned int)array.size();

    unsigned int r = n - 1;
    unsigned int q = r;
    unsigned int p = 0;

    while (r > 0) {
        if (!checkSorting()) return;

        if ((p & 0x03) == 0) {
            heapify(array, p, q);
        }

        if (leonardo(p) == r) {
            p++;
        }
        else {
            p--;
            q = q - leonardo(p);
            heapify(array, p, q);
            q = p - 1;
            p++;
        }

        pointers[0] = 0;
        pointers[1] = r;
        std::swap(array[0], array[r]);
        st.addSwaps();
        makeDelay();
        r--;
    }

    for (unsigned int i = 0; i < n - 1; i++) {

        unsigned int j = i + 1;
        while (j > 0) {
            if (!checkSorting()) return;

            st.addComparisons();
            if (array[j] < array[j - 1]) {
                pointers[0] = j;
                pointers[1] = j - 1;
                std::swap(array[j], array[j - 1]);
                st.addSwaps();
                makeDelay();
                j = j - 1;
            }
            else {
                break;
            }
        }
    }
}

void SmoothSort::sort() {
    pointers.resize(2);
    st.addRecursiveDepth();
    sorting(array);
    st.substractRecursiveDepth();
    sortingFinished();
}

SmoothSort::~SmoothSort() {
    if (thread.joinable()) {
        thread.join();
    }
}
