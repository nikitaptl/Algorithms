#include "algorithms.h"
#include <chrono>

#define RESET_TEXT "\033[0m"
#define BLUE_TEXT "\033[34m"
#define CYAN_TEXT "\033[36m"

class StringGenerator {
public:
    StringGenerator() {
        srand(time(nullptr));
    }

    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";

    int generateRandomNumber(int min, int max) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(mt);
    }

    std::string generateRandomString(int length = -1) {
        if(length == -1) {
            length = generateRandomNumber(10, 200);
        }
        std::string result;
        result.reserve(length);
        for (int i = 0; i < length; i++) {
            result.push_back(alphabet[rand() % alphabet.size()]);
        }
        return result;
    }

    std::vector<std::string *> GenerateTests(int start, int end, int step, int par, int length = -1) {
        std::vector<std::string *> res;
        std::string *max_arr = new std::string[end];
        for (int i = 0; i < end; i++) {
            max_arr[i] = generateRandomString(length);
        }
        if (par == 1) {
            std::sort(max_arr, max_arr + end);
            std::reverse(max_arr, max_arr + end);
        } else if (par == 2) {
            std::sort(max_arr, max_arr + end);
            int n = generateRandomNumber(end / 25, end / 20); // Количество переставленных пар
            for (int i = 0; i < n; i++) {
                int pos1 = generateRandomNumber(0, end - 1);
                int pos2 = generateRandomNumber(0, end - 1);
                std::swap(max_arr[pos1], max_arr[pos2]);
            }
        }

        for (int i = start; i <= end; i += step) {
            std::string *mass = new std::string[i];
            std::copy(max_arr, max_arr + i, mass);
            res.push_back(mass);
        }
        return res;
    }
};


int main() {
    system("chcp 65001"); // Для красивого цветного вывода :)
    int start_bound = 100;
    int end_bound = 3000;
    int step = 100;

    StringGenerator generator;
    auto test1 = generator.GenerateTests(start_bound, end_bound, step, 0);
    auto test2 = generator.GenerateTests(start_bound, end_bound, step, 1);
    auto test3 = generator.GenerateTests(start_bound, end_bound, step, 2);
    auto tests = {test1, test2, test3};
    int i = 1;

    std::cout << CYAN_TEXT << "QUICK SORT" << RESET_TEXT << std::endl;
    for (auto &test: tests) {
        std::cout << BLUE_TEXT << "Тест №" << i++ << RESET_TEXT << std::endl;
        for (int j = 0; j <= (end_bound - start_bound) / step; j++) {
            long long num = 0;
            auto start = std::chrono::high_resolution_clock::now();
            quickSort(test[j], 0, (start_bound + j * step - 1), num);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            std::cout << "   " << j + 1 << ") n = " << (start_bound + j * step) << ", time = " << millisec
                      << ", count = " << num << ".\n";
        }
    }

    std::cout << CYAN_TEXT << "MERGE SORT" << RESET_TEXT << std::endl;
    i = 1;
    for (auto &test: tests) {
        std::cout << BLUE_TEXT << "Тест №" << i++ << RESET_TEXT << std::endl;
        for (int j = 0; j <= (end_bound - start_bound) / step; j++) {
            long long num = 0;
            auto start = std::chrono::high_resolution_clock::now();
            mergeSort(test[j], start_bound + j * step, num);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            std::cout << "   " << j + 1 << ") n = " << (start_bound + j * step) << ", time = " << millisec
                      << ", count = " << num << ".\n";
        }
    }

    std::cout << CYAN_TEXT << "STRING QUICK SORT" << RESET_TEXT << std::endl;
    i = 1;
    for (auto &test: tests) {
        std::cout << BLUE_TEXT << "Тест №" << i++ << RESET_TEXT << std::endl;
        for (int j = 0; j <= (end_bound - start_bound) / step; j++) {
            long long num = 0;
            auto start = std::chrono::high_resolution_clock::now();
            stringQuicksort(test[j], start_bound, start_bound + j * step - 1, num, 0);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            std::cout << "   " << j + 1 << ") n = " << (start_bound + j * step) << ", time = " << millisec
                      << ", count = " << num << ".\n";
        }
    }

    std::cout << CYAN_TEXT << "STRING MERGE SORT" << RESET_TEXT << std::endl;
    i = 1;
    for (auto &test: tests) {
        std::cout << BLUE_TEXT << "Тест №" << i++ << RESET_TEXT << std::endl;
        for (int j = 0; j <= (end_bound - start_bound) / step; j++) {
            long long num = 0;
            auto start = std::chrono::high_resolution_clock::now();
            stringMergeSort(test[j], start_bound + j * step, num);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            std::cout << "   " << j + 1 << ") n = " << (start_bound + j * step) << ", time = " << millisec
                      << ", count = " << num << ".\n";
        }
    }

    std::cout << CYAN_TEXT << "MSD RADIX SORT" << RESET_TEXT << std::endl;
    test1 = generator.GenerateTests(start_bound, end_bound, step, 0, 105);
    test2 = generator.GenerateTests(start_bound, end_bound, step, 1, 105);
    test3 = generator.GenerateTests(start_bound, end_bound, step, 2, 105);
    i = 1;
    for (auto &test: tests) {
        std::cout << BLUE_TEXT << "Тест №" << i++ << RESET_TEXT << std::endl;
        for (int j = 0; j <= (end_bound - start_bound) / step; j++) {
            long long num = 0;
            auto start = std::chrono::high_resolution_clock::now();
            msdRadixSort(test[j], start_bound + j * step - 1, num);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            std::cout << "   " << j + 1 << ") n = " << (start_bound + j * step) << ", time = " << millisec
                      << ", count = " << num << ".\n";
        }
    }
    return 0;
}