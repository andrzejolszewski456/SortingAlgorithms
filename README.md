# Sorting Algorithms & Data Structures Benchmark

A comprehensive C++ performance analysis tool that processes over 1 million movie records from the IMDb database. The project implements custom sorting algorithms and a self-balancing Red-Black Tree, verified with unit tests via GoogleTest.

## Building and Running

### 1. Prerequisites (Dataset Setup)
Since this benchmark uses a specific, pre-filtered subset of the IMDb database provided by the university network, the required dataset is hosted externally to keep the repository lightweight.

1. Download the prepared dataset pack (`.zip`) from this public link: **[Download IMDb Dataset Subsample](https://drive.google.com/drive/folders/1FlAuI6H84jXiQpgMCn8Kb07pG8J4k3vE?usp=sharing)**.
2. Extract the contents (`basics.tsv` and `ratings.tsv`) directly into the **root directory** of this project.

### 2. Compilation via Command Line (CLI)
From the root directory, execute the standard CMake workflow:
```bash
# 1. Create and enter the build directory
mkdir build
cd build

# 2. Configure the project
cmake -DCMAKE_BUILD_TYPE=Release ..

# 3. Build the executable
cmake --build . --config Release

# 4. Run the compiled benchmark application
cd SortingAlgorithms\Release
SortingAlgorithms.exe

# 5. To run the automated GoogleTest suite right after compilation, execute:
UnitTests.exe
```

## Key Features
* **Custom Implementations:** Pure C++ implementations of QuickSort, MergeSort, BucketSort, and a Red-Black Tree (no standard library shortcuts for algorithms).
* **Statistical Data Analysis:** The system not only benchmarks sorting speed but also actively computes real-time statistical metrics—such as precise mathematical averages and medians—directly from the sorted memory structures across multiple data thresholds.
* **Modern Tooling:** Multi-platform build management using CMake Presets (C++17) and automated GoogleTest integration via `FetchContent`.
* **Robust File Handling:** Automated dataset path discovery via `<filesystem>` supporting both IDE (Ninja) and CLI execution.

---

## Project Structure

```text
SortingAlgorithms/
├── CMakeLists.txt              # Root CMake configuration (fetches GoogleTest)
├── CMakePresets.json           # Cross-platform build presets (Release mode)
├── basics.tsv                  # IMDb title data 
├── ratings.tsv                 # IMDb ratings data
└── SortingAlgorithms/
    ├── CMakeLists.txt          # Target definitions and linking
    ├── include/                # Header files (.h)
    ├── src/                    # Source files (.cpp)
    └── tests/                  # Unit tests (TestMain.cpp) 
```