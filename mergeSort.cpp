#include <iterator>
#include <memory>
#include <algorithm>

void merge_sort(int array[], size_t size) {
    if (size > 1) {
        size_t left_side = size / 2;
        size_t right_side = size - left_side;
        merge_sort(&array[0], left_side);
        merge_sort(&array[left_side], right_side);
        size_t left_index = 0;
        size_t right_index = left_side;
        size_t index = 0;
        std::unique_ptr<int[]> new_array(new int[size]);
        while (left_index < left_side || right_index < size) {
            if (array[left_index] > array[right_index]) {
                new_array[index++] = std::move(array[right_index]);
                right_index++;
            } else {
                new_array[index++] = std::move(array[left_index]);
                left_index++;
            }
            if (left_index == left_side) {
                std::copy(std::make_move_iterator(&array[right_index]),
                          std::make_move_iterator(&array[size]),
                          &new_array[index]);
                break;
            }
            if (right_index == size) {
                std::copy(std::make_move_iterator(&array[left_index]),
                          std::make_move_iterator(&array[left_side]),
                          &new_array[index]);
                break;
            }
        }
        std::copy(std::make_move_iterator(&new_array[0]),
                  std::make_move_iterator(&new_array[size]),
                  array);
    }
}
