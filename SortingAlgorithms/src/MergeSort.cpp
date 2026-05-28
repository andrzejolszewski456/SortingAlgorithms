#include "MergeSort.h"

MovieRating* MergeSort::sort(MovieRating* d, MovieRating* p, int size, int ip, int ik) {
    int is = (ip + ik + 1) / 2;
    if ((is - ip) > 1) { sort(d, p, size, ip, is - 1); }
    if ((ik - is) > 0) { sort(d, p, size, is, ik); }
    merge(d, p, size, ip, is, ik);
    return d;
}

MovieRating* MergeSort::merge(MovieRating* d, MovieRating* p, int size, int ip, int is, int ik) {
    int i1 = ip;
    int i2 = is;

    for (int i = ip; i <= ik; i++) {
        if ((i1 == is) || ((i2 <= ik) && (d[i1].rating > d[i2].rating))) {
            p[i] = d[i2];
            i2++;
        }
        else {
            p[i] = d[i1];
            i1++;
        }
    }
    for (int i = ip; i <= ik; i++) { d[i] = p[i]; }
    return d;
}