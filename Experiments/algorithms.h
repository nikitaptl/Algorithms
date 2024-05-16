#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <memory>

#ifndef ALGORITHMS_ALGORITHMS_H
#define ALGORITHMS_ALGORITHMS_H

static int compare(const std::string &str1, const std::string &str2, long long &comparisons) {
    size_t minLength = std::min(str1.length(), str2.length());
    for (size_t i = 0; i < minLength; ++i) {
        ++comparisons;
        if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
    }
    comparisons++;
    if (str1.length() < str2.length()) {
        return -1;
    }
    if (str1.length() > str2.length()) {
        return 1;
    }
    return 0;
}

void mergeSort(std::string arr[], int size, long long &comparisons);

void quickSort(std::string arr[], int start_index, int end_index, long long &comparisons);

void stringQuicksort(std::string arr[], int start_index, int end_index, long long &comparisons, int L);

std::vector<std::pair<std::string, int>> stringMergeSort(std::string arr[], int size, long long &comparisons);

void msdRadixSort(std::string *A, int size, long long &comparisons);

#endif //ALGORITHMS_ALGORITHMS_H
