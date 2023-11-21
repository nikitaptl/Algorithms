#include <iostream>
#include <string>
#include <sstream>

void heapify(int *A, size_t i, size_t size) {
    size_t l = 2 * i + 1, r = 2 * i + 2, largest;
    if (l < size && A[l] > A[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < size && A[r] > A[largest]) {
        largest = r;
    }
    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, largest, size);
    }
}

void buildHeap(int *A, size_t size) {
    for (int i = size / 2; i >= 0; i--) {
        heapify(A, i, size);
    }
}

void heapSort(int *A, size_t size) {
    buildHeap(A, size);
    for (size_t i = size - 1; i > 0; i--) {
        std::swap(A[i], A[0]);
        size -= 1;
        heapify(A, 0, size);
    }
}

void PrintArray(int *A, size_t size) {
    for (int i = 0; i < size; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string str_n;
    std::getline(std::cin, str_n);

    int n = std::stoi(str_n);
    if (n == 0) {
        return 0;
    }
    int *arr = new int[n];

    std::string str;
    std::getline(std::cin, str);
    std::istringstream iss(str);
    for (size_t i = 0; i < n; i++) {
        iss >> arr[i];
    }

    heapSort(arr, n);
    PrintArray(arr, n);
    return 0;
}
