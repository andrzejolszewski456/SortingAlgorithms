#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <unordered_map>
#include <filesystem> // Required for automatic data path discovery

#include "MovieRating.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "BucketSort.h"
#include "RedBlackTree.h"
  //..
//..
int main() {
    auto programStart = std::chrono::high_resolution_clock::now();
    std::vector<int> thresholds = { 10000, 100000, 500000, 1000000 };

    // Default relative paths
    std::string basicsPath = "basics.tsv";
    std::string ratingsPath = "ratings.tsv";
    std::filesystem::path programDirectory = "";

    // If the files are not found in the current working directory (e.g., inside out/build/...),
    // the algorithm automatically traverses up the directory tree to find them in the project root.
    if (!std::filesystem::exists(ratingsPath)) {
        std::filesystem::path potentialPath = std::filesystem::current_path();

        while (potentialPath.has_parent_path() && !std::filesystem::exists(potentialPath / "ratings.tsv")) {
            potentialPath = potentialPath.parent_path();
        }

        if (std::filesystem::exists(potentialPath / "ratings.tsv")) {
            basicsPath = (potentialPath / "basics.tsv").string();
            ratingsPath = (potentialPath / "ratings.tsv").string();
            programDirectory = potentialPath;
        }
    }

    std::unordered_map<std::string, std::string> titleDictionary;
    std::ifstream fileBasics(basicsPath);

    std::cout << "Stage 1: Building the full title dictionary...\n";
    auto startBasics = std::chrono::high_resolution_clock::now();

    if (fileBasics.is_open()) {
        std::string line;
        std::getline(fileBasics, line);
        while (std::getline(fileBasics, line)) {
            std::stringstream ss(line);
            std::string tconst, type, pTitle;
            std::getline(ss, tconst, '\t');
            std::getline(ss, type, '\t');
            std::getline(ss, pTitle, '\t');
            titleDictionary[tconst] = pTitle;
        }
        fileBasics.close();
    }
    else {
        std::cerr << "Warning: Could not open " << basicsPath << "\n";
    }

    auto endBasics = std::chrono::high_resolution_clock::now();
    std::cout << "Dictionary loaded successfully. Time: " << std::chrono::duration<double>(endBasics - startBasics).count() << " s\n";
    std::cout << "Total titles stored in the dictionary: " << titleDictionary.size() << "\n\n";

    std::vector<MovieRating> allMovies;
    allMovies.reserve(1300000);

    std::ifstream fileRatings(ratingsPath);
    if (!fileRatings.is_open()) {
        std::cerr << "Error: Missing ratings.tsv file!\n";
        std::cerr << "Attempted path: " << std::filesystem::absolute(ratingsPath) << "\n";
        return 1;
    }

    std::cout << "Stage 2: Loading dataset records from " << ratingsPath << "...\n";
    std::string line;
    std::getline(fileRatings, line); 

    while (std::getline(fileRatings, line)) {
        std::stringstream ss(line);
        std::string tconst, ratingStr;
        std::getline(ss, tconst, '\t');
        std::getline(ss, ratingStr, '\t');

        if (!ratingStr.empty() && ratingStr != "\\N") {
            try {
                allMovies.push_back({ tconst, std::stod(ratingStr) });
            }
            catch (...) {
                continue;
            }
        }
    }
    fileRatings.close();
    std::cout << "Successfully loaded a total of: " << allMovies.size() << " records.\n\n";

    std::cout << std::fixed << std::setprecision(5);

    int maxData = allMovies.size();
    thresholds.push_back(maxData);

    for (int N : thresholds) {
        std::cout << ">>> PERFORMANCE ANALYSIS FOR N = " << N << " <<<\n";

        MovieRating* tab1 = new MovieRating[N];
        MovieRating* tab2 = new MovieRating[N];
        MovieRating* tab3 = new MovieRating[N];
        MovieRating* temp = new MovieRating[N]; // Dedicated buffer for MergeSort

        for (int i = 0; i < N; ++i) {
            tab1[i] = tab2[i] = tab3[i] = allMovies[i];
        }

        // 1. QuickSort
        auto s1 = std::chrono::high_resolution_clock::now();
        QuickSort::sort(tab1, N, 0, N - 1);
        auto e1 = std::chrono::high_resolution_clock::now();
        std::cout << " [QS] Execution Time: " << std::chrono::duration<double>(e1 - s1).count() << " s\n";

        // 2. MergeSort
        auto s2 = std::chrono::high_resolution_clock::now();
        MergeSort::sort(tab2, temp, N, 0, N - 1);
        auto e2 = std::chrono::high_resolution_clock::now();
        std::cout << " [MS] Execution Time: " << std::chrono::duration<double>(e2 - s2).count() << " s\n";

        // 3. BucketSort
        auto s3 = std::chrono::high_resolution_clock::now();
        BucketSort::sort(tab3, N);
        auto e3 = std::chrono::high_resolution_clock::now();
        std::cout << " [BS] Execution Time: " << std::chrono::duration<double>(e3 - s3).count() << " s\n";

        double sum = 0;
        for (int i = 0; i < N; ++i) sum += tab3[i].rating;
        double average = sum / N;
        double median = (N % 2 == 0) ? (tab3[N / 2 - 1].rating + tab3[N / 2].rating) / 2.0 : tab3[N / 2].rating;

        std::cout << " -> Average Rating: " << std::setprecision(2) << average
            << " | Median Rating: " << median << "\n\n";

        delete[] tab1;
        delete[] tab2;
        delete[] tab3;
        delete[] temp;
    }

    std::cout << "Stage 4: Populating a custom Red-Black Tree with all records (" << maxData << ") and saving output...\n";
    RedBlackTree tree;

    auto s4 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < allMovies.size(); ++i) {
        if (titleDictionary.count(allMovies[i].tconst)) {
            std::string title = titleDictionary[allMovies[i].tconst];
            tree.insert({ allMovies[i].rating, title });
        }
    }
    auto e4 = std::chrono::high_resolution_clock::now();
    std::cout << " Balanced Red-Black Tree population completed in " << std::chrono::duration<double>(e4 - s4).count() << " s\n";

    std::ofstream outputFile((programDirectory / "sorted_movies.txt").string());
    if (outputFile.is_open()) {
        for (const auto& nodeData : tree) {
            outputFile << std::fixed << std::setprecision(1) << nodeData.first << "\t" << nodeData.second << "\n";
        }
        outputFile.close();
        std::cout << "Result file 'sorted_movies.txt' has been successfully generated and saved into: "<< programDirectory.string()<< "\n";
    }
    else {
        std::cerr << "Error: Unable to create output file 'sorted_movies.txt'!\n";
    }

    auto programEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Total program execution runtime: " << std::chrono::duration<double>(programEnd - programStart).count() << " s\n";

    return 0;
}