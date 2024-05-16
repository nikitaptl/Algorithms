#include <iostream>
#include <string>
#include <vector>

std::vector<int> refinedPrefix(std::string str) {
    std::vector<int> result(str.length(), 0);
    for (size_t i = 1; i < str.length(); i++) {
        int k = result[i - 1];

        while (k > 0 && str[i] != str[k]) {
            k = result[k - 1];
        }
        if (str[k] == str[i]) {
            k++;
        }
        result[i] = k;
    }
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] == 0) {
            continue;
        }
        if (i + 1 < result.size() && result[i + 1] > result[i]) {
            size_t j = i + 1;
            while (result[j] > result[j - 1] && j < result.size()) {
                result[j - 1] = 0;
                j++;
            }
            i = j - 1;
        }
    }
    return result;
}

std::vector<int> KWPSearch(std::string pattern, std::string text) {
    auto f_prefix = refinedPrefix(pattern);
    std::vector<int> entries;

    size_t M = pattern.length();
    size_t N = text.length();

    for (size_t patIndex = 0, txtIndex = 0; txtIndex < N;) {
        if (text[txtIndex] == pattern[patIndex]) {
            txtIndex++;
            patIndex++;
            if (patIndex == M) {
                entries.push_back(txtIndex - patIndex);
                patIndex = f_prefix[patIndex - 1];
            }
        } else if (txtIndex < N && text[txtIndex] != pattern[patIndex]) {
            if (patIndex > 0) {
                patIndex = f_prefix[patIndex - 1];
            } else {
                txtIndex++;
            }
        }
    }
    return entries;
}

int main() {
    std::string pattern, text;
    std::getline(std::cin, pattern);
    std::getline(std::cin, text);

    auto result = KWPSearch(pattern, text);
    std::cout << result.size() << std::endl;
    for (auto num: result) {
        std::cout << num << std::endl;
    }
    return 0;
}