#include <iostream>
#include <vector>
#include <mutex>
#include <chrono>
#include "sorting/mergeSort.hpp"
#include "sorting/parallelMergeSort.hpp"

int main() {
    const int SIZE = 10000000;
    std::vector<int> nums(SIZE), nums1(SIZE);
    for (int i = 0; i < SIZE; ++i)
        nums[i] = nums1[i] = rand() % 10000000;

    MergeSort* mergesort = new MergeSort(&nums);
    auto start = std::chrono::high_resolution_clock::now();
    mergesort->sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "MergeSort time: " << std::chrono::duration<double>(end - start).count() << "s\n";
    delete mergesort;

    ParallelMergeSort* mergesort1 = new ParallelMergeSort(&nums1);
    start = std::chrono::high_resolution_clock::now();
    mergesort1->sort();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "ParallelMergeSort time: " << std::chrono::duration<double>(end - start).count() << "s\n";
    delete mergesort1;

    return 0;
}
