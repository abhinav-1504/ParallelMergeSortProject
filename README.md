# Parallel Sort — MergeSort vs ParallelMergeSort (C++)

A performance comparison between classic **recursive Merge Sort** and a **multi-threaded Parallel Merge Sort** implemented in C++. Both algorithms sort a vector of **10 million random integers**, and execution time is benchmarked for each.

---

## Project Structure

```
parallel_sort/
├── .vscode/
│   └── settings.json
├── src/
│   └── app/
│       ├── sorting/
│       │   ├── mergeSort.cpp
│       │   ├── mergeSort.hpp
│       │   ├── parallelMergeSort.cpp
│       │   └── parallelMergeSort.hpp
│       └── main.cpp
```

---

## How It Works

### MergeSort (Single-threaded)
- Classic divide-and-conquer recursive merge sort
- Splits the array in half, recursively sorts each half, then merges the results
- Runs entirely on the **main thread**
- Time complexity: **O(n log n)**

### ParallelMergeSort (Multi-threaded)
- Same divide-and-conquer logic, but each half is sorted in a **separate `std::thread`**
- Uses a **threshold of 5000 elements** — below this, falls back to `std::sort` to avoid thread overhead
- Threads are joined before the merge step to ensure correctness
- Time complexity: **O(n log n)** with reduced wall-clock time on multi-core CPUs

---

##  Build Instructions

### Requirements
- C++11 or later
- `g++` or `clang++`
- POSIX threads (`-lpthread`) support

### Compile

```bash
g++ -std=c++11 -O2 -pthread src/app/main.cpp src/app/sorting/mergeSort.cpp src/app/sorting/parallelMergeSort.cpp -o parallel_sort
```

### Run

```bash
./parallel_sort
```

---

##  Sample Output

```
MergeSort time:         2.84s
ParallelMergeSort time: 1.12s
```

> Results vary based on CPU core count, OS thread scheduling, and available memory.

---

##  Key Implementation Details

| Feature | MergeSort | ParallelMergeSort |
|---|---|---|
| Threading | Single-threaded | Multi-threaded (`std::thread`) |
| Base case | `left >= right` | Threshold: 5000 elements |
| Fallback sort | None | `std::sort` below threshold |
| Merge strategy | Temp vector + in-place copy | Same |
| Empty input handling | `exit(1)` | `exit(1)` |

---

##  Notes

- Both classes take a **pointer** to a `std::vector<int>` and sort it **in place**
- Calling `sort()` on an empty vector causes `exit(1)` — handle input validation before calling
- `ParallelMergeSort` spawns threads recursively, so very large inputs may hit OS thread limits — the threshold helps mitigate this
- The `parallel_sort` binary is the compiled executable (not a source file)

---

##  Tech Stack

- **Language:** C++11
- **Concurrency:** `std::thread` (POSIX threads)
- **Benchmarking:** `std::chrono::high_resolution_clock`
- **IDE:** Visual Studio Code
