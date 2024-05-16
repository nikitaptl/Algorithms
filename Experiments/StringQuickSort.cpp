#include "algorithms.h"

int equalL(std::string arr[], int start_index, int end_index, int L) {
    int frontIndex = start_index;
    for (int i = start_index; i < end_index; ++i) {
        if (arr[i].size() == L) {
            if (i != frontIndex) {
                std::swap(arr[i], arr[frontIndex]);
            }
            ++frontIndex;
        }
    }
    return frontIndex;
}

void stringQuicksort(std::string arr[], int start_index, int end_index, long long &comparisons, int L) {
    if (start_index < end_index) {
        start_index = equalL(arr, start_index, end_index, L);

        std::string pivot = arr[start_index + rand() % (end_index - start_index)];
        int frontIndex = start_index;
        for (int i = start_index; i < end_index; ++i) {
            if (arr[i][L] < pivot[L]) {
                comparisons++;
                if (i != frontIndex) {
                    std::swap(arr[i], arr[frontIndex]);
                }
                ++frontIndex;
            }
        }
        stringQuicksort(arr, start_index, frontIndex - 1, comparisons, L);

        start_index = frontIndex;
        for (int i = start_index; i < end_index; ++i) {
            if (arr[i][L] == pivot[L]) {
                comparisons++;
                if (i != frontIndex) {
                    std::swap(arr[i], arr[frontIndex]);
                }
                ++frontIndex;
            }
        }
        stringQuicksort(arr, start_index, frontIndex - 1, comparisons, L + 1);

        start_index = frontIndex;
        stringQuicksort(arr, start_index, end_index, comparisons, L);
    }
}