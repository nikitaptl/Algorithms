#include <iostream>
#include <string>
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

int minLength(std::vector<int> f_prefix) {
    int result = f_prefix.size();
    int i = f_prefix.size() - 1;
    for (int num = f_prefix[i];; num--, i--) {
        if (f_prefix[i] != num) {
            if (f_prefix[i + 1] <= f_prefix[i]) {
                result = i + 1;
            }
            break;
        }
        if (num == 0) {
            result = i + 1;
            break;
        }
    }
    return result;
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    auto f_prefix = prefix(str);
    int result = minLength(f_prefix);

    std::cout << result;
    return 0;
}