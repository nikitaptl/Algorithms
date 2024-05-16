#include "algorithms.h"

int split(std::string arr[], int start_index, int end_index, long long &comparisons) {
    std::string pivot = arr[end_index];
    int i = start_index - 1;
    for (int j = start_index; j < end_index; j++) {
        if (compare(arr[j], pivot, comparisons) <= 0) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[end_index]);

    return i + 1;
}

void quickSort(std::string arr[], int start_index, int end_index, long long &comparisons) {
        if (start_index < end_index) {
            int mid_index = split(arr, start_index, end_index, comparisons);
            quickSort(arr, start_index, mid_index - 1, comparisons);
            quickSort(arr, mid_index + 1, end_index, comparisons);
        }
}

void mergeSort(std::string arr[], int size, long long &comparisons) {
    if (size > 1) {
        size_t left_side = size / 2;
        size_t right_side = size - left_side;
        mergeSort(&arr[0], left_side, comparisons);
        mergeSort(&arr[left_side], right_side, comparisons);
        size_t left_index = 0;
        size_t right_index = left_side;
        size_t index = 0;
        std::unique_ptr<std::string[]> new_array(new std::string[size]);
        while (left_index < left_side || right_index < size) {
            if (compare(arr[left_index], arr[right_index], comparisons) > 0) {
                new_array[index++] = std::move(arr[right_index]);
                right_index++;
            } else {
                new_array[index++] = std::move(arr[left_index]);
                left_index++;
            }
            if (left_index == left_side) {
                std::copy(std::make_move_iterator(&arr[right_index]),
                          std::make_move_iterator(&arr[size]),
                          &new_array[index]);
                break;
            }
            if (right_index == size) {
                std::copy(std::make_move_iterator(&arr[left_index]),
                          std::make_move_iterator(&arr[left_side]),
                          &new_array[index]);
                break;
            }
        }
        std::copy(std::make_move_iterator(&new_array[0]),
                  std::make_move_iterator(&new_array[size]),
                  arr);
    }
}


