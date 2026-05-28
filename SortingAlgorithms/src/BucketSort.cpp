#include "BucketSort.h"
#include <vector>

MovieRating* BucketSort::sort(MovieRating unsortedArray[], int size) {
    if (size <= 0) return unsortedArray;

    int range = 101; // 0.0, 0.1 ... 10.0
    std::vector<MovieRating>* buckets = new std::vector<MovieRating>[range];

    for (int i = 0; i < size; i++) {
        int index = static_cast<int>(unsortedArray[i].rating * 10.0 + 0.1);
        if (index >= 0 && index < range) {
            buckets[index].push_back(unsortedArray[i]);
        }
    }

    int currentIndex = 0;
    for (int i = 0; i < range; i++) {
        for (size_t j = 0; j < buckets[i].size(); j++) {
            unsortedArray[currentIndex++] = buckets[i][j];
        }
    }

    delete[] buckets;
    return unsortedArray;
}