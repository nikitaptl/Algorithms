#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

std::vector<int> encodingLZW(std::string str) {
    std::unordered_map<std::string, unsigned int> map;
    std::vector<int> result;
    result.reserve(str.size() * 0.3);

    for (int i = 0; i < 128; i++) {
        map[std::string(1, (char) i)] = i;
    }
    int ch = 128;
    for (int i = 0; i < str.size(); i++) {
        std::string prefix = std::string(1, str[i]);
        while (i + 1 < str.size() && map.find(prefix + str[i + 1]) != map.end()) {
            prefix += str[++i];
        }
        result.push_back(map[prefix]);
        if (i + 1 < str.size()) {
            map[prefix + str[i + 1]] = ch++;
        }
    }
    return result;
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    auto result = encodingLZW(str);

    std::cout << "Size of encoded message = " << result.size() << std::endl << "Encoded message: ";
    for (auto el: result) {
        std::cout << el << " ";
    }
    return 0;
}