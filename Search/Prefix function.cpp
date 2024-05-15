#include <iostream>
#include <vector>

std::vector<int> prefix(std::string str) {
    std::vector<int> result(str.length(), 0);

    for (int i = 1; i < str.length(); i++) {
        int k = result[i - 1];

        while (k > 0 && str[i] != str[k]) {
            k = result[k - 1];
        }
        if (str[k] == str[i]) {
            k++;
        }
        result[i] = k;
    }
    return result;
}

int main() {
    std::string str;
    std::cin >> str;

    std::vector<int> result = prefix(str);
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    return 0;
}