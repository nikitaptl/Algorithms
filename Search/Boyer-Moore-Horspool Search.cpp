#include <iostream>
#include <string>
#include <vector>

#define MAX 256

std::vector<int> process(std::string str) {
    int len = str.length();
    std::vector<int> arr(MAX, 0);
    for (int i = 0; i < MAX; ++i) {
        arr[i] = -1;
    }
    for (int i = 0; i < len; ++i) {
        arr[(int) str[i]] = i;
    }
    return arr;
}

std::vector<int> match(std::string text, std::string str) {
    int n = text.length();
    int m = str.length();
    auto arr = process(str);
    std::vector<int> res;

    int offset = 0;
    while (offset <= n - m) {
        int j = m - 1;
        while (j >= 0 && str[j] == text[offset + j]) {
            j -= 1;
        }
        if (j < 0) {
            res.push_back(offset);
            offset += (offset + m < n) ? m - arr[text[offset + m]] : 1;
        } else {
            offset += std::max(1, j - arr[text[offset + j]]);
        }
    }
    return res;
}

int main() {
    std::string text;
    std::string pattern;
    std::cin >> pattern >> text;

    auto result = match(text, pattern);
    std::cout << result.size() << '\n';
    for (const auto &el: result) {
        std::cout << el << '\n';
    }
}