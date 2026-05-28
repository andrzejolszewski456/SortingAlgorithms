#include "QuickSort.h"
#include <algorithm>
#include <cstdlib> 

MovieRating* QuickSort::sort(MovieRating* d, int size, int left, int right) {
    while (left < right) {
        int randomIndex = left + std::rand() % (right - left + 1);
        int mid = (left + right) / 2;
        std::swap(d[randomIndex], d[mid]);

        MovieRating pivot;
        int i = mid;
        int j = left;

        pivot = d[i];
        d[i] = d[right];

        for (int k = left; k <= right - 1; k++) {
            if (d[k].rating < pivot.rating) {
                std::swap(d[k], d[j]);
                j++;
            }
        }

        d[right] = d[j];
        d[j] = pivot;

        if ((j - 1 - left) < (right - (j + 1))) {
            if (left < (j - 1)) {
                sort(d, size, left, j - 1);
            }
            left = j + 1;
        }
        else {
            if ((j + 1) < right) {
                sort(d, size, j + 1, right);
            }
            right = j - 1;
        }
    }

    return d;
}