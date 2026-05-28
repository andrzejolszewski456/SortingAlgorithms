#pragma once
#include "MovieRating.h"

class MergeSort {
public:
    static MovieRating* sort(MovieRating* d, MovieRating* p, int size, int ip, int ik);
private:
    static MovieRating* merge(MovieRating* d, MovieRating* p, int size, int ip, int is, int ik);
};