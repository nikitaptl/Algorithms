#include "algorithms.h"
#include <queue>

const int BNS = 256;

void sortByCategory(std::vector<std::string> &A, int discharge, long long &comparisons) {
    std::vector<std::queue<std::string>> reminders(BNS);
    for (int i = 0; i < A.size(); i++) {
        comparisons++;
        if (A[i].length() <= discharge) continue;
        int num = A[i][discharge];
        reminders[num].push(A[i]);
    }
    int i = 0;
    for (int j = 0; j < reminders.size(); j++) {
        while (!reminders[j].empty()) {
            comparisons++;
            A[i] = reminders[j].front();
            i++;
            reminders[j].pop();
        }
    }
}

int findMax(std::string *A, int size) {
    if (size <= 0) return 0;
    int max = A[0].length();
    for (int i = 1; i < size; i++) {
        if (A[i].length() > max) {
            max = A[i].length();
        }
    }
    return max;
}

void msdRadixSort(std::string *A, int size, long long &comparisons) {
    if (size <= 0) return;
    std::vector<std::string> strs(size);
    int max = findMax(A, size);

    for (int i = 0; i < size; i++) {
        strs[i] = A[i];
    }
    for (int i = 0; i < max; i++) {
        sortByCategory(strs, i, comparisons);
    }
    for (int i = 0; i < strs.size(); i++) {
        A[i] = strs[i];
    }
}
