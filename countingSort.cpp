#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void countingSort(int *A, size_t size, int max = 0, int min = 0) {
    if(max == 0 && min == 0) {
        for(int i = 0; i < size; i++) {
            if(A[i] > max) {
                max = A[i];
                continue;
            }
            if(A[i] < min) {
                min = A[i];
            }
        }
    }
    std::vector<int> vec;
    vec.resize(max + 1, 0);

    if (min != 0) {
        std::vector<int> vec_negative;
        vec_negative.resize(-min + 1, 0);
        for (int i = 0; i < size; i++) {
            if (A[i] < 0) {
                vec_negative[-A[i]] += 1;
            } else {
                vec[A[i]] += 1;
            }
        }
        for (int i = vec_negative.size() - 1; i > 0; i--) {
            for (int j = 0; j < vec_negative[i]; j++) {
                std::cout << -i << " ";
            }
        }
    } else {
        for (int i = 0; i < size; i++) {
            vec[A[i]] += 1;
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i]; j++) {
            std::cout << i << " ";
        }
    }
}
