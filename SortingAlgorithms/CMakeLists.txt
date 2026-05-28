
add_library(SortingAlgorithmsLibrary
    src/QuickSort.cpp
    src/MergeSort.cpp
    src/BucketSort.cpp
    src/RedBlackTree.cpp
)
target_include_directories(SortingAlgorithmsLibrary PUBLIC include)


add_executable(SortingAlgorithms src/main.cpp)
target_link_libraries(SortingAlgorithms PRIVATE SortingAlgorithmsLibrary)

add_executable(UnitTests tests/TestMain.cpp)
target_link_libraries(UnitTests PRIVATE SortingAlgorithmsLibrary gtest_main)

include(CTest)
enable_testing()
add_test(NAME RunAllProjectTests COMMAND UnitTests)