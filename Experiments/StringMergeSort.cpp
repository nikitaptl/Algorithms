#include "algorithms.h"

#define vectorPair std::vector<std::pair<std::string, int>>

std::pair<int, int> lcpCompare(std::pair<std::string, int> &a, std::pair<std::string, int> &b, long long &comparisons) {
    int lcp = std::min(a.second, b.second);
    size_t minLength = std::min(a.first.length(), b.first.length());
    for (size_t i = lcp; i < minLength; ++i) {
        ++comparisons;
        if (a.first[i] < b.first[i]) {
            b.second = lcp;
            return {-1, lcp};
        } else if (a.first[i] > b.first[i]) {
            a.second = lcp;
            return {1, lcp};
        }
        lcp++;
    }
    comparisons++;
    if (a.first.length() < b.first.length()) {
        b.second = lcp;
        return {-1, lcp};
    }
    if (a.first.length() > b.first.length()) {
        a.second = lcp;
        return {1, lcp};
    }
    a.second = lcp;
    b.second = lcp;
    return {0, lcp};
}

vectorPair stringMerge(vectorPair vec1, vectorPair vec2, long long &comparisons) {
    vectorPair result;
    size_t i = 0, j = 0;
    while (i < vec1.size() && j < vec2.size()) {
        comparisons++;
        if (vec1[i].second > vec2[j].second) {
            result.push_back(vec1[i]);
            i++;
        } else if (vec1[i].second < vec2[j].second) {
            result.push_back(vec2[j]);
            j++;
        } else {
            auto [res, lcp] = lcpCompare(vec1[i], vec2[j], comparisons);
            if (res == -1) {
                result.push_back(vec1[i]);
                i++;
            } else {
                result.push_back(vec2[j]);
                j++;
            }
        }
    }
    while (i < vec1.size()) {
        result.push_back(vec1[i++]);
    }
    while (j < vec2.size()) {
        result.push_back(vec2[j++]);
    }
    return result;
}

vectorPair stringMergeSort(std::string arr[], int size, long long &comparisons) {
    if (size == 1) {
        return {{arr[0], 0}};
    }
    int m = size / 2;
    auto P = stringMergeSort(arr, m, comparisons);
    auto Q = stringMergeSort(arr + m, size - m, comparisons);
    return stringMerge(P, Q, comparisons);
}