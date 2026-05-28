#include <gtest/gtest.h>
#include "QuickSort.h"
#include "MergeSort.h"
#include "BucketSort.h"

TEST(SortingAlgorithmsTests, QuickSortSortsCorrectly) {
    MovieRating arr[] = { {"t1", 5.5}, {"t2", 2.1}, {"t3", 8.8} };
    int size = 3;

    QuickSort::sort(arr, size, 0, size - 1);

    EXPECT_DOUBLE_EQ(arr[0].rating, 2.1);
    EXPECT_DOUBLE_EQ(arr[1].rating, 5.5);
    EXPECT_DOUBLE_EQ(arr[2].rating, 8.8);
}

TEST(SortingAlgorithmsTests, MergeSortSortsCorrectly) {
    MovieRating arr[] = { {"t1", 9.3}, {"t2", 1.2}, {"t3", 4.4} };
    MovieRating temp[3];
    int size = 3;

    MergeSort::sort(arr, temp, size, 0, size - 1);

    EXPECT_DOUBLE_EQ(arr[0].rating, 1.2);
    EXPECT_DOUBLE_EQ(arr[1].rating, 4.4);
    EXPECT_DOUBLE_EQ(arr[2].rating, 9.3);
}

TEST(SortingAlgorithmsTests, BucketSortSortsCorrectly) {
    MovieRating arr[] = { {"t1", 7.0}, {"t2", 0.5}, {"t3", 3.2} };
    int size = 3;

    BucketSort::sort(arr, size);

    EXPECT_DOUBLE_EQ(arr[0].rating, 0.5);
    EXPECT_DOUBLE_EQ(arr[1].rating, 3.2);
    EXPECT_DOUBLE_EQ(arr[2].rating, 7.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}