#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
const int BNS = 256; // the Base of the Number System

void PrintVec(std::vector<int> A) {
    for(int i = 0; i < A.size(); i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

int RemainderDivision256(int num, int n) {
    for(int i = 0; i < n; i++) {
        num /= BNS;
    }
    return num % BNS;
}

void SortByCategory(std::vector<int> &A, int discharge) {
    std::vector<std::queue<int>> reminders(BNS);
    for(int i = 0; i < A.size(); i++) {
        auto num = RemainderDivision256(A[i], discharge);
        reminders[num].push(A[i]);
    }
    int i = 0;
    for(int j = 0; j < reminders.size(); j++) {
        if(reminders[j].empty()) {
            continue;
        }
        while(!reminders[j].empty()) {
            A[i] = reminders[j].front();
            i++;
            reminders[j].pop();
        }
    }
}

void radixSort(std::vector<int> &A) {
    std::vector<int> positive_numbers;
    std::vector<int> negative_numbers;

    for(int i = 0; i < A.size(); i++) {
        if(A[i] < 0) {
            ///
            negative_numbers.push_back(-A[i]);
        }
        else {
            positive_numbers.push_back(A[i]);
        }
    }
    for(int i = 0; i < 6; i++) {
        SortByCategory(negative_numbers, i);
    }
    for(int i = 0; i < 6; i++) {
        SortByCategory(positive_numbers, i);
    }
    int i = 0;
    for(int j = negative_numbers.size() - 1; j >= 0; j--) {
        A[i++] = -negative_numbers[j];
    }
    for(int j = 0; j < positive_numbers.size(); j++) {
        A[i++] = positive_numbers[j];
    }
}

int main() {
    std::string str_n;
    std::getline(std::cin, str_n);

    int n = std::stoi(str_n);
    if (n == 0) {
        return 0;
    }
    std::vector<int> vec(n);

    std::string str;
    std::getline(std::cin, str);
    std::istringstream iss(str);
    int num;

    for (size_t i = 0; i < n; i++) {
        iss >> num;
        vec[i] = num;
    } // Amogus :3

    radixSort(vec);
    PrintVec(vec);
    return 0;
}
